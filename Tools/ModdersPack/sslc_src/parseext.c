#include <stdlib.h>

#include "parse.h"
#include "parselib.h"
#include "extra.h"

#include "parseext.h"

extern int loopNesting;

// vars, constants, etc.
void emitNodeExpr(Procedure *p, NodeList *n, LexData *data) {
	emitOp(p, n, T_START_EXPRESSION);
	emitNode(p, n, data);
	emitOp(p, n, T_END_EXPRESSION);
}

void appendNodeListPart(NodeList* dst, const NodeList* src, int offset, int length) {
	dst->nodes = realloc(dst->nodes, sizeof(Node) * (dst->numNodes + length + 9));
	memcpy(&dst->nodes[dst->numNodes], &src->nodes[offset], sizeof(Node) * (length));
	dst->numNodes += length;
}

void appendNodeList(NodeList* dst, const NodeList* src) {
	appendNodeListPart(dst, src, 0, src->numNodes);
}


int parseArrayDereference(Procedure *p, NodeList *nodes, LexData symb, int *lastExprSize) {
	NodeList tmpN;
	LexData d;
	int dotSyntax, nodesBefore, derefCount = 0;
	tmpN.nodes = 0;
	tmpN.numNodes = 0;
	do { // write "get_array(" on each iteration to main nodes stream while writing the ending part to the temp stream
		derefCount++;
		dotSyntax = (lexData.token == '.');
		emitOp(p, nodes, T_TS_GET_ARRAY);
		emitOp(p, nodes, T_START_EXPRESSION);
		if (tmpN.numNodes > 0) {
			emitOp(p, &tmpN, T_END_EXPRESSION); // end of previous expression
		} else { // first iteration
			emitNode(p, &tmpN, &symb);
			emitOp(p, &tmpN, T_END_EXPRESSION);
		}
		nodesBefore = tmpN.numNodes;
		if (dotSyntax) {
			if (expectToken(T_SYMBOL) == -1) {
				parseError("Expected symbol");
			}
			d = lexData; // convert symbol to string constant
			d.token = T_CONSTANT;
			d.type = T_STRING;
			emitOp(p, &tmpN, T_START_EXPRESSION);
			emitNode(p, &tmpN, &d);
			emitOp(p, &tmpN, T_END_EXPRESSION);
		} else {
			parseExpression(p, &tmpN);
			if (expectToken(']') == -1) {
				parseError("Expected ']'");
			}
		}
		if (lastExprSize) *lastExprSize = tmpN.numNodes - nodesBefore;
	} while (expectToken('.') != -1 || expectToken('[') != -1);
	if (tmpN.numNodes > 0) { // append cached nodes
		appendNodeList(nodes, &tmpN);
		free(tmpN.nodes);
	}
	return derefCount;
}

