#pragma once

/********************************************************
 *   _    __                __            __    _ __    *
 *  | |  / /___  ____  ____/ /___  ____  / /   (_) /_   *
 *  | | / / __ \/ __ \/ __  / __ \/ __ \/ /   / / __ \  *
 *  | |/ / /_/ / /_/ / /_/ / /_/ / /_/ / /___/ / /_/ /  *
 *  |___/\____/\____/\__,_/\____/\____/_____/_/_.___/   *
 *                                                      *
 *            Base library for voodoo magick            *
 *                                                      *
 ********************************************************/

#include "sfall/lib.arrays.h"
#include "sfall/lib.math.h"

//
// 0x410003 (1b)    used by rfall
// 0x410004 (4b)    used for lookup table pointer
// 0x4b1554 (148b)  used for temporary code
//

// lookup table : general
#define VOODOO_LIB_LOOKUP_ADDRESS (0x410004)                           // address of lookup table pointer
#define VOODOO_LIB_LOOKUP         read_int(VOODOO_LIB_LOOKUP_ADDRESS)  // address of lookup table
#define VOODOO_LIB_LOOKUP_UNSET   (0x909090)                           // value returned by VOODOO_LIB_LOOKUP before it's initialized
#define VOODOO_LIB_LOOKUP_SIZE    (2048)                               // total size in bytes

// lookup table : id, address, size
#define VOODOO_LIB_LOOKUP_ID_ADDRESS   (VOODOO_LIB_LOOKUP)
#define VOODOO_LIB_LOOKUP_ID_COUNT     (100)                                                         // maximum number of entries
#define VOODOO_LIB_LOOKUP_ID_SIZE_ONE  (12)                                                          // entry size in bytes
#define VOODOO_LIB_LOOKUP_ID_SIZE      (VOODOO_LIB_LOOKUP_ID_COUNT * VOODOO_LIB_LOOKUP_ID_SIZE_ONE)  // total size in bytes

// internal lookup IDs
#define VOODOO_ID_INTERNAL     (1000)
#define VOODOO_ID_call_args    (VOODOO_ID_INTERNAL + 0) // WIP

//
// Native functions
// when possible, use inline procedures
//

procedure VOODOO_nmalloc(variable bytes)
begin
   return call_offset_r1(0x4ef1c5, bytes); // fallout2.nmalloc_
end

inline procedure VOODOO_nfree(variable address)
begin
   call_offset_v1(0x4ef2b4, address); // fallout2.nfree_
end

inline procedure VOODOO_memset(variable address, variable value, variable size)
begin
   call_offset_v3(0x4f0080, address, value, size); // fallout2.memset_
end

inline procedure VOODOO_memzero(variable address, variable size)
begin
   call_offset_v3(0x4f0080, address, 0, size); // fallout2.memset_
end

//
// helpers
//

/*
procedure VOODOO_TempClear(variable slow := false)
begin
   variable a, address := 0x4b1554; // fallout2.refresh_mapper_

   for(a := address; a < 0x4b15e8; a += 4) //
   begin
      if(slow == false and read_int(a) == 0xcccccccc) then
         break;

      write_int(a, 0xcccccccc);
   end

   return address + 1;
end
*/

procedure VOODOO_AssertByte(variable func, variable address, variable expected)
begin
     variable byte := read_byte(address);
     if(byte != expected) then begin
         display_msg("Byte mismatch at "+func+ " (0x"+sprintf("%x",address)+"), expected " + sprintf("%x", expected) + " but got " + sprintf("%x", byte));
         return false;
     end
     return true;
end

// ddraw.sfall::wmAreaMarkVisitedState_hack+0x51 is calculated with VOODOO_CalculateHookFuncOffset(0x4C4670, 0x51);
procedure VOODOO_CalculateHookFuncOffset(variable address, variable offset)
begin
   return read_int(address) + address + offset + 4;
end

procedure VOODOO_CalculateRel32(variable from, variable to)
begin
  return (to - from - 5);
end

procedure VOODOO_WriteRelAddress(variable at, variable address)
begin
  variable addr, byte1, byte2, byte3, byte4;
  addr := VOODOO_CalculateRel32(at, address);
  byte4 := (addr bwand 0xFF000000) / 0x1000000;
  byte3 := (addr bwand 0x00FF0000) / 0x10000;
  byte2 := (addr bwand 0x0000FF00) / 0x100;
  byte1 := (addr bwand 0x000000FF);
  write_byte(at+1, byte1);
  write_byte(at+2, byte2);
  write_byte(at+3, byte3);
  write_byte(at+4, byte4);
