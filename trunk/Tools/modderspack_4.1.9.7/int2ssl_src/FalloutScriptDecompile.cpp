/**
 *
 * Copyright (c) 2005-2009 Anchorite (TeamX), <anchorite2001@yandex.ru>
 * Copyright (c) 2014-2015 Nirran, phobos2077
 * Copyright (c) 2015 alexeevdv <mail@alexeevdv.ru>
 * Distributed under the GNU GPL v3. For full terms see the file license.txt
 *
 */

// C++ standard includes
#include <iostream>
#include <algorithm>
#include <stdio.h>

// int2ssl includes
#include "FalloutScript.h"
#include "ObjectAttributes.h"
#include "Utility.h"

// Third party includes

extern bool g_bIgnoreWrongNumOfArgs;
extern bool g_bInsOmittedArgsBackward;

void CFalloutScript::InitDefinitions()
{
    uint32_t ulNameOffset;
    int32_t nObjectIndex;
    std::string c_strGlobalVarTemplate("GVar%u");


    m_Definitions.RemoveAll();

    for(int32_t i = 0; i < m_Namespace.GetSize(); i++)
    {
        ulNameOffset = m_Namespace.GetOffsetByIndex(i);
        
        if ((nObjectIndex = GetIndexOfProc(ulNameOffset)) != -1)
        {
            m_Definitions.SetAt(ulNameOffset, CDefObject(CDefObject::OBJECT_PROCEDURE, 0, uint32_t(nObjectIndex)));
        }
        else if ((nObjectIndex = GetIndexOfExportedVariable(ulNameOffset)) != -1)
        {
            uint16_t wOpcode = m_ExportedVarValue[nObjectIndex].GetOperator();
            uint32_t ulValue = m_ExportedVarValue[nObjectIndex].GetArgument();

            m_Definitions.SetAt(ulNameOffset, CDefObject(CDefObject::OBJECT_VARIABLE, V_EXPORT | wOpcode, ulValue));
        }
    }

    m_GlobalVarsNames.resize(m_GlobalVar.size());

    for(uint32_t i = 0; i < m_GlobalVarsNames.size(); i++)
    {
        m_GlobalVarsNames[i] = format(c_strGlobalVarTemplate, i);
    }
}

void CFalloutScript::ProcessCode()
{
    printf("    Intial reducing\n");
    InitialReduce();

    printf("    Building execution tree\n");
    
    for(uint32_t i = 0; i < m_ProcTable.GetSize(); i++)
    {
        printf("        Procedure: %d\n", i);
        BuildTree(m_ProcBodies[i]);
    }

    printf("    Extracting and reducing conditions\n");
    
    for(uint32_t i = 0; i < m_ProcTable.GetSize(); i++)
    {
        if (m_ProcTable[i].m_ulType & P_CONDITIONAL)
        {
            ExtractAndReduceCondition(m_ProcBodies[i], m_Conditions[i], 0);
        }

        for(uint32_t j = 0; j < m_ProcBodies[i].size(); j++)
        {
            if (m_ProcBodies[i][j].m_Opcode.GetOperator() == COpcode::O_CALL_CONDITION)
            {
                CNodeArray Condition;
                CNode node = m_ProcBodies[i][j].m_Arguments[0];

                if (node.m_Opcode.GetOperator() != COpcode::O_INTOP)
                {
                    printf("Error: Invalid opcode for start address of condition\n");
                    throw std::exception();
                }

                uint32_t ulCondStartAddress = node.m_Opcode.GetArgument();

                do
                {
                    node = m_ProcBodies[i][j = NextNodeIndex(m_ProcBodies[i], j, -1)];
                } 
                while(node.m_ulOffset != ulCondStartAddress);

                j = NextNodeIndex(m_ProcBodies[i], j, -1);   // For O_JMP opcode

                ExtractAndReduceCondition(m_ProcBodies[i], Condition, j);
                m_ProcBodies[i][j].m_Arguments[0] = Condition[0];
            }
        }
    }


    printf("    Setting borders of blocks\n");

    for(uint32_t i = 0; i < m_ProcTable.GetSize(); i++)
    {
        printf("        Procedure: %d\r", i);
        SetBordersOfBlocks(m_ProcBodies[i]);
    }

    printf("    Renaming global variables\n");
    TryRenameGlobalVariables();

    printf("    Renaming imported variables\n");
    TryRenameImportedVariables();
}

