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
 *                          I N T E R N A L . H
 *      I n t e r n a l   D e f i n i t i o n s   f o r   M C P P
 *
 * In general, definitions in this file should not be changed by implementor.
 */

#ifndef SYSTEM_H
    #error "system.H" must be included prior to "internal.H"
#endif

/* Choices for output destination */
typedef enum {
    OUT,                        /* ~= fp_out    */
    ERR,                        /* ~= fp_err    */
    DBG,                        /* ~= fp_debug  */
    NUM_OUTDEST
} OUTDEST;

#define EOS             '\0'        /* End of string                */
#define CHAR_EOF        0           /* Returned by get_ch() on eof  */

#define VA_ARGS         (UCHARMAX + 1)      /* Signal of variable arguments */
#define GVA_ARGS        (VA_ARGS * 2)       /* GCC-specific variable args   */
#define AVA_ARGS        (VA_ARGS | GVA_ARGS)/* Any variable arguments       */
#define DEF_PRAGMA      (-1 - AVA_ARGS)     /* _Pragma() pseudo-macro       */
#define DEF_NOARGS      (-2 - AVA_ARGS)     /* #define foo vs #define foo() */
#define DEF_NOARGS_PREDEF_OLD   (DEF_NOARGS - 1)
                        /* Compiler-predefined macro without leading '_'    */
#define DEF_NOARGS_PREDEF   (DEF_NOARGS - 2)/* Compiler-predefined macro    */
#define DEF_NOARGS_STANDARD (DEF_NOARGS - 3)/* Standard predefined macro    */
#define DEF_NOARGS_DYNAMIC  (DEF_NOARGS - 4)/* Standard dynamically defined */

/*
 * These magic characters must be control characters which can't be used
 * in source file.
 */
/* for '#pragma MCPP debug macro_call' and -K option in STD mode.   */
#define MAC_INF         0x18        /* Magic for macro informations */
/* In STD and POST_STD modes (IN_SRC and TOK_SEP are for STD mode only).    */
#define DEF_MAGIC       0x19        /* Magic to prevent recursive expansion */
#define IN_SRC          0x1A        /* Magic of name from source    */
#define RT_END          0x1C        /* Magic of macro rescan boundary   */
#define ST_QUOTE        0x1D        /* Magic for stringizing        */
#define CAT             0x1E        /* Token concatenation delim.   */
#define TOK_SEP         0x1F        /* Magic to wrap expanded macro */
/* In OLD_PREP mode.    */
#define COM_SEP         0x1F        /* Comment of 0-length          */

#define MAC_PARM        0x7F        /* Macro parameter signal       */

/* Special character types  */
#define LET             1           /* Letter (alphabet and _)      */
#define DIG             2           /* Digit                        */
#define DOT             4           /* . might start a number       */
#define PUNC            8           /* Punctuators and operators    */
#define QUO             0x10        /* Both flavors of quotation ",'*/
#define SPA             0x20        /* White spaces                 */
#define HSP             0x40
                    /* Horizontal white spaces (' ', '\t', TOK_SEP) */

/*
 * Codes for operators used in #if expression.
 * The value of the scanned operator is stored in 'openum'.
 */
#define INV             0           /* Invalid, must be zero        */
#define OP_EOE          INV         /* End of expression            */
#define VAL             1           /* Value (operand)              */
#define OP_LPA          2           /* (    */
/* The following are unary.     */
#define FIRST_UNOP      OP_PLU      /* First unary operator         */
#define OP_PLU          3           /* +    */ 
#define OP_NEG          4           /* -    */
#define OP_COM          5           /* ~    */
#define OP_NOT          6           /* !    */
#define LAST_UNOP       OP_NOT      /* Last unary operator          */
/* The following are binary.    */
#define FIRST_BINOP     OP_MUL      /* First binary operator        */
#define OP_MUL          7           /* *    */
#define OP_DIV          8           /* /    */
#define OP_MOD          9           /* %    */
#define OP_ADD          10          /* +    */
#define OP_SUB          11          /* -    */
#define OP_SL           12          /* <<   */
#define OP_SR           13          /* >>   */
#define OP_LT           14          /* <    */
#define OP_LE           15          /* <=   */
#define OP_GT           16          /* >    */
#define OP_GE           17          /* >=   */
#define OP_EQ           18          /* ==   */
#define OP_NE           19          /* !=   */
#define OP_AND          20          /* &    */
#define OP_XOR          21          /* ^    */
#define OP_OR           22          /* |    */
#define OP_ANA          23          /* &&   */
#define OP_ORO          24          /* ||   */
#define OP_QUE          25          /* ?    */
#define OP_COL          26          /* :    */
#define LAST_BINOP      OP_COL      /* Last binary operator         */
/* Parenthesis  */
#define OP_RPA          27          /* )    */
#define OP_END          28          /* End of expression marker     */
#define OP_FAIL         (OP_END + 1)    /* For error returns        */

