/*-
 * Copyright (c) 1998, 2002-2008 Kiyoshi Matsui <kmatsui@t3.rim.or.jp>
 * All rights reserved.
 *
 * Some parts of this code are derived from the public domain software
 * DECUS cpp (1984,1985) written by Martin Minow.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 *                          S Y S T E M . C
 *          S y s t e m   D e p e n d e n t   R o u t i n e s
 *
 * Routines dependent on O.S., compiler or compiler-driver.
 * To port MCPP for the systems not yet ported, you must
 *      1. specify the constants in "configed.H" or "noconfig.H",
 *      2. append the system-dependent routines in this file.
 */
#include    "system.H"
#include    "internal.H"

#include    "direct.h"
#define getcwd( buf, size)  _getcwd( buf, size)
#include    "sys/types.h"
#include    "sys/stat.h"                        /* For stat()       */
#if     ! defined( S_ISREG)
#define S_ISREG( mode)  (mode & S_IFREG)
#define S_ISDIR( mode)  (mode & S_IFDIR)
#endif
#define S_IFREG     _S_IFREG
#define S_IFDIR     _S_IFDIR
#define stat( path, stbuf)  _stat( path, stbuf)

/* Function to compare path-list    */
#define stricmp( str1, str2)        _stricmp( str1, str2)
#define str_case_eq( str1, str2)    (stricmp( str1, str2) == 0)

/*
 * PATH_DELIM is defined for the O.S. which has single byte path-delimiter.
 * Note: '\\' or any other character identical to second byte of MBCHAR should
 * not be used for PATH_DELIM for convenience of path-list parsing.
 */
#define PATH_DELIM      '/'
#define SPECIAL_PATH_DELIM  FALSE

/*
 * OBJEXT is the suffix to denote "object" file.
 */
#ifndef OBJEXT
#define OBJEXT     "obj"
#endif

static void     def_a_macro( int opt, char * def);
                /* Do a -D option                   */
static void     chk_opts( int sflag, int trad);
                /* Check consistency of options     */
static void     init_predefines( void);
                /* Set and unset predefined macros  */
static void     init_std_defines( void);
                /* Predefine Standard macros        */
static void     set_limit( void);
                /* Set minimum translation limits   */
static void     set_pragma_op( void);
                /* Set the _Pragma() operator       */
static void     put_info( FILEINFO * sharp_file);
                /* Print compiler-specific-inf      */
static char *   set_files( int argc, char ** argv, char ** in_pp
        , char ** out_pp);
                /* Set input, output, diagnostic    */
static void     set_sys_dirs( int set_cplus_dir);
                /* Set system-specific include dirs */
static void     set_env_dirs( void);
                /* Set user-defined include dirs    */
static void     parse_env( const char * env);
                /* Parse environment variables      */
static void     set_a_dir( const char * dirname);
                /* Append an include directory      */
static char *   norm_dir( const char * dirname, int framework);
                /* Normalize include directory path */
static char *   norm_path( const char * dir, const char * fname, int inf
        , int hmap);    /* Normalize pathname to compare    */
static void     def_macros( void);
                /* Define macros specified by -D    */
static void     undef_macros( void);
                /* Undefine macros specified by -U  */
static char *   md_init( const char * filename, char * output);
                /* Initialize makefile dependency   */
static char *   md_quote( char * output);
                /* 'Quote' special characters       */
static int      open_include( char * filename, int searchlocal, int next);
                /* Open the file to include         */
static int      has_directory( const char * source, char * directory);
                /* Get directory part of fname      */
static int      is_full_path( const char * path);
                /* The path is absolute path list ? */
static int      search_dir( char * filename, int searchlocal, int next);
                /* Search the include directories   */
static int      open_file( const char ** dirp, const char * src_dir
        , const char * filename, int local, int include_opt, int sys_frame);
                /* Open a source file       */
static const char *     set_fname( const char * filename);
                /* Remember the source filename     */
static void     cur_file( FILEINFO * file, FILEINFO * sharp_file, int marker);
                /* Output current source file name  */
static char *   bsl2sl( char * filename);
                /* Convert \ to / in path-list      */
static int      is_junk( void);
                /* The directive has trailing junk? */
static void     do_once( const char * fullname);
                /* Process #pragma once             */
static int      included( const char * fullname);
                /* The file has been once included? */
static void     push_or_pop( int direction);
                /* Push or pop a macro definition   */
static void     do_preprocessed( void);
                /* Process preprocessed file        */
static int      mcpp_getopt( int argc, char * const * argv, const char * opts);
                /* getopt() to prevent linking of glibc getopt  */

/* for mcpp_getopt()    */
static int      mcpp_optind = 1;
static int      mcpp_opterr = 1;
static int      mcpp_optopt;
static char *   mcpp_optarg;

static char     cur_work_dir[ PATHMAX + 1];     /* Current working directory*/

/*
 * incdir[] stores the -I directories (and the system-specific #include <...>
 * directories).  This is set by set_a_dir().  A trailing PATH_DELIM is
 * appended if absent.
 */
static const char **    incdir;         /* Include directories      */
static const char **    incend;         /* -> active end of incdir  */
static int          max_inc;            /* Number of incdir[]       */

typedef struct inc_list {       /* List of directories or files     */
    char *      name;           /* Filename or directory-name       */
    size_t      len;                    /* Length of 'name'         */
} INC_LIST;

/*
 * fnamelist[] stores the souce file names opened by #include directive for
 * debugging information.
 */
static INC_LIST *   fnamelist;          /* Source file names        */
static INC_LIST *   fname_end;          /* -> active end of fnamelist   */
static int          max_fnamelist;      /* Number of fnamelist[]    */

/* once_list[] stores the #pragma once file names.  */
static INC_LIST *   once_list;          /* Once opened file         */
static INC_LIST *   once_end;           /* -> active end of once_list   */
static int          max_once;           /* Number of once_list[]    */

#define INIT_NUM_INCLUDE    32          /* Initial number of incdir[]   */
#define INIT_NUM_FNAMELIST  256         /* Initial number of fnamelist[]    */
#define INIT_NUM_ONCE       64          /* Initial number of once_list[]    */

/*
 * 'search_rule' holds searching rule of #include "header.h" to search first
 * before searching user specified or system-specific include directories.
 * 'search_rule' is initialized to SEARCH_INIT.  It can be changed by -I1, -I2
 * or -I3 option.  -I1 specifies CURRENT, -I2 SOURCE and -I3 both.
 */

static int      search_rule = SEARCH_INIT;  /* Rule to search include file  */

static const int      nflag = TRUE;          /* Flag of -N (-undef) option       */
static long     std_val = -1L;  /* Value of __STDC_VERSION__ or __cplusplus */

#define MAX_DEF   256
#define MAX_UNDEF (MAX_DEF/4)
static char *   def_list[ MAX_DEF];     /* Macros to be defined     */
static char *   undef_list[ MAX_UNDEF]; /* Macros to be undefined   */
static int      def_cnt;                /* Count of def_list        */
static int      undef_cnt;              /* Count of undef_list      */

/* sharp_filename is filename for #line line, used only in cur_file()   */
static char *   sharp_filename = NULL;
static const int  compat_mode = 0;
                /* "Compatible" mode of recursive macro expansion   */