int32_t CFalloutScript::GetIndexOfProc(const char* lpszName)
{
    int32_t nResult = -1;
    std::string strName(lpszName);
    std::string strTestName;

    std::transform(strName.begin(), strName.end(), strName.begin(), ::tolower);

    for(uint32_t i = 0; i < m_ProcTable.GetSize(); i++)
    {
        strTestName = m_Namespace[m_ProcTable[i].m_ulNameOffset];
        std::transform(strTestName.begin(), strTestName.end(), strTestName.begin(), ::tolower);

        if (strTestName == strName)
        {
            nResult = i;
            break;
        }
    }

    return nResult;
}

int32_t CFalloutScript::GetIndexOfProc(uint32_t ulNameOffset)
{
    int32_t nResult = -1;

    for(uint32_t i = 0; i < m_ProcTable.GetSize(); i++)
    {
        if (m_ProcTable[i].m_ulNameOffset == ulNameOffset)
        {
            nResult = i;
            break;
        }
    }

    return nResult;
}

int32_t CFalloutScript::GetIndexOfExportedVariable(uint32_t ulNameOffset)
{
    int32_t nResult = -1;

    for(uint32_t i = 0; i < m_ExportedVarValue.size(); i += 2)
    {
        if (m_ExportedVarValue[i + 1].GetArgument() == ulNameOffset)
        {
            nResult = i;
            break;
        }
    }

    return nResult;
}

void CFalloutScript::SetExternalVariable(uint32_t ulNameOffset)
{
    CDefObject defObject;

    if (!m_Definitions.Lookup(ulNameOffset, defObject))
    {
        m_Definitions.SetAt(ulNameOffset, CDefObject(CDefObject::OBJECT_VARIABLE, V_IMPORT));
    }
}

void CFalloutScript::TryRenameGlobalVariables()
{
    int32_t nNamesCount = m_Namespace.GetSize();
    int32_t nDefinitionsCount = m_Definitions.GetSize();
    int32_t nGlobalVarCount = m_GlobalVar.size();

    CDefObject defObject;
    int32_t nGlobalVarIndex = 0;

    if (nNamesCount - nDefinitionsCount == nGlobalVarCount)
    {
        for(int32_t i = 0; i < m_Namespace.GetSize(); i++)
        {
            if (!m_Definitions.Lookup(m_Namespace.GetOffsetByIndex(i), defObject))
            {
                defObject.m_ObjectType = CDefObject::OBJECT_VARIABLE;
                defObject.m_ulAttributes = V_GLOBAL | m_GlobalVar[nGlobalVarIndex].GetOperator();
                defObject.m_ulVarValue = m_GlobalVar[nGlobalVarIndex].GetArgument();

                m_Definitions.SetAt(m_Namespace.GetOffsetByIndex(i), defObject);
                m_GlobalVarsNames[nGlobalVarIndex] = m_Namespace.GetStringByIndex(i);
                nGlobalVarIndex++;
            }
        }
    }
}

void CFalloutScript::TryRenameImportedVariables()
{
    CDefObject defObject;
    uint32_t ulNameOffset;

    if (m_GlobalVar.size() == 0)
    {
        for(int32_t i = 0; i < m_Namespace.GetSize(); i++)
        {
            ulNameOffset = m_Namespace.GetOffsetByIndex(i);

            if (!m_Definitions.Lookup(ulNameOffset, defObject))
            {
                m_Definitions.SetAt(ulNameOffset, CDefObject(CDefObject::OBJECT_VARIABLE, V_IMPORT));
            }
        }
    }
}

int32_t CFalloutScript::NextNodeIndex( CNodeArray& NodeArray, int32_t nCurrentIndex, int32_t nStep)
{
    int32_t nResult = nCurrentIndex + nStep;

    if ((nResult < 0) || (nResult >= (int)NodeArray.size()))
    {
        printf("Error: Index of node out of range\n");
        throw std::exception();
    }

    return nResult;
}

bool CFalloutScript::CheckSequenceOfNodes(CNodeArray& NodeArray, int32_t nStartIndex, const uint16_t wSequence[], int32_t nSequenceLen)
{
    return RemoveSequenceOfNodes(NodeArray, nStartIndex, 0, wSequence, nSequenceLen);
}