/*
 * The following are operators used in macro definition only.
 */
/* In STD and POST_STD modes.   */
#define OP_STR          30          /* #    */
#define OP_CAT          31          /* ##   */
#define OP_ELL          32          /* ...  */

/*
 * The following are C source operators or punctuators,
 * not preprocessing operators.
 * Note: "sizeof", "defined" are read as identifier for convenience.
 */
#define OP_1            33  /* Any other single byte ops or puncs   */
                                    /* =, ., ;, [, ], {, }, ','     */
#define OP_2            34  /* Any other two bytes operators        */
                    /* &=, |=, ++, +=, --, -=, ->, %=, *=, /=, ^=,  */
#define OP_3            35  /* Three bytes operators :  <<=, >>=    */
/*
 * The following are operators spelled in digraphs.
 */
/* In STD and POST_STD modes.   */
#define OP_LBRACE_D     0x40        /* <% i.e. {    */
#define OP_RBRACE_D     0x41        /* %> i.e. }    */
#define OP_LBRCK_D      0x42        /* <: i.e. [    */
#define OP_RBRCK_D      0x43        /* :> i.e. ]    */
#define OP_SHARP_D      0x44        /* %: i.e. #    */
#define OP_DSHARP_D     0x45        /* %:%: i.e. ## */
#define OP_DIGRAPH      0x40    /* (OP_*_D & OP_DIGRAPH) == 0x40    */

/*
 * The following are for lexical scanning only.
 */
/* Token types          */
#define NO_TOKEN        0
#define NAM             65          /* Identifier (name, keyword)   */
#define NUM             66          /* Preprocessing number         */
#define STR             67          /* Character string literal     */
#define CHR             69          /* Integer character constant   */

/* In STD and POST_STD modes.   */
#define WSTR            68          /* Wide string literal          */
#define WCHR            70          /* Wide character constant      */

#define OPE             71          /* Operator or punctuator       */
#define SPE             72          /* Unknown token (@ or others)  */
#define SEP             73          /* Token separator or magics    */

/* MAC_* represent macro information types for -K option.   */
#define MAC_CALL_START  1
#define MAC_CALL_END    2
#define MAC_ARG_START   3
#define MAC_ARG_END     4

/* MB_ERROR signals wrong multi-byte character sequence.    */
#define MB_ERROR        0x8000

/*
 * The DEFBUF structure stores information about #defined macros.
 * Note that DEFBUF->parmnames is parameter names catenated with commas,
 * which is saved for the check of redefinition for STD mode.
 * 'parmnames' and 'repl' are allocated to the area succeding to name.
 */
typedef struct defbuf {
        struct defbuf * link;       /* Pointer to next def in chain */
        short           nargs;      /* Number of parameters         */
        char *          parmnames;  /* -> Parameter names catenated by ','  */
        char *          repl;       /* Pointer to replacement text  */
        const char *    fname;      /* Macro is defined in the source file  */
        long            mline;      /*          at the line.        */
        char            push;       /* Push level indicator         */
        char            name[1];    /* Macro name                   */
} DEFBUF;

/*
 * The FILEINFO structure stores information about open files and macros
 * being expanded.
 */