#define MAX_ARCH_LEN    16
static char     arch[ MAX_ARCH_LEN];    /* -arch or -m64, -m32 options      */

extern int preprocess_fullpath; // sfall

void    init_system( void)
/* Initialize static variables  */
{
    if (sharp_filename)
        free( sharp_filename);
    sharp_filename = NULL;
    incend = incdir = NULL;
    fnamelist = once_list = NULL;
    search_rule = SEARCH_INIT;
    std_val = -1L;
    def_cnt = undef_cnt = 0;
    mcpp_optind = mcpp_opterr = 1;
}

#define OPTLISTLEN  80

void    do_options(
	const char* dir
)
/*
 * Process command line arguments, called only at MCPP startup.
 */
{
    int         unset_sys_dirs;
        /* Unset system-specific and site-specific include directories ?    */
    int         set_cplus_dir;  /* Set C++ include directory ? (for GCC)*/
    int         sflag;                      /* -S option or similar */
    int         trad;                       /* -traditional         */
    int         gval, sse;

    unset_sys_dirs = sflag = trad = FALSE;
    arch[ 0] = 0;
    gval = sse = 0;
    set_cplus_dir = TRUE;

    /* Get current directory for -I option and #pragma once */
    getcwd( cur_work_dir, PATHMAX);
    bsl2sl( cur_work_dir);
    sprintf( cur_work_dir + strlen( cur_work_dir), "%c%c", PATH_DELIM, EOS);
        /* Append trailing path-delimiter   */

	if (dir)
		set_a_dir(dir);

    /* Check consistency of specified options, set some variables   */
    chk_opts( sflag, trad);

    if (warn_level == -1)               /* No -W option             */
        warn_level = 1;                 /* Default warning level    */
    else if (warn_level == 0xFF)
        warn_level = 0;                 /* -W0 has high precedence  */

    set_env_dirs();
    if (! unset_sys_dirs)
        set_sys_dirs( set_cplus_dir);
}

static void def_a_macro(
    int     opt,                            /* 'D'  */
    char *  def                         /* Argument of -D option    */
)
/*
 * Define a macro specified by -D option.
 * The macro maybe either object-like or function-like (with parameter).
 */
{
    DEFBUF *    defp;
    char *      definition;             /* Argument of -D option    */
    char *      cp;
    int         i;

    /* Convert trigraphs for the environment which need trigraphs   */
    definition = xmalloc( strlen( def) + 4);
    strcpy( definition, def);
    if ((cp = strchr( definition, '=')) != NULL) {
        *cp = ' ';                          /* Remove the '='       */
        cp = "\n";                          /* Append <newline>     */
    } else {
        cp = " 1\n";                        /* With definition "1"  */
    }
    strcat( definition, cp);
    cp = definition;
    while ((char_type[ *cp & UCHARMAX] & SPA) == 0)
        cp++;
    i = *cp;
    *cp = EOS;
    if ((defp = look_id( definition)) != NULL)      /* Pre-defined  */
        undefine( definition);
    *cp = i;
    /* Now, save the definition.    */
    unget_string( definition, NULL);
    do_define( FALSE, 0);      /* Define a macro       */
    *cp = EOS;
    if (str_eq( definition, "__STDC__")) {
        defp = look_id( definition);
        defp->nargs = DEF_NOARGS_STANDARD;
                                /* Restore Standard-predefinedness  */
    }
    free( definition);
    skip_nl();                      /* Clear the appended <newline> */
}

static void     chk_opts( 
    int     sflag,      /* Flag of Standard or post-Standard mode   */
    int     trad                    /* -traditional (GCC only)      */
)
/*
 * Check consistency between the specified options.
 * Set default value of some variables for each 'mcpp_mode'.
 */
{
    if (! stdc_val)
        stdc_val = STDC;

    expand_init();
                /* Set function pointer to macro expansion routine  */
}

static void init_predefines( void)
/*
 * Set or unset predefined macros.
 */
{
    char    tmp[ 16];

    if (std_val != -1L) {               /* Version is specified     */
            stdc_ver = std_val;     /* Value of __STDC_VERSION__    */
    } else {
        if (! cplus_val)
            stdc_ver = stdc_val ? STDC_VERSION : 0L;
    }

    un_predefine( TRUE);
    sprintf( tmp, "%ldL", cplus_val ? cplus_val : stdc_ver);
        if (stdc_ver)
            look_and_install( "__STDC_VERSION__", DEF_NOARGS_STANDARD, null
                    , tmp);
    set_limit();
    stdc2 = cplus_val || stdc_ver >= 199901L;
    stdc3 = (cplus_val >= 199901L) || (stdc_ver >= 199901L);
        /* (cplus_val >= 199901L) makes C++ C99-compatible specs    */
    if (standard)
        init_std_defines();
    if (stdc3)
        set_pragma_op();
}

static void init_std_defines( void)
/*
 * For STD and POST_STD modes.
 * The magic pre-defines are initialized with magic argument counts.
 * expand_macro() notices this and calls the appropriate routine.
 * DEF_NOARGS is one greater than the first "magic" definition.
 * 'DEF_NOARGS - n' are reserved for pre-defined macros.
 * __STDC_VERSION__ and __cplusplus are defined by chk_opts() and set_cplus().
 */
{
    char    tmp[ 16];
    char    timestr[ 14];
    time_t  tvec;
    char *  tstring;

    look_and_install( "__LINE__", DEF_NOARGS_DYNAMIC - 1, null, "-1234567890");
    /* Room for 11 chars (10 for long and 1 for '-' in case of wrap round.  */
    look_and_install( "__FILE__", DEF_NOARGS_DYNAMIC - 2, null, null);
                                            /* Should be stuffed    */

    /* Define __DATE__, __TIME__ as present date and time.          */
    time( &tvec);
    tstring = ctime( &tvec);
    sprintf( timestr, "\"%.3s %c%c %.4s\"",
        tstring + 4,
        *(tstring + 8) == '0' ? ' ' : *(tstring + 8),
        *(tstring + 9),
        tstring + 20);
    look_and_install( "__DATE__", DEF_NOARGS_DYNAMIC, null, timestr);
    sprintf( timestr, "\"%.8s\"", tstring + 11);
    look_and_install( "__TIME__", DEF_NOARGS_DYNAMIC, null, timestr);

    if (! look_id( "__STDC_HOSTED__")) {
        /*
         * Some compilers, e.g. GCC older than 3.3, define this macro by
         * -D option.
         */
        sprintf( tmp, "%d", STDC_HOSTED);
        look_and_install( "__STDC_HOSTED__", DEF_NOARGS_PREDEF, null, tmp);
    }
    if (cplus_val)
        return;

    /* Define __STDC__ as 1 or such for Standard conforming compiler.   */
    if (! look_id( "__STDC__")) {
        sprintf( tmp, "%d", stdc_val);
        look_and_install( "__STDC__", DEF_NOARGS_STANDARD, null, tmp);
    }
}

#define LINE90LIMIT         32767
#define LINE_CPLUS_LIMIT    32767

