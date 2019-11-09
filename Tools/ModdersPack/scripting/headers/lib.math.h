#ifndef LIB_MATH_H
#define LIB_MATH_H

/**
  Numbers...
*/

#define MAX(x, y)    ((x > y) * x + (x <= y) * y)
#define MIN(x, y)    ((x < y) * x + (x >= y) * y)
#define in_range(x, from, to)    (x >= from and x <= to)

procedure max(variable x, variable y) begin
   if (x > y) then return x;
   return y;
end

procedure min(variable x, variable y) begin
   if (x < y) then return x;
   return y;
end

/*procedure round(variable val) begin
   variable intp;
   intp := floor(val);
   if ((val-intp) >= 0.5) then intp++;
   return intp;
end*/

/*procedure ceil(variable val) begin
   variable intp;
   intp := floor(val);
   if (abs(val-intp) > 0.0) then begin
      intp++;
   end
   return intp;
end*/

procedure cap_number(variable num, variable min, variable max) begin
   if (num > max) then num := max;
   else if (num < min) then num := min;
   return num;
end



#endif