void parseArrayAssignment(Procedure *p, NodeList *nodes, LexData symb) {
	int t, numDeref, op, lastExprSize = 0, nIndex = 0;
	LexData d, tmpVar, tmpVarArr;
	NodeList tmpN;

	tmpN.nodes = 0;
	tmpN.numNodes = 0;
	numDeref = parseArrayDereference(p, &tmpN, symb, &lastExprSize);
	t = lex();
	if (t == T_INC || t == T_DEC) { // pretend it's += or -=
		t = (t == T_INC) ? T_ASSIGN_ADD : T_ASSIGN_SUB;
		d.token = T_CONSTANT;
		d.type = T_INT;
		d.intData = 1;
		setNextToken(&d);
	}
	switch(t) {
	case T_ASSIGN:
		tmpN.nodes[0].token = T_TS_SET_ARRAY;
		appendNodeList(nodes, &tmpN);
		parseExpression(p, nodes); // expr
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
		tmpVar.token = tmpVarArr.token = 0;
		if (numDeref > 1) { // multidimensional access - need tmpVar to hold deepest array
			GenTmpVar(p, &tmpVarArr); // assign index of last minus one array to tmp var
			// tmp := get_array(....)
			emitNode(p, nodes, &tmpVarArr);
			emitOp(p, nodes, T_ASSIGN);
			appendNodeListPart(nodes, &tmpN, 1, tmpN.numNodes - lastExprSize - 1);
			emitOp(p, nodes, T_END_STATEMENT);
			emitOp(p, nodes, T_START_STATEMENT);
		}
		nIndex = tmpN.numNodes - lastExprSize + 1; // points to first node in array index after START_EXPRESSION
		if (lastExprSize > 3 || (tmpN.nodes[nIndex].token != T_SYMBOL && tmpN.nodes[nIndex].token != T_CONSTANT)) { // if index is a complex expression
			GenTmpVar(p, &tmpVar); // assign element index to tmp var
			// tmp := (expression)
			emitNode(p, nodes, &tmpVar);
			emitOp(p, nodes, T_ASSIGN);
			appendNodeListPart(nodes, &tmpN, tmpN.numNodes - lastExprSize, lastExprSize); // index expr
			emitOp(p, nodes, T_END_STATEMENT);
			emitOp(p, nodes, T_START_STATEMENT);
		}
		// set_array(tmpVarArr/symb, lastExpr/tmpVar, get_array(tmpVarArr/symb, lastExpr/tmpVar) OP NEXT_EXPRESSION)
		emitOp(p, nodes, T_TS_SET_ARRAY);
		if (tmpVarArr.token) {
			emitNodeExpr(p, nodes, &tmpVarArr); // last array
		} else {
			appendNodeListPart(nodes, &tmpN, 1, 3); // array symbol expr
		}
		if (tmpVar.token) {
			emitNodeExpr(p, nodes, &tmpVar); // last index tmp var
		} else {
			appendNodeListPart(nodes, &tmpN, tmpN.numNodes - lastExprSize, lastExprSize); // index symbol/constant
		}
		emitOp(p, nodes, T_START_EXPRESSION); // binary operator
		emitOp(p, nodes, T_START_EXPRESSION); // get_array
		emitOp(p, nodes, T_TS_GET_ARRAY);
		// same sequence as above...
		if (tmpVarArr.token) {
			emitNodeExpr(p, nodes, &tmpVarArr); // last array
		} else {
			appendNodeListPart(nodes, &tmpN, 1, 3); // array symbol expr
		}
		if (tmpVar.token) {
			emitNodeExpr(p, nodes, &tmpVar); // last index tmp var
		} else {
			appendNodeListPart(nodes, &tmpN, tmpN.numNodes - lastExprSize, lastExprSize); // index symbol/constant
		}
		emitOp(p, nodes, T_END_EXPRESSION);
		parseExpression(p, nodes); // second argument
		emitOp(p, nodes, op); // operator
		emitOp(p, nodes, T_END_EXPRESSION);
		break;
	default:
		parseError("Assignment operator expected (array).");
	}
	free(tmpN.nodes);
}


void parseFor(Procedure *p, NodeList *n) {
	int hadbracket=0;
	NodeList tmp, tmp2;
	if(expectToken('(') != -1) hadbracket=1;
	parseStatement(p);

	emitOp(p, n, T_START_STATEMENT);
	emitOp(p, n, T_WHILE);
	parseExpression(p, n);
	if(expectToken(';') == -1) parseError("Expected ';'");
	emitOp(p, n, T_DO);
	emitOp(p, n, T_START_STATEMENT);
	emitOp(p, n, T_BEGIN);

	tmp=*n;
	n->nodes=0;
	n->numNodes=0;
	parseStatementNoSemicolon(p);
	if (expectToken(';') == -1 && !hadbracket) {
		parseError("Expected ';'");
	}
	if(hadbracket&&expectToken(')') == -1) {
		parseError("Expected ')'");
	}
	tmp2.numNodes=n->numNodes;
	tmp2.nodes=n->nodes;
	n->numNodes=tmp.numNodes;
	n->nodes=tmp.nodes;
	loopNesting++;
	parseStatement(p);
	loopNesting--;
	// special marker for code generator
	emitOp(p, n, T_START_STATEMENT);
	emitOp(p, n, T_LOOP_END);
	emitOp(p, n, T_END_STATEMENT);
	appendNodeList(n, &tmp2); // append post-loop increment part

	emitOp(p, n, T_END);
	emitOp(p, n, T_END_STATEMENT);
	emitOp(p, n, T_END_STATEMENT);
	free(tmp2.nodes);
}


