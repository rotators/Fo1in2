/**
 *
 * Copyright (c) 2005-2009 Anchorite (TeamX), <anchorite2001@yandex.ru>
 * Copyright (c) 2014-2015 Nirran, phobos2077
 * Copyright (c) 2015 alexeevdv <mail@alexeevdv.ru>
 * Distributed under the GNU GPL v3. For full terms see the file license.txt
 *
 */

#ifndef NODE_H
#define NODE_H

// C++ standard includes

// int2ssl includes
#include "Namespace.h"
#include "Opcode.h"

// Third party includes

class CNode;
typedef std::vector<CNode> CNodeArray;
typedef std::vector<CNodeArray> CArrayOfNodeArray;

class CNode
{
public:
    enum Type {
        TYPE_NORMAL,
        TYPE_BEGIN_OF_BLOCK,
        TYPE_END_OF_BLOCK,
        TYPE_OMITTED_ARGUMENT,
        TYPE_BREAK,
        TYPE_CONTINUE,
        TYPE_FOR_LOOP,
        TYPE_CONDITIONAL_EXPRESSION
    };

public:
    CNode(Type type = TYPE_NORMAL);
    CNode(const CNode& node);
    virtual ~CNode();

public:
    CNode& operator = (const CNode& node);

public:
    void StoreTree(int nIndent, int nIndex);
    uint32_t  GetTopOffset();
    bool IsExpression() const;
    bool IsInfix() const;

public:
    uint32_t   m_ulOffset;
    COpcode m_Opcode;

    Type m_Type;
    CNodeArray m_Arguments;
};

// 'Begin' end 'End of block' 'End Else Begin' nodes
const CNode c_NodeBeginOfBlock(CNode::TYPE_BEGIN_OF_BLOCK);
const CNode c_NodeEndOfBlock(CNode::TYPE_END_OF_BLOCK);

#endif //NODE_H
