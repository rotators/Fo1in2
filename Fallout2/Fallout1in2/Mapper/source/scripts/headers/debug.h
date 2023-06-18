#pragma once

#include "global.h"

#define debug_mode   (global_var(GVAR_ENABLE_DEBUG_MESSAGES) == 1)
//#define debug(x)     if debug_mode then display_msg(x)

/*
   To enable styles and colors in the debug console, run a .bat file with:
      reg add HKEY_CURRENT_USER\Console /v VirtualTerminalLevel /t REG_DWORD /d 0x00000001 /f
*/

//
// https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
// https://invisible-island.net/xterm/ctlseqs/ctlseqs.html
// https://vt100.net/docs/vt220-rm/chapter2.html
//
// uppercase names follows terminal documentation(s) one way or another
// lowercase names are made up
//

// bypasses whiny preprocessor and makes it bit easier to see which parts of long string are ANSI garbage
#define _ANSI(x)                                sprintf("%c", 0x1b) + x

// misc
#define _ANSI_RIS                               _ANSI("c")

// OSC : Operating System Command
#define _ANSI_OSC(cmd,arg)                      _ANSI("]" + cmd + ";" + arg + _ANSI("\\"))
#define _ANSI_window_name(text)                 _ANSI_OSC(2,text)

// CSI : Control Sequence Introducer
#define _ANSI_CSI(x)                            _ANSI("[" + x)
#define _ANSI_SGR(color)                        _ANSI_CSI(color) + "m"  // set and forget
#define _ANSI_color_rgb_set(rf,gf,bf,rb,gb,bb)  _ANSI_SGR("38;2;" + rf + ";" + gf + ";" + bf + "48;2;" + rb + ";" + gb + ";" + bb) // set and forget; order: foreground, background, text
#define _ANSI_color_rgb_fg_set(r,g,b)           _ANSI_SGR("38;2;" + r + ";" + g + ";" + b)  // set and forget
#define _ANSI_color_rgb_bg_set(r,g,b)           _ANSI_SGR("48;2;" + r + ";" + g + ";" + b)  // set and forget

#define _ANSI_color_reset                       _ANSI_SGR(0)  // default text foreground/background
#define _ANSI_color(color,text)                 _ANSI_SGR(color) + text + _ANSI_color_reset

// ANSI styles, using "compressed" sequence when possible
#define _ANSI_style_debug(text)                 _ANSI_SGR("1;38;2;60;248;0") + "•" + text + _ANSI_color_reset // STYLE_BOLD + COLOR_GREEN_FALLOUT + dot + text + STYLE_RESET

#define STYLE_RESET                             _ANSI_color_reset
#define STYLE_BOLD                              _ANSI_SGR(1)
#define STYLE_UNDERLINE                         _ANSI_SGR(4)
#define STYLE_INVERSE                           _ANSI_SGR(7)

#define COLOR_BLACK(text)                       _ANSI_color(30,text)
#define COLOR_RED(text)                         _ANSI_color(31,text)
#define COLOR_GREEN(text)                       _ANSI_color(32,text)
#define COLOR_GREEN_FALLOUT(text)               _ANSI_color_rgb_fg_set(60,248,0) + text + _ANSI_color_reset
#define COLOR_YELLOW(text)                      _ANSI_color(33,text)
#define COLOR_BLUE(text)                        _ANSI_color(34,text)
#define COLOR_MAGENTA(text)                     _ANSI_color(35,text)
#define COLOR_CYAN(text)                        _ANSI_color(36,text)
#define COLOR_WHITE(text)                       _ANSI_color(37,text)

#define COLOR_BG_BLACK                          _ANSI_SGR(100)
#define COLOR_BG_RED                            _ANSI_SGR(101)
#define COLOR_BG_GREEN                          _ANSI_SGR(102)
#define COLOR_BG_YELLOW                         _ANSI_SGR(103)
#define COLOR_BG_BLUE                           _ANSI_SGR(104)
#define COLOR_BG_MAGENTA                        _ANSI_SGR(105)
#define COLOR_BG_CYAN                           _ANSI_SGR(106)
#define COLOR_BG_WHITE                          _ANSI_SGR(107)

// Default is green text
//#define debug(x)           debug_msg(" " + STYLE_BOLD + COLOR_GREEN("•"+x))
#define debug(text)        debug_msg(_ANSI_style_debug(text))

#define debug_black(x)     debug_msg(" " + STYLE_BOLD + COLOR_BLACK(x))
#define debug_red(x)       debug_msg(" " + STYLE_BOLD + COLOR_RED(x))
#define debug_green(x)     debug_msg(" " + STYLE_BOLD + COLOR_GREEN(x))
#define debug_yellow(x)    debug_msg(" " + STYLE_BOLD + COLOR_YELLOW(x))
#define debug_blue(x)      debug_msg(" " + STYLE_BOLD + COLOR_BLUE(x))
#define debug_magenta(x)   debug_msg(" " + STYLE_BOLD + COLOR_MAGENTA(x))
#define debug_cyan(x)      debug_msg(" " + STYLE_BOLD + COLOR_CYAN(x))
#define debug_white(x)     debug_msg(" " + STYLE_BOLD + COLOR_WHITE(x))

#define debug_warning(x)   debug_msg(" " + STYLE_INVERSE + COLOR_RED(" " + x + " "))
