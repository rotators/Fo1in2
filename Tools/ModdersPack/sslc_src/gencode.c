#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <setjmp.h>

#include "parse.h"
#include "parselib.h"
#include "extra.h"

#include "opcodes.h"
#include "oplib.h"
#include "opextra.h"

#include "gencode.h"

extern int shortCircuit;

static Program *currentProgram;
static Procedure *currentProcedure;

static int procedureStart;
static int startOffset;

typedef struct {
	int startPos;
	int numBreaks;
	int numContinue;
} LoopInfo;

LoopInfo loopStack[100]; // pointers to beginning of while loops
int loopStackPos = 0;
int breakStack[2048]; // pointers to arguments to JMP (break statements)
int breakStackPos = 0;
int continueStack[2048]; // pointers to arguments to JMP (continue statements)
int continueStackPos = 0;

static int outputSeek(FILE *f, int where, int mode) {
	return fseek(f, where, mode);
}

static int outputTell(FILE *f) {
	return ftell(f);
}

static void writeByte(unsigned char a, FILE *f) {
	fputc(a, f);
}

static void writeWord(unsigned short a, FILE *f) {
	writeByte((unsigned char)(a >> 8), f);
	writeByte((unsigned char)(a & 0x00ff), f);
}

static void writeLong(unsigned long a, FILE *f) {
	writeWord((unsigned short)(a >> 16), f);
	writeWord((unsigned short)(a & 0x0000ffff), f);
}

void writeInt(unsigned long a, FILE *f) {
	writeWord(O_INTOP, f);
	writeLong(a, f);
}

void writeFloat(float a, FILE *f) {
	writeWord(O_FLOATOP, f);
	writeLong(*(unsigned long *)&a, f);
}

void writeString(unsigned long a, FILE *f) {
	writeWord(O_STRINGOP, f);
	writeLong(a, f);
}

void writeOp(unsigned short op, FILE *f) {
	writeWord(op, f);
}

static void writeMemory(unsigned char *p, int len, FILE *f) {
	while(len--) writeByte(*p++, f);
}

static void writenamelist(FILE *f, char *namelist) {
	if (namelist) {
		int len;
		writeLong(*(unsigned long *)namelist, f);
		namelist += 4;
		while((len = *(unsigned short *)namelist) != 0xffff) {
			writeWord((unsigned short)len, f);
			writeMemory(namelist + 2, len, f);
			namelist += len + 2;
		}
	}
	writeMemory("\xff\xff\xff\xff", 4, f);
}

static void writeProcAddress(NodeList *n, int i, FILE *f) {
	int isRef = 0;
	switch(n->nodes[i].token) {
	case T_SYMBOL:

		writeInt(n->nodes[i].value.intData, f);
		/*if (n->nodes[i].flags & P_REFERENCE)
			isRef = 1;  */
		if (!(n->nodes[i].value.type & P_PROCEDURE)) {
			if (n->nodes[i].value.type & P_LOCAL) {
				writeOp(O_FETCH, f);
				if (!isRef)
					writeOp(O_LOOKUP_STRING_PROC, f);
			}
			else if (n->nodes[i].value.type & P_GLOBAL) {
				writeOp(O_FETCH_GLOBAL, f);
				if (!isRef)
					writeOp(O_LOOKUP_STRING_PROC, f);
			}
			else if (n->nodes[i].value.type & P_EXTERN) {
				writeOp(O_FETCH_EXTERNAL, f);
				if (!isRef)
					writeOp(O_LOOKUP_STRING_PROC, f);
			}
		}
		break;
	case T_CONSTANT:
		if (n->nodes[i].value.type == V_STRING) {
			writeString(n->nodes[i].value.stringData, f);
			writeOp(O_LOOKUP_STRING_PROC, f);
		}
		break;
	default:
		parseError("Internal error, invalid function call address\n");
		break;
	}
}

/*
* each element in the table is 24 bytes long:
*    first long == index into namelist for procedure name
*    second     == type of function (P_TIMED, P_CONDITIONAL, none)
*    third      == time this proc should go off, if timed
*    fourth     == ptr to conditional code, if conditional
*    fifth      == ptr to procedure
*    sixth      == number of args to procedure
*/
static void writeProcedureTable(FILE *f, ProcedureList *p) {
	int i;

	writeLong(p->numProcedures, f);    // write size of table in elements
	for (i=0; i < p->numProcedures; ++i) {
		writeLong(p->procedures[i].name, f);
		writeLong(p->procedures[i].type, f);
		if (p->procedures[i].type & P_TIMED)
			writeLong(p->procedures[i].time, f);
		else
			writeLong(0, f);

		writeLong(0, f);     // expression offset
		writeLong(0, f);     // position of this procedure
		writeLong(p->procedures[i].numArgs, f);
	}
}

