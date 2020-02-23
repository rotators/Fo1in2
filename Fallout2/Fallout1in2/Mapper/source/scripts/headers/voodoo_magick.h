#ifndef VOODOO_MAGICK_H
#define VOODOO_MAGICK_H

// Generated automagically -- DO NOT EDIT //

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

// No radius when a location is revealed on the worldmap
// Modifies sfall code
#define VOODOO_location_discover_radius \
              begin                                                                          \
               debug("Writing location_discover_radius patch to 0x480f0d.");                 \
               write_byte (0x480f0d, 0x60);       /* pushad */                               \
               write_int  (0x480f0e, 0x4670a12e); /* mov eax,cs:[4C4670] */                  \
               write_short(0x480f12, 0x004c);                                                \
               /* Calculate where ddraw.sfall::wmAreaMarkVisitedState_hack+0x51 is */        \
               write_int  (0x480f14, 0x4c46c5ba); /* mov edx,fallout2.4C46C5 */              \
               write_byte (0x480f18, 0x00);                                                  \
               write_short(0x480f19, 0xd001);     /* add eax,edx */                          \
               write_short(0x480f1b, 0xc689);     /* mov esi,eax */                          \
               /* esi is now the address where the radius byte is */                         \
               /* since the memory of the code address is read-only protected, */            \
               /* we need to use VirtualProtect to change this */                            \
               write_short(0x480f1d, 0xec83);     /* sub esp,4 */                            \
               write_byte (0x480f1f, 0x04);                                                  \
               write_byte (0x480f20, 0x54);       /* push esp */                             \
               write_short(0x480f21, 0x406a);     /* push 40 */                              \
               write_short(0x480f23, 0x016a);     /* push 1 */                               \
               write_byte (0x480f25, 0x50);       /* push eax */                             \
               write_int  (0x480f26, 0x1815ff2e); /* call cs:[<&fallout2.VirtualProtect>] */ \
               write_short(0x480f2a, 0x6c02);                                                \
               write_byte (0x480f2c, 0x00);                                                  \
               write_short(0x480f2d, 0x06c6);     /* mov ds:[esi],0 */                       \
               write_byte (0x480f2f, 0x00);                                                  \
               write_short(0x480f30, 0xc483);     /* add esp,4 */                            \
               write_byte (0x480f32, 0x04);                                                  \
               write_byte (0x480f33, 0x61);       /* popad */                                \
               write_byte (0x480f34, 0xc3);       /* ret */                                  \
               call_offset_v0(0x480f0d);                                                     \
               debug("Done.");                                                               \
              end                                                                            \
              noop

