#pragma once

#include "global.h"

#define debug_mode   (global_var(GVAR_ENABLE_DEBUG_MESSAGES) == 1)
//#define debug(x)     if debug_mode then display_msg(x)

/*
   To enable styles and colors in the debug console, run a .bat file with:
      reg add HKEY_CURRENT_USER\Console /v VirtualTerminalLevel /t REG_DWORD /d 0x00000001 /f
*/
#define STYLE_RESET           "[0m"
#define STYLE_BOLD            "[1m"
#define STYLE_UNDERLINE       "[4m"
#define STYLE_INVERSE         "[7m"

#define COLOR_BLACK(x)        "[30m" + x + STYLE_RESET
#define COLOR_RED(x)          "[31m" + x + STYLE_RESET
#define COLOR_GREEN(x)        "[32m" + x + STYLE_RESET
#define COLOR_YELLOW(x)       "[33m" + x + STYLE_RESET
#define COLOR_BLUE(x)         "[34m" + x + STYLE_RESET
#define COLOR_MAGENTA(x)      "[35m" + x + STYLE_RESET
#define COLOR_CYAN(x)         "[36m" + x + STYLE_RESET
#define COLOR_WHITE(x)        "[37m" + x + STYLE_RESET

#define COLOR_BG_BLACK        "[100m"
#define COLOR_BG_RED          "[101m"
#define COLOR_BG_GREEN        "[102m"
#define COLOR_BG_YELLOW       "[103m"
#define COLOR_BG_BLUE         "[104m"
#define COLOR_BG_MAGENTA      "[105m"
#define COLOR_BG_CYAN         "[106m"
#define COLOR_BG_WHITE        "[107m"

// Default is green text
#define debug(x)           debug_msg(" " + STYLE_BOLD + COLOR_GREEN("•"+x))

#define debug_black(x)     debug_msg(" " + STYLE_BOLD + COLOR_BLACK(x))
#define debug_red(x)       debug_msg(" " + STYLE_BOLD + COLOR_RED(x))
#define debug_green(x)     debug_msg(" " + STYLE_BOLD + COLOR_GREEN(x))
#define debug_yellow(x)    debug_msg(" " + STYLE_BOLD + COLOR_YELLOW(x))
#define debug_blue(x)      debug_msg(" " + STYLE_BOLD + COLOR_BLUE(x))
#define debug_magenta(x)   debug_msg(" " + STYLE_BOLD + COLOR_MAGENTA(x))
#define debug_cyan(x)      debug_msg(" " + STYLE_BOLD + COLOR_CYAN(x))
#define debug_white(x)     debug_msg(" " + STYLE_BOLD + COLOR_WHITE(x))
