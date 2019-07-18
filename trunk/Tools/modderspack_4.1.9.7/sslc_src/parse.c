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
#include "lex.h"
#include "parseext.h"

int compilerErrorTotal;
extern int backwardcompat;
extern int warnings;
extern int optimize;
extern int debug;
extern int dumpTree;
extern int shortCircuit;
void optimizeTree(Program *program);

/*
* Parser for SSL (Startrek Scripting Language).
*
* All variables are "typeless"; their type is defined by how
* they are used.  All types are promoted to the "highest" type
* in an expression, where the order is from lowest to highest:
* int, float, string.
*
* So,
* if you do 2 + "foo", you get back "2foo".
* if you do 2 + 2.4,   you get 4.4
* if you do 2 + 4,     you get 6 (hopefully :)
* if you do 2 + 2.4 + "foo", you get "4.4foo", since
* expressions are parsed left to right.
* if you do 2 + (2.4 + "foo") you get "22.4foo", due
* to the parentheses.
* etc.
*/
static Program *currentProgram;
static Procedure *currentProcedure;
static InputStream *currentInputStream;
static InputStream *includes[32];
static int tois = -1;

static int tmpCounter = 0;
int loopNesting = 0;
int expressionNesting = 0;

static void freeVariableList(VariableList *v);
static void freeVariable(Variable *v);
static void parseWhile(Procedure *p, NodeList *n);
static int writeBlock(NodeList *n, int i, FILE *f);
static int variable(VariableList *v, char **names, int type, ArrayVarList* arrays, int allowMulti);

extern FILE* parseroutput;

#ifdef BUILDING_DLL

int outputStr(const char *s) {
	if (parseroutput)
		fprintf(parseroutput, "%s", s);
	return 1;
}
int vparseOutput(const char *format, va_list args) {
	int v = 0;
	if (parseroutput)
		vfprintf(parseroutput, format, args);
	return v;
}
int parseOutput(const char *format, ...) {
	int i=0;
	if (parseroutput) {
		va_list arg;

		va_start(arg, format);
		i = vfprintf(parseroutput, format, arg);
		va_end(arg);
	}
	return i;
}

#else

int outputStr(const char *s) {
	fprintf(stdout, "%s", s);
	return 1;
}
int vparseOutput(const char *format, va_list args) {
	return vfprintf(stdout, format, args);
}
int parseOutput(const char *format, ...) {
	int i;
	va_list arg;

	va_start(arg, format);
	i = vfprintf(stdout, format, arg);
	va_end(arg);
	return i;
}

#endif

void parseMessageAtNode(const Node* node, const char *format, ...) {
	char buf[256];
	int i;
	va_list arg;

	if(!debug) return;

	va_start(arg, format);
	i = vsprintf(buf, format, arg);
	if(node) parseOutput("[Message] <%s>:%d:%d: %s\n", lexGetFilename(currentInputStream), node->lineNum, node->column, buf);
	else parseOutput("[Message] <none>:%d: %s\n", -1, buf);
	va_end(arg);
}

void parseWarningAtNode(const Node* node, const char *format, ...) {
	char buf[256];
	int i;
	va_list arg;

	if(!warnings) return;

	va_start(arg, format);
	i = vsprintf(buf, format, arg);
	if(node) parseOutput("[Warning] <%s>:%d:%d: %s\n", lexGetFilename(currentInputStream), node->lineNum, node->column, buf);
	else parseOutput("[Warning] <none>:%d: %s\n", -1, buf);
	va_end(arg);
}

/*
void parseOutputWithOrigin(const char* type, int lineNo, int column, const char *format, ...) {
	char buf[256];
	int i;
	va_list arg;

	va_start(arg, format);
	i = vsprintf(buf, format, arg);
	if (lineNo == -1) {
		parseOutput("[%s] <none>:-1: Warning during code generation: %s\n", type, buf);
	} else {
		parseOutput("[%s] <%s>:%d:%d: %s\n", type, lexGetFilename(currentInputStream), lineNo, column, buf);
	}
	va_end(arg);
}
*/

void parseWarning(const char *format, ...) {
	char buf[256];
	int i;
	va_list arg;

	if(!warnings) return;

	va_start(arg, format);
	i = vsprintf(buf, format, arg);
	if (currentInputStream->lineno == -1)
		parseOutput("[Warning] <none>:-1: Warning during code generation: %s\n", buf);
	else
		parseOutput("[Warning] <%s>:%d:%d: %s\n", lexGetFilename(currentInputStream), lexGetLineno(currentInputStream), lexGetColumn(currentInputStream), buf);
	va_end(arg);
}

void parseErrorAtNode(const Node* node, const char *format, ...) {
	char buf[256];
	int i;
	va_list arg;

	va_start(arg, format);
	i = vsprintf(buf, format, arg);
	if(node) parseOutput("[Error] <%s>:%d:%d: %s\n", lexGetFilename(currentInputStream), node->lineNum, node->column, buf);
	else parseOutput("[Error] <none>:%d: %s\n", -1, buf);
	va_end(arg);

	compilerErrorTotal++;

	longjmp(currentProgram->env, 1);
}
void parseError(const char *format, ...) {
	char buf[256];
	int i;
	va_list arg;

	va_start(arg, format);
	i = vsprintf(buf, format, arg);
	if (currentInputStream->lineno == -1)
		parseOutput("[Error] <none>:-1: Error during code generation: %s\n", buf);
	else
		parseOutput("[Error] <%s>:%d:%d: %s\n", lexGetFilename(currentInputStream), lexGetLineno(currentInputStream), lexGetColumn(currentInputStream), buf);
	va_end(arg);

	compilerErrorTotal++;

	longjmp(currentProgram->env, 1);
}

void parseSemanticError(const char *format, ...) {
	char buf[256];
	int i;
	va_list arg;

	va_start(arg, format);
	i = vsprintf(buf, format, arg);
	if (currentInputStream->lineno == -1)
		parseOutput("[Error] <Semantic> <none>:-1: Error during code generation: %s\n", buf);
	else
		parseOutput("[Error] <Semantic> <%s>:%d:%d: %s\n", lexGetFilename(currentInputStream), lexGetLineno(currentInputStream), lexGetColumn(currentInputStream), buf);
	va_end(arg);

#ifndef BUILDING_DLL
	compilerErrorTotal++;

	longjmp(currentProgram->env, 1);
#endif
}

static void freeVariableList(VariableList *v) {
	int i;

	if (v->variables) {
		for (i=0; i<v->numVariables; ++i)
			freeVariable(v->variables + i);
		free(v->variables);
	}
}

static void freeProcedure(Procedure *p) {
	if (p->namelist) free(p->namelist);
	freeVariableList(&p->variables);
}

static void freeProcedureList(ProcedureList *p) {
	int i;

	if (p->procedures) {
		for (i=0; i<p->numProcedures; ++i)
			freeProcedure(p->procedures + i);
		free(p->procedures);
	}
}

int expectToken(int expectToken) {
	int token;
	token = lex();
	if (token != expectToken) {
		ungetToken();
		return -1;
	}
	return token;
}

static int findName(char *namelist, char *name) {
	char *n;

	if (!namelist) return -1;

	n = namelist + 4;
	while(*(unsigned short *)n != 0xffff) {
		if (_stricmp(n+2, name) == 0)
			return n+2 - namelist;
		n += *(unsigned short *)n + 2;
	}
	return -1;
}

static int findString(char *namelist, char *name) {
	char *n;

	if (!namelist) return -1;

	n = namelist + 4;
	while(*(unsigned short *)n != 0xffff) {
		if (strcmp(n+2, name) == 0)
			return n+2 - namelist;
		n += *(unsigned short *)n + 2;
	}
	return -1;
}

char *getName(int offset, char *namelist) {
	return namelist + offset;
}

