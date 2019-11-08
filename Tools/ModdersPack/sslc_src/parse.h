#ifndef _PARSE_H_
#define _PARSE_H_

#include <stdio.h>

extern	int	compilerErrorTotal;

enum { V_INT=1, V_FLOAT, V_STRING };

/*
 * namelists and stringspaces are encoded with a 2-byte length followed by
 * the name or string.
 * program chunks reference variables by index; if a program encounters
 * a variable index that is greater than the number of locals, this index
 * is referenced as a global variable (after subtracting off the number
 * of local variables).  Global variables can be defined anywhere.
 */

typedef struct {
   int type;   // this type is the type of the variable
   union {
      int intData;
      float floatData;
      int stringData;  /* offset into program's string space */
   };
} Value;

#ifdef BUILDING_DLL

typedef struct {
	int line;
	const char* file;
} Reference;

#endif

#define V_LOCAL    1
#define V_GLOBAL   2
#define V_IMPORT   3
#define V_EXPORT   4
typedef struct {
   int name;   /* offset into program or procedure's namelist */
   int* references;
   int numRefs;
   Value value;
   int type;   // this type is where it was declared
   int arrayLen;
   int declared;
   const char* fdeclared;
   int uses;
   int initialized; // 1 if this variable is explicitly initialized
} Variable;

typedef struct {
   Variable *variables;
   int numVariables;
} VariableList;

#define P_REFERENCE 0x08000000
typedef struct {
   int token;
   const char* file;
   int lineNum;
   Value value;
   int column;
   int stringify;
} Node;

typedef struct {
   Node *nodes;
   int numNodes;
} NodeList;

#define P_TIMED        0x01
#define P_CONDITIONAL  0x02
#define P_IMPORT       0x04
#define P_EXPORT       0x08
#define P_CRITICAL     0x10
#define P_PURE         0x20
#define P_INLINE       0x40
typedef struct {
   int  name;          /* offset into main program's namelist    */
   int type;           /* timed, conditional, or system procedure */
   union {
      int time;
      NodeList condition;
   };
   char *namelist;     /* this program's namelist */
   int numArgs;
   int defined;         // set to 1 if this has been define (and not just declared)
   VariableList variables;
   int* references;
   int numRefs;
   int uses;
   int declared;
   const char* fdeclared;
   int start;
   const char* fstart;
   int end;
   const char* fend;
   NodeList nodes;
   int minArgs; // minimum number of arguments for call
} Procedure;

typedef struct {
   Procedure *procedures;
   int numProcedures;
} ProcedureList;

#include <setjmp.h>

typedef struct {
   ProcedureList procedures;
   VariableList variables;
   VariableList externals;  // all variables either exported from this module,
                            // or imported to this module
   char *stringspace;   /* this program's string space */
   char *namelist;     /* this program's global namelist */
   jmp_buf env;
   //jmp_buf stmtEnv;
} Program;

#include "lex.h"

extern void parse(InputStream *, const char *);
extern void dumpProgram(Program *);

extern void parseStatement(Procedure *p);
extern void parseStatementNoSemicolon(Procedure *p);
extern void parseExpression(Procedure *p, NodeList *nodes);
extern void parseExpGroup(Procedure *p, NodeList *nodes, int num);

extern void emitOp(Procedure *p, NodeList *nodes, int token);
extern void emitInt(Procedure *p, NodeList *nodes, int i);
extern void emitNode(Procedure *p, NodeList *n, LexData *data);

extern int outputStr(const char *s);
extern int parseOutput(const char *format, ...);
extern void parseMessageAtNode(const Node* node, const char *format, ...);
extern void parseWarningAtNode(const Node* node, const char *format, ...);
extern void parseWarning(const char *format, ...);
extern void parseErrorAtNode(const Node* node, const char *format, ...);
extern void parseError(const char *format, ...);
extern void parseSemanticError(const char *format, ...);

extern void CloneLexData(LexData *dest, LexData *source);
extern void GenTmpVar(Procedure *p, LexData* lex);

extern void parseLibArgs(Procedure *, NodeList*, int, int);
extern int expectToken(int expectToken);

extern void freeCurrentProgram(void);
extern char *getName(int offset, char *namelist);

#define P_GLOBAL    0x80000000
#define P_LOCAL     0x40000000
#define P_PROCEDURE 0x20000000
#define P_EXTERN    0x10000000

#include "opcodes.h"

// write out num expressions with opcode x

#define WEXP(x, num) i++; i = writeNumExpression(n, i, num, f); writeOp(x, f)
#define WEXPPROC(x, num) i++; i = writeNumExpressionProc(n, i, num, f); writeOp(x, f)

// make a case for token T_x, write out opcode O_x and num expressions

// use this one to write an 'statement' type opcode/lib function
#define EXP(x, num) case T_##x: WEXP(O_##x, num); break
// this is like above, but can take procedures as arguments
#define EXPPROC(x, num) case T_##x: WEXPPROC(O_##x, num); break

// use this one to write out a library function/opcode that can be
// used in both a statement and expression context, when that opcode/function
// is being used as a statement (for the expression case, just use EXP/EXPPROC)
#define EXPST(x, num) case T_##x: WEXP(O_##x, num); writeOp(O_POP, f); break
#define EXPSTPROC(x, num) case T_##x: WEXPPROC(O_##x, num); writeOp(O_POP, f); break

// write out opcode O_x for token T_x; assumes the output file handle is 'f'.
#define ST(x) case T_##x: i++; writeOp(O_##x, f); break

// parse N expressions, separated by commas.
// assumes input procedure pointer is 'p', and
// all nodes are going into that procedure's node list.

// Use this one to parse statements
#define PARSE(t, n) case T_##t: parseLibArgs(p, nodes, n, 0); break

// Use this one to parse statements with procedures at specific arguments
#define PARSEPROC(t, n, ps) case T_##t: parseLibArgs(p, nodes, n, ps); break

// use this one to parse expressions
#define PARSEEXP(t, n) case T_##t: \
   emitOp(p, nodes, T_##t);        \
   parseLibArgs(p, nodes, n, 0);   \
   break


#endif
