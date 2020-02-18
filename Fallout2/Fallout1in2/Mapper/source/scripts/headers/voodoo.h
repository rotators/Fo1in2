#ifndef VOODOO_H
#define VOODOO_H

#include "sfall/sfall.rotators.h"

/**************************************************
 *                                                *
 *       All kinds of unsafe scripting macros     *
 *  Requires AllowUnsafeScripting=1 in ddraw.ini  *
 *                                                *
 **************************************************/

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
#define VOODOO_remove_circle_name \
   /* fallout2.wmInterfaceDrawCircleOverlay+0xD2 */            \
   write_byte (0x4c407a, 0x90);       /* nop */                \
   /* fallout2.wmInterfaceDrawCircleOverlay+0xEC */            \
   write_int  (0x4c4094, 0x90909090); /* nop; nop; nop; nop */ \
   write_short(0x4c4098, 0x9090)      /* nop; nop */           \

// No radius when a location is revealed on the worldmap
#define VOODOO_location_discover_radius \
   /* _defam */                                                           \
   write_byte (0x41ae05, 0x60);       /* pushad */                        \
   write_int  (0x41ae06, 0x4670a12e); /* mov eax,cs:[4C4670] */           \
   write_short(0x41ae0a, 0x004c);                                         \
   /* Calculate where ddraw.sfall::wmAreaMarkVisitedState_hack+0x51 is */ \
   write_int  (0x41ae0c, 0x4c46c5ba); /* mov edx,fallout2.4C46C5 */       \
   write_byte (0x41ae10, 0x00);                                           \
   write_short(0x41ae11, 0xd001);     /* add eax,edx */                   \
   write_short(0x41ae13, 0xc689);     /* mov esi,eax */                   \
   /* esi is now the address where the radius byte is */                  \
   /* since the memory of the code address is memory protected, */        \
   /* we need to use VirtualProtect to change this */                     \
   write_short(0x41ae15, 0xec83);     /* sub esp,4 */                     \
   write_byte (0x41ae17, 0x04);                                           \
   write_byte (0x41ae18, 0x54);       /* push esp */                      \
   write_short(0x41ae19, 0x406a);     /* push 40 */                       \
   write_short(0x41ae1b, 0x016a);     /* push 1 */                        \
   write_byte (0x41ae1d, 0x50);       /* push eax */                      \
   /* Requires r_fall */                                                  \
   write_int  (0x41ae1e, 0x0415ff2e); /* call cs:[<&VirtualProtect>] */   \
   write_short(0x41ae22, 0x4100);                                         \
   write_byte (0x41ae24, 0x00);                                           \
   write_short(0x41ae25, 0x06c6);     /* mov ds:[esi],0 */                \
   write_byte (0x41ae27, 0x00);                                           \
   write_short(0x41ae28, 0xc483);     /* add esp,4 */                     \
   write_byte (0x41ae2a, 0x04);                                           \
   write_byte (0x41ae2b, 0x61);       /* popad */                         \
   write_byte (0x41ae2c, 0xc3);       /* ret */                           \
   call_offset_v0(0x41ae05)