typedef struct fileinfo {
        char *          bptr;       /* Current pointer into buffer  */
        long            line;       /* Current line number of file  */
        FILE *          fp;         /* Source file if non-null      */
        long            pos;        /* Position next to #include    */
        struct fileinfo *   parent; /* Link to includer             */
        struct ifinfo *     initif; /* Initial ifstack (return there on EOF)*/
        int             sys_header; /* System header file or not    */
        int             include_opt;        /* Specified by -include option */
        const char **   dirp;       /* Include directory the file resides   */
        /*const*/ char *    src_dir;    /* Directory of source file     */
        const char *    real_fname; /* Real file name               */
        const char *    full_fname; /* Real full path list          */
        char *          filename;   /* File/macro name (maybe changed)      */
        char *          buffer;     /* Buffer of current input line */
} FILEINFO;

/*
 * IFINFO stores information of conditional compilation.
 */
typedef struct ifinfo {
        int             stat;       /* State of compilation         */
        long            ifline;     /* Line #if started             */
        long            elseline;   /* Line #else started           */
} IFINFO;

/*
 * These bits are set in IFINFO.stat
 */
#define WAS_COMPILING   1           /* TRUE if compile set at entry */
#define ELSE_SEEN       2           /* TRUE when #else processed    */
#define TRUE_SEEN       4           /* TRUE when #if TRUE processed */

#define compiling       ifstack[0].stat

#define FP2DEST(fp) \
    (fp == fp_out) ? OUT : \
    ((fp == fp_err) ? ERR : \
    ((fp == fp_debug) ? DBG : \
    ((OUTDEST) -1)))

/* VAL_SIGN structure stores information about evaluated number.    */
typedef struct val_sign {
        expr_t          val;        /* Value                        */
        int             sign;       /* Signed, unsigned, error      */
} VAL_SIGN;

/* Values of VAL_SIGN.sign. */
#define SIGNED          1
#define UNSIGNED        0
#define VAL_ERROR       (-1)

/* LINE_COL stores information of line and column data  */
typedef struct line_col {
        long            line;
        size_t          col;
} LINE_COL;

/* Value of macro_line on macro call error.         */
#define MACRO_ERROR     (-1L)

/*
 * Values of insert_sep (flag of insertion of token separator).
 * Used only in POST_STD mode.
 */
#define NO_SEP          0   /* No separator is inserted             */

#define str_eq(s1, s2)  (strcmp(s1, s2) == 0)

#ifndef IO_SUCCESS
#define IO_SUCCESS      0
#endif
#ifndef IO_ERROR
#define IO_ERROR        (errno ? errno : 1)
#endif

/*
 * Externs
 */

/* The minimum translation limits specified by the Standards.       */
extern struct std_limits_ {
        long    str_len;            /* Least maximum of string len. */
        size_t  id_len;             /* Least maximum of ident len.  */
        int     n_mac_pars;         /* Least maximum of num of pars.*/
        int     exp_nest;           /* Least maximum of expr nest   */
        int     blk_nest;           /* Least maximum of block nest  */
        int     inc_nest;           /* Least maximum of include nest*/
        long    n_macro;            /* Least maximum of num of macro*/
        long    line_num;           /* Maximum source line number   */
} std_limits;    
/* The boolean flags specified by the execution options.    */
extern const struct option_flags_ {
        int     c;                  /* -C option (keep comments)    */
        int     k;                  /* -k option (keep white spaces)*/
        int     z;      /* -z option (no-output of included file)   */
        int     p;                  /* -P option (no #line output)  */
        int     q;                  /* -Q option (diag to mcpp.err) */
        int     v;                  /* -v option (verbose)          */
        int     trig;               /* -3 option (toggle trigraphs) */
        int     dig;                /* -2 option (toggle digraphs)  */
        int     lang_asm;           /* -a option (assembler source) */
        int     no_source_line;     /* Do not output line in diag.  */
        int     dollar_in_name;     /* Allow $ in identifiers       */
} option_flags;

