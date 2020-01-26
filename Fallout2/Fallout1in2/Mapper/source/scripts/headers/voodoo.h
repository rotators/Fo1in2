#ifndef VOODOO_H
#define VOODOO_H

/*********************************************************
   All kinds of memory reading/writing macros
   Requires AllowUnsafeScripting=1 in ddraw.ini!
*********************************************************/

// Check current ddraw.dll build (base check, left for reference only; use sfall_rotators macro from sfall.rotators.h in scripts)
#define VOODOO_marker  (read_byte(0x410003) == 0xF4)

// This will disable running the credits after the endgame slides:
// This is done via Sfall now (F1EngineBehavior=1)
#define VOODOO_mode_fo1_ending                   \
               write_int( 0x4A4343, 0x90909090); \
               write_byte(0x4A4347, 0x90)

// This will disable the "You encounter: ..." message:
#define VOODOO_disable_YouEncounter_message      \
               write_int( 0x4C1011, 0x90909090); \
               write_byte(0x4C1015, 0x90);       \
               write_int( 0x4C1042, 0x90909090); \
               write_byte(0x4C1046, 0x90)

// This will change the rest timer "wait until 08:00" to 06:00 like in Fallout 1.
#define VOODOO_rest_till0600 \
               write_int(0x4995F3, 6)

// This will fix Dogmeat generic party dialog strings
// See https://github.com/rotators/Fo1in2/issues/21
#define VOODOO_dogmeat_pm_dialog \
               write_byte(0x444d10, 0x7a)

#endif // VOODOO_H //
