// Base library for voodoo magick.

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

procedure VOODOO_BlockCall(variable address, variable length:=5)
begin
  variable i;
  // an x86 instruction can't be longer than 15 bytes.
  if(length > 15) then begin
     length := 15;
  end

  // operand-size override prefix bytes.
  for(i := 0; i < length-1; i++) begin
   write_byte(address+i, 0x66);
  end
  write_byte(address+length-1, 0x90);
end
