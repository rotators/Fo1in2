#ifndef DEBUG_H
#define DEBUG_H

#include "global.h"

#define debug_mode  (global_var(DEBUG_MODE_MESSAGES_ON) == 1)
#define debug(x)    if debug_mode then display_msg(x)

#endif // DEBUG_H //
