#include "parse.h"
#include "parselib.h"
#include "extra.h"

#include "opcodes.h"
#include "oplib.h"
#include "opextra.h"

#include <stdlib.h>
#include <string.h>

#define Protect(a) if(_stricmp(c, a) == 0) return 1;

#define F_OP(token,op) case token: out->floatData=fd1 op fd2; break;
#define F_IOP(token,op) case token: out->type=V_INT; out->intData=fd1 op fd2; break;
#define I_OP(token,op) case token: out->intData=in1->intData op in2->intData; break;

#define VU_FIRST_ASSIGN_IS_PURE  0x01
#define VU_FIRST_ASSIGN_IN_WHILE 0x02
#define VU_LAST_ASSIGN_IN_WHILE  0x04
#define VU_FIRST_ASSIGN_IS_DEAD  0x08
#define VU_LAST_ASSIGN_IS_PURE   0x10
#define VU_FIRST_READ_IN_WHILE   0x20
#define VU_LAST_READ_IN_WHILE    0x40
#define VU_FIRST_ASSIGN_TRANSFERABLE 0x80

extern int optimize;
static Program* currprogram;

//Sanity checks. Should never be hit
static void assert(int i) {
	if(!i)
		parseError("ICE in optimizer.");
}

//Strip out some nods from a nodelist
static void RemoveNodes(NodeList* nodes, int start, int count) {
	memmove(&nodes->nodes[start], &nodes->nodes[start+count], (nodes->numNodes-(start+count))*sizeof(Node));
	nodes->numNodes-=count;
	//not much point reallocing
}

//Check if a node is a local variable, and return its id if so or -1 otherwise
static int LookupVariable(const Node* node) {
	assert(node->token==T_SYMBOL);
	if(node->value.type!=P_LOCAL) return -1;
	return node->value.intData;
}

//Returns true if a token is known to have no side effects
static int IsTokenPure(int token) {
	//TODO: Go through the whole list
	switch(token) {
	case T_TS_LEN_ARRAY:
	case T_TS_ATOI:
	case T_TS_ATOF:
	case T_TS_TILE_PID:
	case T_TS_MODIFIED_INI:
		return 1;
	}
	return 0;
}

//Returns true if we can prove an expression has no side effects
static int IsExpressionPure(const Node* node) {
	assert(node->token==T_START_EXPRESSION);
	while((++node)->token!=T_END_EXPRESSION) {
		//if(node->token==T_START_EXPRESSION) return 0;
		if(node->token>=T_END_CORE&&!IsTokenPure(node->token)) return 0;
		if(node->token==T_SYMBOL&&node->value.type&P_PROCEDURE) {
			if(node->value.type!=(P_LOCAL|P_PROCEDURE) || !(currprogram->procedures.procedures[node->value.intData].type&P_PURE)) return 0;
		}
	}
	return 1;
}

typedef struct {
	int firstassign;
	int lastassign;
	int firstuse;
	int lastuse;
	int flags;
} VarUsage;

static void FindVarUsage(const Node* node, VarUsage* usage, int varCount) {
	int depth=1, currstatement=0, i=0, whiledepth=0, ifdepth=0, var, expressiondepth;
	memset(usage, 0, varCount*sizeof(VarUsage));
	assert(node->token==T_BEGIN);
	while(depth) {
		i++;
		switch((++node)->token) {
		case T_BEGIN: depth++; break;
		case T_END: depth--; break;
		case T_START_STATEMENT:
			if(ifdepth) ifdepth++;
			if(!whiledepth) {
				currstatement=i;
				if(node[1].token==T_WHILE) {
					whiledepth=1;
				} else if(node[1].token==T_IF&&!ifdepth) {
					ifdepth=1;
				}
			} else whiledepth++;
			break;
		case T_END_STATEMENT:
			if(ifdepth) ifdepth--;
			if(whiledepth) whiledepth--;
			break;
		case T_ASSIGN: case T_ASSIGN_ADD: case T_ASSIGN_SUB: case T_ASSIGN_MUL: case T_ASSIGN_DIV:
			if((var=LookupVariable(&node[-1]))!=-1) {
				int pure=IsExpressionPure(&node[1]);
				usage[var].lastassign=currstatement;
				if(whiledepth) usage[var].flags|=VU_LAST_ASSIGN_IN_WHILE;
				else usage[var].flags&=~VU_LAST_ASSIGN_IN_WHILE;
				if(pure) usage[var].flags|=VU_LAST_ASSIGN_IS_PURE;
				if(!usage[var].firstuse) {
					if(!usage[var].firstassign) {
						usage[var].firstassign=currstatement;
						if(whiledepth) usage[var].flags|=VU_FIRST_ASSIGN_IN_WHILE;
						if(pure) {
							usage[var].flags|=VU_FIRST_ASSIGN_IS_PURE;
							if(!whiledepth&&!ifdepth&&node[2].token==T_CONSTANT&&node[3].token==T_END_EXPRESSION&&node[2].value.type!=V_STRING) {
								usage[var].flags|=VU_FIRST_ASSIGN_TRANSFERABLE|VU_FIRST_ASSIGN_IS_DEAD;
							}
						}
					} else if(!whiledepth && !ifdepth) {
						if(usage[var].flags&VU_FIRST_ASSIGN_IS_PURE&&node->token==T_ASSIGN) usage[var].flags|=VU_FIRST_ASSIGN_IS_DEAD;
					} else if(!pure&&currstatement==usage[var].firstassign) usage[var].flags&=~VU_FIRST_ASSIGN_IS_PURE;
				}
				if(node->token!=T_ASSIGN) {
					usage[var].lastuse=currstatement;
					if(whiledepth) usage[var].flags|=VU_LAST_READ_IN_WHILE;
					else usage[var].flags&=~VU_LAST_READ_IN_WHILE;
					if(!usage[var].firstuse) {
						usage[var].firstuse=currstatement;
						if(whiledepth) usage[var].flags|=VU_FIRST_READ_IN_WHILE;
					}
				}
			}
			break;
		case T_START_EXPRESSION:
			expressiondepth=1;
			while(expressiondepth) {
				i++;
				switch((++node)->token) {
				case T_START_EXPRESSION: expressiondepth++; break;
				case T_END_EXPRESSION: expressiondepth--; break;
				case T_SYMBOL:
					if((var=LookupVariable(node))!=-1) {
						usage[var].lastuse=currstatement;
						if(whiledepth) usage[var].flags|=VU_LAST_READ_IN_WHILE;
						else usage[var].flags&=~VU_LAST_READ_IN_WHILE;
						if(!usage[var].firstuse) {
							usage[var].firstuse=currstatement;
							if(whiledepth) usage[var].flags|=VU_FIRST_READ_IN_WHILE;
						}
					}
				}
			}
			break;
		}
	}
	assert(node->token==T_END);
}