bool CFalloutScript::RemoveSequenceOfNodes(CNodeArray& NodeArray, int32_t nStartIndex, int32_t nCount, const uint16_t wSequence[], int32_t nSequenceLen)
{
    int32_t nCurrentNodeIndex = nStartIndex - 1;

    for(int32_t i = 0; i < nSequenceLen; i++)
    {
        nCurrentNodeIndex = NextNodeIndex(NodeArray, nCurrentNodeIndex, 1);

        if (NodeArray[nCurrentNodeIndex].m_Opcode.GetOperator() != wSequence[nCurrentNodeIndex - nStartIndex])
        {
            return false;
        }
    }

    NodeArray.erase(NodeArray.begin() + nStartIndex, NodeArray.begin() + nStartIndex + nCount);

    return true;
}

void CFalloutScript::InitialReduce()
{
    static uint16_t awTailOfProc[3] = {
        COpcode::O_POP_TO_BASE,
        COpcode::O_POP_BASE,
        COpcode::O_POP_RETURN
    };

    static uint16_t awTailOfCriticalProc[4] = {
        COpcode::O_POP_TO_BASE,
        COpcode::O_POP_BASE,
        COpcode::O_CRITICAL_DONE,
        COpcode::O_POP_RETURN
    };

    static uint16_t awCheckArgCount[3] = {
        COpcode::O_DUP,
        COpcode::O_INTOP,
        COpcode::O_CHECK_ARG_COUNT
    };

    static uint16_t awShortCircuitAnd[5] = {
        COpcode::O_DUP,
        COpcode::O_INTOP,
        COpcode::O_SWAP,
        COpcode::O_IF,
        COpcode::O_POP
    };

    static uint16_t awShortCircuitOr[6] = {
        COpcode::O_DUP,
        COpcode::O_INTOP,
        COpcode::O_SWAP,
        COpcode::O_NOT,
        COpcode::O_IF,
        COpcode::O_POP
    };

    static uint16_t awStoreReturnAdress[2] = {
        COpcode::O_INTOP,
        COpcode::O_D_TO_A
    };

    static uint16_t awReturn[6] = {
        COpcode::O_D_TO_A,
        COpcode::O_SWAPA,
        COpcode::O_POP_TO_BASE,
        COpcode::O_POP_BASE,
        COpcode::O_A_TO_D,
        COpcode::O_POP_RETURN,
    };

    static uint16_t awCriticalReturn[7] = {
        COpcode::O_D_TO_A,
        COpcode::O_SWAPA,
        COpcode::O_POP_TO_BASE,
        COpcode::O_POP_BASE,
        COpcode::O_A_TO_D,
        COpcode::O_CRITICAL_DONE,
        COpcode::O_POP_RETURN,
    };

    uint16_t* pwCode;
    int32_t nCount;

    for(uint32_t i = 0 ; i < m_ProcBodies.size(); i++)
    {
        // Tail
        if (!m_ProcBodies[i].empty())
        {
            pwCode = (m_ProcTable[i].m_ulType & P_CRITICAL) ? awTailOfCriticalProc : awTailOfProc;
            nCount = (m_ProcTable[i].m_ulType & P_CRITICAL) ? 4 : 3;

            if (!RemoveSequenceOfNodes(m_ProcBodies[i], m_ProcBodies[i].size() - nCount, nCount, pwCode, nCount))
            {
                printf("Error: Invalid tail of procedure\'s body\n");
                throw std::exception();
            }
        }

        // Body
        for(uint32_t j = 0; j < m_ProcBodies[i].size(); j++)
        {
            switch(m_ProcBodies[i][j].m_Opcode.GetOperator())
            {
                case COpcode::O_DUP:
                    // 'Check procedure's arguments count' statement
                    if (!RemoveSequenceOfNodes(m_ProcBodies[i], j, 3, awCheckArgCount, 3))
                    {
                        // short circuit AND
                        uint16_t actualOperator = CheckSequenceOfNodes(m_ProcBodies[i], j, awShortCircuitAnd, 5)
                                        ? COpcode::O_AND 
                                        : (CheckSequenceOfNodes(m_ProcBodies[i], j, awShortCircuitOr, 6)
                                            ? COpcode::O_OR
                                            : 0);
                        if (actualOperator)
                        {
                            uint32_t k, skipOffset = m_ProcBodies[i][j+1].m_Opcode.GetArgument();

                            k = j - 1;
                            do
                            {
                                k = NextNodeIndex(m_ProcBodies[i], k, 1);
                            }
                            while (skipOffset > m_ProcBodies[i][k].m_ulOffset);

                            m_ProcBodies[i].insert(m_ProcBodies[i].begin() + k, m_ProcBodies[i][j]);
                            m_ProcBodies[i][k].m_Opcode.SetOperator(actualOperator); // place AND/OR here, so BuildTree() will treat it as a regular binary operator
                            m_ProcBodies[i][k].m_ulOffset = m_ProcBodies[i][k-1].m_ulOffset + COpcode::OPERATOR_SIZE; // adjust offset
                            m_ProcBodies[i].erase(m_ProcBodies[i].begin() + j, m_ProcBodies[i].begin() + j + (actualOperator == COpcode::O_AND ? 5 : 6)); // reduce
                        }
                        else
                        {
                            printf("Error: Unknown sequence of opcodes\n");
                            throw std::exception();
                        }
                    }

                    j--;
                    break;

                case COpcode::O_D_TO_A:
                    // 'return' and 'store return address' statements
                    pwCode = (m_ProcTable[i].m_ulType & P_CRITICAL) ? awCriticalReturn : awReturn;
                    nCount = (m_ProcTable[i].m_ulType & P_CRITICAL) ? 7 : 6;

                    if (!RemoveSequenceOfNodes(m_ProcBodies[i], j, nCount - 1, pwCode, nCount))
                    {
                        if (!RemoveSequenceOfNodes(m_ProcBodies[i], j - 1, 2, awStoreReturnAdress, 2))
                        {
                            printf("Error: Unknown sequence of opcodes\n");
                            throw std::exception();
                        }
                    }

                    j--;
                    break;
            }
        }
    }
}