static void patchOffset(int where, int with, FILE *f) {
	int here = outputTell(f);
	outputSeek(f, where, SEEK_SET);
	writeLong(with, f);
	outputSeek(f, here, SEEK_SET);
}

static void patchProcTableEntry(int where, int which, int elem, int with, FILE *f) {
	// +4 for table size field
	patchOffset(4 + where + which*4*PROCTABLE_SIZE + elem*4, with, f);
}

static void writeVariable(Variable *v, char *namelist, FILE *f) {
	namelist = namelist;
	//   if (!v->uses && warnings)
	//      parseOutput("Warning: variable %s not referenced\n", getName(v->name, namelist));

	switch(v->value.type) {
	case V_INT: writeInt(v->value.intData, f); break;
	case V_FLOAT: writeFloat(v->value.floatData, f); break;
	case V_STRING: writeString(v->value.stringData, f); break;
	}
}

static int writeCallFunc(NodeList *n, int i, FILE *f, int *numArgs) {
	int ret = outputTell(f), proc;
	i++;

	if (n->nodes[i].token != T_SYMBOL &&
		(n->nodes[i].token == T_CONSTANT && n->nodes[i].value.type != V_STRING))
		parseError("Internal error, symbol or string expected.");

	writeInt(0, f);       // push return address
	writeOp(O_D_TO_A, f);

	proc = i;

	i++;

	if (n->nodes[i].token != T_START_EVENT)
		parseError("Internal error, no starting event.");

	i++;

	if (n->nodes[i].token == T_START_ARG) {
		int args = 0;
		i++;
		while(n->nodes[i].token != T_END_ARG) {
			i = writeExpression(n, i, f);
			args++;
		}
		i++;
		writeInt(args, f);
		*numArgs = args;
	}
	else {
		*numArgs = 0;
		writeInt(0, f);
	}

	writeProcAddress(n, proc, f);

	if (n->nodes[i].token == T_CHECK_ARG_COUNT) {
		writeOp(O_DUP, f);      // dup the proc address
		writeInt(*numArgs, f);  // write number of args
		writeOp(O_CHECK_ARG_COUNT, f);   // check to make sure right number
		i++;
	}

	writeOp(O_CALL, f);

	patchOffset(ret+OPCODE_SIZE, outputTell(f), f);  // patch return address

	if (n->nodes[i].token != T_END_EVENT)
		parseError("Internal error, no ending event.");
	i++;
	return i;
}