static int isValidBinaryOp(int op) {
	return op=='+'||op=='-'||op=='*'||op=='/'||op==T_AND||op==T_OR||op==T_BWAND||op==T_BWOR||op==T_BWXOR||
		op=='>'||op=='<'||op==T_EQUAL||op==T_NOT_EQUAL||op==T_LESS_EQUAL||op==T_GREATER_EQUAL;
}

//Calculate the result of a constant operation (doesn't handle strings, which would require namespace modifications)
static void PerformConstOp(const Value* in1, const Value* in2, Value* out, int op, const Node* node) {
	int isfloat;
	assert(isValidBinaryOp(op));
	assert(in1->type==V_INT||in1->type==V_FLOAT);
	assert(in2->type==V_INT||in2->type==V_FLOAT);
	isfloat = in1->type==V_FLOAT || in2->type==V_FLOAT;
	if(isfloat) {
		float fd1=in1->type==V_FLOAT?in1->floatData:(float)in1->intData;
		float fd2=in2->type==V_FLOAT?in2->floatData:(float)in2->intData;
		out->type=V_FLOAT;
		switch(op) {
			F_OP('+', +)
			F_OP('-', -)
			F_OP('*', *)
			F_OP('/', /)
			F_IOP(T_EQUAL, ==)
			F_IOP(T_NOT_EQUAL, !=)
			F_IOP('>', >)
			F_IOP('<', <)
			F_IOP(T_LESS_EQUAL, <=)
			F_IOP(T_GREATER_EQUAL, >=)
		case T_AND:
			out->type=V_INT;
			out->intData=fd1!=0.0 && fd2!=0.0;
			break;
		case T_OR:
			out->type=V_INT;
			out->intData=fd1!=0.0 || fd2!=0.0;
			break;
		case T_BWAND:
			out->type=V_INT;
			parseWarningAtNode(node, "Optimizer encountered a bitwise operation on a float constant");
			out->intData=in1->intData & in2->intData;
			break;
		case T_BWOR:
			out->type=V_INT;
			parseWarningAtNode(node, "Optimizer encountered a bitwise operation on a float constant");
			out->intData=in1->intData | in2->intData;
			break;
		case T_BWXOR:
			out->type=V_INT;
			parseWarningAtNode(node, "Optimizer encountered a bitwise operation on a float constant");
			out->intData=in1->intData ^ in2->intData;
			break;
		}
	} else {
		out->type=V_INT;
		switch(op) {
			I_OP('+', +)
			I_OP('-', -)
			I_OP('*', *)
			I_OP('/', /)
			I_OP(T_AND, &&)
			I_OP(T_OR, ||)
			I_OP(T_BWAND, &)
			I_OP(T_BWOR, |)
			I_OP(T_BWXOR, ^)
			I_OP(T_EQUAL, ==)
			I_OP(T_NOT_EQUAL, !=)
			I_OP('>', >)
			I_OP('<', <)
			I_OP(T_LESS_EQUAL, <=)
			I_OP(T_GREATER_EQUAL, >=)
		}
	}
}

static int ConstantFolding(NodeList* _nodes) {
	int i, token, matched=0;
	Node* nodes=_nodes->nodes;
	for(i=2;i<_nodes->numNodes;i++) {
		token=nodes[i].token;
		if(isValidBinaryOp(token)) {
			if(nodes[i-1].token==T_CONSTANT && nodes[i-2].token==T_CONSTANT && nodes[i-1].value.type!=V_STRING && nodes[i-2].value.type!=V_STRING) {
				parseMessageAtNode(&nodes[i], "Folding constant binary expression");
				matched=1;
				PerformConstOp(&nodes[i-2].value, &nodes[i-1].value, &nodes[i].value, token, &nodes[i]);
				nodes[i].token=T_CONSTANT;
				RemoveNodes(_nodes, i-2, 2);
				i -= 2;
			}/* AND/OR were changed in the tree
				else if(token==T_AND||token==T_OR) {
				if((nodes[i-1].token==T_CONSTANT && nodes[i-1].value.type!=V_STRING) || (nodes[i-2].token==T_CONSTANT && nodes[i-2].value.type!=V_STRING)) {
					if((nodes[i-1].token==T_SYMBOL&&!(nodes[i-1].value.type&P_PROCEDURE)) || (nodes[i-2].token==T_SYMBOL&&!(nodes[i-1].value.type&P_PROCEDURE))) {
						int value, found=0;
						if(nodes[i-1].token==T_CONSTANT && nodes[i-1].value.type!=V_STRING) value=nodes[i-1].value.intData;
						else value=nodes[i-2].value.intData;
						if(!value && token==T_AND) {
							found=1;
						} else if(value && token==T_OR) {
							found=2;
						}
						if(found) {
							parseMessageAtNode(&nodes[i], "Folding semi-constant binary expression");
							nodes[i].token=T_CONSTANT;
							nodes[i].value.type=V_INT;
							nodes[i].value.intData=found-1;
							RemoveNodes(_nodes, i-2, 2);
							i -= 2;
						}
					}
				}
			}*/
		} else if(token==T_NOT||token==T_BWNOT||token==T_NEGATE) {
			if(nodes[i-1].token==T_CONSTANT && nodes[i-1].value.type!=V_STRING) {
				parseMessageAtNode(&nodes[i], "Folding constant unary expression");
				matched=1;
				if(token==T_NOT) {
					nodes[i-1].value.type=V_INT;
					nodes[i-1].value.intData=!nodes[i-1].value.intData;
				} else if (token==T_BWNOT) {
					if(nodes[i-1].value.type!=V_INT) parseWarningAtNode(&nodes[i-1], "Optimizer encountered a bitwise operation on a float constant");
					nodes[i-1].value.type=V_INT;
					nodes[i-1].value.intData = ~nodes[i-1].value.intData;
				} else {
					if (nodes[i-1].value.type==V_INT)
						nodes[i-1].value.intData = -nodes[i-1].value.intData;
					else
						nodes[i-1].value.floatData = -nodes[i-1].value.floatData;
				}
				RemoveNodes(_nodes, i, 1);
				i -= 1;
			}
		}
	}
	return matched;
}