/*
* Add a string to a namelist list.
* namelists are defined by <4-byte total len><string><string> ...
* where a <string> is <2-byte len><string data><one or 2 zero>.
* lengths do not include the headers; the total len *does*
* include the headers for each particular string.
* A length field of 0xffff indicates end of the namelist.
*
* To get the string for any name (be that the name of a variable,
* or a string in a string variable, since I store both as 'names'),
* you have to have the namelist defining that name.
*/
static int addName(char **namelist, char *name) {
	unsigned short slen = strlen(name);
	long tlen;
	char *n = *namelist;
	char *c;
	int odd = 0;

	slen++;  /* increment one for the null */
	if (slen&1) {/* odd? */
		slen++;
		odd = 1;
	}

	if (!n) {
		n = (char*)malloc(4 + 2 + slen + 2);
		*(long *)n = 2 + slen;
		c = n+4;
	}
	else {
		int i;

		tlen = *(long *)n;
		i = findName(n, name);
		if (i != -1)
			return i;

		/* 4 for main header
		tlen for old total length
		2 for this string's header
		slen for this string's length
		2 for ending length
		*/
		n = (char*)realloc(n, 4 + tlen + 2 + slen + 2);
		*(long *)n = tlen + 2 + slen;
		c = n + 4 + tlen;
	}
	*(unsigned short *)c = slen;
	*(unsigned short *)(c + 2 + slen) = 0xffff;
	*namelist = n;
	strcpy(c+2, name);
	if (odd) *(c+2+slen-1) = 0;
	return c+2 - n;
}

static int addString(char **namelist, char *name) {
	unsigned short slen = strlen(name);
	long tlen;
	char *n = *namelist;
	char *c;
	int odd = 0;

	slen++;  /* increment one for the null */
	if (slen&1) {/* odd? */
		slen++;
		odd = 1;
	}

	if (!n) {
		n = (char*)malloc(4 + 2 + slen + 2);
		*(long *)n = 2 + slen;
		c = n+4;
	}
	else {
		int i;

		tlen = *(long *)n;
		i = findString(n, name);
		if (i != -1)
			return i;

		/* 4 for main header
		tlen for old total length
		2 for this string's header
		slen for this string's length
		2 for ending length
		*/
		n = (char*)realloc(n, 4 + tlen + 2 + slen + 2);
		*(long *)n = tlen + 2 + slen;
		c = n + 4 + tlen;
	}
	*(unsigned short *)c = slen;
	*(unsigned short *)(c + 2 + slen) = 0xffff;
	*namelist = n;
	strcpy(c+2, name);
	if (odd) *(c+2+slen-1) = 0;
	return c+2 - n;
}

static void assignValue(Value *v, LexData *what) {
	switch(what->type) {
	case T_INT:
		v->type = V_INT;
		v->intData = what->intData;
		break;
	case T_FLOAT:
		v->type = V_FLOAT;
		v->floatData = what->floatData;
		break;
	case T_STRING:
		v->type = V_STRING;
		v->stringData = addString(&currentProgram->stringspace, what->stringData);
		break;
	}
}

static void constantExpression(LexData* result) {
	int parens = 0;
	int unaryOperator = 0;
	while (expectToken('(') != -1) parens++;
	if (expectToken('-') != -1 || expectToken(T_NOT) != -1 || expectToken(T_BWNOT) != -1) {
		unaryOperator = lexData.token;
	}
	if (expectToken(T_CONSTANT) == -1) {
		parseError("Constant expected.");
	}
	switch (unaryOperator) {
	case '-':
		switch(lexData.type) {
		case T_INT:
			lexData.intData = -lexData.intData;
			break;
		case T_FLOAT:
			lexData.floatData = -lexData.floatData;
			break;
		}
		break;
	case T_NOT:
		switch(lexData.type) {
		case T_INT:
			lexData.intData = !lexData.intData;
			break;
		case T_FLOAT:
			lexData.type = T_INT;
			lexData.intData = !(int)lexData.floatData;
			break;
		}
		break;
	case T_BWNOT:
		switch(lexData.type) {
		case T_INT:
			lexData.intData = ~lexData.intData;
			break;
		case T_FLOAT:
			lexData.type = T_INT;
			lexData.intData = ~(int)lexData.floatData;
			break;
		}
		break;
	}
	*result = lexData;
	for (; parens > 0; --parens) {
		if (expectToken(')') == -1) {
			parseError("')' expected.");
		}
	}
}

static void assignVariable(VariableList *v, int which, LexData *what) {
	assignValue(&v->variables[which].value, what);
	v->variables[which].initialized = 1;
}

static void reference(int* numrefs, int** refs) {
	if(!*refs) {
		*refs = (int*)malloc(8*8);
	} else if(refs[0][numrefs[0]*2-2]==lexGetLineno(currentInputStream) && refs[0][numrefs[0]*2-1]==(int)lexGetFilename(currentInputStream)) {
		return;
	} else if(!(numrefs[0]%8)) {
		*refs = (int*)realloc(*refs, (numrefs[0]+9)*8);
	}
	refs[0][numrefs[0]*2]=lexGetLineno(currentInputStream);
	refs[0][numrefs[0]*2 + 1]=(int)lexGetFilename(currentInputStream);
	numrefs[0]++;
}

static void referenceVariable(VariableList *v, int which) {
	v = v; which = which;
	//   v->variables[which].uses++;
	reference(&v->variables[which].numRefs, &v->variables[which].references);
}

static void referenceProcedure(ProcedureList *p, int which) {
	p->procedures[which].uses++;
	reference(&p->procedures[which].numRefs, &p->procedures[which].references);
}

static int addVariable(VariableList *var, char **namelist, int type, char *name) {
	Variable *v = var->variables;
	int i;

	if (!v) {
		v = (Variable*)malloc(sizeof(Variable));
		i = 0;
	}
	else {
		for (i=0; i < var->numVariables; ++i)
			if (_stricmp(getName(v[i].name, *namelist), name) == 0)
				break;

		if (i == var->numVariables)
			v = (Variable*)realloc(v, sizeof(Variable) * (i+1));
		else {
			parseWarning("Redefinition of variable %s\n", name);
			return i;
		}
	}

	v[i].name = addName(namelist, name);
	v[i].type = type;
	v[i].value.type = V_INT;
	v[i].value.intData = 0;
	v[i].uses = 0;
	v[i].numRefs = 0;
	v[i].references = 0;
	v[i].arrayLen=-1;
	v[i].initialized = 0;
	v[i].declared=lexGetLineno(currentInputStream);
	v[i].fdeclared=lexGetFilename(currentInputStream);
	var->variables = v;
	var->numVariables++;
	return i;
}

void GenTmpVar(Procedure *p, LexData* lex) {
	lex->stringData=(char*)malloc(16);
	lex->token=T_SYMBOL;
	sprintf_s(lex->stringData, 16, "tmp.%d", tmpCounter++);
	addVariable(&p->variables, &p->namelist, V_LOCAL, lex->stringData);
}

static void AddArrayVar(ArrayVarList* arrays, ArrayVar* var) {
	if(arrays->size==0) {
		arrays->vars=(ArrayVar*)malloc(sizeof(ArrayVar)*4);
		arrays->size=4;
	} else if(arrays->size==arrays->count) {
		arrays->size+=4;
		arrays->vars=(ArrayVar*)malloc(sizeof(ArrayVar)*arrays->size);
	}
	arrays->vars[arrays->count].name = (char*)malloc(strlen(var->name)+1);
	strcpy(arrays->vars[arrays->count].name, var->name);
	arrays->vars[arrays->count].len = var->len;
	arrays->vars[arrays->count++].datasize = var->datasize;
}
static int defineVariable(VariableList *v, char **namelist, int type, ArrayVarList* arrays, int allowMulti) {
	int i;
	ArrayVar av;
	LexData symbol;

	do {
		if (expectToken(T_SYMBOL) == -1)
			parseError("Expecting symbol.");
		symbol = lexData;

		if (findName(*namelist, lexData.stringData) != -1)
			parseSemanticError("Redefinition of %s.", lexData.stringData);


		i = addVariable(v, namelist, type, lexData.stringData);

		if (i == -1)
			parseSemanticError("Couldn't add variable %s.", lexData.stringData);

		if(expectToken('[') != -1) {
			if(!arrays) parseSemanticError("Array variable declarations not allowed here");
			av.name=lexData.stringData;
			av.datasize=4;
			if (expectToken(T_CONSTANT) == -1) parseError("Initialization of array bounds with non-constant");
			if (lexData.type!=T_INT) parseError("Initialization of array bounds with non-integer");
			av.len=lexData.intData;
			if(expectToken(',')!=-1) {
				if (expectToken(T_CONSTANT) == -1) parseError("Initialization of array data size with non-constant");
				if (lexData.type!=T_INT) parseError("Initialization of array data size with non-integer");
				av.datasize=lexData.intData;
			}
			if(expectToken(']')==-1) parseError("Expected ']'");
			AddArrayVar(arrays, &av);
		} else if (expectToken(T_ASSIGN) != -1) {
			char buf[1024];
			int allowExpr = (allowMulti && type == V_LOCAL);
			strcpy(buf, symbol.stringData);
			symbol.stringData = buf;
			if (expectToken(T_CONSTANT) == -1) {
				if (allowExpr) {
					emitOp(currentProcedure, &currentProcedure->nodes, T_START_STATEMENT);
					emitNode(currentProcedure, &currentProcedure->nodes, &symbol);
					emitOp(currentProcedure, &currentProcedure->nodes, T_ASSIGN);
					parseExpression(currentProcedure, &currentProcedure->nodes);
					emitOp(currentProcedure, &currentProcedure->nodes, T_END_STATEMENT);
				} else {
					LexData assignConstant;
					constantExpression(&assignConstant);
					assignVariable(v, i, &assignConstant);
				}
			} else
				assignVariable(v, i, &lexData);
		}
	} while(allowMulti && expectToken(',') != -1);
	if (expectToken(';') == -1) {
		if(arrays && backwardcompat == 0) parseError("Expected ';' at end of variable declaration");
	}
	return 0;
}

