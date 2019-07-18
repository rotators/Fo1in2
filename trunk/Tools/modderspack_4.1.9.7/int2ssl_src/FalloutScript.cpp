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
#include <fstream>

// int2ssl includes
#include "FalloutScript.h"

// Third party includes

extern std::ifstream g_ifstream;
extern std::ofstream g_ofstream;

CFalloutScript::CFalloutScript()
{
}

CFalloutScript::~CFalloutScript()
{
}

void CFalloutScript::Serialize()
{

    std::cout << "  Read startup code" << std::endl;
    m_StartupCode.Serialize();

    std::cout << "  Read procedures table" << std::endl;
    m_ProcTable.Serialize();

    std::cout << "  Read namespace" << std::endl;
    m_Namespace.Serialize();

    std::cout << "  Read stringspace" << std::endl;
    m_Stringspace.Serialize();

    COpcode opcode;

    std::cout << "  Read tail of startup code" << std::endl;
    opcode.Expect(COpcode::O_SET_GLOBAL);

    // Sections with variable sizes
    uint32_t ullCurrentOffset = g_ifstream.tellg();

    // Load globals
    m_GlobalVar.clear();
    m_ExportedVar.clear();
    m_ExportedVarValue.clear();
    m_ExportedProc.clear();

    COpcodeArray HeaderTail;

    while(ullCurrentOffset < m_ProcTable.GetOffsetOfProcSection())
    {
        opcode.Serialize();
        ullCurrentOffset += opcode.GetSize();
        HeaderTail.push_back(opcode);
    }

    // Jump to 'start' procedure
    std::cout << "    Check \"Jump to \'start\' procedure\" / \"Jump to end of statup code\"" << std::endl;

    if (!HeaderTail.empty())
    {
        int32_t nIndexOfStart = GetIndexOfProc("start");
        uint32_t ulStartProcAddress = (nIndexOfStart != -1) ? m_ProcTable[nIndexOfStart].m_ulBodyOffset : 18;

        opcode = HeaderTail.back();

        if (opcode.GetOperator() == COpcode::O_JMP)
        {
            HeaderTail.pop_back();

            if (HeaderTail.empty())
            {
                printf("\n");
                printf("Warning: Omitted address of jump\n");
                printf("\n");
            }
            else
            {
                opcode = HeaderTail.back();

                if (opcode.GetOperator() == COpcode::O_INTOP)
                {
                    HeaderTail.pop_back();

                    if (opcode.GetArgument() != ulStartProcAddress)
                    {
                        printf("\n");
                        printf("Warning: Invalid jump address\n");
                        printf("\n");
                    }
                }
                else
                {
                    printf("\n");
                    printf("Warning: Invalid opcode for jump addres\n");
                    printf("\n");
                }
            }
        }
        else
        {
            printf("\n");
            printf("Warning: Omitted  \"Jump to \'start\' procedure\" / \"Jump to end of statup code\"\n");
            printf("\n");
        }
    }

    // # of argument to 'start' procedure
    printf("    Check \"# of argument to \'start\' procedure\"\n");

    std::string strNumOfArgsWarning = "Warning: Omitted  \"# of argument to \'start\' procedure\"\n";

    if (!HeaderTail.empty())
    {
        opcode = HeaderTail.back();

        if (opcode.GetOperator() == COpcode::O_CRITICAL_DONE)
        {
            HeaderTail.pop_back();

            if (!HeaderTail.empty())
            {
                opcode = HeaderTail.back();

                if (opcode.HasArgument())
                {
                    HeaderTail.pop_back();
                }
                else
                {
                    printf("\n");
                    printf("%s", strNumOfArgsWarning.c_str());
                    printf("\n");
                }
            }
            else
            {
                printf("\n");
                printf("%s", strNumOfArgsWarning.c_str());
                printf("\n");
            }
        }
        else
        {
            printf("\n");
            printf("Warning: Omitted expected opcode 0x8003. Opcode with # of arguments will be not analysed\n");
            printf("\n");
        }
    }
    else
    {
        printf("\n");
        printf("%s", strNumOfArgsWarning.c_str());
        printf("\n");
    }

    // Extract 'Export var' section
    printf("    Extract \"Export var\" section\n");
    ExtractCodeElements(HeaderTail, m_ExportedVar, COpcode::O_EXPORT_VAR, 2, "Error: Malformed \"Export var\" section\n", &CFalloutScript::CheckExportVarCode);

    // Extract 'Set exported var values' section
    printf("    Extract \"Set exported var values\" section\n");
    ExtractCodeElements(HeaderTail, m_ExportedVarValue, COpcode::O_STORE_EXTERNAL, 3, "Error: Malformed \"Set exported var values\" section\n", &CFalloutScript::CheckSetExportedVarValueCode);

    // Extract 'Export procedures' section
    printf("    Extract \"Export procedures\" section\n");
    ExtractCodeElements(HeaderTail, m_ExportedProc, COpcode::O_EXPORT_PROC, 3, "Error: Malformed \"Export procedures\" section\n", &CFalloutScript::CheckExportProcCode);

    // Global variables
    printf("    Extract \"Global variables\" section\n");

    for(uint32_t i = 0; i < HeaderTail.size(); i++)
    {
        uint16_t wGlobalVarOperator = HeaderTail[i].GetOperator();

        if ((wGlobalVarOperator != COpcode::O_STRINGOP) &&
            (wGlobalVarOperator != COpcode::O_FLOATOP) &&
            (wGlobalVarOperator != COpcode::O_INTOP)) 
        {
            printf("Error: Malformed \"Global variables\" section\n");
            throw std::exception();
        }

        m_GlobalVar.push_back(HeaderTail[i]);
    }

    // Procedures bodyes
    printf("  Read procedure\'s bodies\n");
    m_ProcBodies.clear();   // Destroy old data
    m_Conditions.clear();
    m_ProcBodies.resize(m_ProcTable.GetSize());
    m_Conditions.resize(m_ProcTable.GetSize());

    CNode node;

    for(uint32_t i = 0; i < m_ProcTable.GetSize(); i++)
    {
        printf("    Procedure: %d\r", i);
        uint32_t ulOffset = m_ProcTable[i].m_ulBodyOffset;
        uint32_t ulSize = m_ProcTable.GetSizeOfProc(i);

        g_ifstream.seekg(ulOffset, std::ios_base::beg);

        while(ulOffset < m_ProcTable[i].m_ulBodyOffset + ulSize)
        {
            node.m_Opcode.Serialize();
            node.m_ulOffset = ulOffset;
            m_ProcBodies[i].push_back(node);
            ulOffset += node.m_Opcode.GetSize();
        }
    }
}