static int ConstantPropagateExpression(Node* nodes, Variable* vars, Value* values, int varCount, int *_i) {
	int expressiondepth=1, matched=0, token, var, i=*_i;
	assert(nodes[i].token==T_START_EXPRESSION);
	while(expressiondepth) {
		token = nodes[++i].token;
		if(token==T_START_EXPRESSION) expressiondepth++;
		else if(token==T_END_EXPRESSION) expressiondepth--;
		else if(token==T_SYMBOL) {
			if((var=LookupVariable(&nodes[i]))!=-1) {
				if(values[var].type!=-1) {
					nodes[i].token=T_CONSTANT;
					nodes[i].value=values[var];
					parseMessageAtNode(&nodes[i], "propagating constant %d", values[var].intData);
					matched=1;
				}
			}
		}
	}
	assert(nodes[i].token==T_END_EXPRESSION);
	*_i=i;
	return matched;
}

static int* FindAssignmentsInBlock(const Node* nodes, const Variable* vars, int varCount) {
	int* results=(int*)calloc(1, varCount*4);
	int statementdepth=1, var;
	assert(nodes->token==T_START_STATEMENT);
	while(statementdepth) {
		switch(nodes->token) {
		case T_START_STATEMENT: statementdepth++; break;
		case T_END_STATEMENT: statementdepth--; break;
		case T_ASSIGN: case T_ASSIGN_ADD: case T_ASSIGN_SUB:
		case T_ASSIGN_MUL: case T_ASSIGN_DIV:
			if(nodes[-1].token==T_SYMBOL&&(var=LookupVariable(&nodes[-1]))!=-1) {
				results[var]=1;
			}
			break;
		}
		nodes++;
	}
	return results;
}

static int ConstantPropagateBlock(Node* nodes, int *_i, Variable* vars, Value* values, int varCount) {
	int i=_i?*_i:0, token, var, matched=0, blockdepth=1, blockbegin, blockend, j;
	assert(nodes->token==T_BEGIN||nodes->token==T_START_STATEMENT);
	if(nodes[i].token==T_BEGIN) {
		blockbegin=T_BEGIN;
		blockend=T_END;
	} else {
		blockbegin=T_START_STATEMENT;
		blockend=T_END_STATEMENT;
	}
	i++;
	while(1) {
		token=nodes[i].token;
		if(token==blockbegin) blockdepth++;
		else if(token==blockend) {
			if(!--blockdepth) break;
		} else if(token==T_ASSIGN || token==T_ASSIGN_ADD ||token==T_ASSIGN_SUB || token==T_ASSIGN_MUL || token==T_ASSIGN_DIV) {
			if((var=LookupVariable(&nodes[i-1]))!=-1) {
				if(nodes[i+1].token==T_START_EXPRESSION && nodes[i+2].token==T_CONSTANT && nodes[i+3].token==T_END_EXPRESSION) {
					if(token==T_ASSIGN) values[var]=nodes[i+2].value;
					else if(values[var].type!=-1) {
						switch(token) {
						case T_ASSIGN_ADD: token='+'; break;
						case T_ASSIGN_SUB: token='-'; break;
						case T_ASSIGN_MUL: token='*'; break;
						case T_ASSIGN_DIV: token='/'; break;
						}
						PerformConstOp(&values[var], &nodes[i+2].value, &values[var], token, &nodes[i]);
					}
				} else {
					values[var].type=-1;
				}
			}
		} else if(token==T_IF) {
			int *aif=0, *aelse=0;
			Value* backup=(Value*)malloc(varCount*sizeof(Value));
			memcpy(backup, values, varCount*sizeof(Value));
			i++;
			matched|=ConstantPropagateExpression(nodes, vars, values, varCount, &i);
			i++;
			assert(nodes[i++].token==T_THEN);
			aif=FindAssignmentsInBlock(&nodes[i], vars, varCount);
			ConstantPropagateBlock(nodes, &i, vars, values, varCount);
			if(nodes[i+1].token==T_ELSE) {
				i+=2;
				memcpy(values, backup, varCount*sizeof(Value));
				aelse=FindAssignmentsInBlock(&nodes[i], vars, varCount);
				for(j=0;j<varCount;j++) if(aelse[j]) aif[j]=1;
				ConstantPropagateBlock(nodes, &i, vars, values, varCount);
			}
			for(j=0;j<varCount;j++) {
				if(aif[j]) values[j].type=-1;
			}
			free(aif);
			if(aelse) free(aelse);
			free(backup);
		} else if(token==T_WHILE) {
			//TODO: Check here if the while loop expression is a single symbol; if it's 0 at this point we can eat the loop, even if the loop modifies it
			Node* nodes2=&nodes[i];
			int* invalidate;
			while(nodes2->token!=T_DO) nodes2++;
			invalidate=FindAssignmentsInBlock(nodes2+1, vars, varCount);
			for(j=0;j<varCount;j++) if(invalidate[j]) values[j].type=-1;
		} else if(token==T_START_EXPRESSION) {
			matched|=ConstantPropagateExpression(nodes, vars, values, varCount, &i);
		}
		i++;
	}
	assert(nodes[i].token==blockend);
	if(_i) *_i=i;
	return matched;
}

static int ConstantPropagation(NodeList* _nodes, Variable* vars, Value* values, int varCount, int numArgs) {
	int i;
	for(i=0;i<numArgs;i++) values[i].type=-1;
	for(i=numArgs;i<varCount;i++) values[i]=vars[i].value;
	return ConstantPropagateBlock(_nodes->nodes, 0, vars, values, varCount);
}

#define SkipStatement { statementdepth=1;                                                                \
                      assert(nodes[i-1].token==T_START_STATEMENT);                                       \
                      while(statementdepth) { if(nodes[i].token==T_START_STATEMENT) statementdepth++;    \
                                              else if(nodes[i].token==T_END_STATEMENT) statementdepth--; \
                                              i++;                                                       \
                      }}

