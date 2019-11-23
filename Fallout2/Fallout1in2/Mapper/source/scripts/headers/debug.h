#ifndef DEBUG_H
#define DEBUG_H

#include "global.h"

#define debug_mode  (global_var(GVAR_ENABLE_DEBUG_MESSAGES) == 1)
#define debug(x)    if debug_mode then display_msg(x)

// Macros for debugging messages
#ifdef DEBUG
#define DEBUGMSG(x)       debug_msg(x);
#else
#define DEBUGMSG(x)       //nothing
#endif

#endif // DEBUG_H //
