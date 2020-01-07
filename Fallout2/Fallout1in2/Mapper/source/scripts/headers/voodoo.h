#ifndef VOODOO_H
#define VOODOO_H

/*********************************************************
   All kinds of memory reading/writing macros
   Requires AllowUnsafeScripting=1 in ddraw.ini!
*********************************************************/

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

// This returns true only if currently used ddraw.dll comes from Rotators repository
#define VOODOO_ddraw_rotators \
               (read_byte(0x410003) == 0xF4) // hlt

#endif // VOODOO_H //
