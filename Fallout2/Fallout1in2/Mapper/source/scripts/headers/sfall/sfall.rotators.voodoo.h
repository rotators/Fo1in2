#pragma once

//#include "sfall.rotators.h"

variable r_call_offset_result;

#define r_call_offset0(addr) \
        r_call_offset_result := r_call_offset(addr)

#define r_call_offset1(addr,arg1) \
        r_call_offset_push(arg1); \
        r_call_offset_result := r_call_offset(addr)

#define r_call_offset2(addr,arg1,arg2) \
        r_call_offset_push(arg1); \
        r_call_offset_push(arg2); \
        r_call_offset_result := r_call_offset(addr)

#define r_call_offset3(addr,arg1,arg2,arg3) \
        r_call_offset_push(arg1); \
        r_call_offset_push(arg2); \
        r_call_offset_push(arg3); \
        r_call_offset_result := r_call_offset(addr)

#define r_call_offset4(addr,arg1,arg2,arg3,arg4) \
        r_call_offset_push(arg1); \
        r_call_offset_push(arg2); \
        r_call_offset_push(arg3); \
        r_call_offset_push(arg4); \
        r_call_offset_result := r_call_offset(addr)

#define r_call_offset5(addr,arg1,arg2,arg3,arg4,arg5) \
        r_call_offset_push(arg1); \
        r_call_offset_push(arg2); \
        r_call_offset_push(arg3); \
        r_call_offset_push(arg4); \
        r_call_offset_push(arg5); \
        r_call_offset_result := r_call_offset(addr)

#define r_call_offset6(addr,arg1,arg2,arg3,arg4,arg5,arg6) \
        r_call_offset_push(arg1); \
        r_call_offset_push(arg2); \
        r_call_offset_push(arg3); \
        r_call_offset_push(arg4); \
        r_call_offset_push(arg5); \
        r_call_offset_push(arg6); \
        r_call_offset_result := r_call_offset(addr)

#define r_call_offset7(addr,arg1,arg2,arg3,arg4,arg5,arg6,arg7) \
        r_call_offset_push(arg1); \
        r_call_offset_push(arg2); \
        r_call_offset_push(arg3); \
        r_call_offset_push(arg4); \
        r_call_offset_push(arg5); \
        r_call_offset_push(arg6); \
        r_call_offset_push(arg7); \
        r_call_offset_result := r_call_offset(addr)

#define r_call_offset8(addr,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8) \
        r_call_offset_push(arg1); \
        r_call_offset_push(arg2); \
        r_call_offset_push(arg3); \
        r_call_offset_push(arg4); \
        r_call_offset_push(arg5); \
        r_call_offset_push(arg6); \
        r_call_offset_push(arg7); \
        r_call_offset_push(arg8); \
        r_call_offset_result := r_call_offset(addr)

#define r_call_offset9(addr,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9) \
        r_call_offset_push(arg1); \
        r_call_offset_push(arg2); \
        r_call_offset_push(arg3); \
        r_call_offset_push(arg4); \
        r_call_offset_push(arg5); \
        r_call_offset_push(arg6); \
        r_call_offset_push(arg7); \
        r_call_offset_push(arg8); \
        r_call_offset_push(arg9); \
        r_call_offset_result := r_call_offset(addr)

#define r_call_offset10(addr,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10) \
        r_call_offset_push(arg1);  \
        r_call_offset_push(arg2);  \
        r_call_offset_push(arg3);  \
        r_call_offset_push(arg4);  \
        r_call_offset_push(arg5);  \
        r_call_offset_push(arg6);  \
        r_call_offset_push(arg7);  \
        r_call_offset_push(arg8);  \
        r_call_offset_push(arg9);  \
        r_call_offset_push(arg10); \
        r_call_offset_result := r_call_offset(addr)