static void set_limit( void)
/*
 * Set the minimum translation limits specified by the Standards.
 */
{
    if (cplus_val) {            /* Specified by C++ 1998 Standard   */
        std_limits.str_len = SLEN_CPLUS_MIN;
        std_limits.id_len = IDLEN_CPLUS_MIN;
        std_limits.n_mac_pars = NMACPARS_CPLUS_MIN;
        std_limits.exp_nest = EXP_NEST_CPLUS_MIN;
        std_limits.blk_nest = BLK_NEST_CPLUS_MIN;
        std_limits.inc_nest = INCLUDE_NEST_CPLUS_MIN;
        std_limits.n_macro = NMACRO_CPLUS_MIN;
        std_limits.line_num = LINE_CPLUS_LIMIT;
    } else if (stdc_ver >= 199901L) {       /* Specified by C 1999 Standard */
        std_limits.str_len = SLEN99MIN;
        std_limits.id_len = IDLEN99MIN;
        std_limits.n_mac_pars = NMACPARS99MIN;
        std_limits.exp_nest = EXP_NEST99MIN;
        std_limits.blk_nest = BLK_NEST99MIN;
        std_limits.inc_nest = INCLUDE_NEST99MIN;
        std_limits.n_macro = NMACRO99MIN;
        std_limits.line_num = LINE99LIMIT;
    } else if (standard) {          /* Specified by C 1990 Standard */
        std_limits.str_len = SLEN90MIN;
        std_limits.id_len = IDLEN90MIN;
        std_limits.n_mac_pars = NMACPARS90MIN;
        std_limits.exp_nest = EXP_NEST90MIN;
        std_limits.blk_nest = BLK_NEST90MIN;
        std_limits.inc_nest = INCLUDE_NEST90MIN;
        std_limits.n_macro = NMACRO90MIN;
        std_limits.line_num = LINE90LIMIT;
    }
    /* Else pre-Standard mode   */
}

static void set_pragma_op( void)
/*
 *      #define _Pragma(a)  _Pragma ( a )
 * Define _Pragma() operator as a special macro so as to be searched
 * easily.  The unusual 'DEF_PRAGMA' is a marker of this psuedo
 * macro.
 */
{
    char *  name = "_Pragma";
    char    tmp[ 16];

    sprintf( tmp, "%c%s ( %c%c )", DEF_MAGIC, name, MAC_PARM, 1);
                                                /* Replacement text */
    look_and_install( name, DEF_PRAGMA, "a", tmp);
}

void    init_sys_macro( void)
/*
 * Define system-specific macros and some Standard required macros
 * and undefine macros specified by -U options.
 */
{
    /* This order is important. */
    def_macros();               /* Define macros specified by -D    */
    init_predefines();                  /* Define predefined macros */
    undef_macros();             /* Undefine macros specified by -U  */
}

void    at_start( void)
/*
 * Do the commands prior to processing main source file after do_options().
 */
{
    FILEINFO *      file_saved = infile;

    put_info( file_saved);
}

static void put_info(
    FILEINFO *  sharp_file
)
/*
 * Putout compiler-specific information.
 */
{
    if (no_output || option_flags.p)
        return;
    sharp_file->line++;
    sharp( sharp_file, 0);
    sharp_file->line--;
}

static void set_env_dirs( void)
/*
 * Add to include path those specified by environment variables.
 */
{
    const char *    env;

    if (cplus_val) {
        if ((env = getenv( ENV_CPLUS_INCLUDE_DIR)) != NULL)
            parse_env( env);
    }
    if ((env = getenv( ENV_C_INCLUDE_DIR)) != NULL)
        parse_env( env);
}

static void parse_env(
    const char *    env
)
/*
 * Parse environmental variable and append the path to include-dir-list.
 */
{
    char *  save;
    char *  save_start;
    char *  p;
    int     sep;

    save = save_start = save_string( env);
    while (*save) {
        p = save;
        while (*p && *p != ENV_SEP)
            p++;
        if (p != save)  {                   /* Variable separator   */
            sep = *p;
            *p = EOS;
            set_a_dir( save);
            if (sep == EOS)
                break;
            save = ++p;
        }
        while (*save == ENV_SEP)
            ++save;
    }
    free( save_start);
}

static void set_sys_dirs(
    int     set_cplus_dir       /* Set C++ include-directory too    */
)
/*
 * Set site-specific and system-specific directories to the include directory
 * list.
 */
{

}

static void set_a_dir(
    const char *    dirname                 /* The path-name        */
)
/*
 * Append an include directory.
 * This routine is called from the following routines (in this order).
 * 1. do_options() by -I option.
 * 2. do_options() by -isystem option (for GNUC).
 * 3. set_env_dirs() by environment variables.
 * 4. set_sys_dirs() by CPLUS_INCLUDE_DIR?, C_INCLUDE_DIR? and system-
 *    specifics (unless -I- or -nostdinc option is specified).
 * Ignore non-existent directory.
 * Note that this routine should be called only in initializing steps,
 *      because increase of include dirs causes reallocation of incdir[].
 * Note: a trailing PATH-DELIM is appended by norm_path().
 */
{
    char *  norm_name;
    const char **   ip;

    if (incdir == NULL) {               /* Should be initialized    */
        max_inc = INIT_NUM_INCLUDE;
        incdir = (const char **) xmalloc( sizeof (char *) * max_inc);
        incend = &incdir[ 0];
    } else if (incend - incdir >= max_inc) {        /* Buffer full  */
        incdir = (const char **) xrealloc( (void *) incdir
                , sizeof (char *) * max_inc * 2);
        incend = &incdir[ max_inc];
        max_inc *= 2;                   
    }

    if (dirname == NULL)
        return;                     /* Only to initialize incdir[]  */
    norm_name = norm_dir( dirname, FALSE);
    if (! norm_name)                        /* Non-existent         */
        return;
    for (ip = incdir; ip < incend; ip++) {
        if (str_case_eq( *ip, norm_name)) {
            if (option_flags.v)
                mcpp_fprintf( ERR, "Duplicate directory \"%s\" is ignored\n"
                        , norm_name);
            free( norm_name);               /* Already registered   */
            return;
        }
    }
    /* Register new directory   */
    *incend++ = norm_name;
}

static char *   norm_dir(
    const char *    dirname,        /* Directory path to normalize  */
    int             framework       /* Setting a framework directory*/
)
/*
 * Normalize include directory path.
 * Handle -isysroot option for GCC, including framework directory for SYS_MAC.
 */
{
    char *  norm_name;

    {
        norm_name = norm_path( dirname, NULL, FALSE, FALSE);
                            /* Normalize the pathname to compare    */
        if (! norm_name && option_flags.v)
            mcpp_fprintf( ERR, "Non-existent directory \"%s\" is ignored\n"
                    , dirname);
    }

    return  norm_name;
}

