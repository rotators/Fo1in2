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

// This will replace RoboDog PID with Dogmeat PID in hardcoded list of dogs PIDs; required for woofs and arfs in combat control
#define VOODOO_dogmeat_pm_dialog \
               write_byte(0x444d10, 0x7a)

// Removes the text under green circles on the worldmap
// Used by Classic Worldmap mod
#define VOODOO_remove_circle_name            \
               write_byte(0x4c407a, 0x90);   \
               write_byte(0x4c4094, 0x90);   \
               write_byte(0x4c4095, 0x90);   \
               write_byte(0x4c4096, 0x90);   \
               write_byte(0x4c4097, 0x90);   \
               write_byte(0x4c4098, 0x90);   \
               write_byte(0x4c4099, 0x90)

// No radius when a location is revealed on the worldmap
#define VOODOO_location_discover_radius \
   write_byte(0x41ae05, 0x60); \
   write_byte(0x41ae06, 0x2E); \
   write_byte(0x41ae07, 0xA1); \
   write_byte(0x41ae08, 0x70); \
   write_byte(0x41ae09, 0x46); \
   write_byte(0x41ae0a, 0x4C); \
   write_byte(0x41ae0b, 0x00); \
   write_byte(0x41ae0c, 0xBA); \
   write_byte(0x41ae0d, 0xC5); \
   write_byte(0x41ae0e, 0x46); \
   write_byte(0x41ae0f, 0x4C); \
   write_byte(0x41ae10, 0x00); \
   write_byte(0x41ae11, 0x01); \
   write_byte(0x41ae12, 0xd0); \
   write_byte(0x41ae13, 0x89); \
   write_byte(0x41ae14, 0xC6); \
   write_byte(0x41ae15, 0x83); \
   write_byte(0x41ae16, 0xEC); \
   write_byte(0x41ae17, 0x04); \
   write_byte(0x41ae18, 0x54); \
   write_byte(0x41ae19, 0x6A); \
   write_byte(0x41ae1a, 0x40); \
   write_byte(0x41ae1b, 0x6A); \
   write_byte(0x41ae1c, 0x01); \
   write_byte(0x41ae1d, 0x50); \
   write_byte(0x41ae1e, 0x2E); \
   write_byte(0x41ae1f, 0xFF); \
   write_byte(0x41ae20, 0x15); \
   write_byte(0x41ae21, 0x04); \
   write_byte(0x41ae22, 0x00); \
   write_byte(0x41ae23, 0x41); \
   write_byte(0x41ae24, 0x00); \
   write_byte(0x41ae25, 0xC6); \
   write_byte(0x41ae26, 0x06); \
   write_byte(0x41ae27, 0x00); \
   write_byte(0x41ae28, 0x83); \
   write_byte(0x41ae29, 0xC4); \
   write_byte(0x41ae2a, 0x04); \
   write_byte(0x41ae2b, 0x61); \
   write_byte(0x41ae2c, 0xC3); \
   call_offset_v0(0x41ae05)

#endif // VOODOO_H //
