#ifndef _OPCODES_H_
#define _OPCODES_H_

//
// Definitions of all the core-level opcodes for the interpreter.
// These should not be modified or changed in any way.
//

// number of longwords for each procedure table entry
#define PROCTABLE_SIZE 6
#define OPCODE_SIZE 2

#define O_OPERATOR   0x8000
#define O_INT        0x4000  // types of constants
#define O_FLOAT      0x2000
#define O_STRING     0x1000  // strings
//#define O_DYNSTRING  0x0800  // dynamic strings
//#define O_TYPEMASK   0xfc00
//#define OP(x) (O_OPERATOR|(x))
#define O_INTOP         (O_CONST|O_INT)
#define O_STRINGOP      (O_CONST|O_STRING)
#define O_FLOATOP       (O_CONST|O_FLOAT)
//#define O_DYNSTRINGOP   (O_STRINGOP|O_DYNSTRING)

// Remember that if any opcodes are added 'in the middle' of this list,
// all scripts must be recompiled.

enum {
	O_NOOP = O_OPERATOR,
	O_CONST,
	O_CRITICAL_START,
	O_CRITICAL_DONE,
	O_JMP,
	O_CALL,
	O_CALL_AT,   // timed function calls
	O_CALL_CONDITION,
	O_CALLSTART,
	O_EXEC,
	O_SPAWN,
	O_FORK,
	O_A_TO_D,
	O_D_TO_A,
	O_EXIT,       // exit prog and purge it from process queue
	O_DETACH,     // detach spawned process from its parent.
	O_EXIT_PROG,  // exit program but leave it in process queue
	O_STOP_PROG,
	O_FETCH_GLOBAL,
	O_STORE_GLOBAL,
	O_FETCH_EXTERNAL,
	O_STORE_EXTERNAL,
	O_EXPORT_VAR,
	O_EXPORT_PROC,
	O_SWAP,
	O_SWAPA,
	O_POP,
	O_DUP,
	O_POP_RETURN,
	O_POP_EXIT,
	O_POP_ADDRESS,
	O_POP_FLAGS,
	O_POP_FLAGS_RETURN,
	O_POP_FLAGS_EXIT,
	O_POP_FLAGS_RETURN_EXTERN,
	O_POP_FLAGS_EXIT_EXTERN,
	O_POP_FLAGS_RETURN_VAL_EXTERN,

	// return from a procedure called from C, leaving the return value
	// on the stack.
	O_POP_FLAGS_RETURN_VAL_EXIT,
	O_POP_FLAGS_RETURN_VAL_EXIT_EXTERN,

	O_CHECK_ARG_COUNT,   // call to do a run-time check of arguments to functions
	O_LOOKUP_STRING_PROC, // call to lookup a procedure index given a string
	O_POP_BASE,
	O_POP_TO_BASE,
	O_PUSH_BASE,
	O_SET_GLOBAL,
	O_FETCH_PROC_ADDRESS,
	O_DUMP,
	O_IF,
	O_WHILE,
	O_STORE,
	O_FETCH,
	O_EQUAL,
	O_NOT_EQUAL,
	O_LESS_EQUAL,
	O_GREATER_EQUAL,
	O_LESS,
	O_GREATER,
	O_ADD,
	O_SUB,
	O_MUL,
	O_DIV,
	O_MOD,
	O_AND,
	O_OR,
	O_BWAND,
	O_BWOR,
	O_BWXOR,
	O_BWNOT,
	O_FLOOR,
	O_NOT,
	O_NEGATE,
	O_WAIT,
	O_CANCEL,
	O_CANCELALL,

	O_STARTCRITICAL,
	O_ENDCRITICAL,

	O_END_CORE // don't use this anywhere, or you'll die
};

// if these ever get above 255, the size of opTable in inttable.i needs to
// be increased.  if it gets bigger than 0x7ff, bad things will happen.

#endif