static char *   norm_path(
    const char *    dir,        /* Include directory (maybe "", never NULL) */
    const char *    fname,
        /* Filename (possibly has directory part, or maybe NULL)    */
    int     inf,    /* If TRUE, output some infs when (mcpp_debug & PATH)   */
    int     hmap            /* "header map" file of Apple-GCC       */
)
/*
 * Normalize the pathname removing redundant components such as
 * "foo/../", "./" and trailing "/.".
 * Append trailing "/" if 'fname' is NULL.
 * Change relative path to absolute path.
 * Dereference a symbolic linked file (or directory) to a real directory/file.
 * Return a malloc'ed buffer, if the directory/file exists.
 * Return NULL, if the specified directory/file does not exist or 'dir' is
 * not a directory or 'fname' is not a regular file.
 * This routine is called from set_a_dir(), init_gcc_macro(), do_once() and
 * open_file().
 */
{
    char *  norm_name;                  /* The path-list converted  */
    char *  start;
    char *  cp1;
    char *  cp2;
    char *  abs_path;
    int     len;                            /* Should not be size_t */
    size_t  start_pos = 0;
    char    slbuf1[ PATHMAX+1];             /* Working buffer       */

    struct _stat    st_buf;

    if (! dir || (*dir && is_full_path( fname)))
        cfatal( "Bug: Wrong argument to norm_path()"        /* _F_  */
                , NULL, 0L, NULL);
    inf = 0;

    strcpy( slbuf1, dir);                   /* Include directory    */
    len = strlen( slbuf1);
    if (fname && len && slbuf1[ len - 1] != PATH_DELIM) {
        slbuf1[ len] = PATH_DELIM;          /* Append PATH_DELIM    */
        slbuf1[ ++len] = EOS;
    } else if (! fname && len && slbuf1[ len - 1] == PATH_DELIM) {
        /* stat() of some systems do not like trailing '/'  */
        slbuf1[ --len] = EOS;
    }
    if (fname)
        strcat( slbuf1, fname);
    if (stat( slbuf1, & st_buf) != 0        /* Non-existent         */
            || (! fname && ! S_ISDIR( st_buf.st_mode))
                /* Not a directory though 'fname' is not specified  */
            || (fname && ! S_ISREG( st_buf.st_mode)))
                /* Not a regular file though 'fname' is specified   */
        return  NULL;

    if (! fname) {
        slbuf1[ len] = PATH_DELIM;          /* Append PATH_DELIM    */
        slbuf1[ ++len] = EOS;
    }
    len = strlen( slbuf1);
    start = norm_name = xmalloc( len + 1);  /* Need a new buffer    */
    strcpy( norm_name, slbuf1);
    bsl2sl( norm_name);

    cp1 = norm_name;

    if (*(cp1 + 1) == ':')
        start = cp1 += 2;               /* Next to the drive letter */
    start_pos = 2;
    if (len == 1 && *norm_name == '/')              /* Only "/"     */
        return  norm_name;

    if (strncmp( cp1, "./", 2) == 0)    /* Remove beginning "./"    */
        memmove( cp1, cp1 + 2, strlen( cp1 + 2) + 1);       /* +1 for EOS   */
    if (*start != '/') {    /* Relative path to current directory   */
        /* Make absolute path   */
        abs_path = xmalloc( len + strlen( cur_work_dir) + 1);
        cp1 = stpcpy( abs_path, cur_work_dir);
        strcpy( cp1, start);
        free( norm_name);
        norm_name = abs_path;
        start = cp1 = norm_name + start_pos;
    }

    while ((cp1 = strstr( cp1, "/./")) != NULL)
        memmove( cp1, cp1 + 2, strlen( cp1 + 2) + 1);
                                        /* Remove "/." of "/./"     */
    cp1 = start;
    /* Remove redundant "foo/../"   */
    while ((cp1 = strstr( cp1, "/../")) != NULL) {
        *cp1 = EOS;
        if ((cp2 = strrchr( start, '/')) != NULL) {
            if (*(cp1 - 1) != '.') {
                memmove( cp2 + 1, cp1 + 4, strlen( cp1 + 4) + 1);
                                        /* Remove "foo/../"         */
                cp1 = cp2;
            } else {                                /* Impossible   */
                break;
            }
        } else {                                    /* Impossible   */ 
            break;
        }
    }

    return  norm_name;
}

static void     def_macros( void)
/*
 * Define macros specified by -D option.
 * This routine should be called before undef_macros().
 */
{
    int         i;

    for (i = 0; i < def_cnt; i++)
        def_a_macro( 'D', def_list[ i]);
}

static void     undef_macros( void)
/*
 * Undefine macros specified by -U option.
 * This routine should be called after init_predefine().
 */
{
    char *      name;
    int         i;

    for (i = 0; i < undef_cnt; i++) {
        name = undef_list[ i];
        if (look_id( name) != NULL)
            undefine( name);
        else if (warn_level & 8)
            mcpp_fprintf( ERR, "\"%s\" wasn't defined\n", name);
    }
}

static const char *     toolong_fname =
        "Too long header name \"%s%.0ld%s\"";               /* _F_  */
static const char *     excess_token =
        "Excessive token sequence \"%s\"";          /* _E_, _W1_    */

int     do_include(
    int     next        /* TRUE if the directive is #include_next   */
)
/*
 * Process the #include line.
 * There are three variations:
 *      #include "file"         search somewhere relative to the
 *                              current (or source) directory, if not
 *                              found, treat as #include <file>.
 *      #include <file>         Search in an implementation-dependent
 *                              list of places.
 *      #include macro-call     Expand the macro call, it must be one of
 *                              "file" or <file>, process as such.
 * On success : return TRUE;
 * On failure of syntax : return FALSE;
 * On failure of file opening : return FALSE.
 * do_include() always absorbs the line (including the <newline>).
 */
{
    const char * const  no_name = "No header name";         /* _E_  */
    char    header[ PATHMAX + 16];
    int     token_type;
    char *  fname;
    char *  filename;
    int     delim;                          /* " or <, >            */

    if ((delim = skip_ws()) == '\n') {      /* No argument          */
        cerror( no_name, NULL, 0L, NULL);
        return  FALSE;
    }
    fname = infile->bptr - 1;       /* Current token for diagnosis  */

    if (standard && (char_type[ delim] & LET)) {    /* Maybe macro  */
        int     c;
        char    *hp;

        hp = header;
        *hp = EOS;
        c = delim;
        while (get_unexpandable( c, FALSE) != NO_TOKEN) {
                                /* Expand any macros in the line    */
            if (header + PATHMAX < hp + (int) (workp - work_buf))
                cfatal( toolong_fname, header, 0L, work_buf);
            hp = stpcpy( hp, work_buf);
            while (char_type[ c = get_ch()] & HSP)
                *hp++ = c;
        }
        *hp = EOS;                          /* Ensure to terminate  */
        if (macro_line == MACRO_ERROR)      /* Unterminated macro   */
            return  FALSE;                  /*   already diagnosed. */
        unget_string( header, NULL);        /* To re-read           */
        delim = skip_ws();
        if (delim == '\n') {
            cerror( no_name, NULL, 0L, NULL);       /* Expanded to  */
            return  FALSE;                          /*   0 token.   */
        }
    }

    token_type = scan_token( delim, (workp = work_buf, &workp)
            , work_buf + PATHMAX);
    if (token_type == STR)                  /* String literal form  */
        goto  found_name;
    else if (token_type == OPE && openum == OP_LT)          /* '<'  */
        workp = scan_quote( delim, work_buf, work_buf + PATHMAX, TRUE);
                                        /* Re-construct or diagnose */
    else                                    /* Any other token in-  */
        goto  not_header;                   /*   cluding <=, <<, <% */

    if (workp == NULL)                      /* Missing closing '>'  */
        goto  syntax_error;

found_name:
    *--workp = EOS;                         /* Remove the closing and   */
    fname = save_string( &work_buf[ 1]);    /*  the starting delimiter. */

    if (skip_ws() != '\n') {
        if (standard) {
            cerror( excess_token, infile->bptr-1, 0L, NULL);
            skip_nl();
            goto  error;
        } else {
            if (warn_level & 1)
                cwarn( excess_token, infile->bptr-1, 0L, NULL);
            skip_nl();
        }
    }

    bsl2sl( fname);
    filename = fname;
    if (open_include( filename, (delim == '"'), next)) {
        /* 'fname' should not be free()ed, it is used as file->         */
        /*      real_fname and has been registered into fnamelist[]     */
        return  TRUE;
    }

    cerror( "Can't open include file \"%s\"", filename, 0L, NULL);  /* _E_  */
error:
    free( fname);
    return  FALSE;

not_header:
    cerror( "Not a header name \"%s\"", fname, 0L, NULL);   /* _E_  */
syntax_error:
    skip_nl();
    return  FALSE;
}

