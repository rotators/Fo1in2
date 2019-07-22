#ifndef MR_MATH_H
#define MR_MATH_H

procedure clamp(variable Value, variable Min_Value, variable Max_Value)
begin
   if (Value > Max_Value) then
      Value := Max_Value;
   else if (Value < Min_Value) then
      Value := Min_Value;
      
   return Value;
end

procedure min(variable ValueA, variable ValueB)
begin
   if (ValueB < ValueA) then
      return ValueB;
      
   return ValueA;
end

procedure max(variable ValueA, variable ValueB)
begin
   if (ValueB > ValueA) then
      return ValueB;
      
   return ValueA;
end

#endif // MR_MATH_H