void parseForEach(Procedure *p, NodeList *n) {
	LexData symbolKey, symbolVal, a, len, count;
	char hasKey = 0, emitEnd = 0, hasParan = 0;
	if(expectToken('(') != -1) {
		hasParan = 1;
	}
	if(expectToken(T_SYMBOL) == -1) parseError("Expected symbol");
	CloneLexData(&symbolVal, &lexData);
	if(expectToken(':') != -1) {
		symbolKey = symbolVal;
		if(expectToken(T_SYMBOL) == -1) parseError("Expected symbol for value");
		CloneLexData(&symbolVal, &lexData);
		hasKey = 1;
	}

	if(expectToken(T_IN) == -1) parseError("Expected 'in'");
	if(expectToken(T_SYMBOL) == -1) {
		GenTmpVar(p, &a);
		emitOp(p, n, T_START_STATEMENT);
		emitNode(p, n, &a);
		emitOp(p, n, T_ASSIGN);
		parseExpression(p, n);
		emitOp(p, n, T_END_STATEMENT);
	} else {
		CloneLexData(&a, &lexData);
	}

	GenTmpVar(p, &len);
	GenTmpVar(p, &count);
	if (!hasKey) GenTmpVar(p, &symbolKey);

	//count:=0;
	emitOp(p, n, T_START_STATEMENT);
	emitNode(p, n, &count);
	emitOp(p, n, T_ASSIGN);
	emitOp(p, n, T_START_EXPRESSION);
	emitInt(p, n, 0);
	emitOp(p, n, T_END_EXPRESSION);
	emitOp(p, n, T_END_STATEMENT);

	//len:=len_array(a);
	emitOp(p, n, T_START_STATEMENT);
	emitNode(p, n, &len);
	emitOp(p, n, T_ASSIGN);
	emitOp(p, n, T_START_EXPRESSION);
	emitOp(p, n, T_TS_LEN_ARRAY);
	emitOp(p, n, T_START_EXPRESSION);
	emitNode(p, n, &a);
	emitOp(p, n, T_END_EXPRESSION);
	emitOp(p, n, T_END_EXPRESSION);
	emitOp(p, n, T_END_STATEMENT);

	//while count < len do begin
	emitOp(p, n, T_START_STATEMENT);
	emitOp(p, n, T_WHILE);
	emitOp(p, n, T_START_EXPRESSION);
	emitNode(p, n, &count);
	emitNode(p, n, &len);
	emitOp(p, n, '<');
	if(expectToken(T_WHILE) != -1) { // optional "while" condition
		emitOp(p, n, T_AND);
		parseExpression(p, n);
	}
	if(hasParan && (expectToken(')') == -1)) {
		parseError("Expected )");
	}
	emitOp(p, n, T_END_EXPRESSION);
	emitOp(p, n, T_DO);
	emitOp(p, n, T_START_STATEMENT);
	emitOp(p, n, T_BEGIN);

	//symbolKey:=get_array_key(a, count);
	emitOp(p, n, T_START_STATEMENT);
	emitNode(p, n, &symbolKey);
	emitOp(p, n, T_ASSIGN);
	emitOp(p, n, T_START_EXPRESSION);
	emitOp(p, n, T_TS_GET_ARRAY_KEY);
	emitOp(p, n, T_START_EXPRESSION);
	emitNode(p, n, &a);
	emitOp(p, n, T_END_EXPRESSION);
	emitOp(p, n, T_START_EXPRESSION);
	emitNode(p, n, &count);
	emitOp(p, n, T_END_EXPRESSION);
	emitOp(p, n, T_END_EXPRESSION);
	emitOp(p, n, T_END_STATEMENT);

	//symbolVal:=get_array(a, symbolKey); // works for both assoc and normal arrays
	emitOp(p, n, T_START_STATEMENT);
	emitNode(p, n, &symbolVal);
	emitOp(p, n, T_ASSIGN);
	emitOp(p, n, T_START_EXPRESSION);
	emitOp(p, n, T_TS_GET_ARRAY);
	emitOp(p, n, T_START_EXPRESSION);
	emitNode(p, n, &a);
	emitOp(p, n, T_END_EXPRESSION);
	emitOp(p, n, T_START_EXPRESSION);
	emitNode(p, n, &symbolKey);
	emitOp(p, n, T_END_EXPRESSION);
	emitOp(p, n, T_END_EXPRESSION);
	emitOp(p, n, T_END_STATEMENT);

	//The actual loop contents
	loopNesting++;
	parseStatement(p);
	loopNesting--;

	// special marker for code generator
	emitOp(p, n, T_START_STATEMENT);
	emitOp(p, n, T_LOOP_END);
	emitOp(p, n, T_END_STATEMENT);
	//count+=1;
	emitOp(p, n, T_START_STATEMENT);
	emitNode(p, n, &count);
	emitOp(p, n, T_ASSIGN_ADD);
	emitOp(p, n, T_START_EXPRESSION);
	emitInt(p, n, 1);
	emitOp(p, n, T_END_EXPRESSION);
	emitOp(p, n, T_END_STATEMENT);

	//end
	emitOp(p, n, T_END);
	emitOp(p, n, T_END_STATEMENT);
	emitOp(p, n, T_END_STATEMENT);

	free(symbolVal.stringData);
	free(symbolKey.stringData);
	free(a.stringData);
	free(len.stringData);
	free(count.stringData);
}

