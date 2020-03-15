#ifndef VOODOO_H
#define VOODOO_H

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

// Used to refresh the game window, including HRP black edges
#define VOODOO_display_win_redraw \
               call_offset_v1(0x4d6f5c,read_int(0x631e4c)) // win_draw_(_display_win)


/////////////////////////////////////////////////// AUTOMAGICK ZONE ///////////////////////////////////////////////////
// sfall-asm:code-begin //

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


////////////////////////////////////////////////////// TEST ZONE //////////////////////////////////////////////////////


// This will make screeenshot without interface and cursor
// recommended: f2_res.ini->[IFACE]->IFACE_BAR_MODE=1,
//              f2_res.ini->[IFACE]->IFACE_BAR_SIDE_ART=0
// ---
// hidemouse/showmouse only ... DON'T! hidemouse doesn't work until cursor is over interface or player is on worldmap
// tap_key(DIK_F12) ... DON'T! doesn't work with compact keyboards (Fn + other key required to "press" F12)
#define VOODOO_clean_screenshot \
               if(get_game_mode bwand 0x1) then                          \
                  hidemouse;                                             \
               else                                                      \
               begin                                                     \
                  intface_hide;                                          \
                  call_offset_v0(0x44ce34);      /* gmouse_3d_off_ */    \
               end                                                       \
               call_offset_v0(0x4dc65c);         /* win_debug_delete_ */ \
               call_offset_v0(0x4c8f4c);         /* dump_screen_ */      \
               if(get_game_mode bwand 0x1) then                          \
                  showmouse;                                             \
               else                                                      \
               begin                                                     \
                  call_offset_v0(0x44cd2c);      /* gmouse_3d_on_ */     \
                  intface_show;                                          \
               end                                                       \
               noop

// This will make screenshots saved in "screen" directory
// HRP required
// sfall-rotators required (sfall cannot patch HRP from scripts)
// ---
// strings are arguments for sprintf(), results are passed to hrp_fopen(); see 0x1001a8e0
// strings cannot be longer than 16b (including trailing "\0")
// directory must exist, HRP/engine won't create it on their own
// --
// hrp_fopen    = 0x1002966a
// hrp_scrnameR = 0x100397bc used when selecting screenshot name
// hrp_scrnameW = 0x100397d0 used when creating screenshot file
#define VOODOO_subdirectory_screenshots \
               r_write_string(r_hrp_offset(0x100397bc), "screen/%.5d.bmp"); \
               r_write_string(r_hrp_offset(0x100397d0), "screen/%.5d.bmp")


////////////////////////////////////////////////////// DANGER ZONE //////////////////////////////////////////////////////


#define VOODOO_ERROR_READ   r_write_byte(read_byte(-1),0)
#define VOODOO_ERROR_WRITE  r_write_byte(-1,0)
#define VOODOO_ERROR_RING0  r_call_offset(0x410003)

#endif // VOODOO_H //