end

procedure VOODOO_MakeCall(variable address, variable func)
begin
  write_byte(address, 0xE8);
  call VOODOO_WriteRelAddress(address, func);
end

procedure VOODOO_MakeJump(variable address, variable func)
begin
  write_byte(address, 0xE9);
  call VOODOO_WriteRelAddress(address, func);
end

procedure VOODOO_WriteNop(variable address, variable length:=1, variable goBackTo90s:=false)
begin
  variable i, n := 0x66;
  if(goBackTo90s) then
   n := 0x90;
  // x86 instructions can't be longer than 15 bytes.
  if not goBackTo90s then
    length := cap_number(length, 1, 15);
  for(i := 0; i < length-1; i++) begin
   write_byte(address+i, n);
  end
  write_byte(address+length-1, 0x90);
end

procedure VOODOO_BlockCall(variable address, variable length:=5)
begin
   call VOODOO_WriteNop(address, cap_number(length, 5, 15));
end

procedure VOODOO_BlockJump(variable address, variable length:=5)
begin
   call VOODOO_WriteNop(address, cap_number(length, 5, 15));
end

//
// opcodes
//

procedure VOODOO_GetOpcodeAddress(variable opcode)
begin
    return read_int(read_int(0x46ce34) + opcode * 4);
end

/*
procedure VOODOO_SetOpcodeAddress(variable opcode, variable address)
begin
    write_int(read_int(0x46ce34) + opcode * 4, address);
end
*/

procedure VOODOO_GetWriteLimitOffset(variable opcode, variable limit)
begin
   variable a, address = VOODOO_GetOpcodeAddress(opcode);

   for(a := 0; a == a; a++) // CAH cannot into for(a:=0 ;; a++)
   begin
      variable byte := read_byte(address + a);
      if(byte == 0x3d) then // cmp
      begin
         if(read_int(address + a + 1) == limit) then
            return a + 1;
      end
      else if(read_int(address + a) == 0xcccccccc) then // int3 int3 int3 int3
         break;
   end

   return 0;
end

//
// lookup table
//

procedure VOODOO_GetLookupData(variable id, variable idx)
begin
   variable a, aMax := VOODOO_LIB_LOOKUP_ID_ADDRESS + VOODOO_LIB_LOOKUP_ID_SIZE; // CAH cannot into for(x:=0, y:=1; x < y; x++)
   variable warn; warn := "VOODOO GetLookupData(" + id + ", " + idx + ") ";

   if(typeof(id) != VALTYPE_INT or id <= 0) then
   begin
      debug(warn + "invalid id");
      return;
   end

   if(typeof(idx) != VALTYPE_INT or idx <= 0) then
   begin
      debug(warn + "invalid idx");
      return 0;
   end

   for(a := VOODOO_LIB_LOOKUP_ID_ADDRESS; a < aMax; a += VOODOO_LIB_LOOKUP_ID_SIZE_ONE)
   begin
      variable curr := read_int(a);

      if(curr == 0) then
         break;
      else if(curr == id) then
         return read_int(a + idx * 4);
   end

   debug(warn + "unknown id");
   return 0;
end

procedure VOODOO_SetLookupData(variable id, variable address, variable size := 0)
begin
   variable a, aMax := VOODOO_LIB_LOOKUP_ID_ADDRESS + VOODOO_LIB_LOOKUP_ID_SIZE; // CAH cannot into for(x:=0, y:=1; x < y; x++)
   variable warn; warn := "VOODOO SetLookupData(" + id + ", 0x" + sprintf("%x, ", address) + size + ") ";

   if(typeof(id) != VALTYPE_INT or id <= 0) then
   begin
      debug(warn + "invalid id");
      return;
   end

   for(a := VOODOO_LIB_LOOKUP_ID_ADDRESS; a < aMax; a += VOODOO_LIB_LOOKUP_ID_SIZE_ONE)
   begin
      variable curr := read_int(a);

      if(curr == id or curr == 0) then
      begin
         write_int(a + 0, id);
         write_int(a + 4, address);
         write_int(a + 8, size);
         return;
      end
   end

   debug(warn + "lookup table is full");
