#pragma once

//
// https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
// https://invisible-island.net/xterm/ctlseqs/ctlseqs.html
// https://vt100.net/docs/vt220-rm/chapter2.html
//
// macros with uppercase names follows terminal(s) documentation one way or another
// macros with lowercase names are made up and tries to be (sic!) more human-friendly
//

// bypasses whiny preprocessor and makes it bit easier to see which parts of long string are ANSI garbage
#define _ANSI(x)                                sprintf("%c", 0x1b) + x

// misc
#define _ANSI_RIS                               _ANSI("c")

// OSC : Operating System Command
#define _ANSI_OSC(cmd,arg)                      _ANSI("]" + cmd + ";" + arg + _ANSI("\\"))
#define _ANSI_window_name(text)                 _ANSI_OSC(2,text)

// CSI : Control Sequence Introducer
#define _ANSI_CSI(x)                            _ANSI("[" + x)
#define _ANSI_SGR(color)                        _ANSI_CSI(color) + "m"  // set <color> and forget
#define _ANSI_color_rgb_set(rf,gf,bf,rb,gb,bb)  _ANSI_SGR("38;2;" + rf + ";" + gf + ";" + bf + "48;2;" + rb + ";" + gb + ";" + bb) // set <rf,gf,bf>,<rb,gb,bb> and forget; order: foreground, background
#define _ANSI_color_rgb_fg_set(r,g,b)           _ANSI_SGR("38;2;" + r + ";" + g + ";" + b)  // set <r,g,b> and forget
#define _ANSI_color_rgb_bg_set(r,g,b)           _ANSI_SGR("48;2;" + r + ";" + g + ";" + b)  // set <r,g,b> and forget

#define _ANSI_color_reset                       _ANSI_SGR(0)  // set foreground/background colors to defaults
#define _ANSI_color(color,text)                 _ANSI_SGR(color) + text + _ANSI_color_reset  // print text with <color> and reset
#define _ANSI_color_set(color)                  _ANSI_SGR(color)  // set <color> and forget
