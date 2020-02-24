#ifndef VOODOO_LIB_H
#define VOODOO_LIB_H

// Base library for voodoo magick.
#include "sfall/lib.math.h"

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

procedure VOODOO_WriteNop(variable address, variable length:=1)
begin
  variable i;
  // x86 instructions can't be longer than 15 bytes.
  length := cap_number(length, 1, 15);
  for(i := 0; i < length-1; i++) begin
   write_byte(address+i, 0x66);
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

// Because of https://github.com/phobos2077/sfall/issues/288
procedure VOODOO_SafeWrite8(variable address, variable value)
begin
   call_offset_v2(0x480f0d, address, (value bwand 0xFF));
end

procedure VOODOO_SafeWrite16(variable address, variable value)
begin
   call_offset_v2(0x480f2f, address, (value bwand 0xFFFF));
end

procedure VOODOO_SafeWrite32(variable address, variable value)
begin
   call_offset_v2(0x480f52, address, value);
end

// ddraw.sfall::wmAreaMarkVisitedState_hack+0x51 is calculated
// with VOODOO_GetHookFuncOffset(0x4C4670, 0x51);
procedure VOODOO_GetHookFuncOffset(variable address, variable offset)
begin
   return call_offset_r2(0x480f74, address, offset);
end

#endif // VOODOO_LIB_H //
