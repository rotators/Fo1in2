#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lex.h"
#include "parse.h"
#include "parselib.h"
#include "extra.h"

LexData lexData;
static char *tokens[256+T_END_TOKEN];
static struct {
	LexData c;
	char *name;
} constants[C_END_CONSTANT];

typedef struct {
	LexData* data;
	int count;
	int size;
} AssignmentCache;
static AssignmentCache cache;

static void AppendToAssignCache() {
	if(!cache.data) {
		cache.size=4;
		cache.data=(LexData*)malloc(4*sizeof(LexData));
	} else if(cache.size==cache.count) {
		cache.size+=4;
		cache.data=(LexData*)realloc(cache.data, cache.size*sizeof(LexData));
	}
	memcpy(&cache.data[cache.count++], &lexData, sizeof(LexData));
}

extern int backwardcompat;

static int ungotToken = -1;
static int lastToken = -1;
static int inited = 0;

static int numFileNames=0;
static int fileNameSize=0;
static char **fileNames=0;
const char *AddFileName(const char *c) {
	if(fileNameSize==0) {
		fileNames=(char**)malloc(8*4);
		fileNameSize=8;
	} else if(numFileNames==fileNameSize-1) {
		fileNameSize+=8;
		fileNames=(char**)realloc(fileNames, fileNameSize*4);
	}
	fileNames[numFileNames]=(char*)malloc(strlen(c)+1);
	strcpy(fileNames[numFileNames], c);
	return fileNames[numFileNames++];
}
void FreeFileNames() {
	int i;
	for(i=0;i<numFileNames;i++) free(fileNames[i]);
	numFileNames=0;
}

/* Old behaviour atoi (begin) */

int old_atoi(const char* p )
{
	int value;
	char sign;

	while(isspace(*p)) {
		++p;
	}

	sign = *p;

	if (sign == '+' || sign == '-' ) {
		++p;
	}

	value = 0;

	while(isdigit(*p)) {
		value = value * 10 + *p - '0';
		++p;
	}

	if (sign == '-' ) {
		value = - value;
	}

	return( value );
}

int atoi_hex(const char* p )
{
	int value, tmp;
	unsigned int i;
	value = 0;

	for(i=0;i<strlen(p);i++) {
		if(p[i]>='0'&&p[i]<='9') tmp=p[i]-'0';
		else tmp=p[i]-'a' + 10;
		value = value*16 + tmp;
	}

	return value;
}

/* Old behaviour atoi (end) */

void lexClose(void) {
	inited = 0;
	if(cache.data) free(cache.data);
}
void initLex(void) {
	int i;

	if (inited) return;

	cache.data=0;
	cache.count=0;
	cache.size=0;

	inited = 1;
	lastToken = -1;
	ungotToken = -1;

	for (i=0; i<256; ++i) {
		tokens[i] = 0;
	}

	tokens[T_PROCEDURE] = "procedure";
	tokens[T_VARIABLE]  = "variable";
	tokens[T_IMPORT]    = "import";
	tokens[T_EXPORT]    = "export";
	tokens[T_IN]        = "in";
	tokens[T_WHEN]      = "when";
	if(backwardcompat == 0) {
		tokens[T_PURE] = "pure";
		tokens[T_INLINE] = "inline";
	}
	tokens[T_BEGIN]     = "begin";
	tokens[T_END]       = "end";
	tokens[T_EXIT]      = "exit";
	tokens[T_DETACH]    = "detach";
	tokens[T_FORK]      = "fork";
	tokens[T_SPAWN]     = "spawn";
	tokens[T_CALLSTART] = "callstart";
	tokens[T_EXEC]      = "exec";

	tokens[T_NOOP]      = "noop";
	tokens[T_WAIT]      = "wait";     // wait specified # milliseconds
	tokens[T_CALL]      = "call";     // call a function
	tokens[T_CANCEL]    = "cancel";   // cancel pending events for function
	tokens[T_CANCELALL] = "cancelall";
	tokens[T_IF]        = "if";
	tokens[T_THEN]      = "then";
	tokens[T_ELSE]      = "else";
	if(backwardcompat == 0) {
		tokens[T_SWITCH]    = "switch";
		tokens[T_CASE]      = "case";
		tokens[T_DEFAULT]   = "default";
	}
	tokens[T_END]       = "end";
	tokens[T_EQUAL]     = "==";
	tokens[T_NOT_EQUAL] = "!=";
	tokens[T_LESS_EQUAL]= "<=";
	tokens[T_GREATER_EQUAL] = ">=";
	tokens[T_ASSIGN]    = ":=";
	tokens[T_AND]       = "and";
	tokens[T_OR]        = "or";
	tokens[T_BWAND]     = "bwand";
	tokens[T_BWOR]      = "bwor";
	tokens[T_BWNOT]     = "bwnot";
	tokens[T_BWXOR]     = "bwxor";
	tokens[T_NOT]       = "not";
	tokens[T_FLOOR]	    = "floor";
	tokens[T_RETURN]    = "return";
	tokens[T_DO]        = "do";
	tokens[T_WHILE]     = "while";
	if(backwardcompat == 0) {
		tokens[T_FOR]       = "for";
		tokens[T_FOREACH]   = "foreach";
		//tokens[T_IN]         = "in";
		tokens[T_BREAK]     = "break";
		tokens[T_CONTINUE]  = "continue";
	}
	tokens[T_INCLUDE]   = "include";
	tokens[T_STARTCRITICAL] = "startcritical";
	tokens[T_ENDCRITICAL]   = "endcritical";
	tokens[T_CRITICAL]  = "critical";

	lexAddConstant(C_TRUE, "true", T_INT, 1);
	lexAddConstant(C_FALSE, "false", T_INT, 0);
	initLibExtras();
}