static void EatStatement(NodeList* _nodes, int start) {
	int statementdepth=1, i=start+1;
	Node* nodes=_nodes->nodes;
	assert(nodes[start].token==T_START_STATEMENT);
	SkipStatement;
	RemoveNodes(_nodes, start, i-start);
}

static void EatAssignsInWhile(NodeList* _nodes, int start, int varid) {
	int statementdepth=1;
	Node* nodes=_nodes->nodes;
	assert(nodes[start++].token==T_START_STATEMENT);
	assert(nodes[start].token==T_WHILE);
	while(statementdepth) {
		switch(nodes[++start].token) {
		case T_START_STATEMENT:
			if(nodes[start+1].token==T_SYMBOL&&nodes[start+2].token>=T_ASSIGN&&nodes[start+2].token<=T_ASSIGN_DIV&&LookupVariable(&nodes[start+1])==varid) {
				EatStatement(_nodes, start--);
			} else statementdepth++;
			break;
		case T_END_STATEMENT: statementdepth--; break;
		}
	}
	assert(nodes[start].token==T_END_STATEMENT);
}

static void EatDeadStore(NodeList* _nodes, int start, int var) {
	Node* nodes=_nodes->nodes;
	assert(nodes[start].token==T_START_STATEMENT);
	if(nodes[start+1].token==T_WHILE) {
		parseMessageAtNode(&nodes[start+1], "Eating dead stores to variable %d in while loop", var);
		EatAssignsInWhile(_nodes, start, var);
	} else {
		parseMessageAtNode(&nodes[start+1], "Eating dead store to variable %d", var);
		EatStatement(_nodes, start);
	}
}

static int DeadStoreRemoval(NodeList* _nodes, VariableList* vars, VarUsage* usage) {
	int i, matched1, matched2=0;
	Node* nodes=_nodes->nodes;
	while(1) {
		matched1=0;
		FindVarUsage(nodes, usage, vars->numVariables);
		for(i=0;i<vars->numVariables;i++) {
			if(usage[i].flags&VU_FIRST_ASSIGN_IS_DEAD) {
				if(usage[i].flags&VU_FIRST_ASSIGN_TRANSFERABLE) {
					parseMessageAtNode(&nodes[usage[i].firstassign], "Using constant variable store for initializer");
					assert(nodes[usage[i].firstassign + 4].token==T_CONSTANT);
					vars->variables[i].value=nodes[usage[i].firstassign + 4].value;
				}
				EatDeadStore(_nodes, usage[i].firstassign, i);
				matched1=1;
				break;
			} else if(usage[i].lastassign>=usage[i].lastuse && usage[i].flags&VU_LAST_ASSIGN_IS_PURE) {
				if(nodes[usage[i].lastassign+1].token!=T_WHILE || usage[i].lastassign>usage[i].lastuse) {
					//Pretty sure I don't need the do check here
					if(nodes[usage[i].lastassign-1].token!=T_THEN&&nodes[usage[i].lastassign-1].token!=T_ELSE&&nodes[usage[i].lastassign-1].token!=T_DO) {
						EatDeadStore(_nodes, usage[i].lastassign, i);
						matched1=1;
						break;
					}
				}
			}
		}
		if(matched1) {
			matched2=1;
			continue;
		}
		break;
	};
	return matched2;
}

static int DeadCodeRemoval(NodeList* _nodes) {
	int i, statementdepth, takebranch, matched=0;
	Node* nodes=_nodes->nodes;
	//First look for constant if branches
	for(i=0;i<_nodes->numNodes;i++) {
		if (nodes[i].token == T_IF && nodes[i - 1].token == T_START_STATEMENT) {
			if(nodes[i+1].token==T_START_EXPRESSION && nodes[i+2].token==T_CONSTANT && nodes[i+3].token==T_END_EXPRESSION) {
				int back=i-1;
				matched=1;
				//Need to check if fallout considers 'if("bingle")' and 'if("")' to be 1 or 0
				takebranch=nodes[i+2].value.intData;
				RemoveNodes(_nodes, --i, 6); //start statement, if, start expression, const, end expression, then
				assert(nodes[i].token==T_START_STATEMENT);
				if(takebranch) {
					int back2=i++, tmp;
					parseMessageAtNode(&nodes[i], "Eliminating constant if expression (true)");
					assert(nodes[i].token==T_BEGIN);
					SkipStatement;
					assert(nodes[i-2].token==T_END);
					RemoveNodes(_nodes, i-2, 2); //end end statement
					tmp=i;
					i=back2;
					assert(nodes[i].token==T_START_STATEMENT);
					assert(nodes[i+1].token==T_BEGIN);
					RemoveNodes(_nodes, i, 2); //begin begin statement
					i=tmp-4;
					if(nodes[i].token==T_ELSE) {
						RemoveNodes(_nodes, i, 1);
						EatStatement(_nodes, i);
					}
				} else {
					parseMessageAtNode(&nodes[i], "Eliminating constant if expression (false)");
					EatStatement(_nodes, i);
					if(nodes[i].token==T_ELSE) {
						int back2=i++, tmp;
						RemoveNodes(_nodes, i-1, 1); //else
						assert(nodes[i].token==T_BEGIN);
						SkipStatement;
						assert(nodes[i-2].token==T_END);
						RemoveNodes(_nodes, i-2, 2); //end end statement
						tmp=i;
						i=back2;
						assert(nodes[i].token==T_START_STATEMENT);
						assert(nodes[i+1].token==T_BEGIN);
						RemoveNodes(_nodes, i, 2); //else begin statement begin
						i=tmp-4;
					}
				}
				assert(nodes[i].token==T_END_STATEMENT);
				RemoveNodes(_nodes, i, 1); //The final end statement
				i=back;
			}
		}
	}
	//Next strip out anything following returns, breaks and continue
	for(i=0;i<_nodes->numNodes;i++) {
		if(nodes[i].token==T_RETURN||nodes[i].token==T_BREAK||nodes[i].token==T_CONTINUE) {
			//if (nodes[i].token==T_RETURN)
			SkipStatement;
			while(nodes[i].token==T_START_STATEMENT) {
				parseMessageAtNode(&nodes[i], "Eating statement hidden by return");
				EatStatement(_nodes, i);
				matched=1;
			}
		}
	}
	//Finally look for empty if blocks and remove them if the expression is pure
	for(i=0;i<_nodes->numNodes-5;i++) {
		if(nodes[i].token==T_THEN&&nodes[i+3].token==T_END&&nodes[i+4].token==T_END_STATEMENT&&nodes[i+5].token!=T_ELSE) {
			int back=i,expressiondepth=1;
			assert(nodes[i+1].token==T_START_STATEMENT);
			assert(nodes[i+2].token==T_BEGIN);
			assert(nodes[i-1].token==T_END_EXPRESSION);
			i-=2;
			while(expressiondepth) {
				if(nodes[i].token==T_START_EXPRESSION) expressiondepth--;
				else if(nodes[i].token==T_END_EXPRESSION) expressiondepth++;
				i--;
			}
			assert(nodes[i].token==T_IF);
			assert(nodes[--i].token==T_START_STATEMENT);
			if(IsExpressionPure(&nodes[i+2])) {
				parseMessageAtNode(&nodes[i], "Eating empty if block");
				EatStatement(_nodes, i);
				matched=1;
			} else {
				parseWarningAtNode(&nodes[i], "Optimizer found an empty if block, but could not remove it because the expression could not be confirmed as pure");
			}
			i=back;
		}
		if(nodes[i].token==T_ELSE&&nodes[i+3].token==T_END&&nodes[i+4].token==T_END_STATEMENT) {
			int back=i,expressiondepth=1;
			assert(nodes[i+1].token==T_START_STATEMENT);
			assert(nodes[i+2].token==T_BEGIN);
			assert(nodes[i-1].token==T_END_STATEMENT);
			parseMessageAtNode(&nodes[i], "Eating empty else block");
			RemoveNodes(_nodes, i, 1);
			EatStatement(_nodes, i);
			matched=1;
		}
	}
	return matched;
}