static const int      mcpp_mode = STD;          /* Mode of preprocessing        */
extern int      stdc_val;           /* Value of __STDC__            */
extern long     stdc_ver;           /* Value of __STDC_VERSION__    */
static const long cplus_val=0;          /* Value of __cplusplus for C++ */
extern int      stdc2;      /* cplus_val or (stdc_ver >= 199901L)   */
extern int      stdc3;      /* (stdc_ver or cplus_val) >= 199901L   */
static const int      standard = TRUE;           /* mcpp_mode is STD or POST_STD */
static const int      std_line_prefix = STD_LINE_PREFIX;    /* #line in C source style      */
extern int      warn_level;         /* Level of warning             */
extern int      errors;             /* Error counter                */
extern long     src_line;           /* Current source line number   */
extern int      wrong_line;         /* Force #line to compiler      */
extern int      newlines;           /* Count of blank lines         */
extern const int      keep_comments;      /* Don't remove comments        */
extern const int      keep_spaces;        /* Don't remove white spaces    */
extern int      include_nest;       /* Nesting level of #include    */
extern const char *     null;       /* "" string for convenience    */
extern const char **    inc_dirp;   /* Directory of #includer       */
extern const char *     cur_fname;  /* Current source file name     */
extern int      no_output;          /* Don't output included file   */
extern int      in_directive;       /* In process of #directive     */
extern int      in_define;          /* In #define line              */
extern int      in_getarg;          /* Collecting arguments of macro*/
extern int      in_include;         /* In #include line             */
extern int      in_if;              /* In #if and non-skipped expr. */
extern long     macro_line;         /* Line number of macro call    */
extern char *   macro_name;         /* Currently expanding macro    */
extern int      openum;             /* Number of operator or punct. */
extern IFINFO *     ifptr;          /* -> current ifstack item      */
extern FILEINFO *   infile;         /* Current input file or macro  */
extern FILE *   fp_in;              /* Input stream to preprocess   */
extern FILE *   fp_out;             /* Output stream preprocessed   */
extern FILE *   fp_err;             /* Diagnostics stream           */
extern FILE *   fp_debug;           /* Debugging information stream */
extern const int      insert_sep;         /* Inserted token separator flag*/
static const int      mkdep=0;              /* Output source file dependency*/
static const int      mbchar=0;             /* Encoding of multi-byte char  */
static const int mbchk=0;              /* Possible multi-byte char     */
static const int bsl_in_mbchar=0;      /* 2nd byte of mbchar has '\\'  */
static const int bsl_need_escape=0;/* '\\' in mbchar should be escaped */
extern long     in_asm;             /* In #asm - #endasm block      */
extern jmp_buf  error_exit;         /* Exit on fatal error          */
extern const char *   cur_fullname;       /* Full name of current source  */
extern char *   workp;              /* Free space in work[]         */
extern char * const     work_end;   /* End of work[] buffer         */
extern char     identifier[];       /* Lastly scanned name          */
extern IFINFO   ifstack[];          /* Information of #if nesting   */
extern char     work_buf[];
        /* Temporary buffer for directive line and macro expansion  */

#define xmalloc malloc
#define xrealloc realloc

/* main.c   */
extern void     un_predefine( int clearall);
                /* Undefine predefined macros   */

/* directive.c  */
extern void     directive( void);
                /* Process #directive line      */
extern DEFBUF * do_define( int ignore_redef, int predefine);
                /* Do #define directive         */
extern DEFBUF * look_id( const char * name);
                /* Look for a #define'd thing   */
extern DEFBUF **    look_prev( const char * name, int * cmp);
                /* Look for place to insert def.*/
extern DEFBUF * look_and_install( const char * name, int numargs
        , const char * parmnames, const char * repl);
                /* Look and insert macro def.   */
extern DEFBUF * install_macro( const char * name, int numargs
        , const char * parmnames, const char * repl, DEFBUF ** prevp, int cmp
        , int predefine);
                /* Install a def to symbol table*/
extern int      undefine( const char * name);
                /* Delete from symbol table     */
extern void     dump_a_def( const char * why, const DEFBUF * dp, int newdef
        , int comment, FILE * fp);
                /* Dump a specific macro def    */

/* eval.c   */
extern expr_t   eval_if( void);
                /* Evaluate #if expression      */
extern VAL_SIGN *   eval_num( const char * nump);
                /* Evaluate preprocessing number*/

/* expand.c */
extern char *   (* expand_macro)( DEFBUF * defp, char * out, char * out_end
        , LINE_COL line_col, int * pragma_op);
                /* Expand a macro completely    */
extern void     expand_init();
                /* Initialize expand_macro()    */
extern DEFBUF * is_macro( char ** cp);
                /* The sequence is a macro call?*/

/* support.c    */
extern int      get_unexpandable( int c, int diag);
                /* Get next unexpandable token  */