int writeNode(NodeList *n, int i, FILE *f) {
	switch(n->nodes[i].token) {
	case T_START_EXPRESSION:
		i = writeExpression(n, i, f);
		break;

	case T_CALL_FUNC: {
		int args;
		i = writeCallFunc(n, i, f, &args);
		break;
					  }
	case T_CONSTANT:
		switch(n->nodes[i].value.type) {
		case V_STRING: writeString(n->nodes[i].value.stringData, f); break;
		case V_FLOAT:  writeFloat(n->nodes[i].value.floatData, f); break;
		case V_INT:    writeInt(n->nodes[i].value.intData, f); break;
		}
		i++;
		break;
	case T_SYMBOL:
		if (n->nodes[i].value.type & P_PROCEDURE) {
			if (n->nodes[i].stringify) {  // special case when passing procedure as reference
				writeString(n->nodes[i].stringify, f);
			} else
				writeInt(n->nodes[i].value.intData, f);
		}
		else {
			if (n->nodes[i].value.type & P_LOCAL) {
				writeInt(n->nodes[i].value.intData, f);
				writeOp(O_FETCH, f);
			}
			else if (n->nodes[i].value.type & P_GLOBAL) {
				writeInt(n->nodes[i].value.intData, f);
				writeOp(O_FETCH_GLOBAL, f);
			}
			else if (n->nodes[i].value.type & P_EXTERN) {
				writeString(currentProgram->externals.variables[n->nodes[i].value.intData].name, f);
				writeOp(O_FETCH_EXTERNAL, f);
			}
			else parseError("Error, unknown type for symbol %x\n", n->nodes[i].value.type);
		}
		i++;
		break;
	case T_IF: { // phobos2077 - ternary (conditional) expressions
		int elseAdr, outAdr;
		elseAdr = outputTell(f);
		writeInt(0, f);
		i = writeExpression(n, i+1, f); // condition
		writeOp(O_IF, f);
		i = writeExpression(n, i, f); // expr if true
		outAdr = outputTell(f);
		writeInt(0, f);
		writeOp(O_JMP, f);
		patchOffset(elseAdr + OPCODE_SIZE, outputTell(f), f);
		i = writeExpression(n, i, f); // expr if false
		patchOffset(outAdr + OPCODE_SIZE, outputTell(f), f);
		break;
			   }
	case T_AND:
	case T_OR: {
		// this is encountered after left argument expression was written, so we have it's result on stack top
		if (shortCircuit) { // phobos2077 - short circuit evaluation of logical operators
			int skipAddr;
			writeOp(O_DUP, f);   // duplicate expr result, if it is 0, this value will be used as result of AND
			skipAddr = outputTell(f);
			writeInt(0, f);      // address for O_IF
			writeOp(O_SWAP, f);  // swap result and address to fit O_IF signature
			if (n->nodes[i].token == T_OR) {
				writeOp(O_NOT, f); // reverse value from left expression, for O_IF
			}
			writeOp(O_IF, f); // the actual conditional jump (jumps if stack top contains 0)
			writeOp(O_POP, f); // remove result of first expression from stack
			i = writeExpression(n, i+1, f); // right expression - if not skipped, will be result of whole AND/OR expression
			patchOffset(skipAddr + OPCODE_SIZE, outputTell(f), f); // point O_IF to skip to this position
		} else { // vanilla code
			int tok = n->nodes[i].token;
			i = writeExpression(n, i+1, f);
			writeOp((tok == T_AND) ? O_AND : O_OR, f);
		}
		break;
			}
	default: {
		switch(n->nodes[i].token) {
		case T_BWNOT: writeOp(O_BWNOT, f); i++; break;
		case T_NEGATE: writeOp(O_NEGATE, f); i++; break;
		case T_EQUAL: writeOp(O_EQUAL, f); i++; break;
		case T_NOT_EQUAL: writeOp(O_NOT_EQUAL, f); i++; break;
		case T_LESS_EQUAL: writeOp(O_LESS_EQUAL, f); i++; break;
		case T_GREATER_EQUAL: writeOp(O_GREATER_EQUAL, f); i++; break;
		case '<': writeOp(O_LESS, f); i++; break;
		case '>': writeOp(O_GREATER, f); i++; break;
		case '+': writeOp(O_ADD, f); i++; break;
		case '-': writeOp(O_SUB, f); i++; break;
		case '*': writeOp(O_MUL, f); i++; break;
		case '/': writeOp(O_DIV, f); i++; break;
		case '%': writeOp(O_MOD, f); i++; break;
		case '^': writeOp(O_TS_POW, f); i++; break; // sfall
		//case T_AND: writeOp(O_AND, f); i++; break; // pbs - removed
		//case T_OR: writeOp(O_OR, f); i++; break; // pbs - removed
		case T_BWAND: writeOp(O_BWAND, f); i++; break;
		case T_BWOR: writeOp(O_BWOR, f); i++; break;
		case T_NOT: writeOp(O_NOT, f); i++; break;
		case T_FLOOR: writeOp(O_FLOOR, f); i++; break;
		case T_BWXOR: writeOp(O_BWXOR, f); i++; break;
		default: i = writeLibExpression(n, i, f); break;
		}
		break;
			 }
	}
	return i;
}

static void writeExportedVariables(VariableList *v, FILE *f) {
	int i;

	for (i=0; i < v->numVariables; ++i)
		if (v->variables[i].type & V_EXPORT) {
			writeString(v->variables[i].name, f);
			writeOp(O_EXPORT_VAR, f);
		}
}

static void writeExportedProcedures(ProcedureList *p, FILE *f) {
	int i;

	for (i=0; i < p->numProcedures; ++i)
		if (p->procedures[i].type & P_EXPORT) {
			writeInt(p->procedures[i].numArgs, f);
			writeInt(i, f);
			writeOp(O_EXPORT_PROC, f);
		}
}

