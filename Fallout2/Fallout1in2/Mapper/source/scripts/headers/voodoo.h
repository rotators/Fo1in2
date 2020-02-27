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
variable addr;

// sfall-asm:defines-begin //

#define VOODOO_SafeMemSet__patch    0x480ee4
#define VOODOO_SafeWrite8___patch   0x480f0d
#define VOODOO_SafeWrite16___patch  0x480f2f
#define VOODOO_SafeWrite32___patch  0x480f52
#define VOODOO_CalcHook__patch      0x480f74

// sfall-asm:defines-end //

#include "sfall/sfall.rotators.h"
#include "debug.h"
#include "voodoo_lib.h"

// Clears memory area at given address by filling it with NOP instructions
#define VOODOO_CAVE(address, length) \
               call_offset_v3(VOODOO_SafeMemSet__patch, address, 0x90, length)

// Used to refresh the game window, including HRP black edges
#define VOODOO_display_win_redraw \
               call_offset_v1(0x4d6f5c,read_int(0x631e4c)) // win_draw_(_display_win)


/////////////////////////////////////////////////// AUTOMAGICK ZONE ///////////////////////////////////////////////////
// sfall-asm:code-begin //

// https://github.com/phobos2077/sfall/issues/285
#define VOODOO_SafeMemSet \
              begin                                                                            \
               write_byte (0x480ee4, 0x52);       /* push edx   - int num (bytes) */           \
               write_byte (0x480ee5, 0x53);       /* push ebx   - uint8 value */               \
               write_byte (0x480ee6, 0x50);       /* push eax   - void* ptr */                 \
               write_byte (0x480ee7, 0x57);       /* push edi */                               \
               write_short(0x480ee8, 0xec83);     /* sub esp,4  - DWORD oldProtect; */         \
               write_byte (0x480eea, 0x04);                                                    \
               write_byte (0x480eeb, 0x54);       /* push esp   - &oldProtect */               \
               write_short(0x480eec, 0x406a);     /* push 40    - PAGE_EXECUTE_READWRITE */    \
               write_byte (0x480eee, 0x53);       /* push ebx   - int num (bytes) */           \
               write_byte (0x480eef, 0x50);       /* push eax   - void* ptr */                 \
               write_int  (0x480ef0, 0x1815ff2e); /* call cs:[<&fallout2.VirtualProtect>] */   \
               write_short(0x480ef4, 0x6c02);                                                  \
               write_byte (0x480ef6, 0x00);                                                    \
               write_short(0x480ef7, 0xc483);     /* add esp,4 */                              \
               write_byte (0x480ef9, 0x04);                                                    \
               write_int  (0x480efa, 0x08244c8b); /* mov ecx,ss:[esp+0x8] - int num (bytes) */ \
               write_int  (0x480efe, 0x0c24448a); /* mov al, ss:[esp+0xC] - uint8 value */     \
               write_int  (0x480f02, 0x04247c8b); /* mov edi,ss:[esp+0x4] - void* ptr */       \
               write_short(0x480f06, 0xaaf3);     /* rep stosb */                              \
               write_byte (0x480f08, 0x5f);       /* pop edi */                                \
               write_byte (0x480f09, 0x58);       /* pop eax */                                \
               write_byte (0x480f0a, 0x5b);       /* pop ebx */                                \
               write_byte (0x480f0b, 0x5a);       /* pop edx */                                \
               write_byte (0x480f0c, 0xc3);       /* ret */                                    \
              end                                                                              \
              noop

#define VOODOO_codecave_selfrun \
              begin                                                                     \
               /* ignore CTRL+R on main screen */                                       \
               write_short(0x480c90, 0x6666);     /* nop */                             \
               write_byte (0x480c92, 0x90);                                             \
               write_short(0x480c93, 0xff33);     /* xor edi,edi */                     \
               /* ignore main_selfrun_exit_ on closing game */                          \
               write_int  (0x480ca2, 0x66666666); /* nop */                             \
               write_byte (0x480ca6, 0x90);                                             \
               /* clear main_selfrun_init_, main_selfrun_exit_, main_selfrun_record_ */ \
               /* skips area occupied by SafeMemSet */                                  \
               VOODOO_CAVE(0x480f0d, 397);                                              \
              end                                                                       \
              noop