static int CanCombine(VarUsage *u1, VarUsage *u2) {
	int u1min=u1->firstassign<u1->firstuse?u1->firstassign:u1->firstuse;
	int u2max=u2->lastassign>u2->lastuse?u2->lastassign:u2->lastuse;
	if(u1min<u2max) return 0;
	if(u1min>u2max) return 1;
	//TODO: If they're equal, if we're in a while loop return 0, otherwise if one is an assign and the other is part of the expression we can probably combine
	return 0;
}

static void VariableReuse(NodeList* _nodes, VariableList* vars, int numArgs, VarUsage* usage) {
	int i, j, k;
	Node* nodes=_nodes->nodes;
	FindVarUsage(nodes, usage, vars->numVariables);
	for(i=vars->numVariables-1;i>=numArgs;i--) {
		for(j=0;j<i;j++) {
			if(CanCombine(&usage[i], &usage[j]) || CanCombine(&usage[j], &usage[i])) {
				parseMessageAtNode(&nodes[0], "Merging variables %d and %d", i, j);
				for(k=0;k<_nodes->numNodes;k++) {
					if(nodes[k].token==T_SYMBOL&&LookupVariable(&nodes[k])==i) nodes[k].value.intData=j;
				}
				FindVarUsage(nodes, usage, vars->numVariables);
				break;
			}
		}
	}
}

static void DeadVariableRemoval(NodeList* _nodes, VariableList* vars, int numArgs) {
	int i, var, j;
	Node* nodes=_nodes->nodes;
	int *uses=(int*)calloc(1, vars->numVariables*4);
	for(i=0;i<vars->numVariables;i++) uses[i]=0;
	for(i=0;i<_nodes->numNodes;i++) {
		if(nodes[i].token==T_SYMBOL && (var=LookupVariable(&nodes[i]))!=-1) uses[var]++;
	}
	for(i=vars->numVariables-1;i>=0;i--) {
		if(!uses[i]) {
			memmove(&vars->variables[i], &vars->variables[i+1], (vars->numVariables-(i+1))*sizeof(Variable));
			vars->numVariables--;
			parseMessageAtNode(&nodes[0], "Eliminating variable id %d", i);
			for(j=0;j<_nodes->numNodes;j++) {
				if(nodes[j].token==T_SYMBOL&&LookupVariable(&nodes[j])>i) nodes[j].value.intData--;
			}
		}
	}
	free(uses);
}

static int Combine(NodeList* _nodes) {
	int i, depth, j, k, matched=0;
	char op;
	Node* nodes=_nodes->nodes;
	for(i=5;i<_nodes->numNodes-4;i++) {
		if(nodes[i].token<T_ASSIGN_ADD||nodes[i].token>T_ASSIGN_DIV) continue;
		switch(nodes[i].token) {
		case T_ASSIGN_ADD: op='+'; break;
		case T_ASSIGN_SUB: op='-'; break;
		case T_ASSIGN_MUL: op='*'; break;
		case T_ASSIGN_DIV: op='/'; break;
		}
		assert(nodes[i+1].token==T_START_EXPRESSION);
		assert(nodes[i-2].token==T_START_STATEMENT);
		assert(nodes[i-1].token==T_SYMBOL);
		if(nodes[i-3].token!=T_END_STATEMENT) continue;
		depth=1;
		j=i-3;
		while(depth) {
			j--;
			if(nodes[j].token==T_START_STATEMENT) depth--;
			else if(nodes[j].token==T_END_STATEMENT) depth++;
		}
		assert(nodes[j].token==T_START_STATEMENT);
		if(nodes[j+1].token!=T_SYMBOL||nodes[j+2].token!=T_ASSIGN||nodes[j+1].value.intData!=nodes[i-1].value.intData||nodes[j+1].value.type!=nodes[i-1].value.type) continue;

		parseMessageAtNode(&nodes[i], "Combining assignments");
		matched=1;

		assert(nodes[i-4].token==T_END_EXPRESSION);
		depth=1;
		k=i+1;
		while(depth) {
			k++;
			if(nodes[k].token==T_START_EXPRESSION) depth++;
			else if(nodes[k].token==T_END_EXPRESSION) depth--;
		}
		assert(nodes[k].token==T_END_EXPRESSION);
		assert(nodes[k+1].token==T_END_STATEMENT);
		memmove(&nodes[i-4], &nodes[i+2], (k-i-1)*sizeof(Node));
		assert(nodes[k-6].token==T_END_EXPRESSION);
		nodes[k-6].token=op;
		nodes[k-5].token=T_END_EXPRESSION;
		nodes[k-4].token=T_END_STATEMENT;
		memmove(&nodes[k-3], &nodes[k+2], (_nodes->numNodes-k-2)*sizeof(Node));
		_nodes->numNodes-=6;
	}
	return matched;
}

