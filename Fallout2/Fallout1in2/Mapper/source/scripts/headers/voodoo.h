#ifndef VOODOO_H
#define VOODOO_H

#include "sfall/sfall.rotators.h"
#include "voodoo_lib.h"
#include "voodoo_magick.h"

/**************************************************
 *                                                *
 *       All kinds of unsafe scripting macros     *
 *  Requires AllowUnsafeScripting=1 in ddraw.ini  *
 *                                                *
 **************************************************/

// Assumes that VOODOO_SafeMemSet is written at main_selfrun_init_ address
#define VOODOO_CAVE(address, length) \
    call_offset_v3(0x480ee4, address, 0x90, length)

// This will disable the "You encounter: ..." message:
#define VOODOO_disable_YouEncounter_message      \
               write_int( 0x4C1011, 0x90909090); \
               write_byte(0x4C1015, 0x90);       \
               write_int( 0x4C1042, 0x90909090); \
               write_byte(0x4C1046, 0x90)

// Used to refresh the game window, including HRP black edges
#define VOODOO_display_win_redraw \
               call_offset_v1(0x4d6f5c,read_int(0x631e4c)) // win_draw_(_display_win)

// This will create codecave out of few selfrun functions related to .vcr recording
// As creation and hotkey blocking is done by scripts, recording is available *only* before first start/load game
#define VOODOO_codecave_selfrun \
              begin                                                                     \
               /* ignore CTRL+R on main screen */                                       \
               write_short(0x480c90, 0x6666); /* nop */                                 \
               write_byte (0x480c92, 0x90);                                             \
               write_short(0x480c93, 0xff33); /* xor edi,edi */                         \
               /* ignore main_selfrun_exit_ call on game exit */                        \
               write_int  (0x480ca2, 0x66666666); /* nop */                             \
               write_byte (0x480ca6, 0x90);                                             \
               /* clear main_selfrun_init_, main_selfrun_exit_, main_selfrun_record_ */ \
               VOODOO_CAVE(0x480f0d, 397);                                              \
              end                                                                       \
              noop


////////////////////////////////////////////////////// TEST ZONE //////////////////////////////////////////////////////


// This will make screeenshot without interface and cursor
// recommended: f2_res.ini->[IFACE]->IFACE_BAR_MODE=1,
//              f2_res.ini->[IFACE]->IFACE_BAR_SIDE_ART=0
// ---
// hidemouse/showmouse only ... DON'T! hidemouse doesn't work until cursor is over interface or player is on worldmap
// tap_key(DIK_F12) ... DON'T! doesn't work with compact keyboards (Fn + other key required to "press" F12)
#define VOODOO_clean_screenshot \
               if(get_game_mode bwand 0x1) then                  \
                  hidemouse;                                     \
               else                                              \
               begin                                             \
                  intface_hide;                                  \
                  call_offset_v0(0x44ce34); /* gmouse_3d_off_ */ \
               end                                               \
               call_offset_v0(0x4c8f4c);      /* dump_screen_ */ \
               if(get_game_mode bwand 0x1) then                  \
                  showmouse;                                     \
               else                                              \
               begin                                             \
                  call_offset_v0(0x44cd2c);  /* gmouse_3d_on_ */ \
                  intface_show;                                  \
               end                                               \
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