static Procedure *findProcedure(ProcedureList *procs, char **namelist, char *name) {
	int i;

	if (!*namelist || !procs || !procs->procedures) return 0;

	for (i=0; i<procs->numProcedures; ++i) {
		if (_stricmp(getName(procs->procedures[i].name, *namelist), name) == 0)
			return procs->procedures + i;
	}

	return 0;
}

static int findProcedureIndex(ProcedureList *procs, char **namelist, char *name) {
	int i;

	if (!*namelist || !procs || !procs->procedures) return 0;

	for (i=0; i<procs->numProcedures; ++i) {
		if (_stricmp(getName(procs->procedures[i].name, *namelist), name) == 0)
			return i;
	}

	return -1;
}

static Procedure *addProcedure(ProcedureList *procs, char **namelist, char *name) {
	int i;
	Procedure *p;

	if (!procs->procedures) {
		procs->procedures = (Procedure*)malloc(sizeof(Procedure));
		procs->numProcedures = 1;
		i = 0;
	}
	else if ((p = findProcedure(procs, namelist, name)) != 0)
		return p;
	else {
		i = procs->numProcedures++;
		procs->procedures = (Procedure*)realloc(procs->procedures, sizeof(Procedure)*(i+1));
	}

	procs->procedures[i].name = addName(namelist, name);
	procs->procedures[i].type = 0;
	procs->procedures[i].namelist = 0;
	procs->procedures[i].numArgs = 0;
	procs->procedures[i].minArgs = 0;
	procs->procedures[i].uses = 0;
	procs->procedures[i].defined = 0;
	procs->procedures[i].variables.variables = 0;
	procs->procedures[i].variables.numVariables = 0;
	procs->procedures[i].nodes.numNodes = 0;
	procs->procedures[i].nodes.nodes = 0;

	procs->procedures[i].condition.numNodes = 0;
	procs->procedures[i].condition.nodes = 0;

	procs->procedures[i].numRefs = 0;
	procs->procedures[i].references = 0;
	procs->procedures[i].declared=-1;
	procs->procedures[i].fdeclared=0;
	procs->procedures[i].fstart=0;
	procs->procedures[i].start=-1;
	procs->procedures[i].end=-1;

	return procs->procedures + i;
}

static int externProcedure(ProcedureList *pl, char **namelist, int type) {
	Procedure *p;
	int numArgs = 0;
	char *argNames = 0;
	VariableList args;

	args.numVariables = 0;
	args.variables = 0;

	if (expectToken(T_SYMBOL) == -1)
		return 1;

	p = findProcedure(pl, namelist, lexData.stringData);

	if (p) {
		if (p->defined == 2)
			parseSemanticError("Redefinition of procedure %s.", lexData.stringData);
	}
	else {
		if (findName(*namelist, lexData.stringData) != -1)
			parseSemanticError("%s already defined.", lexData.stringData);

		p = addProcedure(pl, namelist, lexData.stringData);
	}

	if(p->declared==-1) {
		p->declared=lexGetLineno(currentInputStream);
		p->fdeclared=lexGetFilename(currentInputStream);
	}

	if (expectToken('(') != -1) {
		int i;
		i = lex();
		while(i != ')') {
			if (i != T_VARIABLE)
				parseError("'variable' expected.");
			ungetToken();
			variable(&args, &argNames, V_LOCAL, 0, 0);
			i = lex();
			if (i != ')') {
				if (i != ',')
					parseError("',' expected.");
				i = lex();
			}
			numArgs++;
		}
	}

	if (expectToken(';') == -1)
		parseError("Can't define procedures in an import or export block");

	p->numArgs = p->minArgs = numArgs;
	p->defined = 1;
	p->type |= type;
	if (type | P_EXPORT)
		p->uses = 1;

	freeVariableList(&args);
	if (argNames) free(argNames);

	return 0;
}

static int externVariable(VariableList *v, char **namelist, int type, int flag) {
	int i;

	if (expectToken(T_SYMBOL) == -1)
		parseError("Expecting symbol.");

	if (findName(*namelist, lexData.stringData) != -1)
		parseSemanticError("Redefinition of %s.", lexData.stringData);

	i = addVariable(v, namelist, type, lexData.stringData);

	v->variables[i].arrayLen=-1;
	v->variables[i].declared=lexGetLineno(currentInputStream);
	v->variables[i].fdeclared=lexGetFilename(currentInputStream);

	if (i == -1)
		parseSemanticError("Couldn't add variable %s.", lexData.stringData);

	if (expectToken(T_ASSIGN) != -1) {
		if (flag) {
			LexData assignConstant;
			constantExpression(&assignConstant);
			assignVariable(v, i, &assignConstant);
		}
		else parseError("Can't assign in initialization of imported variables.");
	}
	if (expectToken(';') == -1)
		;
	return 0;
}

static int findVariableIndex(char *var, VariableList *v, char *namelist) {
	int i;

	for (i=0; i<v->numVariables; ++i) {
		if (_stricmp(getName(v->variables[i].name, namelist), var) == 0)
			return i;
	}
	return -1;
}

static int import(Program *p, char **names) {
	if (expectToken(T_IMPORT) == -1) return 1;
	do {
		if (expectToken(T_VARIABLE) != -1) {
			if (expectToken(T_BEGIN) != -1) {
				while(expectToken(T_END) == -1)
					if (externVariable(&p->externals, names, V_IMPORT, 0))
						return 1;
			}
			else if (expectToken(T_SYMBOL) != -1) {
				ungetToken();
				if (externVariable(&p->externals, names, V_IMPORT, 0))
					return 1;
			}
			else parseError("Expected symbol or 'begin' block");
		}
		else if (expectToken(T_PROCEDURE) != -1) {
			if (expectToken(T_BEGIN) != -1) {
				while(expectToken(T_END) == -1) {
					if (externProcedure(&p->procedures, names, P_IMPORT))
						return 1;
				}
			}
			else if (expectToken(T_SYMBOL) != -1) {
				ungetToken();
				if (externProcedure(&p->procedures, names, P_IMPORT))
					return 1;
			}
			else parseError("Expected symbol or 'begin' block");
		}
		else parseError("Expected 'procedure' or 'variable'");
	} while(expectToken(T_IMPORT) != -1);

	ungetToken();
	return 0;
}

static int export(Program *p, char **names) {
	if (expectToken(T_EXPORT) == -1) return 1;
	do {
		if (expectToken(T_VARIABLE) != -1) {
			if (expectToken(T_BEGIN) != -1) {
				while(expectToken(T_END) == -1)
					if (externVariable(&p->externals, names, V_EXPORT, 1))
						return 1;
			}
			else if (expectToken(T_SYMBOL) != -1) {
				ungetToken();
				if (externVariable(&p->externals, names, V_EXPORT, 1))
					return 1;
			}
			else parseError("Expected symbol or 'begin' block");
		}
		else if (expectToken(T_PROCEDURE) != -1) {
			if (expectToken(T_BEGIN) != -1) {
				while(expectToken(T_END) == -1) {
					if (externProcedure(&p->procedures, names, P_EXPORT))
						return 1;
				}
			}
			else if (expectToken(T_SYMBOL) != -1) {
				ungetToken();
				if (externProcedure(&p->procedures, names, P_EXPORT))
					return 1;
			}
			else parseError("Expected symbol or 'begin' block");
		}
		else parseError("Expected 'procedure' or 'variable'");
	} while(expectToken(T_EXPORT) != -1);

	ungetToken();
	return 0;
}