static void OptimizeProcedure(Procedure* proc) {
	int found;
	int hasVars=proc->variables.variables!=0;
	Value *values;
	VarUsage *usage;

	if(hasVars) {
		values = (Value*)malloc(sizeof(Value)*proc->variables.numVariables);
		usage=(VarUsage*)malloc(proc->variables.numVariables*sizeof(VarUsage));
	}
	do {
		found=0;
		found=ConstantFolding(&proc->nodes);
		if(hasVars) {
			if (optimize>=3) { // constant propagation is known to break code
				found|=ConstantPropagation(&proc->nodes, proc->variables.variables, values,  proc->variables.numVariables, proc->numArgs);
			}
			found|=DeadStoreRemoval(&proc->nodes, &proc->variables, usage);
		}
		found|=DeadCodeRemoval(&proc->nodes);
		found|=Combine(&proc->nodes);
	} while(found);
	if(hasVars) {
		DeadVariableRemoval(&proc->nodes, &proc->variables, proc->numArgs); //use this twice so that VariableReuse has no completely dead variables to worry about
		if (optimize>=3) { // variable reuse is known to break code
			VariableReuse(&proc->nodes, &proc->variables, proc->numArgs, usage);
			DeadVariableRemoval(&proc->nodes, &proc->variables, proc->numArgs);
		}
		free(values);
		free(usage);
	}
}

int IsProtectedProc(const char* c) {
	// this should be the full list of procedures (copy-pasted directly from EXE)
	Protect("no_p_proc");
	Protect("start");
	Protect("spatial_p_proc");
	Protect("description_p_proc");
	Protect("desc_p_proc"); // Fallout 1
	Protect("pickup_p_proc");
	Protect("drop_p_proc");
	Protect("use_p_proc");
	Protect("use_obj_on_p_proc");
	Protect("use_skill_on_p_proc");
	Protect("talk_p_proc");
	Protect("critter_p_proc");
	Protect("combat_p_proc");
	Protect("damage_p_proc");
	Protect("map_enter_p_proc");
	Protect("map_exit_p_proc");
	Protect("create_p_proc");
	Protect("destroy_p_proc");
	Protect("look_at_p_proc");
	Protect("timed_event_p_proc");
	Protect("map_update_p_proc");
	Protect("push_p_proc");
	Protect("is_dropping_p_proc");
	Protect("combat_is_starting_p_proc");
	Protect("combat_is_over_p_proc");

	Protect("node998");
	Protect("node999");
	return 0;
}
static int __once = 0;
static void EliminateProcedure(Program *prog, int id) {
	int i, j;
	parseMessageAtNode(&prog->procedures.procedures[id].nodes.nodes[0], "Eliminating procedure %s", prog->namelist + prog->procedures.procedures[id].name);
	/*, remLen, srcOfs;
	long *namesLen;
	char *src, *dst;
	namesLen = (long*)prog->namelist;
	dst = prog->namelist + prog->procedures.procedures[id].name - 2;
	src = dst + 2 + *(short*)dst;
	srcOfs = src - prog->namelist + 2;
	remLen = src - dst;
	//parseMessageAtNode(&prog->procedures.procedures[id].nodes.nodes[0], "Eliminating procedure %s total=%d srcOfs=%d dstOfs=%d rem=%d move=%d", prog->namelist + prog->procedures.procedures[id].name, namesLen, srcOfs-prog->namelist, dstOfs-prog->namelist, remLen, prog->namelist+*namesLen-srcOfs);
	// remove from name list
	if (!__once) {
		memmove(dst, src, *namesLen - (src - prog->namelist) + 4);
		for (i = id; i < prog->procedures.numProcedures; i++) {
			if (prog->procedures.procedures[i].name >= srcOfs)
				prog->procedures.procedures[i].name -= remLen;
		}
		for (i = 0; i < prog->variables.numVariables; i++) {
			if (prog->variables.variables[i].name >= srcOfs)
				prog->variables.variables[i].name -= remLen;
		}
		for (i = 0; i < prog->externals.numVariables; i++) {
			if (prog->externals.variables[i].name >= srcOfs)
				prog->externals.variables[i].name -= remLen;
		}
		*namesLen -= remLen;
		__once = 1;
	}*/
	memmove(&prog->procedures.procedures[id], &prog->procedures.procedures[id+1], (prog->procedures.numProcedures-(id+1))*sizeof(Procedure));
	prog->procedures.numProcedures--;
	for(i=1;i<prog->procedures.numProcedures;i++) {
		NodeList* list=&prog->procedures.procedures[i].nodes;
		for(j=0;j<list->numNodes;j++) {
			if(list->nodes[j].token==T_SYMBOL&&(list->nodes[j].value.type&P_PROCEDURE)&&list->nodes[j].value.intData>=id) {
				//assert(list->nodes[j].value.intData!=id); //The procedure elimination can now cope with circular references, which would trigger this assert
				list->nodes[j].value.intData--;
			}
		}
		if(prog->procedures.procedures[i].type&P_CONDITIONAL) {
			list=&prog->procedures.procedures[i].condition;
			for(j=0;j<list->numNodes;j++) {
				if(list->nodes[j].token==T_SYMBOL&&(list->nodes[j].value.type&P_PROCEDURE)&&list->nodes[j].value.intData>=id) {
					//assert(list->nodes[j].value.intData!=id);
					list->nodes[j].value.intData--;
				}
			}
		}
	}
}