// Fill_W that works like in Fallout 1
// https://github.com/rotators/Fo1in2/issues/16
#define VOODOO_fill_w \
              begin                                                                         \
               /* wmMarkSubTileRadiusVisited_ */                                            \
               write_int  (0x4c3735, 0xfbd7fbe9); /* jmp [patch] */                         \
               write_byte (0x4c3739, 0xff);                                                 \
               /* fill_w implementation */                                                  \
               write_short(0x480f35, 0x4d75);     /* jne _ret */                            \
               write_short(0x480f37, 0xec83);     /* sub esp,4 */                           \
               write_byte (0x480f39, 0x04);                                                 \
               write_int  (0x480f3a, 0x002404c6); /* mov ss:[esp+4],0 */                    \
               /* _loop_begin */                                                            \
               write_int  (0x480f3e, 0x0c244c8b); /* mov ecx,ss:[esp+C] */                  \
               /* move to the next tile to the left */                                      \
               write_byte (0x480f42, 0x49);       /* dec ecx */                             \
               /* the comparison checks are to see if the tile we are currently on is */    \
               /* one of the tiles on the right side of the wm (3, 7, 11 or 15) */          \
               /* if it is, it means we've wrapped around */                                \
               write_short(0x480f43, 0xf983);     /* cmp ecx,3 */                           \
               write_byte (0x480f45, 0x03);                                                 \
               write_short(0x480f46, 0x3974);     /* je _end */                             \
               write_short(0x480f48, 0xf983);     /* cmp ecx,7 */                           \
               write_byte (0x480f4a, 0x07);                                                 \
               write_short(0x480f4b, 0x3474);     /* je _end */                             \
               write_short(0x480f4d, 0xf983);     /* cmp ecx,B */                           \
               write_byte (0x480f4f, 0x0b);                                                 \
               write_short(0x480f50, 0x2f74);     /* je _end */                             \
               write_short(0x480f52, 0xf983);     /* cmp ecx,F */                           \
               write_byte (0x480f54, 0x0f);                                                 \
               write_short(0x480f55, 0x2a74);     /* je _end */                             \
               write_short(0x480f57, 0xed31);     /* xor ebp,ebp */                         \
               write_int  (0x480f59, 0x0c244c89); /* mov ss:[esp+C],ecx */                  \
               /* _reveal_subtile */                                                        \
               write_short(0x480f5d, 0x026a);     /* push 2 */                              \
               write_int  (0x480f5f, 0x1024448b); /* mov eax,ss:[esp+10] */                 \
               write_short(0x480f63, 0xf189);     /* mov ecx,esi */                         \
               write_short(0x480f65, 0xfb89);     /* mov ebx,edi */                         \
               write_byte (0x480f67, 0x56);       /* push esi */                            \
               write_short(0x480f68, 0xea89);     /* mov edx,ebp */                         \
               write_byte (0x480f6a, 0x45);       /* inc ebp */                             \
               write_int  (0x480f6b, 0x0424c4e8); /* call wmMarkSubTileOffsetVisitedFunc */ \
               write_byte (0x480f6f, 0x00);                                                 \
               /* did we uncover all the subtiles in the tile? */                           \
               /* if not, go to _reveal_subtile and uncover another one */                  \
               write_short(0x480f70, 0xfd83);     /* cmp ebp,7 */                           \
               write_byte (0x480f72, 0x07);                                                 \
               write_short(0x480f73, 0xe87c);     /* jl _reveal_subtile */                  \
               write_short(0x480f75, 0x048b);     /* mov eax,ss:[esp+4] */                  \
               write_byte (0x480f77, 0x24);                                                 \
               write_byte (0x480f78, 0x40);       /* inc eax */                             \
               write_short(0x480f79, 0xf883);     /* cmp eax,2 */                           \
               write_byte (0x480f7b, 0x02);                                                 \
               write_short(0x480f7c, 0x0489);     /* mov ss:[esp+4],eax */                  \
               write_byte (0x480f7e, 0x24);                                                 \
               write_short(0x480f7f, 0xbd7c);     /* jl _loop_begin */                      \
               /* _end */                                                                   \
               write_short(0x480f81, 0xc483);     /* add esp,4 */                           \
               write_byte (0x480f83, 0x04);                                                 \
               /* _ret */                                                                   \
               write_short(0x480f84, 0xc483);     /* add esp,C */                           \
               write_byte (0x480f86, 0x0c);                                                 \
               write_int  (0x480f87, 0x0427aee9); /* jmp fallout2.4C373A */                 \
               write_byte (0x480f8b, 0x00);                                                 \
              end                                                                           \
              noop

// This will change the rest timer "wait until 08:00" to 06:00 like in Fallout 1.
#define VOODOO_rest_till_0600 \
               write_byte(0x4995f3, 0x06)

// This will replace RoboDog PID with Dogmeat PID in hardcoded list of dogs PIDs; required for woofs and arfs in combat control
#define VOODOO_dogmeat_pm_dialog \
               write_byte(0x444d10, 0x7a)

// Removes the text under green circles on the worldmap
// Used by Classic Worldmap mod
#define VOODOO_remove_circle_name \
              begin                                                        \
               /* fallout2.wmInterfaceDrawCircleOverlay+0xD2 */            \
               write_byte (0x4c407a, 0x90);       /* nop */                \
               /* fallout2.wmInterfaceDrawCircleOverlay+0xEC */            \
               write_int  (0x4c4094, 0x90909090); /* nop; nop; nop; nop */ \
               write_short(0x4c4098, 0x9090);     /* nop; nop */           \
              end                                                          \
              noop


#endif // VOODOO_MAGICK_H //