static void copyVariables(VariableList *to, char **toNames, VariableList *from, char *fromNames) {
	int i, varI;

	for (i=0; i<from->numVariables; ++i) {
		varI = addVariable(to, toNames, from->variables[i].type,
			getName(from->variables[i].name, fromNames));
		to->variables[i].value = from->variables[i].value;
		to->variables[i].initialized = from->variables[i].initialized;
	}
}

static int variable(VariableList *v, char **names, int type, ArrayVarList* arrays, int allowMulti) {
	if (expectToken(T_VARIABLE) == -1) return 1;

	do {
		if (expectToken(T_BEGIN) != -1) { // sfall addition
			while(expectToken(T_END) == -1) {
				if (defineVariable(v, names, type, arrays, allowMulti))
					return 1;
			}
		}
		else if (expectToken(T_SYMBOL) != -1) {
			ungetToken();
			if (defineVariable(v, names, type, arrays, allowMulti))
				return 1;
		}
		else parseError("Expected symbol or 'begin' block");
	}  while(expectToken(T_VARIABLE) != -1);

	ungetToken();  // put back what was there
	return 0;
}

/*
* A node is just an instruction.
* the token field is set to the token returned from the lexical
* analyzer.  If it's a constant, the value's type is set to the
* type of variable it is.  If it's a symbol, the type field is
* set to the type of symbol (global or local, variable or procedure)
* and the intData field is set to the offset for that variable
* or procedure.
*/
void emitNode(Procedure *p, NodeList *n, LexData *data) {
	int i;

	if (!n->nodes) {
		n->nodes = (Node*)malloc(8*sizeof(Node));
		n->numNodes = 0;
	} else if(!(n->numNodes%8)) {
		n->nodes = (Node*)realloc(n->nodes, sizeof(Node) * (n->numNodes+8));
	}

	i = n->numNodes++;

	n->nodes[i].token = data->token;
	n->nodes[i].lineNum = lexGetLineno(currentInputStream);
	n->nodes[i].column = lexGetColumn(currentInputStream);
	n->nodes[i].stringify = 0;

	switch(data->token) {
	case T_CONSTANT:
		assignValue(&n->nodes[i].value, data);
		break;
	case T_SYMBOL: {
		int v;
		int type = 0;

		//
		// search order is:
		//  local variables
		//  global procedures
		//  global variables
		//  external variables
		//
		v = findVariableIndex(data->stringData, &p->variables, p->namelist);
		type = P_LOCAL;
		if (v == -1) {
			v = findProcedureIndex(&currentProgram->procedures, &currentProgram->namelist, data->stringData);
			if (v == -1) {
				v = findVariableIndex(data->stringData, &currentProgram->variables, currentProgram->namelist);
				type = P_GLOBAL;
				if (v == -1) {
					v = findVariableIndex(data->stringData, &currentProgram->externals, currentProgram->namelist);
					if (v == -1) {
						parseSemanticError("Undefined symbol %s.", data->stringData);
						break;
					}
					//v = findName(currentProgram->namelist, data->stringData);
					type = P_EXTERN;
					referenceVariable(&currentProgram->externals, v);
				}
				else referenceVariable(&currentProgram->variables, v);
			}
			else {
				type |= P_PROCEDURE;
				referenceProcedure(&currentProgram->procedures, v);
				if (data->type & P_REFERENCE) {
					n->nodes[i].stringify = addString(&currentProgram->stringspace, data->stringData);
				}
			}
		}
		else referenceVariable(&p->variables, v);
		n->nodes[i].value.type    = type;
		n->nodes[i].value.intData = v;
		break;
				   }
	}
}

void emitInt(Procedure *p, NodeList *nodes, int i) {
	LexData tmp;
	tmp.token = T_CONSTANT;
	tmp.type = T_INT;
	tmp.intData = i;
	emitNode(p, nodes, &tmp);
}

void emitOp(Procedure *p, NodeList *nodes, int token) {
	LexData tmp;
	tmp.token = token;
	emitNode(p, nodes, &tmp);
}

static void logical_expression(Procedure *p, NodeList *nodes);
static void parseFuncArgs(Procedure *p, NodeList *nodes, Procedure *q);
static int isExpectingProcArg();

static void factor(Procedure *p, NodeList *nodes) {
	int i, refSyntax = 0;

	i = lex();
	if (i == '@') {
		i = lex();
		if (i != T_SYMBOL)
			parseError("Expected symbol");
		refSyntax = 1;
	}

	switch(i) {
	case T_FLOOR:
	case T_NOT:
	case T_BWNOT:
	case '-':
		factor(p, nodes);
		if (i == '-') i = T_NEGATE;
		emitOp(p, nodes, i);
		break;

	case T_SYMBOL: {
		// local?
		LexData d = lexData;
		if (findVariableIndex(lexData.stringData, &p->variables, p->namelist) != -1) {
			if (refSyntax)
				parseSemanticError("Can only stringify procedures.");
			if (expectToken('(') != -1) { // function call
				ungetToken();
				emitOp(p, nodes, T_CALL_FUNC);
				emitNode(p, nodes, &d);
				emitOp(p, nodes, T_START_EVENT);
				parseFuncArgs(p, nodes, 0);
				emitOp(p, nodes, T_END_EVENT);
			}
			else {
				if (expectToken('[') != -1 || expectToken('.') != -1) {
					parseArrayDereference(p, nodes, d, 0);
				}
				else {
					emitNode(p, nodes, &d);
				}
			}
		}
		else {
			Procedure *q;
			q = findProcedure(&currentProgram->procedures, &currentProgram->namelist, lexData.stringData);
			if (q) {
				if(q->type&P_INLINE) parseSemanticError("Cannot use an inline procedure in an expression");
				if (refSyntax) {
					d.type |= P_REFERENCE; // this will make node stringify when writing code
					emitNode(p, nodes, &d);
				} else if (isExpectingProcArg() && (expectToken('(') == -1))  {
					ungetToken();
					emitNode(p, nodes, &d); // emit procedure ID directly
				} else {
					emitOp(p, nodes, T_CALL_FUNC);
					emitNode(p, nodes, &d);
					emitOp(p, nodes, T_START_EVENT);
					parseFuncArgs(p, nodes, q);
					emitOp(p, nodes, T_END_EVENT);
				}
			}
			else if (findVariableIndex(lexData.stringData, &currentProgram->variables, currentProgram->namelist) != -1) {
				if (refSyntax)
					parseSemanticError("Can only stringify procedures.");
				if (expectToken('(') != -1) { // function call
					ungetToken();
					emitOp(p, nodes, T_CALL_FUNC);
					emitNode(p, nodes, &d);
					emitOp(p, nodes, T_START_EVENT);
					parseFuncArgs(p, nodes, 0);
					emitOp(p, nodes, T_END_EVENT);
				}
				else {
					if (expectToken('[') != -1 || expectToken('.') != -1) {  // global var
						parseArrayDereference(p, nodes, d, 0);
					}
					else
						emitNode(p, nodes, &d);
				}
			}
			else if (findVariableIndex(lexData.stringData, &currentProgram->externals, currentProgram->namelist) != -1) {
				if (refSyntax)
					parseSemanticError("Can only stringify procedures.");
				if (expectToken('(') != -1) { // function call
					ungetToken();
					emitOp(p, nodes, T_CALL_FUNC);
					emitNode(p, nodes, &d);
					emitOp(p, nodes, T_START_EVENT);
					parseFuncArgs(p, nodes, 0);
					emitOp(p, nodes, T_END_EVENT);
				}
				else
					emitNode(p, nodes, &d);
			}
			else {
				parseSemanticError("Undefined symbol %s in factor\n", lexData.stringData);
				// for parser:
				if (expectToken('(') != -1) {
					ungetToken();
					parseFuncArgs(p, nodes, 0);
				}
			}
		}
		break;
				   }
	case T_CONSTANT: {
		if (lexData.type == T_STRING) { // could be a function call
			LexData d = lexData;
			if (expectToken('(') != -1) {
				ungetToken();
				emitOp(p, nodes, T_CALL_FUNC);
				emitNode(p, nodes, &d);
				emitOp(p, nodes, T_START_EVENT);
				parseFuncArgs(p, nodes, 0);
				emitOp(p, nodes, T_END_EVENT);
			}
			else
				emitNode(p, nodes, &d);
		}
		else
			emitNode(p, nodes, &lexData);
		break;
					 }
	case '(':
		logical_expression(p, nodes);
		i = lex();
		if (i != ')') {
			parseError("Mismatched parenthesis.");
			ungetToken();
		}
		break;
	case '[':
		parseArrayConstant(p, nodes);
		break;
	case '{':
		parseAssocArrayConstant(p, nodes);
		break;
	default:
		parseLibExpression(p, nodes, i);
		break;
	}
}