#define r_call_offset11(addr,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11) \
        r_call_offset_push(arg1);  \
        r_call_offset_push(arg2);  \
        r_call_offset_push(arg3);  \
        r_call_offset_push(arg4);  \
        r_call_offset_push(arg5);  \
        r_call_offset_push(arg6);  \
        r_call_offset_push(arg7);  \
        r_call_offset_push(arg8);  \
        r_call_offset_push(arg9);  \
        r_call_offset_push(arg10); \
        r_call_offset_push(arg11); \
        r_call_offset_result := r_call_offset(addr)

#define r_call_offset12(addr,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12) \
        r_call_offset_push(arg1);  \
        r_call_offset_push(arg2);  \
        r_call_offset_push(arg3);  \
        r_call_offset_push(arg4);  \
        r_call_offset_push(arg5);  \
        r_call_offset_push(arg6);  \
        r_call_offset_push(arg7);  \
        r_call_offset_push(arg8);  \
        r_call_offset_push(arg9);  \
        r_call_offset_push(arg10); \
        r_call_offset_push(arg11); \
        r_call_offset_push(arg12); \
        r_call_offset_result := r_call_offset(addr)

#define r_call_offset13(addr,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13) \
        r_call_offset_push(arg1);  \
        r_call_offset_push(arg2);  \
        r_call_offset_push(arg3);  \
        r_call_offset_push(arg4);  \
        r_call_offset_push(arg5);  \
        r_call_offset_push(arg6);  \
        r_call_offset_push(arg7);  \
        r_call_offset_push(arg8);  \
        r_call_offset_push(arg9);  \
        r_call_offset_push(arg10); \
        r_call_offset_push(arg11); \
        r_call_offset_push(arg12); \
        r_call_offset_push(arg13); \
        r_call_offset_result := r_call_offset(addr)

#define r_call_offset14(addr,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13,arg14) \
        r_call_offset_push(arg1);  \
        r_call_offset_push(arg2);  \
        r_call_offset_push(arg3);  \
        r_call_offset_push(arg4);  \
        r_call_offset_push(arg5);  \
        r_call_offset_push(arg6);  \
        r_call_offset_push(arg7);  \
        r_call_offset_push(arg8);  \
        r_call_offset_push(arg9);  \
        r_call_offset_push(arg10); \
        r_call_offset_push(arg11); \
        r_call_offset_push(arg12); \
        r_call_offset_push(arg13); \
        r_call_offset_push(arg14); \
        r_call_offset_result := r_call_offset(addr)

#define r_call_offset15(addr,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13,arg14,arg15) \
        r_call_offset_push(arg1);  \
        r_call_offset_push(arg2);  \
        r_call_offset_push(arg3);  \
        r_call_offset_push(arg4);  \
        r_call_offset_push(arg5);  \
        r_call_offset_push(arg6);  \
        r_call_offset_push(arg7);  \
        r_call_offset_push(arg8);  \
        r_call_offset_push(arg9);  \
        r_call_offset_push(arg10); \
        r_call_offset_push(arg11); \
        r_call_offset_push(arg12); \
        r_call_offset_push(arg13); \
        r_call_offset_push(arg14); \
        r_call_offset_push(arg15); \
        r_call_offset_result := r_call_offset(addr)

#define r_call_offset16(addr,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13,arg14,arg15,arg16) \
        r_call_offset_push(arg1);  \
        r_call_offset_push(arg2);  \
        r_call_offset_push(arg3);  \
        r_call_offset_push(arg4);  \
        r_call_offset_push(arg5);  \
        r_call_offset_push(arg6);  \
        r_call_offset_push(arg7);  \
        r_call_offset_push(arg8);  \
        r_call_offset_push(arg9);  \
        r_call_offset_push(arg10); \
        r_call_offset_push(arg11); \
        r_call_offset_push(arg12); \
        r_call_offset_push(arg13); \
        r_call_offset_push(arg14); \
        r_call_offset_push(arg15); \
        r_call_offset_push(arg16); \
        r_call_offset_result := r_call_offset(addr)
