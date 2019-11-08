#ifndef _TOKENS_H_
#define _TOKENS_H_

enum { T_PROCEDURE=256,  // begin keywords
	T_NOOP,
	T_CRITICAL,
	T_TRUE,
	T_FALSE,
	T_VARIABLE,
	T_IMPORT,
	T_EXPORT,
	T_IN,
	T_WHEN,
	T_PURE,
	T_INLINE,
	T_BEGIN,
	T_END,
	T_EXIT,
	T_DETACH,
	T_CALL,
	T_CALL_FUNC,
	T_CALL_AT,
	T_CALL_CONDITION,
	T_CHECK_ARG_COUNT,
	T_CANCEL, // cancel events
	T_CANCELALL,  // cancel all events
	T_WAIT,
	T_CALLSTART,
	T_EXEC,
	T_SPAWN,
	T_FORK,
	T_IF,
	T_THEN,
	T_ELSE,
	T_SWITCH,
	T_CASE,
	T_DEFAULT,
	T_WHILE,
	T_DO,
		// new tokens, loops extensions:
	T_FOR,
	T_FOREACH,
	T_BREAK,
	T_CONTINUE,
	T_LOOP_END, // used by code generator to implement proper "continue"
		// end of new tokens
	T_RETURN,
	T_INCLUDE,

	T_START_EXPRESSION,
	T_END_EXPRESSION,
	T_START_ARG,
	T_END_ARG,
	T_START_EVENT,
	T_END_EVENT,
	T_START_REGION,
	T_END_REGION,
	T_START_STATEMENT,
	T_END_STATEMENT,

	T_SYMBOL,
	T_CONSTANT,
	T_INT,
	T_FLOAT,
	T_STRING,
	T_ASSIGN,
	T_ASSIGN_ADD,
	T_ASSIGN_SUB,
	T_ASSIGN_MUL,
	T_ASSIGN_DIV,
	T_INC,		// new
	T_DEC,		// new
	T_EQUAL,
	T_NOT_EQUAL,
	T_LESS_EQUAL,
	T_GREATER_EQUAL,
	T_AND,
	T_OR,
	T_BWAND,
	T_BWOR,
	T_BWXOR,
	T_BWNOT,
	T_FLOOR,
	T_NOT,
	T_NEGATE,

	T_STARTCRITICAL,
	T_ENDCRITICAL,

	T_EOF,
	T_END_CORE,
};

enum {
	C_TRUE = 0,
	C_FALSE,
	C_END_CORE,
};

#endif
