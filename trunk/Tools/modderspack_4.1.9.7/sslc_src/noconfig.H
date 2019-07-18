/*
 * noconfig.H
 * Configurations for MCPP not using config.h.
 *
 * WARNING: These are default settings.  To configure for your system, you
 *      must edit this file here and there.
 */

#define TRUE                1
#define FALSE               0

/* Default MBCHAR (multi-byte character) encoding.  */
#define UTF8            0x1000  /* UTF-8 encoding           */

/*
 * MBCHAR means multi-byte character encoding.
 * MBCHAR means the default encoding, and you can change the encoding by
 *      #pragma MCPP setlocale, -e <encoding> option or environment variable
 *      LC_ALL, LC_CTYPE, LANG.
 * MBCHAR == 0 means not to recognize any multi-byte character encoding.
 */

/*
 * In order to predefine target-system-dependent macros,
 * several macros are defined here:
 * *_OLD define the macro beginning with an alphabetic letter,
 * *_STD, *_STD?, *_EXT, *_EXT2 define the macro beginning with an '_'.
 * *_STD1 define the macro beginning with '__' and ending with an alphanumeric
 *      letter.
 * *_STD2 define the macro beginning with '__' and ending with '__'.
 * These may not be defined, if they are not needed.
 * They should not be #defined to no token or to "".
 *
 * SYSTEM_OLD, SYSTEM_STD1, SYSTEM_STD2, SYSTEM_EXT, SYSTEM_EXT2
 *      define the target operating system (by name).
 * SYSTEM_SP_OLD, SYSTEM_SP_STD     define the target-OS specific macro name
 * COMPILER_OLD, COMPILER_STD1, COMPILER_STD2, COMPILER_EXT, COMPILER_EXT2
 *          , COMPILER_SP_OLD, COMPILER_SP_STD
 *      define the target compiler (by name).
 * COMPILER_CPLUS        defines the target C++ compiler.
 * COMPILER_SP1, COMPILER_SP2, COMPILER_SP3
 *      define the compiler-specific macros.
 *
 * <macro>_VAL      specify the value of the <macro>.
 *      If not specified, these values default to "1".
 *      To define the value of no-token, specify as "" rather than no-token.
 * SYSTEM_OLD, SYSTEM_STD?, COMPILER_OLD have the value of "1".
 */

/*
 * target-compiler-dependent definitions:
 *
 * LINE_PREFIX  defines the output line prefix, if not "#line 123".
 *              This should be defined as "# " to represent "# 123" format
 *              ("#line " represents "#line 123" format).
 *
 * C_INCLUDE_DIR1, C_INCLUDE_DIR2   may be defined if you have a compiler-
 *              specific include directory which is to be searched *before*
 *              the operating-system specific directories (e.g. /usr/include).
 * CPLUS_INCLUDE_DIR1, CPLUS_INCLUDE_DIR2, CPLUS_INCLUDE_DIR3
 *      , CPLUS_INCLUDE_DIR4     are for C++ include directory which exist
 *              other than C include directory.
 * ENV_C_INCLUDE_DIR    may be defined to the name of environment-variable for
 *              C include directory.
 * ENV_CPLUS_INCLUDE_DIR    is name of environment-variable for C++ include
 *              directory which exists other than ENV_C_INCLUDE_DIR.
 * ENV_SEP      is the separator (other than space) of include-paths in an
 *              environment-variable.  e.g. the ':' in
 *              "/usr/abc/include:/usr/xyz/include"
 *
 * EMFILE       should be defined to the macro to represent errno of 'too many
 *              open files' if the macro is different from EMFILE.
 *
 * ONE_PASS     should be set TRUE, if COMPILER is "one pass compiler".
 *
 * FNAME_FOLD   means that target-system folds upper and lower cases of
 *              directory and file-name.
 *
 * SEARCH_INIT  specifies the default value of 'search_rule' (in system.c).
 *              'search_rule' holds searching rule of #include "header.h" to
 *              search first before searching user specified or system-
 *              specific include directories.
 *              CURRENT means to search the directory relative to "current
 *              directory" which is current at cpp invocation.
 *              SOURCE means to search the directory relative to that of the
 *              source file (i.e. "includer").
 *              (CURRENT & SOURCE) means to search current directory first
 *              source directory next.
 *              'search_rule' is initialized to SEARCH_INIT.
 */
#define CURRENT             1
#define SOURCE              2

