#pragma once

#include "sfall.h"
#include "sfall.rotators.voodoo.h"

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
//      r_message_box(text, [flags, color1, color23, callback)
#define r_message_box(...)                                  sfall_func("r_message_box", __VA_ARGS__)

// Rotators unsafe sfall_funcX macros
// arguments in [square, brackets] are optional
// AllowUnsafeScripting required

#define r_call_offset_push(val)                             sfall_func("r_call_offset_push", val)
#define r_call_offset(addr)                                 sfall_func("r_call_offset", addr)
#define r_call_offset_cdecl(addr)                           sfall_func("r_call_offset_cdecl", addr)
#define r_hrp                                               sfall_func("r_hrp")
#define r_hrp_offset(addr)                                  sfall_func("r_hrp_offset", addr)
#define r_write_byte(addr,val)                              sfall_func("r_write", 0, addr, val)
#define r_write_short(addr,val)                             sfall_func("r_write", 1, addr, val)
#define r_write_int(addr,val)                               sfall_func("r_write", 2, addr, val)
#define r_write_string(addr,val)                            sfall_func("r_write", 3, addr, val)

// TODO: (Re)move
#define message_box_warning(text)      sfall_func("message_box", text, 0x01, 134, 145)