static int lookupConstant(char *name) {
	int i;

	for (i=0; i<C_END_CONSTANT; ++i) {
		if (constants[i].name && _stricmp(constants[i].name, name) == 0)
			return i;
	}
	return -1;
}

void lexAddConstant(int c, char *name, int type, unsigned long val) {
	constants[c].name = name;
	constants[c].c.type = type;
	switch(type) {
	case T_INT:    constants[c].c.intData = val; break;
	case T_FLOAT:  constants[c].c.floatData = *(float *)&val; break;
	case T_STRING: constants[c].c.stringData = *(char **)&val; break;
	default: parseError("Unknown constant type %x\n", type);
	}
}

void lexAddToken(int token, char *name) {
	tokens[token] = name;
}

char* lexGetToken(int token) {
	return tokens[token];
}

static int lookupToken(char *string) {
	int i;

	for (i=256; i<T_END_TOKEN; ++i)
		if (tokens[i] && _stricmp(string, tokens[i]) == 0)
			break;

	return i == T_END_TOKEN ? -1 : i;
}

/*
* tokens are white-space delimited.
* all single-character tokens are defined by their character;
* token a is 'a', token b is 'b', etc.
* Only end-of-line comments are supported; '#' is the start of an
* end-of-line comment.
*/

static InputStream *stream;

const char *lexGetFilename(InputStream *s) { return  s ? s->name : 0; }
/*
* read a character from the current input stream
*/
static int getChar(void) {
	int ret = -1;

	if (!stream) return -1;
	ret = (stream->lastChar = fgetc(stream->file));
	stream->column++;
	if (ret == '\n') {
		stream->lineno++;
		stream->lastLineLen = stream->column - 1;
		stream->column = 1;
	}
	return ret;
}

static void ungetChar(void) {
	if (!stream) return;
	stream->column--;
	if (stream->lastChar == '\n') {
		stream->lineno--;
		stream->column = stream->lastLineLen;
	}
	ungetc(stream->lastChar, stream->file);
	stream->lastChar = -1;
}

static int expect(int what, int hit, int miss) {
	int c = getChar();
	if (c == what) return hit;
	else { ungetChar(); return miss; }
}

