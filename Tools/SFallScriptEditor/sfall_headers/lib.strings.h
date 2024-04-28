/**

  This library contains procedures to work with strings.

  @author phobos2077

*/

#ifndef LIB_STRINGS_H
#define LIB_STRINGS_H

#define is_in_string(str, substr)         (string_pos(str, substr) != -1)
#define string_starts_with(str, substr)   (string_pos(str, substr) == 0)

/**
 * Returns position of first occurance of substr in str, or -1 if not found
 */
procedure string_pos(variable str, variable subst) begin
   variable lst, n;
   lst := string_split(str, subst);
   if (len_array(lst) < 2) then
      return -1;
   return strlen(lst[0]);
end

/**
 * Join array of strings using delimeter
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
 * replaces all occurances of substring in a string with another substring
 */
#define string_replace(str, search, replace)    (string_join(string_split(str, search), replace))

/**
 * sprintf with two arguments
 */
procedure sprintf2(variable str, variable arg1, variable arg2) begin
   variable split, len, i, j, arg;
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
            if (j == 0) then
               arg := arg1;
            else if (j == 1) then
               arg := arg2;
            else
               arg := 0;

            str += sprintf("%" + split[i], arg);
            j++;
         end
      end
   end
   return str;
end

/**
 * sprintf with unlimited number of arguments
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

/**
 * Basically the same as string_split, but delim is of type char instead of string
 */
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

procedure string_repeat(variable str, variable count) begin
   variable out := "", i := 0;
   while (i < count) do begin
      out += str;
      i++;
   end
   return out;
end

/**
 * Workaround for string_split bug in sfall 3.3
 * DEPRECATED as of sfall 3.4 (bug fixed)
 */
procedure string_split_safe(variable str, variable split) begin
   variable lst;
   str += split;
   lst := string_split(str, split);
   resize_array(lst, len_array(lst) - 1);
   return lst;
end

/**
 * The same as sfall string_split, but returns array of integers instead
 * Useful in cunjunction with is_in_array()
 */
procedure string_split_ints(variable str, variable split) begin
   variable i := 0;
   variable list;
   list := string_split(str, split);
   while (i < len_array(list)) do begin
      list[i] := atoi(list[i]);
      i++;
   end
   return list;
end


/**
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