static void term_prime(Procedure *p, NodeList *nodes) {
	int i = lex();

	if (i == '*' || i == '/' || i == '%' || i == '^') { // sfall: added ^
		Node *node;
		//      term(p, nodes);
		factor(p, nodes);
		node = &nodes->nodes[nodes->numNodes - 1];
		if ((i == '/' || i == '%') && node->token == T_CONSTANT && node->value.type != V_STRING && node->value.intData == 0) {
			parseSemanticError("Division by zero!");
		}
		emitOp(p, nodes, i);
		term_prime(p, nodes);
	}
	else ungetToken();
}

static void term(Procedure *p, NodeList *nodes) {
	factor(p, nodes);
	term_prime(p, nodes);
}

static void expr_prime(Procedure *p, NodeList *nodes) {
	int i = lex();

	if (i == '+' || i == '-' || i == T_BWAND  || i == T_BWOR || i == T_BWXOR) {
		term(p, nodes);
		emitOp(p, nodes, i);
		expr_prime(p, nodes);
	}
	else
		ungetToken();
}

static void expression(Procedure *p, NodeList *nodes) {
	term(p, nodes);
	expr_prime(p, nodes);
}

static void compare_prime(Procedure *p, NodeList *nodes) {
	int i = lex();

	switch(i) {
	case '>':
	case '<':
	case T_GREATER_EQUAL:
	case T_LESS_EQUAL:
	case T_EQUAL:
	case T_NOT_EQUAL: break;
	default: ungetToken(); return;
	}
	expression(p, nodes);
	emitOp(p, nodes, i);
}

static void compare_expression(Procedure *p, NodeList *nodes) {
	expression(p, nodes);
	compare_prime(p, nodes);
}

static void logical_prime(Procedure *p, NodeList *nodes) {
	int i;

	i = lex();
	if (i == T_AND || i == T_OR) {
		/* old logic:
		compare_expression(p, nodes);
		emitOp(p, nodes, i);
		logical_prime(p, nodes);*/
		// phobos2077 - new boolean expressions begin
		emitOp(p, nodes, i);
		emitOp(p, nodes, T_START_EXPRESSION);
		compare_expression(p, nodes);
		emitOp(p, nodes, T_END_EXPRESSION);
		logical_prime(p, nodes);
		// boolean end
	}
	else ungetToken();
}

static void logical_expression(Procedure *p, NodeList *nodes) {
	NodeList tmpNodes;
	tmpNodes.numNodes = 0;
	tmpNodes.nodes = 0;
	compare_expression(p, &tmpNodes);
	logical_prime(p, &tmpNodes);
	if (expectToken(T_IF) != -1) { // phobos2077 - ternary operator, python-like
		emitOp(p, nodes, T_IF);
		parseExpression(p, nodes); // condition
		emitOp(p, nodes, T_START_EXPRESSION);
		appendNodeList(nodes, &tmpNodes); // expr if true
		emitOp(p, nodes, T_END_EXPRESSION);
		if (expectToken(T_ELSE) == -1)
			parseError("'else' expected.");
		parseExpression(p, nodes); // expr if false
	} else {
		appendNodeList(nodes, &tmpNodes);
	}

	/*compare_expression(p, nodes);
	logical_prime(p, nodes);*/
}

void parseExpression(Procedure *p, NodeList *nodes) {
	emitOp(p, nodes, T_START_EXPRESSION);

	expressionNesting++;
	logical_expression(p, nodes);
	expressionNesting--;

	emitOp(p, nodes, T_END_EXPRESSION);
}

static int argsListNestLevel = 0;
static int argsListCurArg[300]; // current argument on each level, used only for lib args
static int expectProcArgStack[300]; // each bit specifies if this argument should be a proc reference
									// used to treat procedures differently when passed without argument list (passed by reference, and not called)

static int isExpectingProcArg() {
	return (expectProcArgStack[argsListNestLevel] != 0
			&& (expectProcArgStack[argsListNestLevel] & (1 << argsListCurArg[argsListNestLevel])) != 0);
}

void parseLibArgs(Procedure *p, NodeList* nodes, int n, int procArgs) {
	if (n) {
		int *argNum;
		if (expectToken('(') == -1) parseError("'(' expected");
		expectProcArgStack[++argsListNestLevel] = procArgs; // lib func may expect procedure as one of the arguments
		argNum = &argsListCurArg[argsListNestLevel];
		for (*argNum = 0; *argNum < n; (*argNum)++) {
			if (*argNum > 0 && expectToken(',') == -1)
				parseError("',' expected.");
			parseExpression(p, nodes);
		}
		argsListNestLevel--;
		if (expectToken(')') == -1) parseError("')' expected after args list");
	}
}

static void parseFuncArgs(Procedure *p, NodeList *nodes, Procedure *q) {
	int i;
	int args = 0, argBlock = 0;
	if (expectToken('(') != -1) {
		argBlock = 1;
		expectProcArgStack[++argsListNestLevel] = 0; // not a lib func, for expressions below
		emitOp(p, nodes, T_START_ARG);
		i = lex();
		if (i != ')') {
			ungetToken();
			do {
				parseExpression(p, nodes);
				args++;
				if (expectToken(')') != -1)
					break;

				if (expectToken(',') == -1)
					parseError("',' expected.");
			} while(1);
		}
		emitOp(p, nodes, T_END_ARG);
		argsListNestLevel--;
	}

	if (q) {
		if (q->numArgs != -1) {
			if (args > q->numArgs || args < q->minArgs) {
				parseSemanticError("Wrong number of arguments to procedure %s, must be from %d to %d.",
					getName(q->name, currentProgram->namelist), q->minArgs, q->numArgs);
			}
			// phobos2077 - optional arguments:
			if (q->numArgs > 0 && args < q->numArgs) {
				if (argBlock) {
					nodes->numNodes--; // erase T_END_ARG
				} else {
					emitOp(p, nodes, T_START_ARG);
				}
				for (i = args; i < q->numArgs; i++) {
					emitOp(p, nodes, T_START_EXPRESSION);
					emitInt(p, nodes, 0);
					nodes->nodes[nodes->numNodes - 1].value = q->variables.variables[i].value;
					emitOp(p, nodes, T_END_EXPRESSION);
				}
				emitOp(p, nodes, T_END_ARG);
			}
		}
	}
	else
		emitOp(p, nodes, T_CHECK_ARG_COUNT);
}

