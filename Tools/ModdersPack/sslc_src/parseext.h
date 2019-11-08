#ifndef _PARSEEXT_H_
#define _PARSEEXT_H_

/*
	Extended SSL syntax for sfall
*/

typedef struct {
	char* name;
	int len;
	int datasize;
} ArrayVar;
typedef struct {
	ArrayVar* vars;
	int count;
	int size;
} ArrayVarList;

void appendNodeListPart(NodeList* dst, const NodeList* src, int offset, int length);
void appendNodeList(NodeList* dst, const NodeList* src);

int parseArrayDereference(Procedure *p, NodeList *nodes, LexData symb, int *lastExprSize);
void parseArrayAssignment(Procedure *p, NodeList *nodes, LexData symb);
void parseFor(Procedure *p, NodeList *n);
void parseForEach(Procedure *p, NodeList *n);
void parseSwitch(Procedure *p, NodeList *n);
void parseAssocArrayConstant(Procedure *p, NodeList *n);
void parseArrayConstant(Procedure *p, NodeList *n);

#endif