//This is the old method of procedure elimination; it wouldn't correctly remove circular references
/*static void UpdateProcedureReferences(Procedure* procs, int count) {
	int i,j;
	Node* node;
	for(i=1;i<count;i++) procs[i].uses=0;
	for(i=1;i<count;i++) {
		for(j=0;j<procs[i].nodes.numNodes;j++) {
			node=&procs[i].nodes.nodes[j];
			if(node->token==T_SYMBOL&&node->value.type==(P_PROCEDURE|P_LOCAL)) procs[node->value.intData].uses++;
		}
		if(procs[i].type&P_CONDITIONAL) {
			for(j=0;j<procs[i].condition.numNodes;j++) {
				node=&procs[i].condition.nodes[j];
				if(node->token==T_SYMBOL&&node->value.type==(P_PROCEDURE|P_LOCAL)) procs[node->value.intData].uses++;
			}
		}
	}
}

static void DecendUnusedProcedures(Program *prog) {
	int i, matched=1;
	while(matched) {
		matched=0;
		UpdateProcedureReferences(prog->procedures.procedures, prog->procedures.numProcedures);
		for(i=1;i<prog->procedures.numProcedures;i++) {
			if(prog->procedures.procedures[i].type&(P_TIMED|P_IMPORT|P_EXPORT|P_CONDITIONAL|P_CRITICAL)) continue;
			if(!prog->procedures.procedures[i].uses && !IsProtectedProc(prog->namelist + prog->procedures.procedures[i].name)) {
				EliminateProcedure(prog, i--);
				matched=1;
			}
		}
	}
}*/

static void UpdateProcedureReferences(Procedure* procs, int count) {
	int i,j,matched=1;
	Node* node;
	for(i=1;i<count;i++) {
		if(IsProtectedProc(currprogram->namelist + procs[i].name) || procs[i].type&(P_TIMED|P_CONDITIONAL|P_EXPORT|P_CRITICAL)) procs[i].uses=1;
		//else if(procs[i].type&P_IMPORT) procs[i].uses=2;
		else procs[i].uses=0;
	}
	while(matched) {
		matched=0;
		for(i=1;i<count;i++) {
			if(procs[i].uses!=1||procs[i].type&P_IMPORT) continue;
			procs[i].uses=2;
			for(j=0;j<procs[i].nodes.numNodes;j++) {
				node=&procs[i].nodes.nodes[j];
				if(node->token==T_SYMBOL&&node->value.type==(P_PROCEDURE|P_LOCAL)) {
					if(!procs[node->value.intData].uses) {
						matched=1;
						procs[node->value.intData].uses=1;
					}
				}
			}
			if(procs[i].type&P_CONDITIONAL) {
				for(j=0;j<procs[i].condition.numNodes;j++) {
					node=&procs[i].condition.nodes[j];
					if(node->token==T_SYMBOL&&node->value.type==(P_PROCEDURE|P_LOCAL)) {
						if(!procs[node->value.intData].uses) {
							matched=1;
							procs[node->value.intData].uses=1;
						}
					}
				}
			}
		}
	}
}

static void DecendUnusedProcedures(Program *prog) {
	int i;
	UpdateProcedureReferences(prog->procedures.procedures, prog->procedures.numProcedures);
	for(i=1;i<prog->procedures.numProcedures;i++) {
		if(!prog->procedures.procedures[i].uses) EliminateProcedure(prog, i--);
	}
}

static int ConstantPropagateGlobals(Program *prog) {
	Value* values=(Value*)malloc(prog->variables.numVariables*sizeof(Variable));
	int i, j, matched=0;
	//Make initial list of variables
	for(i=0;i<prog->variables.numVariables;i++) {
		values[i]=prog->variables.variables[i].value;
	}
	//Check for any that are assigned
	for(i=1;i<prog->procedures.numProcedures;i++) {
		for(j=1;j<prog->procedures.procedures[i].nodes.numNodes;j++) {
			if(prog->procedures.procedures[i].nodes.nodes[j].token>=T_ASSIGN&&prog->procedures.procedures[i].nodes.nodes[j].token<=T_ASSIGN_DIV) {
				Node* node=&prog->procedures.procedures[i].nodes.nodes[j-1];
				assert(node->token==T_SYMBOL);
				if(node->value.type==P_GLOBAL) values[node->value.intData].type=-1;
			}
		}
	}
	//Constant propagate any that are not
	for(i=1;i<prog->procedures.numProcedures;i++) {
		for(j=1;j<prog->procedures.procedures[i].nodes.numNodes;j++) {
			Node* node=&prog->procedures.procedures[i].nodes.nodes[j];
			if(node->token==T_SYMBOL && node->value.type==P_GLOBAL && values[node->value.intData].type!=-1) {
				if(node[1].token==T_START_EVENT) {
					parseWarningAtNode(node, "Global variable '%s' is called as a procedure butnever recieves a value", prog->namelist + prog->variables.variables[node->value.intData].name);
				} else {
					parseMessageAtNode(node, "Constant propagating global variable %s", prog->namelist + prog->variables.variables[node->value.intData].name);
					node->token=T_CONSTANT;
					node->value=values[node->value.intData];
					matched=1;
				}
			}
		}
	}
	free(values);
	return matched;
}

static void ShiftSymbolIntValues(Program *prog, int var, int matchType) {
	int i,j;
	for(i=1;i<prog->procedures.numProcedures;i++) {
		NodeList* list=&prog->procedures.procedures[i].nodes;
		for(j=0;j<list->numNodes;j++) {
			if(list->nodes[j].token==T_SYMBOL&&list->nodes[j].value.type==matchType&&list->nodes[j].value.intData>=var) {
				assert(list->nodes[j].value.intData!=var);
				list->nodes[j].value.intData--;
			}
		}
		if(prog->procedures.procedures[i].type&P_CONDITIONAL) {
			list=&prog->procedures.procedures[i].condition;
			for(j=0;j<list->numNodes;j++) {
				if(list->nodes[j].token==T_SYMBOL&&list->nodes[j].value.type==matchType&&list->nodes[j].value.intData>=var) {
					assert(list->nodes[j].value.intData!=var);
					list->nodes[j].value.intData--;
				}
			}
		}
	}
}