void CFalloutScript::ExtractCodeElements(COpcodeArray& Source, COpcodeArray& Destination, uint16_t wDelimeter, uint32_t nSizeOfCodeItem, const char* lpszErrorMessage, bool (CFalloutScript::*pCheckFunc)(uint16_t, int32_t))
{
    uint32_t i = 0;

    for(; i < Source.size(); i++)
    {
        if (Source[i].GetOperator() == wDelimeter)
        {
            break;
        }
    }

    if (i < Source.size())
    {
        if (i < nSizeOfCodeItem - 1)
        {
            std::cout << lpszErrorMessage << std::endl;
            throw std::exception();
        }

        while(Source[i].GetOperator() == wDelimeter)
        {
            for(uint32_t j = 0; j < nSizeOfCodeItem - 1; j++)
            {
                if (!((this->*pCheckFunc)(Source[i - nSizeOfCodeItem + 1 + j].GetOperator(), j)))
                {
                    std::cout << lpszErrorMessage << std::endl;
                    throw std::exception();
                }
            }

            for(uint32_t j = 0; j < nSizeOfCodeItem - 1; j++)
            {
                int ofs = i - nSizeOfCodeItem + 1;
                Destination.push_back(Source[ofs]);
                Source.erase(Source.begin() + ofs);
            }

            Source.erase(Source.begin() + (i - nSizeOfCodeItem + 1)); // Delimeter

            if (i + 1 > Source.size())
            {
                break;
            }
        }
    }
}

bool CFalloutScript::CheckExportVarCode(uint16_t wOperator, int32_t nIndex)
{
    return (nIndex == 0) && (wOperator == COpcode::O_STRINGOP);
}

bool CFalloutScript::CheckSetExportedVarValueCode(uint16_t wOperator, int32_t nIndex)
{
    switch(nIndex)
    {
        case 0:
            return (wOperator == COpcode::O_STRINGOP) || 
                   (wOperator == COpcode::O_FLOATOP)  || 
                   (wOperator == COpcode::O_INTOP);
        case 1:
            return (wOperator == COpcode::O_STRINGOP);

        default:
            return false;
    }
}

bool CFalloutScript::CheckExportProcCode(uint16_t wOperator, int32_t nIndex)
{
    return ((nIndex == 0) || (nIndex == 1)) && (wOperator == COpcode::O_INTOP);
}

bool CFalloutScript::ArgNeedParens( const CNode& node, const CNode& argument, CFalloutScript::Assoc assoc)
{
    return (argument.IsInfix()
        && ((GetPriority(argument.m_Opcode.GetOperator()) != GetPriority(node.m_Opcode.GetOperator()))
            || (GetAssociation(node.m_Opcode.GetOperator()) != assoc)));
}