#define SYSTEM_SP_STD       "__FLAT__"
#define SYSTEM_SP_STD_VAL   "1"
#define SJIS_IS_ESCAPE_FREE TRUE    /* or FALSE following your compiler     */
#define LINE_PREFIX         "#line "
#define STD_LINE_PREFIX     TRUE    /* Output #line by C source format      */
#define HAVE_DIGRAPHS       TRUE    /* Output digraphs as it is     */
#define SEARCH_INIT         SOURCE  /* Include directory relative to source */
#define SJIS_IS_ESCAPE_FREE         TRUE    /* Do not treat SJIS specially  */
#define BIGFIVE_IS_ESCAPE_FREE      TRUE    /* Do not treat specially       */
#define ISO2022_JP_IS_ESCAPE_FREE   TRUE    /* Do not treat specially       */
#define TARGET_HAVE_LONG_LONG       TRUE   /* dummy    */
#define STDC_VERSION        199409L /* Initial value of __STDC_VERSION__    */
#define ENV_C_INCLUDE_DIR   "INCLUDE"
#define ENV_CPLUS_INCLUDE_DIR   "CPLUS_INCLUDE"
#define ENV_SEP             ';'
#define ONE_PASS            FALSE
#define FNAME_FOLD          TRUE

/*
 * CHARBIT, UCHARMAX are respectively CHAR_BIT, UCHAR_MAX of target compiler.
 * CHARBIT should be defined to the number of bits per character.
 * It is needed only for processing of multi-byte character constants.
 * UCHARMAX should be defined to the maximum value of type unsigned char
 * or maximum value of unsigned int which is converted from type (signed)
 * char.
 *
 * LONGMAX      should be defined to the LONG_MAX in <limits.h>.
 * ULONGMAX     should be defined to the ULONG_MAX in <limits.h> or LONG_MAX
 *              for the compiler which does not have unsigned long.
 */

#ifndef CHARBIT
#define CHARBIT             8
#endif
#ifndef UCHARMAX
#define UCHARMAX            0xFF
#endif
#ifndef LONGMAX
#define LONGMAX             0x7FFFFFFFL
#endif
#ifndef ULONGMAX
#define ULONGMAX            0xFFFFFFFFUL
#endif

/*
 * SJIS_IS_ESCAPE_FREE means the compiler does not escape '0x5c' ('\\') in
 * shift-JIS encoded multi-byte character.  SJIS_IS_ESCAPE_FREE == FALSE 
 * enables cpp to insert * '\\' before '\\' of the 2nd byte of SJIS code in
 * literal.  This insertion is for the compiler-proper which can't recognize
 * SJIS literal.
 * BIGFIVE_IS_ESCAPE_FREE means similar case on BIGFIVE encoding.
 * ISO2022_JP_IS_ESCAPE_FREE means similar case on ISO2022_JP encoding.
 */
/*
 *      P A R T   2     Configurations for host-compiler.
 *
 *      WARNING: In case of HOST_COMPILER differs from COMPILER, you must
 *          edit here and there of this part.
 */

#define HOST_HAVE_LONG_LONG         TRUE 
#define HAVE_INTMAX_T               FALSE

/*
 * This definitions should be set TRUE, if *both* of the target
 * and the host compilers have long long type.
 */
#if TARGET_HAVE_LONG_LONG && HOST_HAVE_LONG_LONG
#define HAVE_LONG_LONG      TRUE
#endif

/*
 * Define the format specifier of intmax_t or long long for
 * fprintf( fp_debug,).
 * Both of target COMPILER and HOST_COMPILER should have long long.
 */
#if     HAVE_LONG_LONG
#ifndef LL_FORM
#define LL_FORM             "ll"    /* C99: for long long, "j" for intmax_t */
#endif
#endif

#ifndef HOST_HAVE_STPCPY
#define HOST_HAVE_STPCPY            FALSE
#endif

/*
 * Declaration of standard library functions and macros.
 */

/* stdin, stdout, stderr, FILE, NULL, fgets(), fputs() and other functions. */
#include    "stdio.h"

/* PATHMAX is the maximum length of path-list on the host system.   */
/* _POSIX_* only to get PATH_MAX    */
#define _POSIX_             1
#define _POSIX_SOURCE       1
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE     1
#define _POSIX_C_SOURCE_defined     1
#endif
#include    "limits.h"
#undef  _POSIX_
#undef  _POSIX_SOURCE
#ifdef  _POSIX_C_SOURCE_defined
#undef  _POSIX_C_SOURCE
#undef  _POSIX_C_SOURCE_defined
#endif
#define PATHMAX     PATH_MAX        /* Posix macro  */

/* islower(), isupper(), toupper(), isdigit(), isxdigit(), iscntrl()        */
#include    "ctype.h"

/* errno    */
#include    "errno.h"

#include    "string.h"
#include    "stdlib.h"
#include    "time.h"
#include    "setjmp.h"
