#ifndef VOODOO_LIB_H
#define VOODOO_LIB_H

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
// 0x410003 (1b)   used by rfall
// 0x410004 (4b)   used for lookup table, permanent
// 0x41ade0 (34b)  used for unlocking write functions, temporary
//

// lookup table : general
#define VOODOO_LIB_LOOKUP_ADDRESS (0x410004)                           // address of lookup table pointer
#define VOODOO_LIB_LOOKUP         read_int(VOODOO_LIB_LOOKUP_ADDRESS)  // address of lookup table
#define VOODOO_LIB_LOOKUP_UNSET   (0x909090)                           // value returned by VOODOO_LIB_LOOKUP before it's initialized
#define VOODOO_LIB_LOOKUP_SIZE    (2048)                               // total size in byte

// lookup table : id
#define VOODOO_LIB_LOOKUP_ID_ADDRESS  (VOODOO_LIB_LOOKUP)
#define VOODOO_LIB_LOOKUP_ID_COUNT    (100)                             // maximum number of entries
#define VOODOO_LIB_LOOKUP_ID_SIZE     (VOODOO_LIB_LOOKUP_ID_COUNT * 8)  // total size in bytes

// lookup table : call arguments
#define VOODOO_LIB_LOOKUP_ARGS_ADDRESS  (VOODOO_LIB_LOOKUP_ID_ADDRESS + VOODOO_LIB_LOOKUP_ID_SIZE)
#define VOODOO_LIB_LOOKUP_ARGS_COUNT    (16)                                // maximum arguments allowed
#define VOODOO_LIB_LOOKUP_ARGS_SIZE     (VOODOO_LIB_LOOKUP_ARGS_COUNT * 4)  // total size in bytes

// internal lookup IDs
#define VOODOO_ID_INTERNAL     (1000)
#define VOODOO_ID_call_args    (VOODOO_ID_INTERNAL + 0) // WIP
#define VOODOO_ID_call_offset  (VOODOO_ID_INTERNAL + 1) // used by VOODOO_call_offset*()

//
// Native functions
// when possible, use inline procedures
//

procedure VOODOO_nmalloc(variable bytes)
begin
   variable address := call_offset_r1(0x4ef1c5, bytes); // fallout2.nmalloc_

   #ifdef VOODOO_LIB_DEBUG_NMALLOC
   debug("VOODOO nmalloc(" + bytes + ") = 0x" + sprintf("%x", address));
   #endif

   return address;
end

inline procedure VOODOO_memset(variable address, variable value, variable size)
begin
   call_offset_v3(0x4f0080, address, value, size); // fallout2.memset_
end

inline procedure VOODOO_memzero(variable address, variable size)
begin
   call_offset_v3(0x4f0080, address, 0, size); // fallout2.memset_
end

procedure VOODOO_AssertByte(variable func, variable address, variable expected)
begin
     variable byte := read_byte(address);
     if(byte != expected) then begin
         display_msg("Byte mismatch at "+func+ " ("+address+"), expected " + sprintf("%x", expected) + " but got " + sprintf("%x", byte));
         return false;
     end
     return true;
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

// ddraw.sfall::wmAreaMarkVisitedState_hack+0x51 is calculated
// with VOODOO_GetHookFuncOffset(0x4C4670, 0x51);
procedure VOODOO_GetHookFuncOffset(variable address, variable offset)
begin
   return call_offset_r2(VOODOO_CalcHook__patch, address, offset);
end

procedure VOODOO_GetAddressOf(variable id)
begin
   variable a, aMax := VOODOO_LIB_LOOKUP_ID_ADDRESS + VOODOO_LIB_LOOKUP_ID_SIZE; // CAH cannot into for(x:=0, y:=1; x < y; x++)

   if(typeof(id) != VALTYPE_INT or id <= 0) then
   begin
      // TODO warning
      return;
   end

   for(a := VOODOO_LIB_LOOKUP_ID_ADDRESS; a < aMax; a += 8)
   begin
      if(read_int(a) == id) then
      begin
         return read_int(a + 4);
      end
   end

   return 0;
end

procedure VOODOO_SetAddressOf(variable id, variable address)
begin
   variable a, aMax := VOODOO_LIB_LOOKUP_ID_ADDRESS + VOODOO_LIB_LOOKUP_ID_SIZE; // CAH cannot into for(x:=0, y:=1; x < y; x++)

   if(typeof(id) != VALTYPE_INT or id <= 0) then
   begin
      // TODO warning
      return;
   end

   for(a := VOODOO_LIB_LOOKUP_ID_ADDRESS; a < aMax; a += 8)
   begin
      if(read_int(a) == 0) then
      begin
         write_int(a + 0, id);
         write_int(a + 4, address);
         return;
      end
   end

   // TODO warning
end

procedure VOODOO_DumpAddressOf
begin
   variable idx := 0, a, aMax := VOODOO_LIB_LOOKUP_ID_ADDRESS + VOODOO_LIB_LOOKUP_ID_SIZE; // CAH cannot into for(x:=0, y:=1; x < y; x++)

   for(a := VOODOO_LIB_LOOKUP_ID_ADDRESS; a < aMax; a += 8)
   begin
      variable id := read_int(a), address;

      if(id == 0) then
         break;

      id := read_int(a + 0);
      address := read_int(a + 4);

      display_msg("VOODOO AddressOf[" + idx + "] " + id + " = 0x" + sprintf("%x", address));

      idx++;
   end
end

