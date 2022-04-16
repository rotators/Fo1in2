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

// Button sound when clicking on the worldmap for the ultimate Fallout 1 experience.
#define VOODOO_sound_on_wm \
              begin                                                         \
               $addr := VOODOO_Alloc(VOODOO_ID_sound_on_wm_patch, 79);      \
               write_byte ($addr,    0x60);       /* pushad */              \
               call VOODOO_MakeCall($addr+1, 0x004CAAA0);                   \
               write_int  ($addr+6,  0x0000158b); /* mov edx,ds:[530000] */ \
               write_short($addr+10, 0x0053);                               \
               write_short($addr+12, 0xfa83);     /* cmp edx,0 */           \
               write_byte ($addr+14, 0x00);                                 \
               write_short($addr+15, 0x1d74);     /* je 410086 */           \
               write_short($addr+17, 0xfa83);     /* cmp edx,1 */           \
               write_byte ($addr+19, 0x01);                                 \
               write_short($addr+20, 0x2e75);     /* jne 41009C */          \
               write_short($addr+22, 0xf883);     /* cmp eax,0 */           \
               write_byte ($addr+24, 0x00);                                 \
               write_short($addr+25, 0x2975);     /* jne 41009C */          \
               write_int  ($addr+27, 0x503e20b8); /* mov eax,503E20 */      \
               write_byte ($addr+31, 0x00);                                 \
               call VOODOO_MakeCall($addr+32, 0x004519A8);                  \
               write_int  ($addr+37, 0x000005c6); /* mov ds:[530000],0 */   \
               write_short($addr+41, 0x0053);                               \
               write_byte ($addr+43, 0x00);                                 \
               write_short($addr+44, 0x16eb);     /* jmp 41009C */          \
               write_short($addr+46, 0xf883);     /* cmp eax,1 */           \
               write_byte ($addr+48, 0x01);                                 \
               write_short($addr+49, 0x1175);     /* jne 41009C */          \
               write_int  ($addr+51, 0x503e14b8); /* mov eax,503E14 */      \
               write_byte ($addr+55, 0x00);                                 \
               call VOODOO_MakeCall($addr+56, 0x004519A8);                  \
               write_int  ($addr+61, 0x000005c6); /* mov ds:[530000],1 */   \
               write_short($addr+65, 0x0053);                               \
               write_byte ($addr+67, 0x01);                                 \
               write_byte ($addr+68, 0x61);       /* popad */               \
               write_short($addr+69, 0xc501);     /* add ebp,eax */         \
               write_short($addr+71, 0xef83);     /* sub edi,16 */          \
               write_byte ($addr+73, 0x16);                                 \
               call VOODOO_MakeJump($addr+74, 0x004BFE94);                  \
               /* END */                                                    \
               call VOODOO_MakeJump(0x004BFE8F, $addr);                     \
              end                                                           \
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