// build tree for all nodes from nStartIndex to file offset ulEndOffset (not including)
uint32_t CFalloutScript::BuildTreeBranch(CNodeArray& NodeArray, uint32_t nStartIndex, uint32_t ulEndOffset)
{
    uint16_t wOperator;
    //uint32_t ulArgument;
    uint32_t nNumOfArgs;

    COpcode::COpcodeAttributes opcodeAttributes;
    uint32_t j;
    for (j = nStartIndex; (j < NodeArray.size() && NodeArray[j].m_ulOffset < ulEndOffset); j++)
    {
        wOperator = NodeArray[j].m_Opcode.GetOperator();
        //ulArgument = NodeArray[j].m_Opcode.GetArgument();

        opcodeAttributes = NodeArray[j].m_Opcode.GetAttributes();
        nNumOfArgs = int32_t(opcodeAttributes.m_ulNumArgs);

        switch(wOperator)
        {
            case COpcode::O_FETCH_EXTERNAL:
            case COpcode::O_STORE_EXTERNAL:
            {
                int32_t nExtVarNameNodeIndex = NextNodeIndex(NodeArray, j, -1);
                uint16_t wOpeartor = NodeArray[nExtVarNameNodeIndex].m_Opcode.GetOperator();
                uint32_t ulArgument = NodeArray[nExtVarNameNodeIndex].m_Opcode.GetArgument();

                if ((wOpeartor != COpcode::O_STRINGOP) && (wOpeartor != COpcode::O_INTOP))
                {
                    printf("Error: Invalid reference to external variable\n");
                    throw std::exception();
                }

                SetExternalVariable(ulArgument);
                break;
            }

            case COpcode::O_CALL:
            {
                int32_t nProcNumOfArgsNodeIndex = NextNodeIndex(NodeArray, j, -2);
                uint16_t wProcNumOfArgsOperator = NodeArray[nProcNumOfArgsNodeIndex].m_Opcode.GetOperator();
                uint32_t ulProcNumOfArgs = NodeArray[nProcNumOfArgsNodeIndex].m_Opcode.GetArgument();

                if (wProcNumOfArgsOperator != COpcode::O_INTOP)
                {
                    printf("Error: Invalid opcode for procedure\'s number of arguments\n");
                    throw std::exception();
                }

                nNumOfArgs = int32_t(ulProcNumOfArgs) + 2;
                break;
            }

            case COpcode::O_ADDREGION:
            {
                int32_t nAddRegionNumOfArgsNodeIndex = NextNodeIndex(NodeArray, j, -1);
                uint16_t wAddRegionNumOfArgsOperator = NodeArray[nAddRegionNumOfArgsNodeIndex].m_Opcode.GetOperator();
                uint32_t ulAddRegionNumOfArgs = NodeArray[nAddRegionNumOfArgsNodeIndex].m_Opcode.GetArgument();

                if (wAddRegionNumOfArgsOperator != COpcode::O_INTOP)
                {
                    printf("Error: Invalid opcode for addRegion number of arguments\n");
                    throw std::exception();
                }

                nNumOfArgs = int32_t(ulAddRegionNumOfArgs) + 1;
                break;
            }
        }

        // Check nodes
        uint32_t nOmittedArgStartIndex = nNumOfArgs;
        COpcode::COpcodeAttributes checkOpcodeAttributes;
        int32_t nNodeIndex = j;

        for(uint32_t k = 0; k < nNumOfArgs; k++)
        {
            nNodeIndex = NextNodeIndex(NodeArray, nNodeIndex, -1);
            if (!NodeArray[nNodeIndex].IsExpression())
            {
                if (g_bIgnoreWrongNumOfArgs)
                {
                    if (IsOmittetArgsAllowed(wOperator))
                    {
                        printf("Warning: Omitted expression found\n");
                        nOmittedArgStartIndex = k;
                        break;
                    }
                    else
                    {
                        printf("Error: Not enough arguments for %X\n", NodeArray[j].m_ulOffset);
                        throw std::exception();
                    }
                }
                else
                {
                    printf("Error: Expression required for %X\n", NodeArray[j].m_ulOffset);
                    throw std::exception();
                }
            }
        }

        // Move arguments
        for(uint32_t k = 0; k < nNumOfArgs; k++)
        {
            if (k < nOmittedArgStartIndex)
            {
                NodeArray[j].m_Arguments.insert(NodeArray[j].m_Arguments.begin() + 0, NodeArray[j-1]);
                NodeArray.erase(NodeArray.begin() + j - 1);
                j--;
            }
            else
            {
                if (g_bInsOmittedArgsBackward)
                {
                    NodeArray[j].m_Arguments.push_back(CNode(CNode::TYPE_OMITTED_ARGUMENT));
                }
                else
                {
                    NodeArray[j].m_Arguments.insert(NodeArray[j].m_Arguments.begin() + 0, CNode(CNode::TYPE_OMITTED_ARGUMENT));
                }
            }
        }

        if (wOperator == COpcode::O_IF)
        {
            // process possible conditional expression - this may be either normal IF statement or (x IF y ELSE z) expression
            uint32_t ulElseOffset = NodeArray[j].m_Arguments[0].m_Opcode.GetArgument();
            int32_t ulElseIndex, ulSkipIndex = -1;
            ulElseIndex = BuildTreeBranch(NodeArray, j + 1, ulElseOffset); // true branch
            if (NodeArray[ulElseIndex - 1].m_Opcode.GetOperator() == COpcode::O_JMP)
            {
                uint32_t ulSkipOffset = NodeArray[ulElseIndex - 1].m_Opcode.GetArgument();
                if (ulSkipOffset > NodeArray[j].m_ulOffset)
                {
                    ulSkipIndex = BuildTreeBranch(NodeArray, ulElseIndex, ulSkipOffset); // false branch
                    if (NodeArray[ulElseIndex - 2].IsExpression() && NodeArray[ulSkipIndex - 1].IsExpression())
                    { // conditional expression
                        NodeArray[j].m_Type = CNode::TYPE_CONDITIONAL_EXPRESSION;
                        NodeArray[j].m_Arguments.erase(NodeArray[j].m_Arguments.begin() + 0); // address not needed anymore
                        NodeArray[j].m_Arguments.insert(NodeArray[j].m_Arguments.begin() + 0, NodeArray[ulElseIndex - 2]); // true expression
                        NodeArray[j].m_Arguments.insert(NodeArray[j].m_Arguments.begin() + 2, NodeArray[ulSkipIndex - 1]); // false expression
                        NodeArray.erase(NodeArray.begin() + j + 1, NodeArray.begin() + j + 1 + ulSkipIndex - j - 1);
                        continue;
                    }
                }
            }
            j = ((ulSkipIndex != -1) ? ulSkipIndex : ulElseIndex) - 1; // skip already built
        }
    }

    return j;
}