static int parseEvent(Procedure *p, NodeList *nodes) {
	int i;
	Procedure *other;
	int calloffset = nodes->numNodes;

	if (expectToken(T_SYMBOL) == -1) {
		if (expectToken(T_CONSTANT) != -1 || lexData.type != T_STRING) {
			parseSemanticError("Symbol or string expected.");
			return 0;
		}
	}

	if (lexData.token == T_SYMBOL) {
		other = findProcedure(&currentProgram->procedures, &currentProgram->namelist, lexData.stringData);
		if (!other) { // not a procedure, see if it's a variable
			int v;
			v = findVariableIndex(lexData.stringData, &p->variables, p->namelist);
			if (v == -1) {
				v = findVariableIndex(lexData.stringData, &currentProgram->variables, currentProgram->namelist);
				if (v == -1)
					v = findVariableIndex(lexData.stringData, &currentProgram->externals, currentProgram->namelist);
				if (v == -1)
					parseSemanticError("Undefined procedure %s.", lexData.stringData);
			}
		} else if(other->type&P_PURE) {
			parseSemanticError("Cannot call a pure function");
		} else if(other->type&P_INLINE && optimize>=1) {
			int firstVar=p->variables.numVariables;
			LexData ld;
			nodes->numNodes -= 2; // eat "start statement" and "call"
			if(other->numArgs) {
				if(expectToken('(')==-1) parseError("Expected '('.");
				for (i = 0; i < other->numArgs; i++) {
					GenTmpVar(p, &ld);
					emitOp(p, nodes, T_START_STATEMENT);
					emitNode(p, nodes, &ld);
					emitOp(p, nodes, T_ASSIGN);
					parseExpression(p, nodes);
					emitOp(p, nodes, T_END_STATEMENT);
					if(i!=other->numArgs-1 && expectToken(',')==-1) parseError("Expected ','");
				}
				if(expectToken(')')==-1) parseError("Expected ')'.");
			}
			for(i=other->numArgs;i<other->variables.numVariables;i++) {
				GenTmpVar(p, &ld);
				if(other->variables.variables[i].value.intData || other->variables.variables[i].type!=V_INT) {
					emitOp(p, nodes, T_START_STATEMENT);
					emitNode(p, nodes, &ld);
					emitOp(p, nodes, T_ASSIGN);
					ld.token=T_CONSTANT;
					ld.intData=other->variables.variables[i].value.intData;
					ld.type=other->variables.variables[i].value.type;
					//TODO: Check this is valid for strings
					emitNode(p, nodes, &ld);
					emitOp(p, nodes, T_END_STATEMENT);
				}
			}
			p->variables.variables = realloc(p->variables.variables, sizeof(Variable)*p->variables.numVariables);
			nodes->nodes = realloc(nodes->nodes, sizeof(Node) * (nodes->numNodes+other->nodes.numNodes+9));
			memcpy(&nodes->nodes[nodes->numNodes], &other->nodes.nodes[1], (other->nodes.numNodes-2)*sizeof(Node));
			for(i=nodes->numNodes;i<nodes->numNodes+other->nodes.numNodes-2;i++) {
				if(nodes->nodes[i].token==T_SYMBOL&&nodes->nodes[i].value.type==P_LOCAL) {
					nodes->nodes[i].value.intData+=firstVar;
				}
			}
			nodes->numNodes += (other->nodes.numNodes - 2);
			return 1;
		}
	}
	else other = 0;

	emitNode(p, nodes, &lexData);

	emitOp(p, nodes, T_START_EVENT);

	parseFuncArgs(p, nodes, other);

	i = lex();

	switch(i) {
	case T_IN:
	case T_WHEN:
		if (i == T_IN)
			nodes->nodes[calloffset-1].token = T_CALL_AT;
		else
			nodes->nodes[calloffset-1].token = T_CALL_CONDITION;
		emitNode(p, nodes, &lexData);
		parseExpression(p, nodes);
		break;
	default: ungetToken(); break;
	}
	emitOp(p, nodes, T_END_EVENT);
	return 0;
}

static void parseIf(Procedure *p, NodeList *nodes);
static void parseBlock(Procedure *p);
void parseExpGroup(Procedure *p, NodeList *nodes, int num) {
	if (num > 0) {
		parseExpression(p, nodes);
		num--;
	}
	while(num-- > 0) {
		if (expectToken(',') == -1)
			parseError("',' expected.");
		parseExpression(p, nodes);
	}
}



// Parse a statement from the input stream.

static void parseStatementInternal(Procedure *p, char requireSemicolon) {
	int i, inlinedEvent = 0;
	NodeList *nodes;
	nodes = &p->nodes;
	i = lex();
	emitOp(p, &p->nodes, T_START_STATEMENT);
	if (i == T_BEGIN) {
		ungetToken();
		parseBlock(p);
	}
	else {
		if(i!=T_FOR && i!=T_FOREACH && i!=T_SWITCH && i!=T_SYMBOL) emitNode(p, &p->nodes, &lexData);
		switch(i) {
		case T_SWITCH:
			parseSwitch(p, &p->nodes);
			break;
		case T_IF:
			parseIf(p, &p->nodes);
			break;
		case T_WHILE:
			parseWhile(p, &p->nodes);
			break;
		case T_FOR:
			parseFor(p, &p->nodes);
			break;
		case T_FOREACH:
			parseForEach(p, &p->nodes);
			break;
		default: {
			switch(i) {
			default:
				parseLib(p, &p->nodes, i);
				break;

				PARSE(DETACH, 0);
				PARSE(EXIT, 0);
				PARSE(SPAWN, 1);
				PARSE(CALLSTART, 1);
				PARSE(EXEC, 1);
				PARSE(FORK, 1);
				PARSE(WAIT, 1);
				PARSE(STARTCRITICAL, 0);
				PARSE(ENDCRITICAL, 0);

			case T_NOOP: break;

			case T_SYMBOL: {
				int t, op, setArray = 0;
				LexData d, symb;
				symb = lexData;
				t = lex();
				if (t == '[' || t == '.') {
					parseArrayAssignment(p, &p->nodes, symb);
					break;
				}
				if (t == T_INC || t == T_DEC) { // pretend it's += or -=
					t = (t == T_INC) ? T_ASSIGN_ADD : T_ASSIGN_SUB;
					d.token = T_CONSTANT;
					d.type = T_INT;
					d.intData = 1;
					setNextToken(&d);
				}
				switch(t) {
				case T_ASSIGN:
					emitNode(p, &p->nodes, &symb); // lvalue
					emitNode(p, &p->nodes, &lexData); // :=
					parseExpression(p, &p->nodes); // expr
					break;
				case T_ASSIGN_ADD:
				case T_ASSIGN_SUB:
				case T_ASSIGN_DIV:
				case T_ASSIGN_MUL:
					switch(t) {
					case T_ASSIGN_ADD: op = '+'; break;
					case T_ASSIGN_MUL: op = '*'; break;
					case T_ASSIGN_SUB: op = '-'; break;
					case T_ASSIGN_DIV: op = '/'; break;
					}
					emitNode(p, &p->nodes, &symb); // lvalue
					emitOp(p, &p->nodes, T_ASSIGN);
					emitOp(p, &p->nodes, T_START_EXPRESSION);
					emitOp(p, &p->nodes, T_START_EXPRESSION);
					emitNode(p, &p->nodes, &symb);
					emitOp(p, &p->nodes, T_END_EXPRESSION);
					parseExpression(p, &p->nodes);
					emitOp(p, &p->nodes, op);
					emitOp(p, &p->nodes, T_END_EXPRESSION);
					break;
				default:
					parseError("Assignment operator expected.");
				}
				break;
						   }
			case T_CALL:
				inlinedEvent = parseEvent(p, &p->nodes);
				break;
			case T_CANCEL:
				if (expectToken('(') == -1)
					parseError("'(' expected");
				if (expectToken(T_SYMBOL) == -1)
					parseError("Symbol expected");
				emitNode(p, &p->nodes, &lexData);
				if (expectToken(')') == -1)
					parseError("')' expected");
				break;
			case T_CANCELALL:
				emitNode(p, &p->nodes, &lexData);
				break;
			case T_RETURN:
				if(p->type&P_INLINE) parseSemanticError("Cannot use return in an inline procedure");
				if (expectToken(';') == -1)
					parseExpression(p, &p->nodes);
				else {
					ungetToken();
					emitOp(p, &p->nodes, T_START_EXPRESSION);
					emitInt(p, &p->nodes, 0);
					emitOp(p, &p->nodes, T_END_EXPRESSION);
				}
				break;
			case T_BREAK:
			case T_CONTINUE:
				if (loopNesting == 0) parseSemanticError("Cannot use break or continue outside of loop");
				break;
			}
			if (requireSemicolon && expectToken(';') == -1) parseError("expecting ';'.");
			break;
			}
		}
	}
	if (!inlinedEvent)
		emitOp(p, &p->nodes, T_END_STATEMENT);
}

void parseStatement(Procedure *p) {
	parseStatementInternal(p, 1);
}

// sfall addition
void parseStatementNoSemicolon(Procedure *p) {
	parseStatementInternal(p, 0);
}