end

procedure VOODOO_ClearLookupData
begin
   variable a, aMax := VOODOO_LIB_LOOKUP_ID_ADDRESS + VOODOO_LIB_LOOKUP_ID_SIZE; // CAH cannot into for(x:=0, y:=1; x < y; x++)

   for(a := VOODOO_LIB_LOOKUP_ID_ADDRESS; a < aMax; a += VOODOO_LIB_LOOKUP_ID_SIZE_ONE)
   begin
      variable curr := read_int(a), address;

      if(curr == 0) then
         break;

      address := read_int(a + 4);
      if(address > 0) then
         call VOODOO_nfree(address);

      call VOODOO_memzero(a, VOODOO_LIB_LOOKUP_ID_SIZE_ONE);
   end
end

procedure VOODOO_DumpLookupData
begin
   variable idx := 0, a, aMax := VOODOO_LIB_LOOKUP_ID_ADDRESS + VOODOO_LIB_LOOKUP_ID_SIZE; // CAH cannot into for(x:=0, y:=1; x < y; x++)

   for(a := VOODOO_LIB_LOOKUP_ID_ADDRESS; a < aMax; a += VOODOO_LIB_LOOKUP_ID_SIZE_ONE)
   begin
      variable id := read_int(a), address, size, msg;

      if(id == 0) then
         break;

      address := read_int(a + 4);
      size    := read_int(a + 8);

      if(size == 0) then
         size := "???";

      msg := "VOODOO Lookup[" + idx + "] " + id + " = 0x" + sprintf("%x ", address) + size + "b";

      if(debug_mode) then
         debug(msg);
      else
         debug_msg(msg);

      idx++;
   end
end

// used by sfall-asm --malloc
procedure VOODOO_Alloc(variable id, variable size, variable clear := -1)
begin
   variable address := VOODOO_nmalloc(size);

   call VOODOO_SetLookupData(id, address, size);

   if(clear >= 0) then
      call VOODOO_memset(address, clear, size);

   return address;
end

procedure VOODOO_LookupAddress(variable id)
begin
   return VOODOO_GetLookupData(id, 1);
end

procedure VOODOO_LookupSize(variable id)
begin
   return VOODOO_GetLookupData(id, 2);
end

//
// init/finish
//

procedure VOODOO_Init()
begin
   variable address;

   if(VOODOO_LIB_LOOKUP == VOODOO_LIB_LOOKUP_UNSET) then
   begin
      debug("VOODOO init");

      // init lookup table

      address := VOODOO_nmalloc(VOODOO_LIB_LOOKUP_SIZE);
      call VOODOO_memzero(address, VOODOO_LIB_LOOKUP_SIZE);
      write_int(VOODOO_LIB_LOOKUP_ADDRESS, address);

      // init internals

      debug("VOODOO lookup = 0x" + sprintf("%x", VOODOO_LIB_LOOKUP));
      call VOODOO_DumpLookupData();

      return 1;
   end

   debug("VOODOO lookup (cached) = 0x" + sprintf("%x", VOODOO_LIB_LOOKUP));
   return 0;
end

procedure VOODOO_Finish()
begin
   if(VOODOO_LIB_LOOKUP == VOODOO_LIB_LOOKUP_UNSET) then
      return;

   debug("VOODOO finish");

   call VOODOO_ClearLookupData();
   call VOODOO_DumpLookupData(); // (in)sanity check, remove once lookup stuff is stable

   call VOODOO_nfree(VOODOO_LIB_LOOKUP);
   write_int(VOODOO_LIB_LOOKUP_ADDRESS, VOODOO_LIB_LOOKUP_UNSET);
end

//
// misc
//

// https://github.com/phobos2077/sfall/issues/288
procedure VOODOO_call_offset_r(variable num, variable address, variable arg1 := 0, variable arg2 := 0, variable arg3 := 0, variable arg4 := 0)
begin
   if(num == 0) then
      return call_offset_r0(address);
   else if(num == 1) then
      return call_offset_r1(address, arg1);
   else if(num == 2) then
      return call_offset_r2(address, arg1, arg2);
   else if(num == 3) then
      return call_offset_r3(address, arg1, arg2, arg3);
   else if(num == 4) then
      return call_offset_r4(address, arg1, arg2, arg3, arg4);

   display_msg("VOODOO call_offset_r invalid num<" + num + ">");
end
