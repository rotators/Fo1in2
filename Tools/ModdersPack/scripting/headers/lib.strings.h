/**

  This library contains procedures to work with strings.

  @author phobos2077

*/

#ifndef LIB_STRINGS_H
#define LIB_STRINGS_H

#include "sfall.h"

/**
 * Checks if *str* contains *sub* as part of it anywhere in the string. 
 * @arg {string} str
 * @arg {string} sub
 * @ret {bool}
 */
#define string_contains(str, sub)      (string_find(str, sub) != -1)

/**
 * Checks if *str* contains *sub* at the beginning of the string.
 * @arg {string} str
 * @arg {string} sub
 * @ret {bool}
 */
#define string_starts_with(str, sub)   (string_find(str, sub) == 0)

/**
 * Same as *string_format*, but takes parameters from a given list array.
 * @arg {string} fmt
 * @arg {list} arr
 * @ret {string}
 */
#define string_format_array(fmt, arr)  sprintf_array(fmt, arr)

/**
 * Replaces all occurances of *search* in *str* with *replace* string.
 * @arg {string} str
 * @arg {string} search
 * @arg {string} replace
 * @ret {string}
 */
#define string_replace(str, search, replace)    (string_join(string_split(str, search), replace))

/**
 * @deprecated - use *string_format* instead
 */
#define sprintf2(fmt, arg1, arg2)      string_format2(fmt, arg1, arg2)

/**
 * Joins *array* of strings into a new string using *join* as delimeter.
 * @arg {list} array
 * @arg {string} join
 * @ret {string}
 */
procedure string_join(variable array, variable join) begin
   variable str, i, len;
   str := "";
   len := len_array(array);
   if (len > 0) then begin
      str := array[0];
      for (i:=1; i<len; i++) begin
         str += join + array[i];
      end
   end
   return str;
end

/**
 * Like *sprintf* but takes parameters from a given list array.
 * @arg {string} str
 * @arg {list} args
 * @ret {string}
 */
procedure sprintf_array(variable str, variable args) begin
   variable split, len, i, j;
   split := string_split(str, "%");
   len := len_array(split);
   str := "";
   if (len > 0) then begin
      str := split[0];
      j := 0;
      for (i := 1; i < len; i++) begin
         if (split[i] == "") then begin
            if (i < len - 1) then begin
               str += "%" + split[i+1];
               i++;
            end
         end else begin
            str += sprintf("%" + split[i], args[j]);
            j++;
         end
      end
   end
   return str;
end

/**
 * Returns position of last occurance of substr in str, or -1 if not found
 */
/*procedure string_rpos(variable str, variable substr) begin
variable lst, n;
   lst := string_split(str, substr);
   n := len_array(lst);
   if (n < 2) then
      return -1;
   return string_len(str) - (string_len(lst[n-1]) + string_len(substr));
end*/

// UNFINISHED, don't use!
procedure string_get_tokens(variable str, variable delim) begin
   variable lst, line, token, maxlen, len, count;
   count := 1;
   maxlen := 4;
   token := tokenize(str, 0, delim);
   //if (token != 0) then
      //count := 1;
      line := token;
      while (line != str) do begin
         count += 1;
         len := strlen(token);
         if (len > maxlen) then
            maxlen := len;
         token := tokenize(str, line, delim);
         if (token != 0) then
            line += delim + token;
      end
   //end

   return count;
end

/**
 * Creates a string by repeating *str* *count* times.
 * @arg {string} str
 * @arg {int} count
 * @ret {string}
 */
procedure string_repeat(variable str, variable count) begin
   variable out := "", i := 0;
   while (i < count) do begin
      out += str;
      i++;
   end
   return out;
end

/**
 * The same as sfall string_split, but returns array of integers instead
 * Useful in cunjunction with is_in_array()
 * @arg {string} str
 * @arg {string} split
 * @ret {list}
 */
procedure string_split_ints(variable str, variable split) begin
   variable n := 0;
   variable list, result, val;

   if (str == "" or typeof(str) != VALTYPE_STR) then
      return temp_array_list(0);

   list := string_split(str, split);
   result := temp_array_list(0);
   foreach (val in list) begin
      if (val != "") then begin
         resize_array(result, n + 1);
         result[n] := atoi(val);
         n++;
      end
   end
   return result;
end

/**
 * *atoi* proc wrapper, for use as a delegate.
 * @arg {string} str
 * @ret {int}
 */
procedure string_to_int(variable str) begin
   return atoi(str);
end

/**
 * *atof* proc wrapper, for use as a delegate.
 * @arg {string} str
 * @ret {float}
 */
procedure string_to_float(variable str) begin
   return atof(str);
end

/**
 * Converts any value to a string, for use as a delegate.
 * @arg {any} val
 * @ret {string}
 */
procedure to_string(variable val) begin
   return ""+val;
end


/**
  DEPRECATED, use string_format instead!

  String parse functions. Idea taken from KLIMaka on TeamX forums.
  Placeholders in format %d% are replaced from string. d refers to variable index (starting from 1).
  You can repeat one placeholder multiple times, or use placeholders in any order.

  Example:
  parse_str_2("Hello, %2%. I have only $%1% to spare.", money_amount, dude_name);
  Will return:
  Hello, Killiano. I have only $1200 to spare.

  The *_list function takes a temp_array as second parameter.
*/

#define _TOKENIZE_BEGIN       \
   variable token, rest, line, result, n; \
   line := tokenize(str, 0, '%'); \
   result := line; \
   while line != str do begin \
      token := tokenize(str, line, '%'); \
      line += "%" + token; \
      if token == "" then result += "%"; \
      else begin

#define _TOKENIZE_END       \
      end \
      rest := tokenize(str, line, '%'); \
      if (rest != 0) then begin \
         line += "%" + rest; \
         result += rest; \
      end \
   end \
   return result;


procedure parse_str_list(variable str, variable list) begin
_TOKENIZE_BEGIN
      n := atoi(token) - 1;
      if (n >= 0 and n < len_array(list)) then result += list[n];
_TOKENIZE_END
end

procedure parse_str_2(variable str, variable x1, variable x2) begin
_TOKENIZE_BEGIN
      n := atoi(token);
      if (n == 1) then result += x1;
      else if (n == 2) then result += x2;
_TOKENIZE_END
end

procedure parse_str_4(variable str, variable x1, variable x2, variable x3, variable x4) begin
_TOKENIZE_BEGIN
      n := atoi(token);
      if (n == 1) then result += x1;
      else if (n == 2) then result += x2;
      else if (n == 3) then result += x3;
      else if (n == 4) then result += x4;
_TOKENIZE_END
end

#undef _TOKENIZE_BEGIN
#undef _TOKENIZE_END

#endif