void CFalloutScript::BuildTree(CNodeArray& NodeArray)
{
    if (NodeArray.size() > 0)
    {
        BuildTreeBranch(NodeArray, 0, NodeArray[NodeArray.size() - 1].m_ulOffset + COpcode::OPERATOR_SIZE);
    }
}

void CFalloutScript::ExtractAndReduceCondition(CNodeArray& Source, CNodeArray& Destination, int32_t nStartIndex)
{
    // Extract
    CNode node;
    int32_t nNodeIndex;;

    node = Source[nNodeIndex = NextNodeIndex(Source, nStartIndex - 1, 1)];

    if (node.m_Opcode.GetOperator() != COpcode::O_JMP)
    {
        printf("Error: Invalid startup of condition\n");
        throw std::exception();
    }

    CNode nodeJumpAddress = node.m_Arguments[0];

    if (nodeJumpAddress.m_Opcode.GetOperator() != COpcode::O_INTOP)
    {
        printf("Error: Invalid startup of condition\n");
        throw std::exception();
    }

    uint32_t ulJumpOffset = node.m_Arguments[0].m_Opcode.GetArgument();

    do
    {
        node = Source[nNodeIndex = NextNodeIndex(Source, nNodeIndex, 1)];
    }
    while(node.m_ulOffset < ulJumpOffset);

    Destination.resize(nNodeIndex - nStartIndex);

    for(int32_t j = 0; j < nNodeIndex - nStartIndex; j++)
    {
        Destination[j] = Source[nStartIndex + j];
    }

    // Reduce
    static uint16_t awStartupOfCondition[2] = {
        COpcode::O_JMP,
        COpcode::O_CRITICAL_START
    };

    static uint16_t awCleanupOfCondition[2] = {
        COpcode::O_CRITICAL_DONE,
        COpcode::O_STOP_PROG
    };

    // Startup
    if (!RemoveSequenceOfNodes(Destination, 0, 2, awStartupOfCondition, 2))
    {
        printf("Error: Invalid startup of condition\n");
        throw std::exception();
    }

    // Cleanup
    if (!RemoveSequenceOfNodes(Destination, Destination.size() - 2, 2, awCleanupOfCondition, 2))
    {
        printf("Error: Invalid cleanup of condition\n");
        throw std::exception();
    }

    // Check condition
    if (Destination.size() != 1)
    {
        printf("Error: Invalid condition. Only one expression allowed\n");
        throw std::exception();
    }
    else
    {
        if (Destination[0].m_Opcode.GetAttributes().m_Type != COpcode::COpcodeAttributes::TYPE_EXPRESSION)
        {
            printf("Error: Invalid condition. Expression required\n");
            throw std::exception();
        }
    }

    // Remove from source
    Source.erase(Source.begin() + nStartIndex, Source.begin() + nStartIndex + nNodeIndex - nStartIndex);
}

