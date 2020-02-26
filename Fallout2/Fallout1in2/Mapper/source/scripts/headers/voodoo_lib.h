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

#include "sfall/lib.math.h"

// Because of https://github.com/phobos2077/sfall/issues/288
procedure VOODOO_SafeWrite8(variable address, variable value)
begin
   call_offset_v2(VOODOO_SafeWrite8___patch, address, (value bwand 0xFF));
end

procedure VOODOO_SafeWrite16(variable address, variable value)
begin
   call_offset_v2(VOODOO_SafeWrite16___patch, address, (value bwand 0xFFFF));
end

procedure VOODOO_SafeWrite32(variable address, variable value)
begin
   call_offset_v2(VOODOO_SafeWrite32___patch, address, value);
end

procedure VOODOO_CalculateRel32(variable from, variable to) begin
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
  call VOODOO_SafeWrite8(at+1, byte1);
  call VOODOO_SafeWrite8(at+2, byte2);
  call VOODOO_SafeWrite8(at+3, byte3);
  call VOODOO_SafeWrite8(at+4, byte4);
end

procedure VOODOO_MakeCall(variable address, variable func)
begin
  call VOODOO_SafeWrite8(address, 0xE8);
  call VOODOO_WriteRelAddress(address, func);
end

procedure VOODOO_MakeJump(variable address, variable func)
begin
  call VOODOO_SafeWrite8(address, 0xE9);
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

// Could also be called BlockJump.
procedure VOODOO_BlockCall(variable address, variable length:=5)
begin
   call VOODOO_WriteNop(address, cap_number(length, 5, 15));
end

// Because of https://github.com/phobos2077/sfall/issues/288
procedure VOODOO_call_offset_r0(variable address)
begin
   call VOODOO_MakeJump(0x00410004, address);
   return call_offset_r0(0x00410004);
end



// ddraw.sfall::wmAreaMarkVisitedState_hack+0x51 is calculated
// with VOODOO_GetHookFuncOffset(0x4C4670, 0x51);
procedure VOODOO_GetHookFuncOffset(variable address, variable offset)
begin
   return call_offset_r2(VOODOO_CalcHook__patch, address, offset);
end

procedure VOODOO_nmalloc(variable bytes)
begin
   return call_offset_r1(0x4ef1c5, bytes); // fallout2.nmalloc
end

#endif // VOODOO_LIB_H //