void parseSwitch(Procedure *p, NodeList *n) {
	LexData symbol;
	int cases=0;
	if(expectToken(T_SYMBOL)==-1) {
		GenTmpVar(p, &symbol);
		emitNode(p, n, &symbol);
		emitOp(p, n, T_ASSIGN);
		parseExpression(p, n);
		emitOp(p, n, T_END_STATEMENT);
		emitOp(p, n, T_START_STATEMENT);
	} else {
		CloneLexData(&symbol, &lexData);
	}
	if(expectToken(T_BEGIN)==-1) parseError("Expected begin");
	while(expectToken(T_CASE)!=-1) {
		if(cases) {
			emitOp(p, n, T_ELSE);
			emitOp(p, n, T_START_STATEMENT);
			emitOp(p, n, T_BEGIN);
			emitOp(p, n, T_START_STATEMENT);
		}
		emitOp(p, n, T_IF);
		emitOp(p, n, T_START_EXPRESSION);
		emitNode(p, n, &symbol);
		parseExpression(p, n);
		emitOp(p, n, T_EQUAL);
		emitOp(p, n, T_END_EXPRESSION);
		emitOp(p, n, T_THEN);
		emitOp(p, n, T_START_STATEMENT);
		emitOp(p, n, T_BEGIN);
		if(expectToken(':')==-1) parseError("Expected ':'");
		while(expectToken(T_EOF)==-1&&expectToken(T_CASE)==-1&&expectToken(T_DEFAULT)==-1&&expectToken(T_END)==-1) parseStatement(p);
		ungetToken();
		emitOp(p, n, T_END);
		emitOp(p, n, T_END_STATEMENT);
		cases++;
	}
	if(cases&&expectToken(T_DEFAULT)!=-1) {
		if(expectToken(':')==-1) parseError("Expected ':'");
		emitOp(p, n, T_ELSE);
		emitOp(p, n, T_START_STATEMENT);
		emitOp(p, n, T_BEGIN);
		while(expectToken(T_EOF)==-1&&expectToken(T_CASE)==-1&&expectToken(T_DEFAULT)==-1&&expectToken(T_END)==-1) parseStatement(p);
		ungetToken();
		emitOp(p, n, T_END);
		emitOp(p, n, T_END_STATEMENT);
	}
	if(!cases) parseSemanticError("switch statement with no cases");
	while(--cases) {
		emitOp(p, n, T_END_STATEMENT);
		emitOp(p, n, T_END);
		emitOp(p, n, T_END_STATEMENT);
	}
	if(expectToken(T_END)==-1) parseError("Expected end");
}

void parseAssocArrayConstant(Procedure *p, NodeList *n) {
	emitOp(p, n, T_TS_TEMP_ARRAY);
	emitOp(p, n, T_START_EXPRESSION);
	emitInt(p, n, -1);
	emitOp(p, n, T_END_EXPRESSION);
	emitOp(p, n, T_START_EXPRESSION);
	emitInt(p, n, 0);
	emitOp(p, n, T_END_EXPRESSION);
	if (lex() != '}') {
		ungetToken();
		emitOp(p, n, T_TS_STACK_ARRAY);
		parseExpression(p, n);
		if (expectToken(':') == -1) parseError("Expected ':'");
		parseExpression(p, n);
		emitOp(p, n, '+');
		while (lex() == ',') {
			emitOp(p, n, T_TS_STACK_ARRAY);
			parseExpression(p, n);
			if (expectToken(':') == -1) parseError("Expected ':'");
			parseExpression(p, n);
			emitOp(p, n, '+');
		}
		ungetToken();
		if (lex() != '}') {
			parseError("Mismatched '{}'");
		}
	}
	return;
}

void parseArrayConstant(Procedure *p, NodeList *n) {
	int i;
	emitOp(p, n, T_TS_TEMP_ARRAY);
	for (i=0; i<2; i++) {
		emitOp(p, n, T_START_EXPRESSION);
		emitInt(p, n, 0);
		emitOp(p, n, T_END_EXPRESSION);
	}
	if (lex() != ']') {
		ungetToken();
		emitOp(p, n, T_TS_STACK_ARRAY);
		emitOp(p, n, T_START_EXPRESSION);
		emitInt(p, n, 0);
		emitOp(p, n, T_END_EXPRESSION);
		parseExpression(p, n);
		emitOp(p, n, '+');
		i=1;
		while (lex() == ',') {
			emitOp(p, n, T_TS_STACK_ARRAY);
			emitOp(p, n, T_START_EXPRESSION);
			emitInt(p, n, i);
			emitOp(p, n, T_END_EXPRESSION);
			parseExpression(p, n);
			emitOp(p, n, '+');
			i++;
		}
		ungetToken();
		if (lex() != ']') {
			parseError("Mismatched '[]'");
		}
	}
	return;
}