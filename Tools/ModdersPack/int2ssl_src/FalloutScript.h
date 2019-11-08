/**
 *
 * Copyright (c) 2005-2009 Anchorite (TeamX), <anchorite2001@yandex.ru>
 * Copyright (c) 2014-2015 Nirran, phobos2077
 * Copyright (c) 2015 alexeevdv <mail@alexeevdv.ru>
 * Distributed under the GNU GPL v3. For full terms see the file license.txt
 *
 */

#ifndef FALLOUT_SCRIPT_H
#define FALLOUT_SCRIPT_H

// C++ standard includes
#include <vector>

// int2ssl includes
#include "StartupCode.h"
#include "ProcTable.h"
#include "Namespace.h"
#include "Node.h"

// Third party includes

class CFalloutScript
{
public:
    CFalloutScript();
    virtual ~CFalloutScript();

public:
    virtual void Serialize();

    void Dump();

    void InitDefinitions();
    void ProcessCode();

    void StoreSource();
    void StoreTree();

private:
    enum Assoc {
        NON_ASSOC,
        LEFT_ASSOC,
        RIGHT_ASSOC,
    };

private:
    void ExtractCodeElements(COpcodeArray& Source, COpcodeArray& Destination, uint16_t wDelimeter, uint32_t nSizeOfCodeItem, const char* lpszErrorMessage, bool (CFalloutScript::*pCheckFunc)(uint16_t, int32_t));
    bool CheckExportVarCode(uint16_t wOperator, int32_t nIndex);
    bool CheckSetExportedVarValueCode(uint16_t wOperator, int32_t nIndex);
    bool CheckExportProcCode(uint16_t wOperator, int32_t nIndex);

    int32_t GetIndexOfProc(const char* lpszName);
    int32_t GetIndexOfProc(uint32_t ulNameOffset);
    int32_t GetIndexOfExportedVariable(uint32_t ulNameOffset);

    void SetExternalVariable(uint32_t ulNameOffset);
    void TryRenameGlobalVariables();
    void TryRenameImportedVariables();

    int32_t NextNodeIndex( CNodeArray& NodeArray, int32_t nCurrentIndex, int32_t nSteep);
    bool CheckSequenceOfNodes(CNodeArray& NodeArray, int32_t nStartIndex, const uint16_t wSequence[], int32_t nSequenceLen);
    bool RemoveSequenceOfNodes(CNodeArray& NodeArray,int32_t nStartIndex, int32_t nCount, const uint16_t wSequence[], int32_t nSequenceLen);

    void InitialReduce();
    void BuildTree(CNodeArray& NodeArray);
    void ExtractAndReduceCondition(CNodeArray& Source, CNodeArray& Destination, int32_t nStartIndex);
    void SetBordersOfBlocks(CNodeArray& NodeArray);
    uint32_t BuildTreeBranch(CNodeArray& NodeArray, uint32_t nStartIndex, uint32_t ulEndOffset);
    void ReduceConditionalExpressions(CNodeArray& NodeArray);
    bool IsOmittetArgsAllowed(uint16_t wOpcode);

    void StoreDefinitions();
    void StoreDeclarations();

    std::string GetSource( CNode& node, bool bLabel, uint32_t ulNumArgs);
    std::string GetSource( CNode& node, bool bLabel, uint32_t ulNumArgs, uint32_t aulProcArg[], uint32_t ulProcArgCount);
    bool ArgNeedParens(const CNode& node, const CNode& argument, CFalloutScript::Assoc assoc = CFalloutScript::NON_ASSOC);
    std::string GetIndentString(int32_t nLevel);

    int GetPriority(uint16_t wOperator);
    Assoc GetAssociation(uint16_t wOperator);

private:
    
    class CDefObject
    {
    public:
        enum ObjectType {
            OBJECT_VARIABLE,
            OBJECT_PROCEDURE
        };

    public:
        CDefObject(ObjectType type = OBJECT_VARIABLE, uint32_t ulAttributes = 0, uint32_t ulObjectData = 0);

    public:
        ObjectType m_ObjectType;
        uint32_t m_ulAttributes;

        union {
            uint32_t m_ulVarValue;
            uint32_t m_ulProcIndex;
        };
    };

private:
    // CMapuint32_tToDefObject
    typedef CMap<uint32_t, uint32_t, CDefObject, CDefObject&> CMapuint32_tToDefObject;

    CStartupCode m_StartupCode;
    CProcTable   m_ProcTable;
    CNamespace   m_Namespace;
    CNamespace   m_Stringspace;

    COpcodeArray m_GlobalVar;
    COpcodeArray m_ExportedVar;
    COpcodeArray m_ExportedVarValue;
    COpcodeArray m_ExportedProc;

    CArrayOfNodeArray m_ProcBodies;
    CArrayOfNodeArray m_Conditions;

    CMapuint32_tToDefObject m_Definitions;
    std::vector<std::string> m_GlobalVarsNames;
};

#endif //FALLOUT_SCRIPT_H