static int  open_include(
    char *  filename,               /* File name to include         */
    int     searchlocal,            /* TRUE if #include "file"      */
    int     next                    /* TRUE if #include_next        */
)
/*
 * Open an include file.  This routine is only called from do_include() above.
 * It searches the list of directories via search_dir() and opens the file
 * via open_file(), linking it into the list of active files.
 * Returns TRUE if the file was opened, FALSE if it fails.
 */
{
    char    src_dir[ PATHMAX] = { EOS, };   /* Directory part of includer   */
    int     full_path;              /* Filename is full-path-list   */
    int     has_dir = FALSE;        /* Includer has directory part  */
    int     has_dir_src = FALSE;
    int     has_dir_fname = FALSE;

    full_path = is_full_path( filename);

    if (!full_path && searchlocal && (search_rule & SOURCE)) {
        has_dir_src  = has_directory( infile->src_dir, src_dir);
        has_dir_fname = has_directory( infile->real_fname
                , src_dir + strlen( src_dir));
        /* Get directory part of the parent file of the file to include.*/
        /* Note that infile->dirp of main input file is set to "" and   */
        /* remains the same even if -include options are processed.     */
        has_dir = has_dir_src || has_dir_fname
                || (**(infile->dirp) != EOS);
    }

    if ((searchlocal && ((search_rule & CURRENT) || !has_dir)) || full_path) {
        /*
         * Look in local directory first.
         * Try to open filename relative to the "current directory".
         */
        if (open_file( &null, NULL, filename, searchlocal && !full_path
                , FALSE, FALSE))
            return  TRUE;
        if (full_path)
            return  FALSE;
    }

    if (searchlocal && (search_rule & SOURCE) && has_dir) {
        /*
         * Look in local directory of source file.
         * Try to open filename relative to the "source directory".
         */
        if (open_file( infile->dirp, src_dir, filename, TRUE, FALSE, FALSE))
            return  TRUE;
    }

    /* Search the include directories   */
    if (search_dir( filename, searchlocal, next))
        return  TRUE;

    return  FALSE;
}

static int  has_directory(
    const char *    source,         /* Filename to examine          */
    char *  directory               /* Put directory stuff here     */
)
/*
 * If a directory is found in the 'source' filename string (i.e. "includer"),
 * the directory part of the string is copied to 'directory' and 
 * has_directory() returns TRUE.
 * Else, nothing is copied and it returns FALSE.
 */
{
    const char *    sp;
    size_t  len;

    if (! source)
        return  FALSE;
    if ((sp = strrchr( source, PATH_DELIM)) == NULL) {
        return  FALSE;
    } else {
        len = (size_t)(sp - source) + 1;    /* With path-delimiter  */
        memcpy( directory, source, len);
        directory[ len] = EOS;
        return  TRUE;
    }
}

static int  is_full_path(
    const char *    path
)
/*
 * Check whether the path is a full (absolute) path list or not.
 */
{
    if (! path)
        return  FALSE;
    if ((path[1] == ':' && path[2] == PATH_DELIM)   /* "C:/path"    */
            || path[0] == PATH_DELIM)       /* Root dir of current drive    */
        return  TRUE;
    else
        return  FALSE;
}

static int  search_dir(
    char *  filename,               /* File name to include         */
    int     searchlocal,            /* #include "header.h"          */
    int     next                    /* TRUE if #include_next        */
)
/*
 * Look in any directories specified by -I command line arguments,
 * specified by environment variable, then in the builtin search list.
 */
{
    const char **   incptr;                 /* -> inlcude directory */

    incptr = incdir;

    for ( ; incptr < incend; incptr++) {
        if (strlen( *incptr) + strlen( filename) >= PATHMAX)
            cfatal( toolong_fname, *incptr, 0L, filename);  /* _F_  */
        if (open_file( incptr, NULL, filename, FALSE, FALSE, FALSE))
            /* Now infile has been renewed  */
            return  TRUE;
    }

    return  FALSE;
}

static int  open_file(
    const char **   dirp,           /* Pointer to include directory */
    const char *    src_dir,        /* Source directory of includer */
    const char *    filename,       /* Filename (possibly has directory)    */
    int         local,                      /* #include "file"      */
    int         include_opt,        /* Specified by -include option */
    int         sys_frame           /* System framework header (for SYS_MAC)*/
)
/*
 * Open a file, add it to the linked list of open files, close the includer
 * if nessesary and truncate the includer's buffer.
 * This is called from open_include() and at_start().
 */
{
    char        dir_fname[ PATHMAX] = { EOS, };
    static int  max_open;
    int         len;
    FILEINFO *  file = infile;
    FILE *      fp;
    char *      fullname;
    const char *    fname;

    errno = 0;      /* Clear errno possibly set by path searching   */

    /* src_dir is usually NULL.  This is specified to   */
    /* search the source directory of the includer.     */
    if (src_dir && *src_dir != EOS) {
        strcpy( dir_fname, src_dir);
        strcat( dir_fname, filename);
        fname = dir_fname;
    } else {
        fname = filename;
    }
    fullname = norm_path( *dirp, fname, TRUE, FALSE);
                                    /* Convert to absolute path     */
    if (! fullname)                 /* Non-existent or directory    */
        return  FALSE;
    if (standard && included( fullname))        /* Once included    */
        goto  _true;
        
    if ((max_open != 0 && max_open <= include_nest)
                            /* Exceed the known limit of open files */
            || ((fp = fopen( fullname, "r")) == NULL && errno == EMFILE)) {
                            /* Reached the limit for the first time */
        /*
         * Table of open files is full.
         * Remember the file position and close the includer.
         * The state will be restored by get_line() on end of the included.
         */
        file->pos = ftell( file->fp);
        fclose( file->fp);
        /* In case of failure, re-open the includer */
        if ((fp = fopen( fullname, "r")) == NULL) {
            file->fp = fopen( cur_fullname, "r");
            fseek( file->fp, file->pos, SEEK_SET);
            goto  _false;
        }
        if (max_open == 0)      /* Remember the limit of the system */
            max_open = include_nest;
    } else if (fp == NULL)                  /* No read permission   */ 
        goto  _false;
    /* Truncate buffer of the includer to save memory   */
    len = (int) (file->bptr - file->buffer);
    if (len) {
        file->buffer = xrealloc( file->buffer, len + 1);
        file->bptr = file->buffer + len;
    }

    if (! include_opt)
        sharp( NULL, 0);    /* Print includer's line num and fname  */
    add_file( fp, src_dir, filename, fullname, include_opt);
    /* Add file-info to the linked list.  'infile' has been just renewed    */
    /*
     * Remember the directory for #include_next.
     * Note: inc_dirp is restored to the parent includer's directory
     *   by get_ch() when the current includer is finished.
     */
    infile->dirp = inc_dirp = dirp;
    cur_fullname = fullname;

    if (option_flags.z) {
        no_output++;        /* Don't output the included file       */
        if (include_nest == 2)
            mcpp_fprintf( OUT, "#include \"%s\"\n", fullname);
            /* Output #include line instead, if it is in main source file   */
    } else if (! include_opt) {     /* Do not sharp() on -include   */
        src_line = 1;                   /* Working on line 1 now    */
        sharp( NULL, 1);    /* Print out the included file name     */
    }
    src_line = 0;                       /* To read the first line   */

_true:
    return  TRUE;
_false:
    free( fullname);
    return  FALSE;
}

