
#include "sfall.h"
#include "define_lite.h"
#include "define_extra.h"

#include "lib.arrays.h"
#include "lib.strings.h"
// #include "lib.inven.h"

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
   if val == -1 or val == "" then val := def;
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
   if val == -1 or val == "" then val := def;
   return val;
end

// Gets the value from sfall-mods.ini as a temp array of strings
procedure GetConfigList(variable section, variable key) begin
   variable val := get_ini_string(ini + "|" + section + "|" + key);
   if val == -1 or val == "" then return [];

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
   if not str or (strlen(str) == 0) then begin
      str := def;
   end
   return str;
end

procedure InitConfigs begin
   translationIni := GetIniConfigStr("Main", "TranslationsINI", "Translations.ini", "ddraw.ini");
end