void CFalloutScript::SetBordersOfBlocks(CNodeArray& NodeArray)
{
    if (NodeArray.empty())
    {
        return;
    }

    uint32_t ulOffset;

    // Start of procedure
    if (NodeArray[0].m_Opcode.GetOperator() == COpcode::O_PUSH_BASE)
    {
        ulOffset = NodeArray[0].m_ulOffset;
        NodeArray[0] = c_NodeBeginOfBlock;
        NodeArray[0].m_ulOffset = ulOffset;
    }

    // End of procedure
    int32_t nLastNodeIndex = NodeArray.size() ? NodeArray.size() - 1 : 0;

    if ((NodeArray[nLastNodeIndex].m_Opcode.GetOperator() == COpcode::O_POP_RETURN) &&
        (NodeArray[nLastNodeIndex].m_Opcode.GetArgument() == 0) &&
        (NodeArray[nLastNodeIndex].m_Arguments[0].m_Opcode.GetOperator() == COpcode::O_INTOP))
    {
        ulOffset = NodeArray[nLastNodeIndex].m_ulOffset;
        NodeArray[nLastNodeIndex] = c_NodeEndOfBlock;
        NodeArray[nLastNodeIndex].m_ulOffset = ulOffset;
    }
    else
    {
        ulOffset = NodeArray[nLastNodeIndex].m_ulOffset;
        NodeArray.insert(NodeArray.begin() + nLastNodeIndex + 1, CNode(c_NodeEndOfBlock));
        NodeArray[nLastNodeIndex].m_ulOffset = ulOffset;
    }
    
    // Body
    //CNode node;

    for(uint32_t i = 0; i < NodeArray.size(); i++)
    {
        switch(NodeArray[i].m_Opcode.GetOperator())
        {
            case COpcode::O_WHILE:
            {
                CNode node = NodeArray[i].m_Arguments[0];
                uint32_t loopOffset = NodeArray[i].m_Arguments[1].GetTopOffset();

                if (node.m_Opcode.GetOperator() != COpcode::O_INTOP)
                {
                    printf("Error: Invalid opcode for jump-address\n");
                    throw std::exception();
                }

                NodeArray.insert(NodeArray.begin() + i + 1, CNode(c_NodeBeginOfBlock));
                NodeArray[i + 1].m_ulOffset = NodeArray[i].m_ulOffset;
                ulOffset = node.m_Opcode.GetArgument();

                int32_t nNodeIndex = i + 1;
                std::vector<int32_t> jumps;
                do
                {
                    node = NodeArray[nNodeIndex = NextNodeIndex(NodeArray, nNodeIndex, 1)];
                    if (node.m_Opcode.GetOperator() == COpcode::O_JMP && node.m_Type == CNode::TYPE_NORMAL && node.m_Arguments.size() > 0)
                    {
                        uint32_t ofs = node.m_Arguments[0].m_Opcode.GetArgument();
                        if (ofs == ulOffset)
                        {
                            NodeArray[nNodeIndex].m_Type = CNode::TYPE_BREAK;
                        }
                        else if (ofs == loopOffset)
                        {
                            NodeArray[nNodeIndex].m_Type = CNode::TYPE_CONTINUE; // continue in "while" loop
                        }
                        else
                        {
                            jumps.push_back(nNodeIndex);
                        }
                    }
                }
                while(node.m_ulOffset < ulOffset);

                bool isForLoop = false;
                if (NodeArray[nNodeIndex - 2].m_Arguments.size() > 0 && i > 0)
                { // *might* be a "for" loop
                    loopOffset = NodeArray[nNodeIndex - 2].GetTopOffset();
                    for (uint32_t j = 0; j < jumps.size(); j++)
                    {
                        if (NodeArray[jumps[j]].m_Arguments[0].m_Opcode.GetArgument() == loopOffset)
                        { // jump points to the last statement in loop
                            NodeArray[jumps[j]].m_Type = CNode::TYPE_CONTINUE; // it's a continue
                            isForLoop = true; // in a "for" loop
                        }
                    }
                }

                NodeArray.insert(NodeArray.begin() + nNodeIndex, CNode(c_NodeEndOfBlock));
                NodeArray[nNodeIndex].m_ulOffset = NodeArray[nNodeIndex + 1].m_ulOffset;

                node = NodeArray[nNodeIndex - 1];

                if (node.m_Opcode.GetOperator() != COpcode::O_JMP)
                {
                    printf("Error: Invalid tail of \'while\' statement\n");
                    throw std::exception();
                }

                if (node.m_Arguments[0].m_Opcode.GetOperator() != COpcode::O_INTOP)
                {
                    printf("Error: Invalid opcode for jump-address\n");
                    throw std::exception();
                }

                if (isForLoop)
                {
                    NodeArray[i].m_Type = CNode::TYPE_FOR_LOOP;
                    NodeArray[i].m_Arguments[0] = NodeArray[i - 1]; // "for" initializer
                    NodeArray[i].m_Arguments.push_back(NodeArray[nNodeIndex - 2]); // "for" increment
                    NodeArray.erase(NodeArray.begin() + i - 1); // eat statement before "while"
                    NodeArray.erase(NodeArray.begin() + nNodeIndex - 3, NodeArray.begin() + nNodeIndex - 3 + 2); // eat last statement in loop along with jmp
                }
                else
                {
                    NodeArray.erase(NodeArray.begin() + nNodeIndex - 1);
                    NodeArray[i].m_Arguments.erase(NodeArray[i].m_Arguments.begin() + 0);
                }
            }
            break;

            case COpcode::O_IF:
            {
                if (NodeArray[i].m_Type == CNode::TYPE_CONDITIONAL_EXPRESSION)
                {
                    printf("Error: Conditional expression left in stack\n");
                    throw std::exception();
                }
                CNode node = NodeArray[i].m_Arguments[0];

                if (node.m_Opcode.GetOperator() != COpcode::O_INTOP)
                {
                    printf("Error: Invalid opcode for jump-address\n");
                    throw std::exception();
                }

                NodeArray.insert(NodeArray.begin() + i + 1, CNode(c_NodeBeginOfBlock));
                NodeArray[i + 1].m_ulOffset = NodeArray[i + 2].m_ulOffset;
                ulOffset = node.m_Opcode.GetArgument(); // offset for jump
                    
                int32_t nNodeIndex = i + 1;

                do
                {
                    node = NodeArray[nNodeIndex = NextNodeIndex(NodeArray, nNodeIndex, 1)];
                }
                while(node.m_ulOffset < ulOffset);

                NodeArray.insert(NodeArray.begin() + nNodeIndex, CNode(c_NodeEndOfBlock));
                NodeArray[nNodeIndex].m_ulOffset = NodeArray[nNodeIndex + 1].m_ulOffset;

                node = NodeArray[nNodeIndex - 1];

                if (node.m_Opcode.GetOperator() == COpcode::O_JMP && node.m_Type != CNode::TYPE_BREAK && node.m_Type != CNode::TYPE_CONTINUE)
                { // else block
                    if (node.m_Arguments[0].m_Opcode.GetOperator() != COpcode::O_INTOP)
                    {
                        printf("Error: Invalid opcode for jump-address\n");
                        throw std::exception();
                    }
                    //uint32_t jumpPastElseOffset =
                    ulOffset = node.m_Arguments[0].m_Opcode.GetArgument();
                    //printf("(else) goto %x > %x", ulOffset, node.m_ulOffset);
                    if (ulOffset > node.m_ulOffset)
                    {
                        NodeArray.erase(NodeArray.begin() + nNodeIndex - 1); // remove jump
                        NodeArray.insert(NodeArray.begin() + nNodeIndex, CNode(c_NodeBeginOfBlock));
                        NodeArray[nNodeIndex].m_ulOffset = NodeArray[nNodeIndex + 1].m_ulOffset;

                        CNode Bnode = NodeArray[nNodeIndex - 1];
                        //CNode Cnode = NodeArray[nNodeIndex + 1];
                        if ((Bnode.m_Type == CNode::TYPE_END_OF_BLOCK)/* &&
                                (Cnode.m_Opcode.GetOperator() != COpcode::O_IF)*/)
                        {
                            do
                            {
                                node = NodeArray[nNodeIndex = NextNodeIndex(NodeArray, nNodeIndex, 1)];
                            }
                            while(node.m_ulOffset < ulOffset);
                            NodeArray.insert(NodeArray.begin() + nNodeIndex, CNode(c_NodeEndOfBlock));
                            NodeArray[nNodeIndex].m_ulOffset = NodeArray[nNodeIndex + 1].m_ulOffset;
                        }
                    }
                }
            }
            NodeArray[i].m_Arguments.erase(NodeArray[i].m_Arguments.begin() + 0);
            i++;

            break;
        }
    }
}

void CFalloutScript::ReduceConditionalExpressions(CNodeArray& NodeArray)
{
    /*
    if (NodeArray.IsEmpty())
    {
        return;
    }
    CNode node;

    for (int32_t i = 0; i < NodeArray.GetSize(); i++)
    {
        if (NodeArray[i].m_Opcode.GetOperator() == COpcode::O_IF)
        {
            if (ReduceExpressionBlock(NodeArray, i+1))
            {

            }
        }
    }
    */
}

bool CFalloutScript::IsOmittetArgsAllowed(uint16_t wOpcode)
{
    if (((wOpcode >= COpcode::O_END_CORE) && (wOpcode < COpcode::O_END_OP)) ||
        (wOpcode == COpcode::O_POP_RETURN))
    {
        return true;
    }
    else
    {
        return false;
    }
}