void    add_file(
    FILE *      fp,                         /* Open file pointer    */
    const char *    src_dir,                /* Directory of source  */
    const char *    filename,               /* Name of the file     */
    const char *    fullname,               /* Full path list       */
    int         include_opt         /* File specified by -include option    */
)
/*
 * Initialize tables for this open file.  This is called from open_file()
 * (for #include files), and from the entry to MCPP to open the main input
 * file.  It calls a common routine get_file() to build the FILEINFO
 * structure which is used to read characters.
 */
{
    FILEINFO *      file;
    const char *    too_many_include_nest =
            "More than %.0s%ld nesting of #include";    /* _F_ _W4_ */

    filename = set_fname( filename);    /* Search or append to fnamelist[]  */
    fullname = set_fname( fullname);    /* Search or append to fnamelist[]  */
    file = get_file( filename, src_dir, fullname, (size_t) NBUFF, include_opt);
                                        /* file == infile           */
    file->fp = fp;                      /* Better remember FILE *   */
    cur_fname = filename;

    if (include_nest >= INCLUDE_NEST)   /* Probably recursive #include      */
        cfatal( too_many_include_nest, NULL, (long) INCLUDE_NEST, NULL);
    if (standard && (warn_level & 4)
            && include_nest == std_limits.inc_nest + 1)
        cwarn( too_many_include_nest, NULL, (long) std_limits.inc_nest, NULL);
    include_nest++;
}

static const char *     set_fname(
    const char *    filename
)
/*
 * Register the source filename to fnamelist[].
 * Search fnamelist[] for filename or append filename to fnamelist[].
 * Returns the pointer.
 * file->real_fname and file->full_fname points into fnamelist[].
 */
{
    INC_LIST *  fnamep;
    size_t      fnamelen;

    if (fnamelist == NULL) {            /* Should be initialized    */
        max_fnamelist = INIT_NUM_FNAMELIST;
        fnamelist = (INC_LIST *) xmalloc( sizeof (INC_LIST) * max_fnamelist);
        fname_end = &fnamelist[ 0];
    } else if (fname_end - fnamelist >= max_fnamelist) {
                                /* Buffer full: double the elements */
        fnamelist = (INC_LIST *) xrealloc( (void *) fnamelist
                , sizeof (INC_LIST) * max_fnamelist * 2);
        fname_end = &fnamelist[ max_fnamelist];
        max_fnamelist *= 2;
    }

    /* Register the filename in fnamelist[] */
    fnamelen = strlen( filename);
    for (fnamep = fnamelist; fnamep < fname_end; fnamep++) {
        if (fnamep->len == fnamelen && str_case_eq( fnamep->name, filename))
            return  filename;           /* Already registered       */
    }
    fname_end->name = xmalloc( fnamelen + 1);
    filename = strcpy( fname_end->name, filename);
                                /* Global pointer for get_file()    */
    fname_end->len = fnamelen;
    fname_end++;

    return  filename;
}

void    sharp(
    FILEINFO *  sharp_file,
    int         flag        /* Flag to append to the line for GCC   */
)
/*
 * Output a line number line.
 * 'file' is 'sharp_file' if specified,
 * else (i.e. 'sharp_file' is NULL) 'infile'.
 */
{
    static FILEINFO *   sh_file;
    static int  sh_line;
    FILEINFO *  file;
    int         line;

    file = sharp_file ? sharp_file : infile;
    if (! file)
        return;
    while (! file->fp)
        file = file->parent;
    line = sharp_file ? sharp_file->line : src_line;
    if (no_output || option_flags.p || file == NULL
            || (file == sh_file && line == sh_line))
        goto  sharp_exit;
    sh_file = file;
    sh_line = line;
    if (keep_comments)
        mcpp_fputc( '\n', OUT);         /* Ensure to be on line top */
    if (std_line_prefix)
        mcpp_fprintf( OUT, "#line %ld", line);
    else
        mcpp_fprintf( OUT, "%s%ld", LINE_PREFIX, line);
    cur_file( file, sharp_file, flag);
    mcpp_fputc( '\n', OUT);
sharp_exit:
    wrong_line = FALSE;
}

static void cur_file(
    FILEINFO *  file,                   /* infile or sharp_file     */
    FILEINFO *  sharp_file,             /* The 'file' or NULL       */
    int         flag                    /* Flag to append for GCC   */
)
/*
 * Output current source file name and line number.
 * Called only from sharp() above.
 */
{
    const char *    name;

    /* Usually, the path not "normalized"   */
    if (sharp_file) {                       /* Main input file  */
        name = file->filename;
    } else if (str_eq( file->filename, file->real_fname)) {
		// sfall: added
		if (preprocess_fullpath) {    // 
			name = file->full_fname;  // 
		} else { // end of added
			sprintf( work_buf, "%s%s", *(file->dirp), cur_fname);
			name = work_buf;
		}
    } else {            /* Changed by '#line fname' directive   */
        name = file->filename;
    }
    if (sharp_filename == NULL || ! str_eq( name, sharp_filename)) {
        if (sharp_filename != NULL)
            free( sharp_filename);
        sharp_filename = save_string( name);
    }
    mcpp_fprintf( OUT, " \"%s\"", name);
}

static char *   bsl2sl(
    char * filename
)
/*
 * Convert '\\' in the path-list to '/'.
 */
{
    static int  diagnosed = FALSE;
    char *  cp;

    cp = filename;

    while (*cp) {
        if (bsl_in_mbchar) {
            int     c;
            c = *cp & UCHARMAX;
        }
        if (*cp == '\\') {
            *cp++ = PATH_DELIM;
            if (!diagnosed && (warn_level & 2) && (warn_level != -1)) {
                            /* Backslash in source program          */
                cwarn( "Converted \\ to %s", "/", 0L, NULL);        /* _W2_ */
                    diagnosed = TRUE;       /* Diagnose only once   */
            }
        } else {
            cp++;
        }
    }

    return  filename;
}

static const char * const   unknown_arg =
        "Unknown argument \"%s\"";      /*_W1_*/
static const char * const   not_ident =
        "Not an identifier \"%s\"";     /*_W1_*/