static void writeExportedValues(VariableList *v, char *namelist, FILE *f) {
	int i;

	for (i=0; i < v->numVariables; ++i)
		if (v->variables[i].type & V_EXPORT) {
			writeVariable(v->variables + i, namelist, f);
			writeString(v->variables[i].name, f);
			writeOp(O_STORE_EXTERNAL, f);
		}
}

static void writeVariables(VariableList *v, char *namelist, int start, FILE *f) {
	int i;

	for (i=start; i<v->numVariables; ++i)
		writeVariable(v->variables + i, namelist, f);
}

/*
static void writeClearLocalVariables(VariableList *v, FILE *f) {
int i;

for (i=0; i<v->numVariables; ++i) {
writeInt(0, f);
writeInt(i, f);
writeOp(O_STORE, f);
}
}
*/

int writeExpressionProc(NodeList *n, int i, FILE *f) {
	if (n->nodes[i].token != T_START_EXPRESSION)
		parseError("no starting expression");
	/*
		phobos2077 - commented this out, because passing procedures as arguments is now done on parsing stage

	if (n->nodes[i+1].token == T_CALL_FUNC) {
		i+=2;
		writeProcAddress(n, i, f);

		i++;
		if (n->nodes[i].token != T_START_EVENT)
			parseError("No starting event");
		i++;
		if (n->nodes[i].token != T_END_EVENT)
			parseError("Arguments not allowed for procedures as arguments");
		i++;
		if (n->nodes[i].token != T_END_EXPRESSION)
			parseError("No ending expression");
		i++;
	}
	else*/
	i = writeExpression(n, i, f);
	return i;
}

int writeNumExpressionProc(NodeList *n, int i, int num, FILE *f) {
	while(num--)
		i = writeExpressionProc(n, i, f);

	return i;
}

int writeExpression(NodeList *n, int i, FILE *f) {
	if (n->nodes[i++].token != T_START_EXPRESSION)
		parseError("start-expression expected.");

	while(n->nodes[i].token != T_END_EXPRESSION) {
		if (n->nodes[i].token == T_CALL_FUNC) {
			int args;
			int proc = n->nodes[i+1].value.intData;
			int j = i;
			i = writeCallFunc(n, i, f, &args);
			if (n->nodes[i+1].token == T_SYMBOL &&
				(n->nodes[i+1].value.type & P_PROCEDURE))
				if (currentProgram->procedures.procedures[proc].numArgs != args) {
					parseErrorAtNode(&n->nodes[j], "Wrong number of arguments to procedure %s.  Expected %d, got %d\n",
						getName(currentProgram->procedures.procedures[proc].name, currentProgram->namelist),
						currentProgram->procedures.procedures[proc].numArgs,
						args);
				}
		}
		else
			i = writeNode(n, i, f);
	}

	return i+1;
}

int writeNumExpression(NodeList *n, int i, int num, FILE *f) {
	while(num--)
		i = writeExpression(n, i, f);

	return i;
}

