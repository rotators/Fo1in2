#ifndef _LEX_H_
#define _LEX_H_

#include "tokens.h"

typedef struct {
   int token; /* token we just parsed */
   int type;  /* will be either T_INT, T_FLOAT, T_STRING, or T_SYMBOL */
   union {
      char *stringData;
      int   intData;
      float floatData;
   };
} LexData;

extern LexData lexData;
extern char *tokens[];

#include <stdio.h>

typedef struct {
   const char *name;
   int lastChar;
   int lineno;
   int column;
   int lastLineLen;
   // int lastColumn; // column of last token
   union {
      FILE *file;
      struct {
         char *string;
         int len;
         char *curpos;
         int readEOF;
      } s;
   };
} InputStream;

extern const char* AddFileName(const char *c);
extern void FreeFileNames();
extern void ungetToken(void);
extern void setNextToken(LexData *data);
extern int lex(void);
extern void initLex(void), lexClose(void);
extern void startLex(InputStream *);
extern void continueLex(InputStream *);
extern int lexGetLineno(InputStream *);
extern int lexGetColumn(InputStream *);
extern const char *lexGetFilename(InputStream *);
extern void lexAddToken(int token, char *name);
extern void lexAddConstant(int c, char *name, int type, unsigned long val);
char* lexGetToken(int token);
#define INPUT_FILE   1
#define INPUT_STRING 2

#endif