static void EliminateUnreferencedGlobals(Program *prog) {
	int i,j,var;
	Node* node;
	//count variable references
	for(i=0;i<prog->variables.numVariables;i++) prog->variables.variables[i].uses=0;
	for(i=0;i<prog->externals.numVariables;i++)
		prog->externals.variables[i].uses=(prog->externals.variables[i].type == V_EXPORT); // assume export variable is always used
	for(i=1;i<prog->procedures.numProcedures;i++) {
		for(j=0;j<prog->procedures.procedures[i].nodes.numNodes;j++) {
			node=&prog->procedures.procedures[i].nodes.nodes[j];
			if(node->token==T_SYMBOL) {
				if(node->value.type==P_GLOBAL) prog->variables.variables[node->value.intData].uses++;
				if(node->value.type==P_EXTERN) prog->externals.variables[node->value.intData].uses++;
			}
		}
		if(prog->procedures.procedures[i].type&P_CONDITIONAL) {
			for(j=0;j<prog->procedures.procedures[i].condition.numNodes;j++) {
				node=&prog->procedures.procedures[i].condition.nodes[j];
				if(node->token==T_SYMBOL) {
					if(node->value.type==P_GLOBAL) prog->variables.variables[node->value.intData].uses++;
					if(node->value.type==P_EXTERN) prog->externals.variables[node->value.intData].uses++;
				}
			}
		}
	}
	//remove any variables that aren't referenced or exported
	for(var=prog->variables.numVariables-1;var>=0;var--) {
		if(!prog->variables.variables[var].uses) {
			parseMessageAtNode(0, "Eliminating unused global variable %s", prog->namelist + prog->variables.variables[var].name);

			memmove(&prog->variables.variables[var], &prog->variables.variables[var+1], (prog->variables.numVariables-(var+1))*sizeof(Variable));
			prog->variables.numVariables--;
			ShiftSymbolIntValues(prog, var, P_GLOBAL);
		}
	}
	// remove unreferenced import variables
	for(var=prog->externals.numVariables-1;var>=0;var--) {
		if(!prog->externals.variables[var].uses) {
			parseMessageAtNode(0, "Eliminating unused import variable %s", prog->namelist + prog->externals.variables[var].name);

			memmove(&prog->externals.variables[var], &prog->externals.variables[var+1], (prog->externals.numVariables-(var+1))*sizeof(Variable));
			prog->externals.numVariables--;
			ShiftSymbolIntValues(prog, var, P_EXTERN);
		}
	}
}

static void CompressNamelist(Program *prog) {
	char* list=prog->namelist + 4, *endptr;
	int entries=0, *refs, *offsets, *transforms, i, j;
	Procedure* proc;

	while(*(unsigned short*)list != 0xffff) {
		entries++;
		list+=*(unsigned short*)list + 2;
	}
	endptr=list + 2;
	refs=(int*)calloc(1, entries*4);
	offsets=(int*)malloc(entries*4);
	transforms=(int*)malloc(entries*4);
	//first find the offsets
	list=prog->namelist +4;
	for(i=0;i<entries;i++) {
		offsets[i]=2 + (unsigned int)list - (unsigned int)prog->namelist;
		list+=*(unsigned short*)list + 2;
	}
	memcpy(transforms, offsets, entries*4);
	//Then check all variables, imports and procedures to see where in the namelist they point
	for(i=0;i<prog->externals.numVariables;i++) {
		for(j=0;j<entries;j++) {
			if(prog->externals.variables[i].name==offsets[j]) refs[j]|=1;
		}
	}
	for(i=0;i<prog->variables.numVariables;i++) {
		for(j=0;j<entries;j++) {
			if(prog->variables.variables[i].name==offsets[j]) refs[j]|=2;
		}
	}

	for(i=0;i<prog->procedures.numProcedures;i++) {
		proc = &prog->procedures.procedures[i];
		for(j=0;j<entries;j++) {
			if(proc->name==offsets[j]) refs[j]|=4;
		}
	}
	//For each string that isn't referenced, remove it
	for(i=entries-1;i>=0;i--) {
		if(!refs[i]) {
			int len=*(unsigned short*)(prog->namelist + offsets[i] - 2) + 2;
			parseMessageAtNode(0, "Removing unused string '%s' from program namespace", prog->namelist + offsets[i]);
			(*(unsigned int*)prog->namelist)-=len;
			memmove(prog->namelist + offsets[i] - 2, len + prog->namelist + offsets[i] - 2, endptr - (len + prog->namelist + offsets[i] - 2));
			transforms[i]=0x7fffffff;
			for(j=i+1;j<entries;j++) transforms[j]-=len;
		} else if(refs[i]==2&&optimize>=3) {
			int len=*(unsigned short*)(prog->namelist + offsets[i] - 2) + 2;
			if(len>4) {
				parseMessageAtNode(0, "Shortening non-visible string '%s' in program namespace", prog->namelist + offsets[i]);
				*(unsigned short*)(prog->namelist + offsets[i] - 2)=2;
				*(char*)(prog->namelist + offsets[i] + 0)='a';
				*(char*)(prog->namelist + offsets[i] + 1)=0;
				(*(unsigned int*)prog->namelist)-=len-4;
				memmove(prog->namelist + offsets[i] + 2, len + prog->namelist + offsets[i] - 2, endptr - (len + prog->namelist + offsets[i] - 2));
				for(j=i+1;j<entries;j++) transforms[j]-=len-4;
			}
		}
	}
	//And finally, update the name pointers of everything else
	for(i=0;i<prog->externals.numVariables;i++) {
		for(j=0;j<entries;j++) {
			if(prog->externals.variables[i].name==offsets[j]) {
				assert(transforms[j]!=0x7fffffff);
				prog->externals.variables[i].name=transforms[j];
				break;
			}
		}
	}
	for(i=0;i<prog->variables.numVariables;i++) {
		for(j=0;j<entries;j++) {
			if(prog->variables.variables[i].name==offsets[j]) {
				assert(transforms[j]!=0x7fffffff);
				prog->variables.variables[i].name=transforms[j];
				break;
			}
		}
	}
	for(i=0;i<prog->procedures.numProcedures;i++) {
		proc = &prog->procedures.procedures[i];
		for(j=0;j<entries;j++) {
			if(proc->name==offsets[j]) {
				assert(transforms[j]!=0x7fffffff);
				proc->name=transforms[j];
				break;
			}
		}
	}

	free(refs);
	free(offsets);
	free(transforms);
}

void optimizeTree(Program *prog) {
	int i, matched=1;
	currprogram=prog;
	if(optimize==1)
	{
		DecendUnusedProcedures(prog);
		EliminateUnreferencedGlobals(prog);
	}
	else
	{
		while(matched) {
			matched=0;
			DecendUnusedProcedures(prog);
			for(i=1;i<prog->procedures.numProcedures;i++) {
				if(prog->procedures.procedures[i].type&P_IMPORT) continue;
				OptimizeProcedure(&prog->procedures.procedures[i]);
			}
			DecendUnusedProcedures(prog);
			matched|=ConstantPropagateGlobals(prog);
			EliminateUnreferencedGlobals(prog);
		}
	}
	CompressNamelist(prog);
}