// https://github.com/phobos2077/sfall/issues/288
#define VOODOO_SafeWrite8_ \
              begin                                                                          \
               write_byte (0x480f0d, 0x52);       /* push edx   - int8 value */              \
               write_byte (0x480f0e, 0x50);       /* push eax   - void* ptr */               \
               write_short(0x480f0f, 0xec83);     /* sub esp,4  - DWORD oldProtect; */       \
               write_byte (0x480f11, 0x04);                                                  \
               write_byte (0x480f12, 0x54);       /* push esp   - &oldProtect */             \
               write_short(0x480f13, 0x406a);     /* push 40    - PAGE_EXECUTE_READWRITE */  \
               write_short(0x480f15, 0x016a);     /* push 1     - byte */                    \
               write_byte (0x480f17, 0x50);       /* push eax   - void* ptr */               \
               write_int  (0x480f18, 0x1815ff2e); /* call cs:[<&fallout2.VirtualProtect>] */ \
               write_short(0x480f1c, 0x6c02);                                                \
               write_byte (0x480f1e, 0x00);                                                  \
               write_short(0x480f1f, 0xc483);     /* add esp,4 */                            \
               write_byte (0x480f21, 0x04);                                                  \
               write_int  (0x480f22, 0x0424448b); /* mov eax,ss:[esp+4] */                   \
               write_int  (0x480f26, 0x0024548b); /* mov edx,ss:[esp] */                     \
               write_short(0x480f2a, 0x0288);     /* mov ds:[edx],al */                      \
               write_byte (0x480f2c, 0x58);       /* pop eax */                              \
               write_byte (0x480f2d, 0x5a);       /* pop edx */                              \
               write_byte (0x480f2e, 0xc3);       /* ret */                                  \
              end                                                                            \
              noop

// https://github.com/phobos2077/sfall/issues/288
#define VOODOO_SafeWrite16_ \
              begin                                                                          \
               write_byte (0x480f2f, 0x52);       /* push edx   - int16 value */             \
               write_byte (0x480f30, 0x50);       /* push eax   - void* ptr */               \
               write_short(0x480f31, 0xec83);     /* sub esp,4  - DWORD oldProtect; */       \
               write_byte (0x480f33, 0x04);                                                  \
               write_byte (0x480f34, 0x54);       /* push esp   - &oldProtect */             \
               write_short(0x480f35, 0x406a);     /* push 40    - PAGE_EXECUTE_READWRITE */  \
               write_short(0x480f37, 0x026a);     /* push 2     - 2 bytes */                 \
               write_byte (0x480f39, 0x50);       /* push eax   - void* ptr */               \
               write_int  (0x480f3a, 0x1815ff2e); /* call cs:[<&fallout2.VirtualProtect>] */ \
               write_short(0x480f3e, 0x6c02);                                                \
               write_byte (0x480f40, 0x00);                                                  \
               write_short(0x480f41, 0xc483);     /* add esp,4 */                            \
               write_byte (0x480f43, 0x04);                                                  \
               write_int  (0x480f44, 0x0424448b); /* mov eax,ss:[esp+4] */                   \
               write_int  (0x480f48, 0x0024548b); /* mov edx,ss:[esp] */                     \
               write_short(0x480f4c, 0x8966);     /* mov ds:[edx],ax */                      \
               write_byte (0x480f4e, 0x02);                                                  \
               write_byte (0x480f4f, 0x58);       /* pop eax */                              \
               write_byte (0x480f50, 0x5a);       /* pop edx */                              \
               write_byte (0x480f51, 0xc3);       /* ret */                                  \
              end                                                                            \
              noop

