#pragma once

/**************************************************
 *       _    __                __                *
 *      | |  / /___  ____  ____/ /___  ____       *
 *      | | / / __ \/ __ \/ __  / __ \/ __ \      *
 *      | |/ / /_/ / /_/ / /_/ / /_/ / /_/ /      *
 *      |___/\____/\____/\__,_/\____/\____/       *
 *                                                *
 *      All kinds of unsafe scripting macros      *
 *  Requires AllowUnsafeScripting=1 in ddraw.ini  *
 *                                                *
 *      Remember to wear protective goggles       *
 *                                                *
 **************************************************/

// used with auto generated VOODOO_nmalloc code
variable $addr;

// sfall-asm:defines-begin //
// sfall-asm:defines-end //

#include "sfall/sfall.rotators.h"
#include "debug.h"
#include "voodoo_lib.h"

// This will revert the nerfed player hit chance back to how it was in Fo1
#define VOODOO_RevertToHitPlayerNerf \
               write_byte(0x4244ED, 0xEB)

// This will change the skill bonus from survivalist perk to 0.
// The bonus for all perk ranks is applied via gl_survivalist.ssl script.
// #define VOODOO_survivalist_bonus \
//               write_byte(0x496FAB, 0)

// This will change the skill bonus from Mr. Fixit perk to 20%.
// In Fo2, the perk gives only +10%, while in Fo1 it is +20%.
// #define VOODOO_mr_fixit_bonus \
//               write_byte(0x496E00, 20)

// In Fo2, the perk gives a +20% light level increase, while in Fo1 it is only +10%.
#define VOODOO_night_vision_bonus \
               begin                                        \
                write_short(0x47A91D, 0xC069);              \
                write_int(0x47A91F, 6553);                  \
                call VOODOO_WriteNop(0x47A923, 15, true);   \
               end                                          \
               noop

// This will change the credits and wordlmap music tracks, so that
// the HQ music pack will not overwrite the Fo1 music with Fo2 tracks.
/*
#define VOODOO_fo1_music \
               write_string(0x501A40, "maybe"); \
               write_string(0x50F790, "03WORLD")
*/

// This will change the resting strings in the PIPBOY.MSG to start at 320.
// This is used in combination with VOODOO_rest_till_0600 to change the resting times.
#define VOODOO_rest_strings \
               write_int(0x499746, 320)

// This changes the animated head reaction values. See modreact.h for more details.
#define VOODOO_talking_head_mood \
               write_byte(0x4A29F5, 25); \
               write_byte(0x4A2A0D, 75)

// This will shut down the game and not just send the player back to the main menu
/*
#define VOODOO_close_game \
   write_byte(0x481B2A, 0xB8); /* mov eax, 27 (ESC key input) */ \
   write_int(0x481B2B, 27); \
   signal_end_game
*/

/////////////////////////////////////////////////// AUTOMAGICK ZONE ///////////////////////////////////////////////////
//
// ALL MANUAL EDITS BETWEEN "sfall-asm:code-begin" AND "sfall-asm:code-end" COMMENTS WILL BE LOST
//
// sfall-asm:code-begin //

// Disables the "Encounter! Investigate?" dialog
#define VOODOO_disable_encounter_dialog \
              begin                                          \
               write_short(0x4c0b9d, 0x01b0); /* mov al,1 */ \
               call VOODOO_WriteNop(0x4C0B75, 40, true);     \
              end                                            \
              noop

// This will disable the "You encounter: ..." message
#define VOODOO_disable_YouEncounter_message \
              begin                               \
               call VOODOO_BlockCall(0x4c1011);   \
               call VOODOO_BlockCall(0x4c1042);   \
              end                                 \
              noop

// This will replace RoboDog PID with Dogmeat PID in hardcoded list of dogs PIDs; required for woofs and arfs in combat control
#define VOODOO_dogmeat_pm_dialog \
               write_byte(0x444d10, 0x7a)

// Removes the text under green circles on the worldmap
// Used by Classic Worldmap mod
#define VOODOO_remove_circle_name \
              begin                                             \
               /* fallout2.wmInterfaceDrawCircleOverlay+0xD2 */ \
               call VOODOO_WriteNop(0x4c407a);                  \
               /* fallout2.wmInterfaceDrawCircleOverlay+0xEC */ \
               call VOODOO_BlockCall(0x4c4094,6);               \
              end                                               \
              noop

// This will change the rest timer from "wait until 08:00" to "wait until 06:00" like in Fallout 1.
#define VOODOO_rest_till_0600 \
               write_byte(0x4995f3, 0x06)

// sfall-asm:code-end //
//
// ALL MANUAL EDITS BETWEEN "sfall-asm:code-begin" AND "sfall-asm:code-end" COMMENTS WILL BE LOST
//