static int writeStatement(NodeList *n, int i, FILE *f) {
	if (n->nodes[i].token == T_BEGIN)
		return writeBlock(n, i, f);

	if (n->nodes[i].token != T_START_STATEMENT)
		parseError("start-statement expected");

	i++;

	while(n->nodes[i].token != T_END_STATEMENT) {
		switch(n->nodes[i].token) {
		case T_BEGIN: i = writeBlock(n, i, f); break;
		case T_START_STATEMENT: i = writeStatement(n, i, f); break;
		case T_CANCEL:
			i++;
			if (n->nodes[i].token != T_SYMBOL)
				parseError("Internal error, symbol expected.");

			writeProcAddress(n, i, f);
			writeOp(O_CANCEL, f);
			break;

			EXP(CANCELALL, 0);

		case T_CALL_AT: {
			int proc;
			int flag = 0;
			int args = 0;

			i++;
			if (n->nodes[i].token != T_SYMBOL &&
				(n->nodes[i].token == T_CONSTANT && n->nodes[i].value.type != V_STRING))
				parseError("Internal error, symbol expected.");

			proc = i;

			i++;

			if (n->nodes[i].token != T_START_EVENT)
				parseError("Internal error, no starting event.");

			i++;

			if (n->nodes[i].token == T_START_ARG) {
				parseError("Internal error, arguments not currently allowed to events.");
				i++;
				while(n->nodes[i].token != T_END_ARG) {
					i = writeExpression(n, i, f);
					args++;
				}
				i++;
				writeInt(args, f);
			}

			if (n->nodes[i].token == T_CHECK_ARG_COUNT) {
				flag = 1;
				i++;
			}

			if (n->nodes[i].token != T_IN)
				parseError("Internal error, no event specifier, got %d", n->nodes[i].token);

			i++;

			if (n->nodes[i].token != T_START_EXPRESSION)
				parseError("Internal error, no starting expression");

			i = writeExpression(n, i, f);

			writeProcAddress(n, proc, f);

			if (flag) {
				writeOp(O_DUP, f);
				writeInt(args, f);
				writeOp(O_CHECK_ARG_COUNT, f);
				i++;
			}

			writeOp(O_CALL_AT, f);
			break;
						}
		case T_CALL_CONDITION: {
			int addr = outputTell(f), proc, cond, flag = 0;

			i++;

			if (n->nodes[i].token != T_SYMBOL &&
				(n->nodes[i].token == T_CONSTANT && n->nodes[i].value.type != V_STRING))
				parseError("Internal error, symbol expected.");

			writeInt(0, f);
			writeOp(O_JMP, f);

			proc = i;  // save procedure node

			i++;

			if (n->nodes[i].token != T_START_EVENT)
				parseError("Internal error, no starting event.");

			i++;

			if (n->nodes[i].token == T_START_ARG)
				parseError("Internal error, arguments not currently allowed to events.");

			if (n->nodes[i].token == T_CHECK_ARG_COUNT) {
				flag = 1;
				i++;
			}

			if (n->nodes[i].token != T_WHEN)
				parseError("Internal error, no event specifier");

			i++;

			if (n->nodes[i].token != T_START_EXPRESSION)
				parseError("Internal error, no starting expression");

			cond = outputTell(f);
			writeOp(O_CRITICAL_START, f);
			i = writeExpression(n, i, f);
			writeOp(O_CRITICAL_DONE, f);
			writeOp(O_STOP_PROG, f);

			patchOffset(addr + OPCODE_SIZE, outputTell(f), f);
			writeInt(cond, f);
			writeProcAddress(n, proc, f);
			if (flag) {
				writeOp(O_DUP, f);
				writeInt(0, f);
				writeOp(O_CHECK_ARG_COUNT, f);
				i++;
			}
			writeOp(O_CALL_CONDITION, f);
			break;
							   }
		case T_CALL: {
			int ret = outputTell(f), proc;
			int args = 0;
			i++;

			if (n->nodes[i].token != T_SYMBOL &&
				(n->nodes[i].token == T_CONSTANT && n->nodes[i].value.type != V_STRING))
				parseError("Internal error, symbol expected.");

			writeInt(0, f);       // push return address
			writeOp(O_D_TO_A, f);

			proc = i;

			i++;

			if (n->nodes[i].token != T_START_EVENT)
				parseError("Internal error, no starting event.");

			i++;

			if (n->nodes[i].token == T_START_ARG) {
				i++;
				while(n->nodes[i].token != T_END_ARG) {
					i = writeExpression(n, i, f);
					args++;
				}
				i++;
			}
			writeInt(args, f);

			writeProcAddress(n, proc, f);

			if (n->nodes[i].token == T_CHECK_ARG_COUNT) {
				writeOp(O_DUP, f);
				writeInt(args, f);
				writeOp(O_CHECK_ARG_COUNT, f);
				i++;
			}

			writeOp(O_CALL, f);

			patchOffset(ret+OPCODE_SIZE, outputTell(f), f);  // patch return address
			writeOp(O_POP, f);

			if (n->nodes[i].token != T_END_EVENT)
				parseError("Internal error, no ending event.");
			i++;
			break;
					 }
		case T_IF: {
			int true, false, j;

			false = outputTell(f);
			writeInt(0, f);
			j = i;
			i = writeExpression(n, i+1, f);
			writeOp(O_IF, f);

			if (n->nodes[i].token != T_THEN)
				parseError("Internal error, 'then' expected.");
			i++;     // skip then
			if (n->nodes[i].token == T_BEGIN) {
				i++;
				while(n->nodes[i].token != T_END)
					i = writeStatement(n, i, f);
				i++;  // skip end
			}
			else i = writeStatement(n, i, f);

			if (n->nodes[i].token == T_ELSE) {
				true = outputTell(f);
				writeInt(0, f);
				writeOp(O_JMP, f);

				patchOffset(false+OPCODE_SIZE, outputTell(f), f);

				i++;
				if (n->nodes[i].token == T_BEGIN) {
					i++;
					while(n->nodes[i].token != T_END)
						i = writeStatement(n, i, f);
					i++;
				}
				else i = writeStatement(n, i, f);
				patchOffset(true+OPCODE_SIZE, outputTell(f), f);
			}
			else {
				unsigned long a = outputTell(f);
				patchOffset(false+OPCODE_SIZE, a, f);
			}

			break;
				   }
		case T_WHILE: {
			int false, top, j, pos;

			false = outputTell(f);
			writeInt(0, f);
			top = outputTell(f);
			loopStack[++loopStackPos].startPos = top;
			loopStack[loopStackPos].numBreaks = 0;
			loopStack[loopStackPos].numContinue = 0;
			i = writeExpression(n, i+1, f);
			writeOp(O_WHILE, f);

			if (n->nodes[i].token != T_DO)
				parseError("Internal error, 'do' expected.");
			i++;     // skip do
			if (n->nodes[i].token == T_BEGIN) {
				i++;
				while(n->nodes[i].token != T_END)
					i = writeStatement(n, i, f);
				i++;  // skip end
			}
			else i = writeStatement(n, i, f);

			writeInt(top, f);
			writeOp(O_JMP, f);

			pos = outputTell(f);
			patchOffset(false+OPCODE_SIZE, pos, f);

			for (j = 0; j < loopStack[loopStackPos].numBreaks; j++) { // for each break, change it's JMP argument to proper address
				patchOffset(breakStack[breakStackPos--] + OPCODE_SIZE, pos, f);
			}
			continueStackPos -= loopStack[loopStackPos].numContinue; // remove all "continue" pointers found in current loop from the stack,
																     // this will only apply to "WHILE" loops
			loopStackPos--;

			break;
					  }
		case T_ASSIGN_ADD:
		case T_ASSIGN_MUL:
		case T_ASSIGN_SUB:
		case T_ASSIGN_DIV: {
			int j = i-1;
			int op;

			switch(n->nodes[i].token) {
			case T_ASSIGN_ADD: op = O_ADD; break;
			case T_ASSIGN_MUL: op = O_MUL; break;
			case T_ASSIGN_SUB: op = O_SUB; break;
			case T_ASSIGN_DIV: op = O_DIV; break;
			}

			if (n->nodes[j].value.type & P_LOCAL) {
				writeInt(n->nodes[j].value.intData, f);
				writeOp(O_FETCH, f);
			} else if (n->nodes[j].value.type & P_GLOBAL) {
				writeInt(n->nodes[j].value.intData, f);
				writeOp(O_FETCH_GLOBAL, f);
			} else if (n->nodes[j].value.type & P_EXTERN) {
				writeString(currentProgram->externals.variables[n->nodes[j].value.intData].name, f);
				writeOp(O_FETCH_EXTERNAL, f);
			}

			else parseError("Error, unknown type for symbol %x\n", n->nodes[j].value.type);

			i = writeExpression(n, i+1, f);

			writeOp((unsigned short)op, f);

			if (n->nodes[j].value.type & P_LOCAL) {
				writeInt(n->nodes[j].value.intData, f);
				writeOp(O_STORE, f);
			}
			else if (n->nodes[j].value.type & P_GLOBAL) {
				writeInt(n->nodes[j].value.intData, f);
				writeOp(O_STORE_GLOBAL, f);
			}
			else {
				writeString(currentProgram->externals.variables[n->nodes[j].value.intData].name, f);
				writeOp(O_STORE_EXTERNAL, f);
			}
			break;
						   }
		case T_ASSIGN: {
			int j = i-1;
			i = writeExpression(n, i+1, f);
			if (n->nodes[j].value.type & P_LOCAL) {
				writeInt(n->nodes[j].value.intData, f);
				writeOp(O_STORE, f);
			}
			else if (n->nodes[j].value.type & P_GLOBAL) {
				writeInt(n->nodes[j].value.intData, f);
				writeOp(O_STORE_GLOBAL, f);
			}
			else if (n->nodes[j].value.type & P_EXTERN) {
				writeString(currentProgram->externals.variables[n->nodes[j].value.intData].name, f);
				writeOp(O_STORE_EXTERNAL, f);
			}
			else parseError("Error, unknown type for symbol %x\n", n->nodes[j].value.type);
			break;
					   }
					   EXP(WAIT, 1);
					   EXP(FORK, 1);
					   EXP(SPAWN, 1);
					   EXP(CALLSTART, 1);
					   EXP(EXEC, 1);
					   EXP(DETACH, 0);
					   EXP(EXIT, 0);
					   EXP(STARTCRITICAL, 0);
					   EXP(ENDCRITICAL, 0);
		case T_RETURN: {
			int value = 0;

			i++;
			if (n->nodes[i].token == T_START_EXPRESSION) { // return with a value
				value = 1;
				i = writeExpression(n, i, f);
				writeOp(O_D_TO_A, f);
				writeOp(O_SWAPA, f);
			}

			// clear our stack
			writeOp(O_POP_TO_BASE, f);

			// restore previous base address
			writeOp(O_POP_BASE, f);

			if (value) // push any return value
				writeOp(O_A_TO_D, f);

			if (currentProcedure && (currentProcedure->type & P_CRITICAL))
				writeOp(O_CRITICAL_DONE, f);

			writeOp(O_POP_RETURN, f);
			break;
					   }
		case T_CONTINUE:
			loopStack[loopStackPos].numContinue++;
			continueStack[++continueStackPos] = outputTell(f); // address will be patched to point to end of loop for FOR and FOREACH loops
			writeInt(loopStack[loopStackPos].startPos, f); // but default address will be used by "while"
			writeOp(O_JMP, f);
			i++;
			break;
		case T_BREAK:
			loopStack[loopStackPos].numBreaks++;
			breakStack[++breakStackPos] = outputTell(f); // address will be patched to point to exit from loop
			writeInt(0, f);
			writeOp(O_JMP, f);
			i++;
			break;
		case T_LOOP_END: {
			// should be only once at the end of each FOR, FOREACH loop, before increment operator
			int j, pos = outputTell(f);
			for (j = 0; j < loopStack[loopStackPos].numContinue; j++) { // for each continue, change it's JMP to point to this address
				patchOffset(continueStack[continueStackPos--] + OPCODE_SIZE, pos, f);
			}
			loopStack[loopStackPos].numContinue = 0;
			i++;
						 }
			break;
		default: i = writeLibStatement(n, i, f); break;
		}
	}
	return i+1;
}

