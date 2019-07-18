#ifndef _GENCODE_H_
#define _GENCODE_H_

extern void generateCode(Program *, const char *);

extern int writeNumExpression(NodeList *n, int i, int num, FILE *f);
extern int writeExpression(NodeList *n, int i, FILE *f);
extern int writeExpressionProc(NodeList *n, int i, FILE *f);
extern int writeNumExpressionProc(NodeList *n, int i, int num, FILE *f);
extern void writeOp(unsigned short op, FILE *f);
extern void writeInt(unsigned long a, FILE *f);
extern void writeFloat(float a, FILE *f);
extern void writeString(unsigned long a, FILE *f);
extern int writeBlock(NodeList *n, int i, FILE *f);

#endif