static void parseBlock(Procedure *p) {
	int i;
	ArrayVarList arrays;
	LexData tlex;
	arrays.vars=0;
	arrays.size=0;
	arrays.count=0;

	if (expectToken(T_BEGIN) == -1)
		parseError("expected 'begin'.");

	emitNode(p, &p->nodes, &lexData);  // emit the begin

	variable(&p->variables, &p->namelist, V_LOCAL, &arrays, 1);

	for(i=0;i<arrays.count;i++) {
		emitOp(p, &p->nodes, T_START_STATEMENT);
		tlex.token=T_SYMBOL;
		tlex.stringData=arrays.vars[i].name;
		emitNode(p, &p->nodes, &tlex);
		emitOp(p, &p->nodes, T_ASSIGN);
		emitOp(p, &p->nodes, T_START_EXPRESSION);
		emitOp(p, &p->nodes, T_TS_TEMP_ARRAY);
		emitOp(p, &p->nodes, T_START_EXPRESSION);
		emitInt(p, &p->nodes, arrays.vars[i].len);
		emitOp(p, &p->nodes, T_END_EXPRESSION);
		emitOp(p, &p->nodes, T_START_EXPRESSION);
		emitInt(p, &p->nodes, arrays.vars[i].datasize);
		emitOp(p, &p->nodes, T_END_EXPRESSION);
		emitOp(p, &p->nodes, T_END_EXPRESSION);
		emitOp(p, &p->nodes, T_END_STATEMENT);
	}

	while((i = lex()) != T_END) {
		if (i == T_EOF)
			parseError("Premature EOF encountered.");
		ungetToken();
		parseStatement(p);
	}
	emitNode(p, &p->nodes, &lexData);  // emit the end

	if(arrays.vars) {
		for(i=0;i<arrays.count;i++) {
			free(arrays.vars[i].name);
		}
		free(arrays.vars);
	}
}

static void parseIf(Procedure *p, NodeList *n) {
	int emitend=0;
	parseExpression(p, n);
	if (expectToken(T_THEN) == -1) {
		parseError("Expected 'then'.");
		return;
	}
	emitNode(p, n, &lexData);
	if (expectToken(T_BEGIN) == -1) {
		emitend=1;
		emitOp(p, n, T_START_STATEMENT);
		emitOp(p, n, T_BEGIN);
	} else ungetToken();
	parseStatement(p);
	if(emitend) {
		emitend=0;
		emitOp(p, n, T_END);
		emitOp(p, n, T_END_STATEMENT);
	}
	if (expectToken(T_ELSE) != -1) {
		emitNode(p, n, &lexData);
		if (expectToken(T_BEGIN) == -1) {
			emitend=1;
			emitOp(p, n, T_START_STATEMENT);
			emitOp(p, n, T_BEGIN);
		} else ungetToken();
		parseStatement(p);
		if(emitend) {
			emitOp(p, n, T_END);
			emitOp(p, n, T_END_STATEMENT);
		}
	}
}

static void parseWhile(Procedure *p, NodeList *n) {
	int emitend=0;
	parseExpression(p, n);
	if (expectToken(T_DO) == -1) {
		parseError("Expected 'do'.");
		return;
	}
	emitNode(p, n, &lexData);
	if (expectToken(T_BEGIN) == -1) {
		emitend=1;
		emitOp(p, n, T_START_STATEMENT);
		emitOp(p, n, T_BEGIN);
	} else ungetToken();
	loopNesting++;
	parseStatement(p);
	loopNesting--;
	if(emitend) {
		emitOp(p, n, T_END);
		emitOp(p, n, T_END_STATEMENT);
	}
}

void CloneLexData(LexData *dest, LexData *source) {
	*dest=*source;
	dest->stringData=malloc(strlen(source->stringData)+1);
	strcpy_s(dest->stringData, strlen(source->stringData)+1, source->stringData);
}


int procedure(void) {
	Procedure *p;
	int numArgs = 0, minArgs = 0;
	char *argNames = 0;
	VariableList args;
	int critical = 0, pure=0, inlined=0;

	args.numVariables = 0;
	args.variables = 0;

	if (expectToken(T_CRITICAL) != -1)
		critical = 1;

	if (expectToken(T_PURE) != -1)
		pure = 1;

	if (expectToken(T_INLINE) != -1)
		inlined = 1;

	if (expectToken(T_PROCEDURE) == -1)
		return 1;
	if (expectToken(T_SYMBOL) == -1)
		return 1;

	p = findProcedure(&currentProgram->procedures, &currentProgram->namelist, lexData.stringData);
	if (p) {
		if (p->type & P_IMPORT)
			parseSemanticError("Can't define imported procedures");

		if (p->defined == 2)
			parseSemanticError("Redefinition of procedure %s.", lexData.stringData);
	}
	else {
		if (findName(currentProgram->namelist, lexData.stringData) != -1)
			parseSemanticError("%s already defined.", lexData.stringData);

		p = addProcedure(&currentProgram->procedures, &currentProgram->namelist, lexData.stringData);
	}

	if(p->declared==-1) {
		p->declared=lexGetLineno(currentInputStream);
		p->fdeclared=lexGetFilename(currentInputStream);
	}

	if(critical) p->type|=P_CRITICAL;
	if(pure) p->type|=P_PURE;
	if(inlined) p->type|=P_INLINE;

	if(pure&&inlined) parseSemanticError("A procedure cannot be both pure and inline");
	currentProcedure = p;

	if (expectToken('(') != -1) {
		int i, optionalPart = 0;
		i = lex();
		while(i != ')') {
			if (i != T_VARIABLE)
				parseError("'variable' expected.");
			ungetToken();
			variable(&args, &argNames, V_LOCAL, 0, 0);
			if (args.variables[args.numVariables - 1].initialized) {
				optionalPart = 1;
			} else {
				if (optionalPart)
					parseSemanticError("Optional arguments must not precede required arguments.");
				minArgs++;
			}
			i = lex();
			if (i != ')') {
				if (i != ',')
					parseError("',' expected.");
				i = lex();
			}
			numArgs++;
		}
	}

	if (p->defined == 1) {
		if (p->numArgs != numArgs) {
			parseSemanticError("Wrong number of arguments to procedure %s\n",
					getName(p->name, currentProgram->namelist));
		} else if (numArgs != minArgs) {
			parseSemanticError("Default argument values are not allowed for a forward-declared procedure: %s\n",
					getName(p->name, currentProgram->namelist));
		}
	} else if (p->defined == 0) {
		p->numArgs = numArgs;
		p->minArgs = minArgs;
	}

	if (expectToken(';') != -1) {
		char* tmpNames = 0;
		copyVariables(&p->variables, &tmpNames, &args, argNames);
		freeVariableList(&args);
		if (argNames) free(argNames);
		if (tmpNames) free(tmpNames);
		if(p->type&P_INLINE) parseSemanticError("Cannot forward declare in inline procedure");
		p->defined = 1;
		return 0;
	}
	if (p->defined == 1) {
		int i;
		for (i=0; i < args.numVariables; ++i) {
			p->variables.variables[i].name = addName(&p->namelist, getName(args.variables[i].name, argNames));
		}
	} else {
		copyVariables(&p->variables, &p->namelist, &args, argNames);
	}

	freeVariableList(&args);
	if (argNames) free(argNames);

	p->start=lexGetLineno(currentInputStream);
	p->fstart=lexGetFilename(currentInputStream);

	if (expectToken(T_IN) != -1) {
		if (expectToken(T_CONSTANT) == -1)
			parseError("Constant expected.");

		p->type |= P_TIMED;
		p->time = lexData.intData;
	}
	else if (expectToken(T_WHEN) != -1) {
		p->type |= P_CONDITIONAL;
		parseExpression(p, &p->condition);
	}

	if(p->type&(P_TIMED|P_CONDITIONAL) && (pure||inlined)) {
		parseSemanticError("Timed or conditional procedures cannot be marked pure or inline");
	}
	if(p->type&(P_IMPORT|P_EXPORT) && inlined) {
		parseSemanticError("inline procedures cannot be imported or exported");
	}

	//emitOp(p, &p->nodes, T_BEGIN);
	parseBlock(p);

	if(!optimize || !(p->type&P_INLINE)) {
		p->nodes.numNodes--; //Avoid double begin/end
		emitOp(p, &p->nodes, T_START_STATEMENT);
		emitOp(p, &p->nodes, T_RETURN);
		emitOp(p, &p->nodes, T_START_EXPRESSION);
		emitInt(p, &p->nodes, 0);
		emitOp(p, &p->nodes, T_END_EXPRESSION);
		emitOp(p, &p->nodes, T_END_STATEMENT);
		emitOp(p, &p->nodes, T_END);
	}

	p->defined = 2;

	p->end=lexGetLineno(currentInputStream);
	p->fend=lexGetFilename(currentInputStream);

	return 0;
}