static int writeBlock(NodeList *n, int i, FILE *f) {
	if (n->nodes[i].token != T_BEGIN)
		parseError("begin expected");

	i++;
	while(n->nodes[i].token != T_END)
		i = writeStatement(n, i, f);

	return i+1;
}

static void writeCode(NodeList *n, FILE *f) {
	writeBlock(n, 0, f);
}

extern int IsProtectedProc(const char* c);
static void writeProcedure(Procedure *p, int tableOffset, FILE *f) {
	if (!(p->type & (P_IMPORT|P_EXPORT)) && p->defined == 1)
		parseError("No code for procedure %s\n", getName(p->name, currentProgram->namelist));

	if (!p->nodes.numNodes) return;

	if (!p->uses && !IsProtectedProc(getName(p->name, currentProgram->namelist)))
		parseWarningAtNode(&p->nodes.nodes[0], "Procedure %s not referenced\n", getName(p->name, currentProgram->namelist));

	if (p->type & P_CONDITIONAL) {
		int here, cond;

		here = outputTell(f);
		writeInt(0, f);  // offset to start of this procedure
		writeOp(O_JMP, f);    // jump to that offset
		cond = outputTell(f);
		writeOp(O_CRITICAL_START, f);
		writeExpression(&p->condition, 0, f);
		writeOp(O_CRITICAL_DONE, f);
		writeOp(O_STOP_PROG, f);
		patchOffset(here + OPCODE_SIZE, outputTell(f), f);
		patchProcTableEntry(tableOffset, 0, 3, cond, f);
	}
	writeOp(O_PUSH_BASE, f);

	writeVariables(&p->variables, p->namelist, p->numArgs, f);

	currentProcedure = p;

	writeCode(&p->nodes, f);

	//   writeClearLocalVariables(&p->variables, f);

	writeOp(O_POP_TO_BASE, f);
	writeOp(O_POP_BASE, f);

	if (currentProcedure && (currentProcedure->type & P_CRITICAL))
		writeOp(O_CRITICAL_DONE, f);

	writeOp(O_POP_RETURN, f);
}

