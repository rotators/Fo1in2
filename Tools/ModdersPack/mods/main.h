#ifndef MAIN_H
#define MAIN_H

#include "..\scripting\headers\sfall.h"
#include "..\scripting\headers\define_lite.h"
#include "..\scripting\headers\define_extra.h"
#include "..\scripting\headers\command_lite.h"
#include "..\scripting\headers\dik.h"
/*
#include "..\scripting\headers\lib.arrays.h"
#include "..\scripting\headers\lib.strings.h"
#include "..\scripting\headers\lib.inven.h"
*/

variable ini := "sfall-mods.ini";
variable translationIni;

// Gets the integer value from the specified ini
procedure GetIniConfig(variable section, variable key, variable def, variable inifile) begin
   variable val := get_ini_setting(inifile + "|" + section + "|" + key);
   if val == -1 then val := def;
   return val;
end

// Gets the string value from the specified ini
procedure GetIniConfigStr(variable section, variable key, variable def, variable inifile) begin
   variable val := get_ini_string(inifile + "|" + section + "|" + key);
   if val == -1 orElse val == "" then val := def;
   return val;
end

// Gets the integer value from sfall-mods.ini
procedure GetConfig(variable section, variable key, variable def) begin
   variable val := get_ini_setting(ini + "|" + section + "|" + key);
   if val == -1 then val := def;
   return val;
end

// Gets the string value from sfall-mods.ini
procedure GetConfigStr(variable section, variable key, variable def) begin
   variable val := get_ini_string(ini + "|" + section + "|" + key);
   if val == -1 orElse val == "" then val := def;
   return val;
end

// Gets the value from sfall-mods.ini as a temp array of strings
procedure GetConfigList(variable section, variable key) begin
   variable val := get_ini_string(ini + "|" + section + "|" + key);
   if val == -1 orElse val == "" then return [];

   return string_split(val, ",");
end

// Gets the value from sfall-mods.ini as a temp array of ints
procedure GetConfigListInt(variable section, variable key) begin
   variable arr, i, item;

   arr := GetConfigList(section, key);
   for (i := 0; i < len_array(arr); i++) begin
      arr[i] := atoi(arr[i]);
   end
   return arr;
end

// Translates given string using Translations.ini
procedure Translate(variable id, variable def) begin
   variable str := get_ini_string(translationIni + "|Sfall|" + id);
   if (str == 0 orElse (strlen(str) == 0)) then begin
      str := def;
   end
   return str;
end

procedure InitConfigs begin
   translationIni := GetIniConfigStr("Main", "TranslationsINI", "Translations.ini", "ddraw.ini");
end

#endif