int top(void) {
	tmpCounter=0;
	while(1) {
		if (expectToken(T_EOF) != -1) {
			if (tois != -1) {
				fclose(currentInputStream->file);
				free(currentInputStream);
				currentInputStream = includes[tois];
				includes[tois--] = 0;
				continueLex(currentInputStream);
			}
			else break;
		}
		if (variable(&currentProgram->variables, &currentProgram->namelist, V_GLOBAL, 0, 1) &&
			import(currentProgram, &currentProgram->namelist) &&
			export(currentProgram, &currentProgram->namelist) &&
			procedure()) {
				if (expectToken(T_INCLUDE) != -1) {
					InputStream *tmp;
					if (tois == sizeof(includes) / sizeof(includes[0]))
						parseError("Too many includes!");
					includes[++tois] = currentInputStream;
					tmp = malloc(sizeof(InputStream));
					lex();
					if (lexData.type != T_STRING)
						parseError("Invalid type given to include");
					tmp->name=AddFileName(lexData.stringData);
					tmp->file = fopen(lexData.stringData, "r");
					if (!tmp->file)
						parseError("Couldn't find include file %s\n", lexData.stringData);
					currentInputStream = tmp;
					startLex(tmp);
				}
				else {
					parseError("Expecting top-level statement");
					return 1;
				}
		}
	}
	return 0;
}

static void freeVariable(Variable *v) {
	v = v;
}

static void freeProgram(Program *s) {
	freeProcedureList(&s->procedures);
	freeVariableList(&s->variables);
	if (s->stringspace) free(s->stringspace);
	if (s->namelist) free(s->namelist);
	free(s);
}

void freeCurrentProgram(void) {
	if (currentProgram)
		freeProgram(currentProgram);
}

void dumpNodes(Procedure* p, NodeList* nodes, FILE* f) {
	int i, indent = 0;
	char indentstr[100];
	indentstr[0] = 0;

	for (i = 0; i < nodes->numNodes; i++) {
		Node node;
		node = nodes->nodes[i];
		fprintf(f, "\n%s", indentstr);
		switch (node.token) {
		case T_START_STATEMENT:
		case T_START_EXPRESSION:
			if (nodes->nodes[i].token == T_START_EXPRESSION)
				fprintf(f, "EXPRESSION:");
			else
				fprintf(f, "STATEMENT:");
			indentstr[indent] = '\t';
			indentstr[++indent] = 0;
			break;
		case T_END_STATEMENT:
		case T_END_EXPRESSION:
			indentstr[--indent] = 0;
			break;
		case T_SYMBOL:
			fprintf(f, "symbol %d", node.value.intData);
			break;
		case T_CONSTANT:
			if (node.value.type == T_STRING)
				fprintf(f, "\"%s\"", currentProgram->stringspace + node.value.stringData);
			else if (nodes->nodes[i].value.type == T_FLOAT)
				fprintf(f, "%.5f", node.value.floatData);
			else
				fprintf(f, "%d", node.value.intData);
				break;
		default:
			if (node.token < 127)
				fprintf(f, "'%c'", node.token);
			else if (lexGetToken(node.token))
				fprintf(f, "%s", lexGetToken(node.token));
			else
				fprintf(f, "%d", node.token);
		}

	}
}

void dumpAllNodes(const char* fileName) {
	FILE* f = fopen(fileName, "wt");
	int i;
	if (!f)
		return;
	for (i = 1; i < currentProgram->procedures.numProcedures; i++) {
		fprintf(f, "\nPROCEDURE %d:", i);
		dumpNodes(&currentProgram->procedures.procedures[i], &currentProgram->procedures.procedures[i].nodes, f);
		fprintf(f, "\n\n");
	}
	fclose(f);
}

void parse(InputStream *stream, const char *output) {
	initLex();
	startLex(stream);
	currentProgram = (Program*)malloc(sizeof(Program));
	currentProgram->procedures.procedures = 0;
	currentProgram->procedures.numProcedures = 0;
	currentProgram->variables.variables = 0;
	currentProgram->variables.numVariables = 0;
	currentProgram->externals.variables = 0;
	currentProgram->externals.numVariables = 0;
	currentProgram->stringspace   = 0;
	currentProgram->namelist     = 0;
	currentInputStream = stream;
	// bogus procedure so we never have a zero procedure offset
	addProcedure(&currentProgram->procedures, &currentProgram->namelist, "..............");

	if (setjmp(currentProgram->env)) {
		freeProgram(currentProgram);
		currentProgram = 0;
		lexClose();
		if (output)
			remove( output);
		return;
	}

	if (top()) {
		freeProgram(currentProgram);
		currentProgram = 0;
		lexClose();
		if (output)
			remove( output);
		return;
	}

	lexClose();
	currentInputStream->lineno = -1;
	if (optimize)
		optimizeTree(currentProgram);
	if (output) {
		if (dumpTree) {
			char name[260] = "";
			char *c;
			strcpy_s(name, 260, output);
			c = strrchr(name, '.');
			if (c) {
				*c = 0;
			}
			strcat_s(name, 260, "_tree.txt");
			dumpAllNodes(name);
		}
		generateCode(currentProgram, output);
	}
}




#ifdef BUILDING_DLL

int _stdcall numProcs() { return currentProgram->procedures.numProcedures-1; }
void _stdcall getProc(int i, Procedure* proc) {
	*proc=currentProgram->procedures.procedures[i+1];
}
int _stdcall getProcNamespaceSize(int i) {
	if(!currentProgram->procedures.procedures[i+1].namelist) return -1;
	return *(unsigned int*)currentProgram->procedures.procedures[i+1].namelist;
}
void _stdcall getProcNamespace(int i, char* data) {
	unsigned int size=*(unsigned int*)currentProgram->procedures.procedures[i+1].namelist;
	memcpy(data, currentProgram->procedures.procedures[i+1].namelist+4, size);
}
int _stdcall numVars() {
	return (currentProgram->variables.numVariables + currentProgram->externals.numVariables);
}
void _stdcall getVar(int i, Variable* var) {
	int numNormalVars = currentProgram->variables.numVariables;
	if (i >= numNormalVars) {
		*var = currentProgram->externals.variables[i - numNormalVars];
	} else {
		*var=currentProgram->variables.variables[i];
	}
}
/*int _stdcall numExternals() { return currentProgram->externals.numVariables; }
void _stdcall getExternal(int i, Variable* var) {
	*var=currentProgram->externals.variables[i];
}*/
void _stdcall getProcVar(int i, int j, Variable* var) {
	*var=currentProgram->procedures.procedures[i+1].variables.variables[j];
}
int _stdcall namespaceSize() {return *(unsigned int*)currentProgram->namelist; }
void _stdcall getNamespace(char* data) {
	unsigned int size=*(unsigned int*)currentProgram->namelist;
	memcpy(data, currentProgram->namelist+4, size);
}
int _stdcall stringspaceSize() {
	return currentProgram->stringspace
		? *(unsigned int*)currentProgram->stringspace
		: 0;
}
void _stdcall getStringspace(char* data) {
	unsigned int size=*(unsigned int*)currentProgram->stringspace;
	memcpy(data, currentProgram->stringspace+4, size);
}
void _stdcall getProcRefs(int i, Reference* refs) {
	memcpy(refs, currentProgram->procedures.procedures[i+1].references, currentProgram->procedures.procedures[i+1].numRefs*8);
}
void _stdcall getVarRefs(int i, Reference* refs) {
	int numNormalVars = currentProgram->variables.numVariables;
	VariableList* varlist;
	if (i >= numNormalVars) {
		i = i - numNormalVars;
		varlist = &currentProgram->externals;
	} else {
		varlist = &currentProgram->variables;
	}
	memcpy(refs, varlist->variables[i].references, varlist->variables[i].numRefs*8);
}
void _stdcall getProcVarRefs(int i, int j, Reference* refs) {
	memcpy(refs, currentProgram->procedures.procedures[i+1].variables.variables[j].references, currentProgram->procedures.procedures[i+1].variables.variables[j].numRefs*8);
}


#endif