static int validSymbolChar(int c) {
	return (c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ||
		(c >= '0' && c <= '9') ||
		c == '_';
}

#define GOT_DECIMAL 0x01
#define GOT_MINUS   0x02
#define GOT_PLUS    0x04

static int validNumberChar(int c) {
	return (c >= '0' && c <= '9') || c == '.';
}

static int validHexNumberChar(int c) {
	return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f');
}

static void parseNumber(void) {
	int c;
	char buf[80];
	int i = 0;
	int floatFlag = 0;
	int hexFlag = 0;

	c = getChar();
	if(c=='0') {
		c=getChar();
		if(c=='x' || c=='X') hexFlag=1;
		else ungetChar();
	} else ungetChar();

	if(hexFlag) {
		do {
			c = getChar();
			if(c>='A' && c<='F') c-= 'A' - 'a';
			buf[i++] = c;
		} while(validHexNumberChar(c));

		buf[--i] = 0;
		ungetChar();

		lexData.type = T_INT;
		lexData.intData = atoi_hex(buf);
	} else {
		do {
			c = getChar();
			buf[i++] = c;

			if (c == '.')
				floatFlag = 1;
		} while(validNumberChar(c));

		buf[--i] = 0;
		ungetChar();

		if (floatFlag) {
			lexData.type = T_FLOAT;
			lexData.floatData = (float)atof(buf);
		}
		else {
			lexData.type = T_INT;
			lexData.intData = old_atoi(buf);
		}
	}
}

static void parseCharConstant(void) {
	int c;

	c = getChar();

	if (c != '\'')
		return;

	c = getChar();

	if (c == '\\') {
		c = getChar();
		switch(c) {
		case 'a': c = '\a'; break;
		case 'b': c = '\b'; break;
		case 'f': c = '\f'; break;
		case 'n': c = '\n'; break;
		case 'r': c = '\r'; break;
		case 't': c = '\t'; break;
		case 'v': c = '\t'; break;
		case '0': {
			int d;

			d = getChar();
			if (!isdigit(d)) parseError("Illegally formatted octal constant\n");
			d = d - '0';
			if (d > 7)
				parseError("Illegally formatted octal constant\n");
			c = d;

			d = getChar();
			if (!isdigit(d)) parseError("Illegally formatted octal constant\n");
			d = d - '0';
			if (d > 7)
				parseError("Illegally formatted octal constant\n");
			c = (c * 8) + d;

			d = getChar();
			if (d == '\'')
				ungetChar();
			else {
				if (!isdigit(d)) parseError("Illegally formatted octal constant\n");
				d = d - '0';
				if (d > 7)
					parseError("Illegally formatted octal constant\n");
				c = (c * 8) + d;
			}
			break;
				  }
		default:
			parseError("Illegally formatted escaped character\n");
			break;
		}
	}
	lexData.type = T_INT;
	lexData.intData = c;

	c = getChar();
	if (c != '\'')
		parseError("Illegally formated character constant\n");
}

static void parseString(char *buf, int skipEsc)
{
	int c;
	int i = 0;

	while(1) {
		c = getChar();

		if (c == EOF) {
			break;
		}

		if (c == '"') {   // got end of string, find next line
			do {
				c = getChar();
			} while(c == ' ' || c == '\t' || c == '\n' || c == '\v');

			if (c == '"')  // two strings back to back
				continue;
			else {         // single string
				ungetChar();
				break;
			}
		}

		if (!skipEsc && c == '\\') {  // got escape sequence
			c = getChar();

			switch(c) {
			case 'a':
				c = '\a';
				break;

			case 'b':
				c = '\b';
				break;

			case 'f':
				c = '\f';
				break;

			case 'n':
				c = '\n';
				break;

			case 'r':
				c = '\r';
				break;

			case 't':
				c = '\t';
				break;

			case 'v':
				c = '\t';
				break;
			case '\\':
			case '"':
				break;
			default:
				parseWarning("Unrecognised escape character '%c'", c);
			}
		}

		buf[i++] = c;
	}

	buf[i] = 0;
	lexData.type = T_STRING;
	lexData.stringData = buf;
}

void continueLex(InputStream *s) {
	stream = s;
}

void startLex(InputStream *s) {
	stream = s;
	s->lineno = 1;
	s->column = 1;
}

int lexGetLineno(InputStream *s) {
	return s ? s->lineno : -1;
}

int lexGetColumn(InputStream *s) {
	return s ? s->column : -1;
}

/*
* read a symbol from the input stream
*/
int lex_internal(void) {
	int c, i;
	static char buf[2][1024];
	static int which;
	int ret;

	/* read past spaces */
top:
	c = getChar();

	switch(c) {
	case EOF:
		ret = T_EOF;
		break;

	case '/': {
		int d;

		d = getChar();

		if (d == '*') {
			while(1) {
				d = getChar();

				while(d != '*') {   // got slash-star, now look for star-slash
					if (d == EOF) {
						ungetChar();
						goto top;
					}

					d = getChar();
				}

				d = getChar();   // found star, is next char a slash?

				if (d == '/')    // yup, start parsing over
					goto top;
				else if (d == '*')
					ungetChar();

				// else just continue
			}
		}
		else if (d != '/') {
			if (d == '=')
				ret = T_ASSIGN_DIV;
			else {
				ungetChar();
				ret = '/';
			}

			break;
		}
		/*FALLTHRU*/
			  }

	case '#': {  // parse compiler directives
		do {
			c = getChar();
		} while(c != EOF && c != '\n' && !validSymbolChar(c));

		if (validSymbolChar(c)) {
			int i = 0, j;

			buf[which][0] = c;

			while(1) {
				c = getChar();

				if (!validSymbolChar(c))
					break;

				buf[which][i+1] = c;
				i++;
			}

			buf[which][i+1] = 0;

			if (_stricmp(buf[which], "line") == 0) {// line directive
				do {
					c = getChar();
				} while(c != EOF && c != '\n' && !isdigit(c));


				if (c == EOF) {
					ungetChar();
				}
				else if (c != '\n') {
					ungetChar();
					parseNumber();
					j = lexData.intData;

					do {
						c = getChar();
					} while(c != EOF && c != '\n' && c != '"');

					if (c == '"') {
						stream->lineno = j - 1;
						parseString(buf[which], 1);
						stream->name=AddFileName(buf[which]);
					}
					else if (c == EOF)
						ungetChar();
				}
			}
			else if (c == EOF) {
				ungetChar();
			}
			else if (c != '\n') {
				do {
					c = getChar();
				} while(c != '\n' && c != EOF) ;

				if (c == EOF)
					ungetChar();
			}
		}
		else if (c == EOF) {
			ungetChar();
		}
		else if (c != '\n') {
			do {
				c = getChar();
			} while(c != '\n' && c != EOF) ;

			if (c == EOF)
				ungetChar();
		}
			  }

	case '\t':
	case ' ':
	case '\n':
	case '\v':
		goto top;
		break;

	case '1': case '2': case '3': case '4': case '5':
	case '6': case '7': case '8': case '9': case '0':
	case '.':
		if (lastToken == T_SYMBOL || lastToken == ']') {
			ret = c;
		} else {
			ungetChar();
			parseNumber();
			ret = T_CONSTANT;
		}
		break;

	case '\'':
		ungetChar();
		parseCharConstant();
		ret = T_CONSTANT;
		break;

	case '"':
		parseString(buf[which], 0);
		ret = T_CONSTANT;
		break;

#define EXPECT(x, y, z) case x: ret = expect(y, z, x); break;
		EXPECT(':', '=', T_ASSIGN);
		EXPECT('=', '=', T_EQUAL);
		EXPECT('>', '=', T_GREATER_EQUAL);
		EXPECT('<', '=', T_LESS_EQUAL);
		EXPECT('!', '=', T_NOT_EQUAL);

case '+':
	if(expect('=', T_ASSIGN_ADD, 0)) ret=T_ASSIGN_ADD;
	else if(expect('+', T_INC, 0)) ret=T_INC;
	else ret='+';
	break;
case '-':
	if (expect('=', T_ASSIGN_SUB, 0)) ret=T_ASSIGN_SUB;
	else if (expect('-', T_DEC, 0)) ret=T_DEC;
	/*else {
		int c = getChar();
		if (validNumberChar(c)) {
			ungetChar();
			parseNumber();
			if (lexData.type == T_FLOAT)
				lexData.floatData = -lexData.floatData;
			else
				lexData.intData = -lexData.intData;
			ret = T_CONSTANT;
		} else {
			ungetChar();
			ret='-';
		}
	}*/
	else ret='-';
	break;

	EXPECT('*', '=', T_ASSIGN_MUL);

case '{': case '}':
case '(': case ')':
case ';': case ',': case '%':
case '^': // sfall
case '[': case ']':
	ret = c;
	break;
case '@':
	if(expect('"', 1, 0)) {
		parseString(buf[which], 1);
		ret = T_CONSTANT;
		break;
	} else {
		ret = c;
		break;
	}
default:
	i = 0;

	do {
		buf[which][i++] = c;
		c = getChar();
	} while(validSymbolChar(c));

	ungetChar();
	buf[which][i] = 0;
	ret = lookupToken(buf[which]);

	if (ret == -1) {
		ret = lookupConstant(buf[which]);

		if (ret == -1) {
			lexData.stringData = buf[which];
			ret = T_SYMBOL;
		}
		else {
			lexData.type = constants[ret].c.type;

			switch(lexData.type) {
			case T_INT:
				lexData.intData = constants[ret].c.intData;
				break;

			case T_FLOAT:
				lexData.floatData = constants[ret].c.floatData;
				break;

			case T_STRING:
				lexData.stringData = constants[ret].c.stringData;
				break;
			}

			ret = T_CONSTANT;
		}
	}

	break;
	}

	which = !which;
	//lexData.token = ret;
	return lastToken = ret;
}

int lex(void) {
	int token;
	if (ungotToken != -1) {
		token = ungotToken;
		ungotToken = -1;
		return token;
	}
	token=lex_internal();
	//parseOutput("%d ", token);
	lastToken = token;
	lexData.token = token;
	return token;
}

void ungetToken(void) { ungotToken = lastToken; }

void setNextToken(LexData *data) {
	ungotToken = data->token;
	lexData = *data;
}