#ifndef __SFALL_ROTATORS__
#define __SFALL_ROTATORS__

#if !defined(metarule_exist)
#include "sfall.h"
#endif

// https://stackoverflow.com/a/44291052/11998612 + tweaks
#define __sfall_prefix(...)                        0,__VA_ARGS__
#define __sfall_lastof(x,a,b,c,d,e,f,g,h,i,j,...)  j
#define __sfall_cntarg(...)                        __sfall_lastof(__VA_ARGS__,8,7,6,5,4,3,2,1,0,0)
#define __sfall_numarg(...)                        __sfall_cntarg(__sfall_prefix(__VA_ARGS__))
#define __sfall_merge(left,right)                  left ## right
#define __sfall_func(count)                        __sfall_merge(sfall_func,count)

// automagically counts number of arguments and selects matching sfall_funcX when script is preprocessed
// if more than 9 arguments is used, sfall_func9 is selected
#define sfall_func(...)   __sfall_func(__sfall_numarg(__VA_ARGS__))(__VA_ARGS__)

// Check if current ddraw.dll build is from Rotators
#define sfall_rotators  (read_byte(0x410003) == 0xF4 and sfall_func("metarule_exist", "rotators"))

// Rotators sfall_funcX macros
// arguments in [square, brackets] are optional

#define r_get_ini_string(file, section, key, defaultValue)  sfall_func("r_get_ini_string", file, section, key, defaultValue)
//      r_message_box(text, [flags, color1, color23)
#define r_message_box(...)                                  sfall_func("r_message_box", __VA_ARGS__)

#endif // __SFALL_ROTATORS__ //