// Fill_W that works like in Fallout 1
#define VOODOO_fill_w \
   /* wmMarkSubTileRadiusVisited_ */                            \
   write_int  (0x4c3735, 0xf576f5e9); /* jmp fallout2.41AE2F */ \
   write_byte (0x4c3739, 0xff);                                 \
   /* _defam ? */                                               \
   write_short(0x41ae2f, 0x4d75);     /* jne fallout2.41AE7E */ \
   write_short(0x41ae31, 0xec83);     /* sub esp,4 */           \
   write_byte (0x41ae33, 0x04);                                 \
   write_int  (0x41ae34, 0x002404c6); /* mov ss:[esp+4],0 */    \
   write_int  (0x41ae38, 0x0c244c8b); /* mov ecx,ss:[esp+C] */  \
   write_byte (0x41ae3c, 0x49);       /* dec ecx */             \
   write_short(0x41ae3d, 0xf983);     /* cmp ecx,3 */           \
   write_byte (0x41ae3f, 0x03);                                 \
   write_short(0x41ae40, 0x3974);     /* je 0x41AE7E */         \
   write_short(0x41ae42, 0xf983);     /* cmp ecx,7 */           \
   write_byte (0x41ae44, 0x07);                                 \
   write_short(0x41ae45, 0x3474);     /* je 0x41AE7E */         \
   write_short(0x41ae47, 0xf983);     /* cmp ecx,B */           \
   write_byte (0x41ae49, 0x0b);                                 \
   write_short(0x41ae4a, 0x2f74);     /* je 0x41AE7E */         \
   write_short(0x41ae4c, 0xf983);     /* cmp ecx,F */           \
   write_byte (0x41ae4e, 0x0f);                                 \
   write_short(0x41ae4f, 0x2a74);     /* je 0x41AE7E */         \
   write_short(0x41ae51, 0xed31);     /* xor ebp,ebp */         \
   write_int  (0x41ae53, 0x0c244c89); /* mov ss:[esp+C],ecx */  \
   write_short(0x41ae57, 0x026a);     /* push 2 */              \
   write_int  (0x41ae59, 0x1024448b); /* mov eax,ss:[esp+10] */ \
   write_short(0x41ae5d, 0xf189);     /* mov ecx,esi */         \
   write_short(0x41ae5f, 0xfb89);     /* mov ebx,edi */         \
   write_byte (0x41ae61, 0x56);       /* push esi */            \
   write_short(0x41ae62, 0xea89);     /* mov edx,ebp */         \
   write_byte (0x41ae64, 0x45);       /* inc ebp */             \
   write_int  (0x41ae65, 0x0a85cae8); /* call 0x4c3434 */       \
   write_byte (0x41ae69, 0x00);                                 \
   write_short(0x41ae6a, 0xfd83);     /* cmp ebp,7 */           \
   write_byte (0x41ae6c, 0x07);                                 \
   write_short(0x41ae6d, 0xe87c);     /* jl 41AE58 */           \
   write_short(0x41ae6f, 0x048b);     /* mov eax,ss:[esp+4] */  \
   write_byte (0x41ae71, 0x24);                                 \
   write_byte (0x41ae72, 0x40);       /* inc eax */             \
   write_short(0x41ae73, 0xf883);     /* cmp eax,2 */           \
   write_byte (0x41ae75, 0x02);                                 \
   write_short(0x41ae76, 0x0489);     /* mov ss:[esp+4],eax */  \
   write_byte (0x41ae78, 0x24);                                 \
   write_short(0x41ae79, 0xbd7c);     /* jl 41AE39 */           \
   write_short(0x41ae7b, 0xc483);     /* add esp,4 */           \
   write_byte (0x41ae7d, 0x04);                                 \
   write_short(0x41ae7e, 0xc483);     /* add esp,C */           \
   write_byte (0x41ae80, 0x0c);                                 \
   write_int  (0x41ae81, 0x0a88b4e9); /* jmp fallout2.4C373A */ \
   write_byte (0x41ae85, 0x00)

// Fixes the bug where money is not displayed after exiting barter. https://github.com/rotators/Fo1in2/issues/26
#define VOODOO_dialog_money_fix \
   /* gdialog_bk+0x75 */                                                    \
   write_int (0x447acd, 0xfd33b4e9); /* jmp fallout2.41AE86 */              \
   write_byte(0x447ad1, 0xff);                                              \
   write_byte(0x41ae86, 0x60);       /* pushad */                           \
   write_int (0x41ae87, 0x02bea4e8); /* call <fallout2.gdProcessUpdate_> */ \
   write_byte(0x41ae8b, 0x00);                                              \
   write_byte(0x41ae8c, 0x61);       /* popad */                            \
   write_int (0x41ae8d, 0x0bbf1ae8); /* call <fallout2.win_show_> */        \
   write_byte(0x41ae91, 0x00);                                              \
   write_int (0x41ae92, 0x02cc3be9); /* jmp fallout2.447AD2 */              \
   write_byte(0x41ae96, 0x00)

// Used to refresh the game window, including HRP black edges
#define VOODOO_display_win_redraw \
               call_offset_v1(0x4d6f5c,read_int(0x631e4c)) // win_draw_(_display_win)


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