extern void     skip_nl( void);
                /* Skip to the end of the line  */
extern int      skip_ws( void);
                /* Skip over white-spaces       */
extern int      scan_token( int c, char ** out_pp, char * out_end);
                /* Get the next token           */
extern char *   scan_quote( int delim, char * out, char * out_end, int diag);
                /* Scan a quoted literal        */
extern int      id_operator( const char * name);
                /* Check identifier-like ops    */
extern void     expanding( const char * name, int to_be_freed);
                /* Save macro name expanding    */
extern void     clear_exp_mac( void);
                /* Clear expanding macro infs   */
extern int      get_ch( void);
                /* Get the next char from input */
extern void     unget_ch( void);
                /* Push back the char to input  */
extern FILEINFO *   unget_string( const char * text, const char * name);
                /* Push back the string to input*/
extern char *   save_string( const char * text);
                /* Stuff string in malloc mem.  */
extern FILEINFO *   get_file( const char * name, const char * src_dir
        , const char * fullname, size_t bufsize, int include_opt);
                /* New FILEINFO initialization  */
extern LINE_COL *   get_src_location( LINE_COL * p_line_col);
                /* Get location on source file  */
extern void     cfatal( const char * format, const char * arg1, long arg2
        , const char * arg3);
                /* Print a fatal error and exit */
extern void     cerror( const char * format, const char * arg1, long arg2
        , const char * arg3);
                /* Print an error message       */
extern void     cwarn( const char * format, const char * arg1, long arg2
        , const char * arg3);
                /* Print a warning message      */
/* Support for alternate output mechanisms (e.g. memory buffers) */
extern int mcpp_fputc(int c, OUTDEST od);
extern int mcpp_fputs(const char *s, OUTDEST od);
extern int mcpp_fprintf( OUTDEST od, const char *format, ...);

/* system.c */
extern void     do_options();
                /* Process command line args    */
extern void     init_sys_macro( void);
                /* Define system-specific macro */
extern void     at_start( void);
                /* Commands prior to main input */
extern int      do_include( int next);
                /* Process #include directive   */
extern void     add_file( FILE * fp, const char * src_dir
        , const char * filename, const char * fullname, int include_opt);
                /* Chain the included file      */
extern void     sharp( FILEINFO * sharp_file, int marker);
                /* Output # line number         */
extern void     do_pragma( void);
                /* Process #pragma directive    */
extern void     do_old( void);
                /* Process older directives     */
#if ! HOST_HAVE_STPCPY
extern char *   stpcpy( char * dest, const char * src);
                /* Non-Standard library function*/
#endif

/* directive.c  */
extern void     clear_symtable( void);
                /* Free all macro definitions   */
/* system.c     */
extern void     clear_filelist( void);
                /* Free filename and directory list     */
/* The following 5 functions are to Initialize static variables.    */
/* directive.c  */
extern void     init_directive( void);
/* eval.c   */
extern void     init_eval( void);
/* support.c    */
extern void     init_support( void);
/* system.c */
extern void     init_system( void);

/* Non-ASCII characters are always checked by mb_read().    */
#define NA      0x4000  /* Non-ASCII characters */

/* Horizontal spaces (' ', '\t' and TOK_SEP)    */
#define HSPA    (SPA | HSP)

  /* Pointer to one of the following type_*[].    */

#define EJ1     0x100   /* 1st byte of EUC_JP   */
#define EJ2     0x200   /* 2nd byte of EUC_JP   */
#define GB1     0x400   /* 1st byte of GB2312   */
#define GB2     0x800   /* 2nd byte of GB2312   */
#define KS1     0x1000  /* 1st byte of KSC5601  */
#define KS2     0x2000  /* 2nd byte of KSC5601  */

#define EJ1N    (NA | EJ1)
#define EU12N   (NA | EJ1 | EJ2 | GB1 | GB2 | KS1 | KS2)
    /* 1st or 2nd byte of EUC_JP, GB2312 or KSC5601, or any other non-ASCII */

