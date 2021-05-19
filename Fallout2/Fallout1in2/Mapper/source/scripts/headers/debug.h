#pragma once

#include "global.h"

#define debug_mode  (global_var(GVAR_ENABLE_DEBUG_MESSAGES) == 1)
#define debug(x)    if debug_mode then display_msg(x)