procedure VOODOO_Init()
begin
   variable address;

   if(VOODOO_LIB_LOOKUP == VOODOO_LIB_LOOKUP_UNSET) then
   begin
      variable o, write_min_value := 0x410000, write_max_value := 0x6b403f, write_min_wanted := 0x410000, write_max_wanted := 0xFF00DD00;

      variable unlock_opcodes := temp_array(4, 0);
      unlock_opcodes := [0x1d1, 0x1d0, 0x1cf, 0x21b]; // must be right after temp_array(); opcodes order is important

      for(o := 0; o<len_array(unlock_opcodes); o++)
      begin
         variable opcode := unlock_opcodes[o];
         variable opcode_address := VOODOO_GetOpcodeAddress(opcode);
         variable opcode_min_offset := VOODOO_GetWriteLimitOffset(opcode, write_min_value);
         variable opcode_max_offset := VOODOO_GetWriteLimitOffset(opcode, write_max_value);
         variable opcode_min_address := opcode_address + opcode_min_offset;
         variable opcode_max_address := opcode_address + opcode_max_offset;

         if(opcode_min_offset == 0 or opcode_max_offset == 0) then
            continue;

         if(read_int(opcode_min_address) == write_min_wanted and read_int(opcode_max_address) == write_max_wanted) then
            continue;

         //display_msg("VOODOO unlocking opcode 0x" + sprintf("%x", opcode) + " @ 0x" + sprintf("%x", opcode_address));

         if(opcode == 0x1d1) then
         begin
            variable u, unlock_address := 0x41ade0; // hello _defam my old friend... i've come to overwrite you again...
            variable unlock := temp_array(0, 0);

            unlock := array_push(unlock, read_int(unlock_address + 0x00));
            unlock := array_push(unlock, read_int(unlock_address + 0x04));
            unlock := array_push(unlock, read_int(unlock_address + 0x08));
            unlock := array_push(unlock, read_int(unlock_address + 0x0c));
            unlock := array_push(unlock, read_int(unlock_address + 0x10));
            unlock := array_push(unlock, read_int(unlock_address + 0x14));
            unlock := array_push(unlock, read_int(unlock_address + 0x18));
            unlock := array_push(unlock, read_int(unlock_address + 0x1c));
            unlock := array_push(unlock, read_int(unlock_address + 0x20));

            // You're a hero...
            write_int  (unlock_address + 0x00, 0xec835052);
            write_int  (unlock_address + 0x04, 0x406a5404);
            write_int  (unlock_address + 0x08, 0x2e50046a);
            write_int  (unlock_address + 0x0c, 0x021815ff);
            write_int  (unlock_address + 0x10, 0xc483006c);
            write_int  (unlock_address + 0x14, 0x24448b04);
            write_int  (unlock_address + 0x18, 0x24548b04);
            write_int  (unlock_address + 0x1c, 0x58028900);
            write_short(unlock_address + 0x20, 0xc35a);

            call_offset_v2(unlock_address, opcode_min_address, write_min_wanted);
            call_offset_v2(unlock_address, opcode_max_address, write_max_wanted);

            // ...and you have to leave.
            for(u:=0; u<len_array(unlock); u++)
            begin
               write_int(unlock_address + u * 4, unlock[u]);
            end
         end
         else
         begin
            write_int(opcode_min_address, write_min_wanted);
            write_int(opcode_max_address, write_max_wanted);
         end

         //display_msg("VOODOO unlocked opcode 0x" + sprintf("%x", opcode) + " @ 0x" + sprintf("%x", opcode_address));
      end

      // init lookup table

      address := VOODOO_nmalloc(VOODOO_LIB_LOOKUP_SIZE);
      call VOODOO_memzero(address, VOODOO_LIB_LOOKUP_SIZE);
      write_int(VOODOO_LIB_LOOKUP_ADDRESS, address);

      // init internals

      address := VOODOO_nmalloc(VOODOO_LIB_LOOKUP_ARGS_SIZE);
      call VOODOO_memzero(address, VOODOO_LIB_LOOKUP_ARGS_SIZE);
      call VOODOO_SetAddressOf(VOODOO_ID_call_args, address);

      address := VOODOO_nmalloc(10);
      call VOODOO_memset(address, 0x90, 10);
      call VOODOO_SetAddressOf(VOODOO_ID_call_offset, address);

      debug("VOODOO lookup = 0x" + sprintf("%x", read_int(VOODOO_LIB_LOOKUP_ADDRESS)));
      call VOODOO_DumpAddressOf();

      return 1;
   end

   debug("VOODOO lookup (cached) = 0x" + sprintf("%x", read_int(VOODOO_LIB_LOOKUP_ADDRESS)));
   return 0;
end

// https://github.com/phobos2077/sfall/issues/288
procedure VOODOO_call_offset_r0(variable address)
begin
   variable jmpaddress := VOODOO_GetAddressOf(VOODOO_ID_call_offset);

   call VOODOO_MakeJump(jmpaddress, address);
   return call_offset_r0(jmpaddress);
end

// https://github.com/phobos2077/sfall/issues/288
procedure VOODOO_call_offset_r4(variable address, variable arg1, variable arg2, variable arg3, variable arg4)
begin
   variable jmpaddress := VOODOO_GetAddressOf(VOODOO_ID_call_offset);

   call VOODOO_MakeJump(jmpaddress, address);
   return call_offset_r4(jmpaddress, arg1, arg2, arg3, arg4);
end

#endif // VOODOO_LIB_H //