static void writeProcedures(Program *prog, int tableOffset, FILE *f) {
	int i;
	ProcedureList *p = &prog->procedures;

	for (i=0; i<p->numProcedures; ++i) {
		if (_stricmp(getName(p->procedures[i].name, prog->namelist), "start") == 0) {
			if (p->procedures[i].type & P_IMPORT)
				parseError("Procedure 'start' cannot be imported");

			startOffset = outputTell(f);
		}

		// procedure at location zero is intentially boguz, and shouldn't
		// be tested
		if (i && !p->procedures[i].defined)
			parseError("Procedure %s prototyped but never defined\n", getName(p->procedures[i].name, prog->namelist));

		if (!(p->procedures[i].type & P_IMPORT)) {
			patchProcTableEntry(tableOffset, 0, 4, outputTell(f), f);
			writeProcedure(p->procedures+i, tableOffset, f);
		}
		tableOffset += 4 * PROCTABLE_SIZE;
	}
}

void generateCode(Program *p, const char *file) {
	FILE *f;
	int startAddr;
	currentProgram = p;

	startOffset = -1;
	f = fopen(file, "wb");

	if (!f) {
		parseError("Couldn't open %s for write.", file);
	}

	/* startup code pushes the address of an exit instruction onto the */
	/* address stack, then jumps to the entry point of the program.    */
	/* When that function returns, it will pop the address of the exit */
	/* instruction and execute it, exiting the program */
	writeOp(O_CRITICAL_START,f);//2   0
	writeInt(18, f);            //6
	writeOp(O_D_TO_A, f);       //2

	startAddr = outputTell(f);
	writeInt(0, f);             //6   10
	writeOp(O_JMP,f);           //2

	writeOp(O_EXIT_PROG,f);     //2   18 used when the start procedure returns

	writeOp(O_POP, f);               //2  20
	writeOp(O_POP_FLAGS_RETURN, f);  //2

	writeOp(O_POP, f);               //2  24
	writeOp(O_POP_FLAGS_EXIT, f);    //2

	writeOp(O_POP, f);                    //2  28
	writeOp(O_POP_FLAGS_RETURN_EXTERN, f);//2

	writeOp(O_POP, f);                    //2  32
	writeOp(O_POP_FLAGS_EXIT_EXTERN, f);  //2

	// return a value from an external function
	writeOp(O_POP_FLAGS_RETURN_VAL_EXTERN, f); //2  36

	// return a value from a local procedure called from C
	writeOp(O_POP_FLAGS_RETURN_VAL_EXIT, f);   // 38

	// return a value from an exported procedure called from C
	writeOp(O_POP_FLAGS_RETURN_VAL_EXIT_EXTERN, f);  // 40

	// startup code 42 bytes long.  If you add anything above this line that
	// emits code, you have to change the constant length of the startup code
	// in intrpret.c

	// write out our procedure tables
	procedureStart = outputTell(f);
	writeProcedureTable(f, &p->procedures);

	// write out our name and string spaces
	writenamelist(f, p->namelist);
	writenamelist(f, p->stringspace);

	// write out globals

	patchOffset(startAddr + OPCODE_SIZE, outputTell(f), f);

	writeOp(O_SET_GLOBAL, f); // 2
	writeVariables(&p->variables, p->namelist, 0, f);
	writeExportedVariables(&p->externals, f);
	writeExportedValues(&p->externals, p->namelist, f);
	writeExportedProcedures(&p->procedures, f);

	writeInt(0, f);  // write out # args to the starting function
	writeOp(O_CRITICAL_DONE, f);
	startAddr = outputTell(f);
	writeInt(18, f);  // push address of exit, in case there is no start
	writeOp(O_JMP, f);

	// write the procedures
	writeProcedures(p, procedureStart, f);

	// patch offset to where the program actually starts
	if (startOffset == -1)
		parseWarning("Warning, no 'start' procedure\n");
	else
		patchOffset(startAddr+OPCODE_SIZE, startOffset, f);

	fclose(f);
}