// https://github.com/phobos2077/sfall/issues/288
#define VOODOO_SafeWrite32_ \
              begin                                                                          \
               write_byte (0x480f52, 0x52);       /* push edx   - int32 value */             \
               write_byte (0x480f53, 0x50);       /* push eax   - void* ptr */               \
               write_short(0x480f54, 0xec83);     /* sub esp,4  - DWORD oldProtect; */       \
               write_byte (0x480f56, 0x04);                                                  \
               write_byte (0x480f57, 0x54);       /* push esp   - &oldProtect */             \
               write_short(0x480f58, 0x406a);     /* push 40    - PAGE_EXECUTE_READWRITE */  \
               write_short(0x480f5a, 0x046a);     /* push 4     - 4 bytes */                 \
               write_byte (0x480f5c, 0x50);       /* push eax   - void* ptr */               \
               write_int  (0x480f5d, 0x1815ff2e); /* call cs:[<&fallout2.VirtualProtect>] */ \
               write_short(0x480f61, 0x6c02);                                                \
               write_byte (0x480f63, 0x00);                                                  \
               write_short(0x480f64, 0xc483);     /* add esp,4 */                            \
               write_byte (0x480f66, 0x04);                                                  \
               write_int  (0x480f67, 0x0424448b); /* mov eax,ss:[esp+4] */                   \
               write_int  (0x480f6b, 0x0024548b); /* mov edx,ss:[esp] */                     \
               write_short(0x480f6f, 0x0289);     /* mov ds:[edx],eax */                     \
               write_byte (0x480f71, 0x58);       /* pop eax */                              \
               write_byte (0x480f72, 0x5a);       /* pop edx */                              \
               write_byte (0x480f73, 0xc3);       /* ret */                                  \
              end                                                                            \
              noop

#define VOODOO_CalcHook \
              begin                                                  \
               write_short(0x480f74, 0x8b2e); /* mov esi,cs:[eax] */ \
               write_byte (0x480f76, 0x30);                          \
               write_short(0x480f77, 0xd001); /* add eax,edx */      \
               write_short(0x480f79, 0xf001); /* add eax,esi */      \
               write_short(0x480f7b, 0xc083); /* add eax,4 */        \
               write_byte (0x480f7d, 0x04);                          \
               write_byte (0x480f7e, 0xc3);   /* ret */              \
              end                                                    \
              noop

