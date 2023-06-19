#pragma once

#include "ansi.h"
#include "global.h"

#define debug_mode   (global_var(GVAR_ENABLE_DEBUG_MESSAGES) == 1)
//#define debug(x)     if debug_mode then display_msg(x)

/*
   To enable styles and colors in the debug console, run a .bat file with:
      reg add HKEY_CURRENT_USER\Console /v VirtualTerminalLevel /t REG_DWORD /d 0x00000001 /f
*/

// ANSI styles, using "compressed" sequence when possible
#define STYLE_debug(text) \
 _ANSI_SGR("1;38;2;60;248;0") + "•" + text + _ANSI_color_reset // STYLE_BOLD + COLOR_GREEN_FALLOUT + dot + text + STYLE_RESET

#define STYLE_RESET                             _ANSI_color_reset
#define STYLE_BOLD                              _ANSI_color_set(1)
#define STYLE_UNDERLINE                         _ANSI_color_set(4)
#define STYLE_INVERSE                           _ANSI_color_set(7)

#define COLOR_BLACK(text)                       _ANSI_color(30,text)
#define COLOR_RED(text)                         _ANSI_color(31,text)
#define COLOR_GREEN(text)                       _ANSI_color(32,text)
#define COLOR_GREEN_FALLOUT(text)               _ANSI_color_rgb_fg_set(60,248,0) + text + _ANSI_color_reset
#define COLOR_YELLOW(text)                      _ANSI_color(33,text)
#define COLOR_BLUE(text)                        _ANSI_color(34,text)
#define COLOR_MAGENTA(text)                     _ANSI_color(35,text)
#define COLOR_CYAN(text)                        _ANSI_color(36,text)
#define COLOR_WHITE(text)                       _ANSI_color(37,text)

#define COLOR_BG_BLACK                          _ANSI_color_set(100)
#define COLOR_BG_RED                            _ANSI_color_set(101)
#define COLOR_BG_GREEN                          _ANSI_color_set(102)
#define COLOR_BG_YELLOW                         _ANSI_color_set(103)
#define COLOR_BG_BLUE                           _ANSI_color_set(104)
#define COLOR_BG_MAGENTA                        _ANSI_color_set(105)
#define COLOR_BG_CYAN                           _ANSI_color_set(106)
#define COLOR_BG_WHITE                          _ANSI_color_set(107)

// Default is green text
//#define debug(x)           debug_msg(" " + STYLE_BOLD + COLOR_GREEN("•"+x))
#define debug(text)        debug_msg(STYLE_debug(text))

#define debug_black(x)     debug_msg(" " + STYLE_BOLD + COLOR_BLACK(x))
#define debug_red(x)       debug_msg(" " + STYLE_BOLD + COLOR_RED(x))
#define debug_green(x)     debug_msg(" " + STYLE_BOLD + COLOR_GREEN(x))
#define debug_yellow(x)    debug_msg(" " + STYLE_BOLD + COLOR_YELLOW(x))
#define debug_blue(x)      debug_msg(" " + STYLE_BOLD + COLOR_BLUE(x))
#define debug_magenta(x)   debug_msg(" " + STYLE_BOLD + COLOR_MAGENTA(x))
#define debug_cyan(x)      debug_msg(" " + STYLE_BOLD + COLOR_CYAN(x))
#define debug_white(x)     debug_msg(" " + STYLE_BOLD + COLOR_WHITE(x))

#define debug_warning(x)   debug_msg(" " + STYLE_INVERSE + COLOR_RED(" " + x + " "))
