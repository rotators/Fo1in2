#ifndef VOODOO_H
#define VOODOO_H

#include "sfall/sfall.rotators.h"

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


// Fill_W that works like in Fallout 1
#define VOODOO_fill_w \
   write_byte(0x4c3735, 0xE9); /* jmp fallout2.41AE2F */  \
   write_byte(0x4c3736, 0xF5); \
   write_byte(0x4c3737, 0x76); \
   write_byte(0x4c3738, 0xF5); \
   write_byte(0x4c3739, 0xFF); \
   write_byte(0x41ae2f, 0x75); /* jne fallout2.41AE7E */  \
   write_byte(0x41ae30, 0x4D); \
   write_byte(0x41ae31, 0x83); /* sub esp,4 */  \
   write_byte(0x41ae32, 0xEC); \
   write_byte(0x41ae33, 0x04); \
   write_byte(0x41ae34, 0xC6); /* mov ss:[esp+4],0 */  \
   write_byte(0x41ae35, 0x04); \
   write_byte(0x41ae36, 0x24); \
   write_byte(0x41ae37, 0x00); \
   write_byte(0x41ae38, 0x8B); /* mov ecx,ss:[esp+C] */  \
   write_byte(0x41ae39, 0x4C); \
   write_byte(0x41ae3a, 0x24); \
   write_byte(0x41ae3b, 0x0C); \
   write_byte(0x41ae3c, 0x49); /* dec ecx */  \
   write_byte(0x41ae3d, 0x83); /* cmp ecx,3 */  \
   write_byte(0x41ae3e, 0xF9); \
   write_byte(0x41ae3f, 0x03); \
   write_byte(0x41ae40, 0x74); /* je 0x41AE7E */  \
   write_byte(0x41ae41, 0x39); \
   write_byte(0x41ae42, 0x83); /* cmp ecx,7 */  \
   write_byte(0x41ae43, 0xF9); \
   write_byte(0x41ae44, 0x07); \
   write_byte(0x41ae45, 0x74); /* je 0x41AE7E */  \
   write_byte(0x41ae46, 0x34); \
   write_byte(0x41ae47, 0x83); /* cmp ecx,B */  \
   write_byte(0x41ae48, 0xF9); \
   write_byte(0x41ae49, 0x0B); \
   write_byte(0x41ae4a, 0x74); /* je 0x41AE7E */  \
   write_byte(0x41ae4b, 0x2F); \
   write_byte(0x41ae4c, 0x83); /* cmp ecx,F */  \
   write_byte(0x41ae4d, 0xF9); \
   write_byte(0x41ae4e, 0x0F); \
   write_byte(0x41ae4f, 0x74); /* je 0x41AE7E */  \
   write_byte(0x41ae50, 0x2A); \
   write_byte(0x41ae51, 0x31); /* xor ebp,ebp */  \
   write_byte(0x41ae52, 0xED); \
   write_byte(0x41ae53, 0x89); /* mov ss:[esp+C],ecx */  \
   write_byte(0x41ae54, 0x4C); \
   write_byte(0x41ae55, 0x24); \
   write_byte(0x41ae56, 0x0C); \
   write_byte(0x41ae57, 0x6A); /* push 2 */  \
   write_byte(0x41ae58, 0x02); \
   write_byte(0x41ae59, 0x8B); /* mov eax,ss:[esp+10] */  \
   write_byte(0x41ae5a, 0x44); \
   write_byte(0x41ae5b, 0x24); \
   write_byte(0x41ae5c, 0x10); \
   write_byte(0x41ae5d, 0x89); /* mov ecx,esi */  \
   write_byte(0x41ae5e, 0xF1); \
   write_byte(0x41ae5f, 0x89); /* mov ebx,edi */  \
   write_byte(0x41ae60, 0xFB); \
   write_byte(0x41ae61, 0x56); /* push esi */  \
   write_byte(0x41ae62, 0x89); /* mov edx,ebp */  \
   write_byte(0x41ae63, 0xEA); \
   write_byte(0x41ae64, 0x45); /* inc ebp */  \
   write_byte(0x41ae65, 0xE8); /* call 0x4c3434 */  \
   write_byte(0x41ae66, 0xCA); \
   write_byte(0x41ae67, 0x85); \
   write_byte(0x41ae68, 0x0A); \
   write_byte(0x41ae69, 0x00); \
   write_byte(0x41ae6a, 0x83); /* cmp ebp,7 */  \
   write_byte(0x41ae6b, 0xFD); \
   write_byte(0x41ae6c, 0x07); \
   write_byte(0x41ae6d, 0x7C); /* jl 41AE58 */  \
   write_byte(0x41ae6e, 0xE8); \
   write_byte(0x41ae6f, 0x8B); /* mov eax,ss:[esp+4] */  \
   write_byte(0x41ae70, 0x04); \
   write_byte(0x41ae71, 0x24); \
   write_byte(0x41ae72, 0x40); /* inc eax */  \
   write_byte(0x41ae73, 0x83); /* cmp eax,2 */  \
   write_byte(0x41ae74, 0xF8); \
   write_byte(0x41ae75, 0x02); \
   write_byte(0x41ae76, 0x89); /* mov ss:[esp+4],eax */  \
   write_byte(0x41ae77, 0x04); \
   write_byte(0x41ae78, 0x24); \
   write_byte(0x41ae79, 0x7C); /* jl 41AE39 */  \
   write_byte(0x41ae7a, 0xBD); \
   write_byte(0x41ae7b, 0x83); /* add esp,4 */  \
   write_byte(0x41ae7c, 0xC4); \
   write_byte(0x41ae7d, 0x04); \
   write_byte(0x41ae7e, 0x83); /* add esp,C */  \
   write_byte(0x41ae7f, 0xC4); \
   write_byte(0x41ae80, 0x0C); \
   write_byte(0x41ae81, 0xE9); /* jmp fallout2.4C373A */  \
   write_byte(0x41ae82, 0xB4); \
   write_byte(0x41ae83, 0x88); \
   write_byte(0x41ae84, 0x0A); \
   write_byte(0x41ae85, 0x00)



// This will make screeenshot without interface and cursor
// recommended: f2_res.ini->[IFACE]->IFACE_BAR_MODE=1
#define VOODOO_make_clean_screenshot \
               intface_hide;                                  \
               call_offset_v0(0x44ce34); /* gmouse_3d_off_ */ \
               call_offset_v0(0x4c8f4c); /* dump_screen_   */ \
               call_offset_v0(0x44cd2c); /* gmouse_3d_on_  */ \
               intface_show

// This will make screenshots saved in "screen" directory
// sfall-rotators required (sfall cannot patch HRP from scripts)
// ---
// strings are arguments for sprintf(), results are passed to hrp_fopen() in 0x1001A8e0
// strings cannot be be longer than 16b (including trailing "\0")
// directory must exists, HRP does not checks that
// --
// hrp_fopen    = 0x1002966A
// hrp_scrnameR = 0x100397bc used when selecting screenshot name
// hrp_scrnameW = 0x100397d0 used when creating screenshot file

#define VOODOO_subdirectory_screenshots \
               r_write_string(0x100397bc, "screen/%.5d.bmp); \
               r_write_string(0x100397d0, "screen/%.5d.bmp)

#endif // VOODOO_H //