static int  is_junk( void)
/*
 * Check the trailing junk in a directive line.
 */
{
    int     c;

    c = skip_ws();
    unget_ch();
    if (c != '\n') {                        /* Trailing junk        */
        if (warn_level & 1)
            cwarn( unknown_arg, infile->bptr, 0L, NULL);
        return TRUE;
    } else {
        return FALSE;
    }
}

#define PUSH    1
#define POP    -1

void    do_pragma( void)
/*
 * Process the #pragma lines.
 * 1. Process the sub-directive for MCPP.
 * 2. Pass the line to the compiler-proper.
 *      #pragma MCPP put_defines, #pragma MCPP preprocess,
 *      #pragma MCPP preprocessed and #pragma once are, however, not put
 *      out so as not to duplicate output when re-preprocessed.
 * When EXPAND_PRAGMA == TRUE and (__STDC_VERSION__ >= 199901L or
 * __cplusplus >= 199901L), the line is subject to macro expansion unless
 * the next to 'pragma' token is one of 'STDC', 'GCC' or 'MCPP'.
 */
{
    int         c;
    int         warn = FALSE;               /* Necessity of warning */
    int         token_type;
    char *      bp;                         /* Pointer to argument  */
    char *      tp;
    FILEINFO *  file;

    wrong_line = TRUE;                      /* In case of error     */
    c = skip_ws();
    bp = infile->bptr - 1;  /* Remember token to pass to compiler   */
    if (c == '\n') {
        if (warn_level & 1)
            cwarn( "No sub-directive", NULL, 0L, NULL);     /* _W1_ */
        unget_ch();
        return;
    }
    token_type = scan_token( c, (tp = work_buf, &tp), work_end);

    if (token_type != NAM) {
        if (warn_level & 1)
            cwarn( not_ident, work_buf, 0L, NULL);
        goto  skip_nl;
    } else if (str_eq( identifier, "once")) {   /* #pragma once     */
       if (! is_junk()) {
            file = infile;
            while (file->fp == NULL)
                file = file->parent;
            do_once( file->full_fname);
            goto  skip_nl;
        }
    }

    if (warn) {
        if (warn_level & 1)
            cwarn( unknown_arg, identifier, 0L, NULL);
        goto  skip_nl;                  /* Do not putout the line   */
    }

    sharp( NULL, 0);    /* Synchronize line number before output    */
    if (! no_output) {
        mcpp_fputs( "#pragma ", OUT);
        mcpp_fputs( bp, OUT);           /* Line is put out          */
    }
skip_nl: /* Don't use skip_nl() which skips to the newline in source file */
    while (get_ch() != '\n')
        ;
}

static void do_once(
    const char *    fullname        /* Full-path-list of the header */
)
/*
 * Process #pragma once so as not to re-include the file later.
 * This directive has been imported from GCC V.1.* / cpp as an extension.
 */
{
    if (once_list == NULL) {                /* Should initialize    */
        max_once = INIT_NUM_ONCE;
        once_list = (INC_LIST *) xmalloc( sizeof (INC_LIST) * max_once);
        once_end = &once_list[ 0];
    } else if (once_end - once_list >= max_once) {
                                            /* Double the elements  */
        once_list = (INC_LIST *) xrealloc( (void *) once_list
                , sizeof (INC_LIST) * max_once * 2);
        once_end = &once_list[ max_once];
        max_once *= 2;
    }
    once_end->name = fullname;
    once_end->len = strlen( fullname);
    once_end++;
}

static int  included(
    const char *    fullname
)
/*
 * Has the file been once included ?
 * This routine is only called from open_file().
 */
{
    INC_LIST *  inc;
    size_t      fnamelen;

    if (once_list == NULL)              /* No once file registered  */
        return  FALSE;
    fnamelen = strlen( fullname);
    for (inc = once_list; inc < once_end; inc++) {
        if (inc->len == fnamelen && str_case_eq( inc->name, fullname)) {
            /* Already included */
            return  TRUE;
        }
    }
    return  FALSE;                          /* Not yet included     */
}

static void push_or_pop(
    int     direction
)
/* Process #pragma MCPP push_macro( "MACRO"),
 * #pragma MCPP pop_macro( "MACRO") for other compilers than Visual C,
 * and #pragma push_macro( "MACRO"), #pragma pop_macro( "MACRO") for Visual C.
 * Note:1. "push" count is set in defp->push.
 *      2. pushed definitions are inserted immediatly after the current
 *          definition of the same name.
 *      3. the definitions of a same name macro can be pushed multiple times.
 */
{
    char *          tp;
    DEFBUF **       prevp;
    DEFBUF *        defp;
    DEFBUF *        dp;
    int             cmp;
    size_t          s_name, s_def;

    if (skip_ws() == '('
            && scan_token( skip_ws(), (tp = work_buf, &tp), work_end) == STR
            && skip_ws() == ')') {          /* Correct syntax       */

        if (is_junk())
            return;
        s_name = strlen( work_buf) - 2;
        *(work_buf + s_name + 1) = '\0';
        memcpy( identifier, work_buf + 1, s_name + 1);
                                            /* Remove enclosing '"' */
        prevp = look_prev( identifier, &cmp);
        if (cmp == 0) { /* Current definition or pushed definition exists   */
            defp = *prevp;
            if (direction == PUSH) {/* #pragma push_macro( "MACRO") */
                if (defp->push) {           /* No current definition*/
                    if (warn_level & 1)
                        cwarn( "\"%s\" is already pushed"   /* _W1_ */
                                , identifier, 0L, NULL);
                    return;
                }
                /* Else the current definition exists.  Push it     */
                s_def = sizeof (DEFBUF) + 3 + s_name
                        + strlen( defp->repl) + strlen( defp->fname);
                if (mcpp_mode == STD)
                    s_def += strlen( defp->parmnames);
                dp = (DEFBUF *) xmalloc( s_def);
                memcpy( dp, defp, s_def);   /* Copy the definition  */
                dp->link = *prevp;          /* Insert to linked-list*/
                *prevp = dp;                /*      the pushed def  */
                prevp = &dp->link;          /* Next link to search  */
            } else {                /* #pragma pop_macro( "MACRO")  */
                if (defp->push == 0) {      /* Current definition   */
                    if (defp->link == NULL
                            || ! str_eq( identifier, defp->link->name)) {
                        if (warn_level & 1)
                            cwarn( "\"%s\" has not been pushed"     /* _W1_ */
                                    , identifier, 0L, NULL);
                        return;
                    } else {
                        *prevp = defp->link;
                                /* Link the previous and the next   */
                        free( defp);
                            /* Delete the definition to enable popped def   */
                    }
                }   /* Else no current definition exists    */
            }
            while ((defp = *prevp) != NULL) {
                /* Increment or decrement "push" count of all pushed defs   */
                if ((cmp = memcmp( defp->name, identifier, s_name)) > 0)
                    break;
                defp->push += direction;        /* Increment or decrement   */
                prevp = &defp->link;
            }
        } else {    /* No current definition nor pushed definition  */
            if (warn_level & 1)
                cwarn( "\"%s\" has not been defined"        /* _W1_ */
                        , identifier, 0L, NULL);
        }
    } else {        /* Wrong syntax */
        if (warn_level & 1)
            cwarn( "Bad %s syntax", direction == PUSH       /* _W1_ */
                    ? "push_macro" : "pop_macro", 0L, NULL);
    }
}

