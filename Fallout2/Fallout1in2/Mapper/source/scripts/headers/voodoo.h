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

#define VOODOO_ID_sound_on_wm_patch  1

// sfall-asm:defines-end //

#include "sfall/sfall.rotators.h"
#include "debug.h"
#include "voodoo_lib.h"

// This will change the skill bonus from survivalist perk to 0.
// The bonus for all perk ranks is applied via gl_survivalist.ssl script.
#define VOODOO_survivalist_bonus \
               write_byte(0x496FAB, 0)

// This will change the skill bonus from Mr. Fixit perk to 20%.
// In Fo2, the skill gives only +10%, while in Fo1 it is +20%.
#define VOODOO_mr_fixit_bonus \
               write_byte(0x496E00, 20)

// This will change the credits and wordlmap music tracks, so that
// the HQ music pack will not overwrite the Fo1 music with Fo2 tracks.
#define VOODOO_fo1_music \
               write_string(0x501A40, "maybe");    \
               write_string(0x50F790, "03WORLD")

/////////////////////////////////////////////////// AUTOMAGICK ZONE ///////////////////////////////////////////////////
//
// ALL MANUAL EDITS BETWEEN "sfall-asm:code-begin" AND "sfall-asm:code-end" COMMENTS WILL BE LOST
//
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

// Sound when clicking to move on WM, when clicking the player location/hotspot button and inside the town interface.
// See https://www.youtube.com/watch?v=dGZjse7uC_0&t=50m for reference on how it works in the original.
#define VOODOO_sound_on_wm \
              begin                                                                             \
               /* Sound when clicking location/hotspot */                                       \
               $addr := VOODOO_Alloc(VOODOO_ID_sound_on_wm_patch, 119);                         \
               write_byte ($addr,     0x60);       /* pushad */                                 \
               write_int  ($addr+1,   0x503e34b8); /* mov eax,<fallout2.Ib2p1xx1_1> */          \
               write_byte ($addr+5,   0x00);                                                    \
               call VOODOO_MakeCall($addr+6, 0x004519A8);                                       \
               write_int  ($addr+11,  0x000005c6); /* mov ds:[<bool pressed>],1 */              \
               write_short($addr+15,  0x0053);                                                  \
               write_byte ($addr+17,  0x01);                                                    \
               write_byte ($addr+18,  0x61);       /* popad */                                  \
               write_int  ($addr+19,  0x2e90a13e); /* mov eax,ds:[<hotspot2_pic>] */            \
               write_short($addr+23,  0x0067);                                                  \
               call VOODOO_MakeJump($addr+25, 0x4C425C);                                        \
               /* Sound when releasing mouse while clicking location/hotspot */                 \
               write_byte ($addr+30,  0x60);       /* pushad */                                 \
               write_int  ($addr+31,  0x530000a0); /* mov al, ds:[<bool pressed>] */            \
               write_byte ($addr+35,  0x00);                                                    \
               write_short($addr+36,  0x013c);     /* cmp al,1 */                               \
               write_short($addr+38,  0x1175);     /* jne <exit> */                             \
               write_int  ($addr+40,  0x503e40b8); /* mov eax,<fallout2.Ib2lu1x1_1> */          \
               write_byte ($addr+44,  0x00);                                                    \
               call VOODOO_MakeCall($addr+45, 0x004519A8);                                      \
               write_int  ($addr+50,  0x000005c6); /* mov ds:[<bool pressed>],0 */              \
               write_short($addr+54,  0x0053);                                                  \
               write_byte ($addr+56,  0x00);                                                    \
               write_byte ($addr+57,  0x61);       /* popad */                                  \
               write_int  ($addr+58,  0x2e88a13e); /* mov eax,ds:[<hotspot1_pic>] */            \
               write_short($addr+62,  0x0067);                                                  \
               call VOODOO_MakeJump($addr+64, 0x4C425C);                                        \
               /* wmPartyInitWalking_ - sound when clicking on the WM to walk. */               \
               write_byte ($addr+69,  0x60);       /* pushad */                                 \
               write_int  ($addr+70,  0x503e14b8); /* mov eax,<fallout2.Ib1p1xx1_7> */          \
               write_byte ($addr+74,  0x00);                                                    \
               call VOODOO_MakeCall($addr+75, 0x004519A8);                                      \
               write_byte ($addr+80,  0x61);       /* popad */                                  \
               call VOODOO_MakeCall($addr+81, 0x004C1E54);                                      \
               call VOODOO_MakeJump($addr+86, 0x004C02DF);                                      \
               /* Register sound for townmap buttons */                                         \
               write_int  ($addr+91,  0x2dd88789); /* mov ds:[edi+<_wmTownMapButtonId>],eax */  \
               write_short($addr+95,  0x0067);                                                  \
               write_byte ($addr+97,  0x50);       /* push eax */                               \
               write_int  ($addr+98,  0x451990bb); /* mov ebx,<fallout2.gsound_med_butt_rele */ \
               write_byte ($addr+102, 0x00);                                                    \
               write_int  ($addr+103, 0x451988ba); /* mov edx,<fallout2.gsound_med_butt_pres */ \
               write_byte ($addr+107, 0x00);                                                    \
               call VOODOO_MakeCall($addr+108, 0x004D87F8);                                     \
               write_byte ($addr+113, 0x58);       /* pop eax */                                \
               call VOODOO_MakeJump($addr+114, 0x004C4B9A);                                     \
               call VOODOO_MakeJump(0x4C4257, $addr);                                           \
               call VOODOO_MakeJump(0x4C4250, $addr+30);                                        \
               call VOODOO_MakeJump(0x4C02DA, $addr+69);                                        \
               call VOODOO_MakeJump(0x4C4B94, $addr+91);                                        \
               write_byte (0x4C4B99, 0x90);                                                     \
               /* END */                                                                        \
              end                                                                               \
              noop

// sfall-asm:code-end //
//
// ALL MANUAL EDITS BETWEEN "sfall-asm:code-begin" AND "sfall-asm:code-end" COMMENTS WILL BE LOST
//
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
