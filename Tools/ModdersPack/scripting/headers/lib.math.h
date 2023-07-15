#ifndef LIB_MATH_H
#define LIB_MATH_H

/**
  Numbers...
*/

// for sfall 4.2.3/3.8.23
pure procedure unsigned_int_compare(variable a, variable b) begin
   if ((a bwxor b) == 0) then return 0; // a == b
   return 1 if ((b == 0) orElse a div b) else -1;
end

#define MAX(x, y)                    ((x > y) * x + (x <= y) * y)
#define MIN(x, y)                    ((x < y) * x + (x >= y) * y)

#define math_max(x, y)               (x if x > y else y)
#define math_min(x, y)               (x if x < y else y)
#define math_in_range(x, from, to)   (x >= from and x <= to)


procedure math_clamp(variable val, variable a, variable b) begin
   variable min, max;
   if (a < b) then begin
      min := a;
      max := b;
   end else begin
      min := b;
      max := a;
   end
   if (val < min) then
      return min;
   else if (val > max) then
      return max;
   else
      return val;
end


#endif