void    do_old( void)
/*
 * Process the out-of-standard directives.
 * GCC permits #include_next and #warning even in STANDARD mode.
 */
{
    static const char * const   unknown
            = "Unknown #directive \"%s\"%.0ld%s";       /* _E_ _W8_ */
    static const char * const   ext
            = "%s is not allowed by Standard%.0ld%s";   /* _W2_ _W8_*/

    if (compiling) {
        if (option_flags.lang_asm) {        /* "Assembler" source   */
            if (warn_level & 1)
                cwarn( unknown, identifier, 0L, NULL);
            mcpp_fputs( infile->buffer, OUT);   /* Putout the line  */
        } else {
            cerror( unknown, identifier, 0L, NULL);
        }
    } else if (warn_level & 8) {
        cwarn( unknown, identifier, 0L, " (in skipped block)");
    }
    skip_nl();
    unget_ch();
    return;
}

static void do_preprocessed( void)
/*
 * The source file has been already preprocessed.
 * Copy the lines to output.
 * Install macros according the #define directives.
 */
{
    const char *    corrupted =
            "This preprocessed file is corrupted";          /* _F_  */
    FILEINFO *      file;
    char *          lbuf;
    char *          cp;
    const char **   incptr;
    char *          comment = NULL;
    char *          colon = NULL;
    const char *    dir;
#if STD_LINE_PREFIX == FALSE
    char            conv[ NBUFF];
    char *          arg;

    /*
     * Compiler cannot accept C source style #line.
     * Convert it to the compiler-specific format.
     */
    strcpy( conv, LINE_PREFIX);
    arg = conv + strlen( conv);
#endif
    file = infile;
    lbuf = file->bptr = file->buffer;           /* Reset file->bptr */

    /* Copy the input to output until a comment line appears.       */
    while (fgets( lbuf, NBUFF, file->fp) != NULL
            && memcmp( lbuf, "/*", 2) != 0) {
#if STD_LINE_PREFIX == FALSE
        if (memcmp( lbuf, "#line ", 6) == 0) {
            strcpy( arg, lbuf + 6);
            mcpp_fputs( conv, OUT);
        } else
#endif
        {
            mcpp_fputs( lbuf, OUT);
        }
    }
    if (! str_eq( lbuf, "/* Currently defined macros. */\n"))
        cfatal( "This is not a preprocessed source"         /* _F_  */
                , NULL, 0L, NULL);

    /* Define macros according to the #define lines.    */
    while (fgets( lbuf, NWORK, file->fp) != NULL) {
        if (memcmp( lbuf, "/*", 2) == 0) {
                                    /* Standard predefined macro    */
            continue;
        }
        if (memcmp( lbuf, "#define ", 8) != 0) {
            if (memcmp( lbuf, "#line", 5) == 0)
                continue;
            else
                cfatal( corrupted, NULL, 0L, NULL);
        }
        /* Filename and line-number information in comment as:  */
        /* dir/fname:1234\t*/
        cp = lbuf + strlen( lbuf);
        if ((memcmp( cp - 4, "\t*/\n", 4) != 0)
                || (*(cp - 4) = EOS
                        , (comment = strrchr( lbuf, '*')) == NULL)
                || (memcmp( --comment, "/* ", 3) != 0)
                || ((colon = strrchr( comment, ':')) == NULL))
            cfatal( corrupted, NULL, 0L, NULL);
        src_line = atol( colon + 1);        /* Pseudo line number   */
        *colon = EOS;
        dir = comment + 3;
        inc_dirp = &null;
        /* Search the include directory list    */
        for (incptr = incdir ; incptr < incend; incptr++) {
            if (memcmp( *incptr, dir, strlen( *incptr)) == 0) {
                inc_dirp = incptr;
                break;
            }
        }
        /* Register the filename to fnamelist[] */
        /* inc_dirp may be NULL, and cur_fname may be "(predefined)"    */
        cur_fname = set_fname( dir + strlen( *inc_dirp));
        strcpy( comment - 2, "\n");         /* Remove the comment   */
        unget_string( lbuf + 8, NULL);
        do_define( FALSE, 0);
        get_ch();                               /* '\n' */
        get_ch();                               /* Clear the "file" */
        unget_ch();                             /* infile == file   */
    }
    file->bptr = file->buffer + strlen( file->buffer);
}

/*
 * Note: The getopt() of glibc should not be used since the specification
 *  differs from the standard one.
 *  Use this mcpp_getopt() for mcpp.
 */

/* Based on the public-domain-software released by AT&T in 1985.    */

#define OPTERR( s, c)   if (mcpp_opterr) {  \
    mcpp_fputs( argv[0], ERR);  \
    mcpp_fputs( s, ERR);        \
    mcpp_fputc( c, ERR);        \
    mcpp_fputc( '\n', ERR);     \
    }

static int  mcpp_getopt(
    int         argc,
    char * const *  argv,
    const char *    opts
)
/*
 * Get the next option (and it's argument) from the command line.
 */
{
    const char * const   error1 = ": option requires an argument --";
    const char * const   error2 = ": illegal option --";
    static int      sp = 1;
    int             c;
    const char *    cp;

    if (sp == 1) {
        if (argc <= mcpp_optind ||
                argv[ mcpp_optind][ 0] != '-'
                    || argv[ mcpp_optind][ 1] == '\0') {
            return  EOF;
        } else if (strcmp( argv[ mcpp_optind], "--") == 0) {
            mcpp_optind++;
            return  EOF;
        }
    }
/*  mcpp_optopt = c = (unsigned char) argv[ mcpp_optind][ sp];  */
    mcpp_optopt = c = argv[ mcpp_optind][ sp] & UCHARMAX;
    if (c == ':' || (cp = strchr( opts, c)) == NULL) {
        OPTERR( error2, c)
        if (argv[ mcpp_optind][ ++sp] == '\0') {
            mcpp_optind++;
            sp = 1;
        }
        return  '?';
    }
    if (*++cp == ':') {
        if (argv[ mcpp_optind][ sp+1] != '\0') {
            mcpp_optarg = &argv[ mcpp_optind++][ sp+1];
        } else if (argc <= ++mcpp_optind) {
            OPTERR( error1, c)
            sp = 1;
            return  '?';
        } else {
            mcpp_optarg = argv[ mcpp_optind++];
        }
        sp = 1;
    } else {
        if (argv[ mcpp_optind][ ++sp] == '\0') {
            sp = 1;
            mcpp_optind++;
        }
        mcpp_optarg = NULL;
    }
    return  c;
}

#if ! HOST_HAVE_STPCPY
char *  stpcpy(
    char *          dest,
    const char *    src
)
/*
 * Copy the string and return the advanced pointer.
 */
{
    const char * s;
    char *  d;

    for (s = src, d = dest; (*d++ = *s++) != '\0'; )
        ;
    return  d - 1;
}
#endif

void    clear_filelist( void)
/*
 * Free malloced memory for filename-list and directory-list.
 */
{
    const char **   incp;
    INC_LIST *  namep;

    for (incp = incdir; incp < incend; incp++)
        free( (void *) *incp);
    free( (void *) incdir);
    for (namep = fnamelist; namep < fname_end; namep++)
        free( (void *) namep->name);
    free( (void *) fnamelist);
    if (standard)
        free( (void *) once_list);
}