static const short   char_type[ UCHARMAX + 1] = {
/*
 * For EUC_JP, GB2312, KSC5601 or other similar multi-byte char encodings.
 */

/* Character type codes */
/*   0,     1,     2,     3,     4,     5,     6,     7,                    */
/*   8,     9,     A,     B,     C,     D,     E,     F,       Hex          */

   000,   000,   000,   000,   000,   000,   000,   000,    /* 00           */
   000,   HSPA,  SPA,   SPA,   SPA,   SPA,   000,   000,    /* 08           */
   000,   000,   000,   000,   000,   000,   000,   000,    /* 10           */
    /* 0x17-0x1A and 0x1F will be cleared in some modes by chk_opts()       */
   000,   LET,   LET,   000,   000,   000,   000,   HSPA,   /* 18           */
   HSPA,  PUNC,  QUO,   PUNC,  000,   PUNC,  PUNC,  QUO,    /* 20  !"#$%&'  */
   PUNC,  PUNC,  PUNC,  PUNC,  PUNC,  PUNC,  DOT,   PUNC,   /* 28 ()*+,-./  */
   DIG,   DIG,   DIG,   DIG,   DIG,   DIG,   DIG,   DIG,    /* 30 01234567  */
   DIG,   DIG,   PUNC,  PUNC,  PUNC,  PUNC,  PUNC,  PUNC,   /* 38 89:;<=>?  */

   000,   LET,   LET,   LET,   LET,   LET,   LET,   LET,    /* 40 @ABCDEFG  */
   LET,   LET,   LET,   LET,   LET,   LET,   LET,   LET,    /* 48 HIJKLMNO  */
   LET,   LET,   LET,   LET,   LET,   LET,   LET,   LET,    /* 50 PQRSTUVW  */
   LET,   LET,   LET,   PUNC,  000,   PUNC,  PUNC,  LET,    /* 58 XYZ[\]^_  */
   000,   LET,   LET,   LET,   LET,   LET,   LET,   LET,    /* 60 `abcdefg  */
   LET,   LET,   LET,   LET,   LET,   LET,   LET,   LET,    /* 68 hijklmno  */
   LET,   LET,   LET,   LET,   LET,   LET,   LET,   LET,    /* 70 pqrstuvw  */
   LET,   LET,   LET,   PUNC,  PUNC,  PUNC,  PUNC,  000,    /* 78 xyz{|}~   */

   NA,    NA,    NA,    NA,    NA,    NA,    NA,    NA,     /*   80 .. 87   */
   NA,    NA,    NA,    NA,    NA,    NA,    EJ1N,  NA,     /*   88 .. 8F   */
   NA,    NA,    NA,    NA,    NA,    NA,    NA,    NA,     /*   90 .. 97   */
   NA,    NA,    NA,    NA,    NA,    NA,    NA,    NA,     /*   98 .. 9F   */
   NA,    EU12N, EU12N, EU12N, EU12N, EU12N, EU12N, EU12N,  /*   A0 .. A7   */
   EU12N, EU12N, EU12N, EU12N, EU12N, EU12N, EU12N, EU12N,  /*   A8 .. AF   */
   EU12N, EU12N, EU12N, EU12N, EU12N, EU12N, EU12N, EU12N,  /*   B0 .. B7   */
   EU12N, EU12N, EU12N, EU12N, EU12N, EU12N, EU12N, EU12N,  /*   B8 .. BF   */
   EU12N, EU12N, EU12N, EU12N, EU12N, EU12N, EU12N, EU12N,  /*   C0 .. C7   */
   EU12N, EU12N, EU12N, EU12N, EU12N, EU12N, EU12N, EU12N,  /*   C8 .. CF   */
   EU12N, EU12N, EU12N, EU12N, EU12N, EU12N, EU12N, EU12N,  /*   D0 .. D7   */
   EU12N, EU12N, EU12N, EU12N, EU12N, EU12N, EU12N, EU12N,  /*   D8 .. DF   */
   EU12N, EU12N, EU12N, EU12N, EU12N, EU12N, EU12N, EU12N,  /*   E0 .. E7   */
   EU12N, EU12N, EU12N, EU12N, EU12N, EU12N, EU12N, EU12N,  /*   E8 .. EF   */
   EU12N, EU12N, EU12N, EU12N, EU12N, EU12N, EU12N, EU12N,  /*   F0 .. F7   */
   EU12N, EU12N, EU12N, EU12N, EU12N, EU12N, EU12N, NA,     /*   F8 .. FF   */
};