// Fill_W that works like in Fallout 1
// https://github.com/rotators/Fo1in2/issues/16
// https://github.com/phobos2077/sfall/issues/287
#define VOODOO_fill_w \
              begin                                                                      \
               /* fill_w implementation */                                               \
               /* malloc(patch) - this code can be used with --malloc */                 \
               addr := VOODOO_nmalloc(87);                                               \
               debug("Allocated 87 bytes @ "+ addr);                                     \
               call VOODOO_SafeWrite16(addr+0, 0x4d75);       /* jne _ret */             \
               call VOODOO_SafeWrite16(addr+2, 0xec83);       /* sub esp,4 */            \
               call VOODOO_SafeWrite8 (addr+4, 0x04);                                    \
               call VOODOO_SafeWrite32(addr+5, 0x002404c6);   /* mov ss:[esp+4],0 */     \
               /* _loop_begin */                                                         \
               call VOODOO_SafeWrite32(addr+9, 0x0c244c8b);   /* mov ecx,ss:[esp+C] */   \
               /* move to the next tile to the left */                                   \
               call VOODOO_SafeWrite8 (addr+13, 0x49);        /* dec ecx */              \
               /* the comparison checks are to see if the tile we are currently on is */ \
               /* one of the tiles on the right side of the wm (3, 7, 11 or 15) */       \
               /* if it is, it means we've wrapped around */                             \
               call VOODOO_SafeWrite16(addr+14, 0xf983);      /* cmp ecx,3 */            \
               call VOODOO_SafeWrite8 (addr+16, 0x03);                                   \
               call VOODOO_SafeWrite16(addr+17, 0x3974);      /* je _end */              \
               call VOODOO_SafeWrite16(addr+19, 0xf983);      /* cmp ecx,7 */            \
               call VOODOO_SafeWrite8 (addr+21, 0x07);                                   \
               call VOODOO_SafeWrite16(addr+22, 0x3474);      /* je _end */              \
               call VOODOO_SafeWrite16(addr+24, 0xf983);      /* cmp ecx,B */            \
               call VOODOO_SafeWrite8 (addr+26, 0x0b);                                   \
               call VOODOO_SafeWrite16(addr+27, 0x2f74);      /* je _end */              \
               call VOODOO_SafeWrite16(addr+29, 0xf983);      /* cmp ecx,F */            \
               call VOODOO_SafeWrite8 (addr+31, 0x0f);                                   \
               call VOODOO_SafeWrite16(addr+32, 0x2a74);      /* je _end */              \
               call VOODOO_SafeWrite16(addr+34, 0xed31);      /* xor ebp,ebp */          \
               call VOODOO_SafeWrite32(addr+36, 0x0c244c89);  /* mov ss:[esp+C],ecx */   \
               /* _reveal_subtile */                                                     \
               call VOODOO_SafeWrite16(addr+40, 0x026a);      /* push 2 */               \
               call VOODOO_SafeWrite32(addr+42, 0x1024448b);  /* mov eax,ss:[esp+10] */  \
               call VOODOO_SafeWrite16(addr+46, 0xf189);      /* mov ecx,esi */          \
               call VOODOO_SafeWrite16(addr+48, 0xfb89);      /* mov ebx,edi */          \
               call VOODOO_SafeWrite8 (addr+50, 0x56);        /* push esi */             \
               call VOODOO_SafeWrite16(addr+51, 0xea89);      /* mov edx,ebp */          \
               call VOODOO_SafeWrite8 (addr+53, 0x45);        /* inc ebp */              \
               call VOODOO_MakeCall(addr+54, 0x4c3434);                                  \
               /* did we uncover all the subtiles in the tile? */                        \
               /* if not, go to _reveal_subtile and uncover another one */               \
               call VOODOO_SafeWrite16(addr+59, 0xfd83);      /* cmp ebp,7 */            \
               call VOODOO_SafeWrite8 (addr+61, 0x07);                                   \
               call VOODOO_SafeWrite16(addr+62, 0xe87c);      /* jl _reveal_subtile */   \
               call VOODOO_SafeWrite16(addr+64, 0x048b);      /* mov eax,ss:[esp+4] */   \
               call VOODOO_SafeWrite8 (addr+66, 0x24);                                   \
               call VOODOO_SafeWrite8 (addr+67, 0x40);        /* inc eax */              \
               call VOODOO_SafeWrite16(addr+68, 0xf883);      /* cmp eax,2 */            \
               call VOODOO_SafeWrite8 (addr+70, 0x02);                                   \
               call VOODOO_SafeWrite16(addr+71, 0x0489);      /* mov ss:[esp+4],eax */   \
               call VOODOO_SafeWrite8 (addr+73, 0x24);                                   \
               call VOODOO_SafeWrite16(addr+74, 0xbd7c);      /* jl _loop_begin */       \
               /* _end */                                                                \
               call VOODOO_SafeWrite16(addr+76, 0xc483);      /* add esp,4 */            \
               call VOODOO_SafeWrite8 (addr+78, 0x04);                                   \
               /* _ret */                                                                \
               call VOODOO_SafeWrite16(addr+79, 0xc483);      /* add esp,C */            \
               call VOODOO_SafeWrite8 (addr+81, 0x0c);                                   \
               call VOODOO_MakeJump(addr+82, 0x4c373a);                                  \
               /* END */                                                                 \
               /* Hook in wmMarkSubTileRadiusVisited_ */                                 \
               call VOODOO_MakeJump(0x004C3735, addr);                                   \
              end                                                                        \
              noop

// No radius when a location is revealed on the worldmap
// Modifies sfall code
// https://github.com/phobos2077/sfall/issues/255
#define VOODOO_location_discover_radius \
              begin                                                                                   \
               debug("Applying location_discover_radius");                                            \
               /* Calculate where ddraw.sfall::wmAreaMarkVisitedState_hack+0x51 and write 0 to it. */ \
               call VOODOO_SafeWrite8(VOODOO_GetHookFuncOffset(0x4C4670, 0x51), 0x0);                 \
               debug("Done.");                                                                        \
              end                                                                                     \
              noop

// This will disable the "You encounter: ..." message
#define VOODOO_disable_YouEncounter_message \
              begin                             \
               call VOODOO_BlockCall(0x4c1011);   \
               call VOODOO_BlockCall(0x4c1042);   \
              end                               \
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
