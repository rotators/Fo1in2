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
#include "ObjectAttributes.h"
#include "Utility.h"

// Third party includes

extern std::string g_strIndentFill;
extern std::ofstream g_ifstream;
extern std::ofstream g_ofstream;

void CFalloutScript::StoreTree()
{
    std::string strOutLine;

    g_ofstream << "============== Procedures ==================" << std::endl;
    g_ofstream << std::endl;

    for(uint32_t nIndexOfProc = 0; nIndexOfProc < m_ProcTable.GetSize(); nIndexOfProc++)
    {
        g_ofstream << format("%d: %s (0x%08x)", nIndexOfProc, m_Namespace[m_ProcTable[nIndexOfProc].m_ulNameOffset].c_str(), m_ProcTable[nIndexOfProc].m_ulBodyOffset) << std::endl;
        g_ofstream << "===============================" << std::endl;

        if (m_ProcTable[nIndexOfProc].m_ulType & P_CONDITIONAL)
        {
            g_ofstream << "Condition" << std::endl;
            g_ofstream << "===============================" << std::endl;

            for(uint32_t i = 0; i < m_Conditions[nIndexOfProc].size(); i++)
            {
                g_ofstream << format("0x%08X: ", m_Conditions[nIndexOfProc][i].m_ulOffset) << std::endl;
                m_Conditions[nIndexOfProc][i].StoreTree(0, 0);
            }

            g_ofstream << std::endl;
            g_ofstream << "Body" << std::endl;
            g_ofstream << "===============================" << std::endl;
        }

        for(uint32_t i = 0; i < m_ProcBodies[nIndexOfProc].size(); i++)
        {
            g_ofstream << format("0x%08X: ", m_ProcBodies[nIndexOfProc][i].m_ulOffset) << std::endl;
            m_ProcBodies[nIndexOfProc][i].StoreTree(0, 0);
        }

        g_ofstream << std::endl;
    }

}

void CFalloutScript::StoreSource()
{
    StoreDefinitions();
    g_ofstream << std::endl;
    g_ofstream << std::endl;
    StoreDeclarations();
}

void CFalloutScript::StoreDefinitions()
{
    std::string c_strBogusProcedureName("..............");
    std::string c_strArgumentTemplate("arg%u");

    printf("    Storing definitions\n");

    // Unnamed global variables
    int32_t nNamesCount = m_Namespace.GetSize();
    int32_t nDefinitionsCount = m_Definitions.GetSize();
    std::string strDefinition;
    uint32_t ulVarValue;

    if (nNamesCount != nDefinitionsCount)
    {
        g_ofstream << "/*******************************************************" << std::endl
                   << "*      Some unreferenced imported varables found.      *" << std::endl
                   << "*      Because of it it is impossible to specify       *" << std::endl
                   << "*      the real names of global variables.             *" << std::endl
                   << "*******************************************************/" << std::endl
                   << std::endl;

        for(uint32_t i = 0; i < m_GlobalVar.size(); i++)
        {
            ulVarValue = m_GlobalVar[i].GetArgument();
            strDefinition = "variable ";
            strDefinition += m_GlobalVarsNames[i];

            switch(m_GlobalVar[i].GetOperator())
            {
                case COpcode::O_STRINGOP:
                    strDefinition = format(strDefinition + " := \"%s\"", escape_str(m_Stringspace[ulVarValue]).c_str());
                    break;

                case COpcode::O_FLOATOP:
                    strDefinition = format(strDefinition + " := %.5f", *((float*)(&ulVarValue)));
                    break;

                case COpcode::O_INTOP:
                    if (ulVarValue != 0)
                    {
                        strDefinition = format(strDefinition + " := %d", (long)ulVarValue);
                    }
                    break;
            }

            strDefinition += ";";

            if ((m_GlobalVar[i].GetOperator() == COpcode::O_INTOP) && (ulVarValue & 0x80000000))
            {
                strDefinition = format(strDefinition + " /* (%d) */", ulVarValue);
            }

            g_ofstream << strDefinition << std::endl;
        }

        g_ofstream << std::endl;
    }


    // Named objects
    uint32_t ulNameOffset;
    CDefObject defObject;

    enum OutDefObject {
        OUT_NOTHING,
        OUT_UNKNOWN_VARIABLE,
        OUT_GLOBAL_VARIABLE,
        OUT_EXPORTED_VARIABLE,
        OUT_IMPORTED_VARIABLE,
        OUT_PROCEDURE,
        OUT_EXPORTED_PROCEDURE,
        OUT_IMPORTED_PROCEDURE
    };

    OutDefObject lastOut = OUT_NOTHING;
    OutDefObject currentOut = OUT_NOTHING;
    CProcDescriptor procDescriptor;

    for(int32_t i = 0; i < m_Namespace.GetSize(); i++)
    {
        ulNameOffset = m_Namespace.GetOffsetByIndex(i);

        if (i == 0)
        {
            if (m_Namespace[ulNameOffset] == c_strBogusProcedureName)
            {
                continue;
            }
            else
            {
                std::cout << "Warning: Bogus procedure with name "
                          << c_strBogusProcedureName
                          << " not found at expected location" << std::endl;
            }
        }

        if (m_Definitions.Lookup(ulNameOffset, defObject))
        {
            strDefinition = "";

            switch(defObject.m_ObjectType)
            {
                case CDefObject::OBJECT_PROCEDURE:
                    procDescriptor = m_ProcTable[defObject.m_ulProcIndex];

                    if (procDescriptor.m_ulType & P_IMPORT)
                    {
                        strDefinition = "import ";
                        currentOut = OUT_IMPORTED_PROCEDURE;
                    }
                    else if (procDescriptor.m_ulType & P_EXPORT)
                    {
                        strDefinition = "export ";
                        currentOut = OUT_EXPORTED_PROCEDURE;
                    }
                    else
                    {
                        currentOut = OUT_PROCEDURE;
                    }

                    strDefinition += "procedure ";
                    strDefinition += m_Namespace[ulNameOffset];

                    if (procDescriptor.m_ulNumArgs != 0)
                    {
                        strDefinition += "(";

                        for(uint32_t i = 0; i < procDescriptor.m_ulNumArgs; i++)
                        {
                            if (i == 0)
                            {
                                strDefinition = format(strDefinition + "variable " + c_strArgumentTemplate.c_str(), i);
                            }
                            else
                            {
                                strDefinition = format(strDefinition + ", variable " + c_strArgumentTemplate.c_str(), i);
                            }
                        }

                        strDefinition += ")";
                    }

                    strDefinition += ";";

                    if (procDescriptor.m_ulType & P_NOTIMPLEMENTED)
                    {
                        strDefinition += " /* Prodedure defined, but not implemented */";
                    }

                    break;

                case CDefObject::OBJECT_VARIABLE:
                    if (defObject.m_ulAttributes & V_IMPORT)
                    {
                        strDefinition = "import ";
                        currentOut = OUT_IMPORTED_VARIABLE;
                    }
                    else if (defObject.m_ulAttributes & V_EXPORT)
                    {
                        strDefinition = "export ";
                        currentOut = OUT_EXPORTED_VARIABLE;
                    }
                    else 
                    {
                        currentOut = OUT_GLOBAL_VARIABLE;
                    }

                    strDefinition += "variable ";
                    strDefinition += m_Namespace[ulNameOffset];

                    if (!(defObject.m_ulAttributes & V_IMPORT))
                    {
                        switch(defObject.m_ulAttributes & 0xFFFF)
                        {
                            case COpcode::O_STRINGOP:
                                strDefinition = format(strDefinition + " := \"%s\"", escape_str(m_Stringspace[defObject.m_ulVarValue]).c_str());
                                break;

                            case COpcode::O_FLOATOP:
                                strDefinition = format(strDefinition + " := %.5f", *((float*)(&defObject.m_ulVarValue)));
                                break;

                            case COpcode::O_INTOP:
                                if (defObject.m_ulVarValue != 0)
                                {
                                    strDefinition = format(strDefinition + " := %d", (long)defObject.m_ulVarValue);
                                }
                                break;
                        }
                    }

                    strDefinition += ";";

            }
        }
        else 
        {
            currentOut = OUT_UNKNOWN_VARIABLE;
            strDefinition = "/* ?import? variable ";
            strDefinition += m_Namespace.GetStringByIndex(i) + "; */";
        }

        if ((currentOut != lastOut) && (lastOut != OUT_NOTHING))
        {
            g_ofstream << std::endl;
        }

        lastOut = currentOut;
        g_ofstream << strDefinition << std::endl;
    }
}

void CFalloutScript::StoreDeclarations()
{
    std::string c_strBogusProcedureName("..............");
    std::string c_strArgumentTemplate("arg%u");
    std::string c_strLocalVarTemplate("LVar%u");

    std::cout << "    Storing declarations" << std::endl;

    std::string strOutLine;

    for(uint32_t i = 0; i < m_ProcTable.GetSize(); i++)
    {
        std::cout << format("        Procedure: %d", i) << std::endl;

        // Bogus procedure
        if ((i == 0) && (m_Namespace[m_ProcTable[i].m_ulNameOffset] == c_strBogusProcedureName))
        {
            continue;
        }

        // Empty procedure
        if (m_ProcTable.GetSizeOfProc(i) == 0)
        {
            g_ofstream << "/*******************************************************" << std::endl
                       << "*    Found Procedure without body.                     *" << std::endl
                       << "*                                                      *" << std::endl;
            strOutLine = "*    Name: ";
            strOutLine+= m_Namespace[m_ProcTable[i].m_ulNameOffset];

            while(strOutLine.length() <  55)
            {
                strOutLine += " ";
            }

            strOutLine += "*";
            g_ofstream << strOutLine << std::endl
                       << "*                                                      *" << std::endl;

            if (!(m_ProcTable[i].m_ulType & P_NOTIMPLEMENTED))
            {
                g_ofstream << "*    Other possible name(s):                           *" << std::endl;

                for(uint32_t j = i + 1; j < m_ProcTable.GetSize(); j++)
                {
                    if (m_ProcTable[j].m_ulBodyOffset == m_ProcTable[i].m_ulBodyOffset)
                    {
                        strOutLine = "*       ";
                        strOutLine+= m_Namespace[m_ProcTable[j].m_ulNameOffset];

                        while(strOutLine.length() <  55)
                        {
                            strOutLine += " ";
                        }

                        strOutLine += "*";
                        g_ofstream << strOutLine << std::endl;
                        strOutLine = "*       ";
                    }
                }
            }
            else
            {
                g_ofstream << "*           Not implemented                            *" << std::endl;
            }

            g_ofstream << "*                                                      *" << std::endl
                       << "*******************************************************/" << std::endl
                       << std::endl;
            continue;
        }

        // 'Normal' procedure
        CProcDescriptor procDescriptor = m_ProcTable[i];

        if (procDescriptor.m_ulType & P_CRITICAL)
        {
            strOutLine = "critical ";
        }
        else
        {
            strOutLine = "";
        }

        strOutLine += "procedure ";
        strOutLine+= m_Namespace[m_ProcTable[i].m_ulNameOffset];

        if (procDescriptor.m_ulNumArgs != 0)
        {
            strOutLine += "(";

            for(uint32_t i = 0; i < procDescriptor.m_ulNumArgs; i++)
            {
                if (i == 0)
                {
                    strOutLine = format(strOutLine + "variable " + c_strArgumentTemplate.c_str(), i);
                }
                else
                {
                    strOutLine = format(strOutLine + ", variable " + c_strArgumentTemplate.c_str(), i);
                }
            }

            strOutLine += ")";
        }

        if (procDescriptor.m_ulType & P_TIMED)
        {
            strOutLine = format(strOutLine + " in %d", procDescriptor.m_ulTime);
        }
        else if (procDescriptor.m_ulType & P_CONDITIONAL)
        {
            strOutLine = format(strOutLine + " when (%s)", GetSource(m_Conditions[i][0], false, procDescriptor.m_ulNumArgs).c_str());
        }

        g_ofstream << strOutLine << std::endl;

        bool bLocalVar = true;
        uint32_t ulLocalVarIndex = procDescriptor.m_ulNumArgs;
        int32_t nIndentLevel = 0;
        //CNode::Type prevNodeType = CNode::TYPE_NORMAL;

        for(uint32_t nNodeIndex = 0; nNodeIndex < m_ProcBodies[i].size(); nNodeIndex++)
        {
            if (m_ProcBodies[i][nNodeIndex].m_Type == CNode::TYPE_BEGIN_OF_BLOCK)
            {
                if ((nNodeIndex > 1) && (m_ProcBodies[i][nNodeIndex - 1].m_Type == CNode::TYPE_END_OF_BLOCK))
                {
                    g_ofstream << GetIndentString(nIndentLevel) << "else begin" << std::endl;
                    nIndentLevel++;
                }              
                else
                {
                    g_ofstream << "begin" << std::endl;
                    nIndentLevel++;
                }
                //prevNodeType = CNode::TYPE_BEGIN_OF_BLOCK;
            }
            else if (m_ProcBodies[i][nNodeIndex].m_Type == CNode::TYPE_END_OF_BLOCK)
            {
                nIndentLevel--;
                g_ofstream << GetIndentString(nIndentLevel) << "end" << std::endl;
                //prevNodeType = CNode::TYPE_END_OF_BLOCK;
            }
            else
            {
                //prevNodeType = CNode::TYPE_NORMAL;
                uint16_t wOperator = m_ProcBodies[i][nNodeIndex].m_Opcode.GetOperator();

                if ((m_ProcBodies[i][nNodeIndex].m_Opcode.GetAttributes().m_Type == COpcode::COpcodeAttributes::TYPE_EXPRESSION) &&
                    (wOperator != COpcode::O_STRINGOP) && (wOperator != COpcode::O_FLOATOP) && (wOperator != COpcode::O_INTOP))
                {
                    printf("Warning: Result of expression is left in stack. (Opcode 0x%04X at 0x%08X)\n", wOperator, m_ProcBodies[i][nNodeIndex].m_ulOffset);
                }

                switch(wOperator)
                {
                    case COpcode::O_STRINGOP:
                    case COpcode::O_FLOATOP:
                    case COpcode::O_INTOP:
                    {
                        if (!bLocalVar)
                        {
                            printf("Warning: Free value found. Converted to definition of local variable\n");
                        }

                        std::string str = "variable ";
                        str += c_strLocalVarTemplate + " := ";

                        strOutLine = format(str.c_str(), ulLocalVarIndex);
                        g_ofstream << GetIndentString(nIndentLevel) << strOutLine << GetSource(m_ProcBodies[i][nNodeIndex], false, procDescriptor.m_ulNumArgs) <<  ";" << std::endl;
                        ulLocalVarIndex++;
                        break;
                    }
                    case COpcode::O_IF:
                        g_ofstream << GetIndentString(nIndentLevel) << GetSource(m_ProcBodies[i][nNodeIndex], false, procDescriptor.m_ulNumArgs) << " then ";
                        break;

                    case COpcode::O_WHILE:
                        if (m_ProcBodies[i][nNodeIndex].m_Type == CNode::TYPE_FOR_LOOP)
                        {
                            std::string str = GetIndentString(nIndentLevel) + "for (";
                            for (uint32_t j = 0; j < m_ProcBodies[i][nNodeIndex].m_Arguments.size(); j++)
                            {
                                if (j > 0)
                                {
                                    str += "; ";
                                }
                                str += GetSource(m_ProcBodies[i][nNodeIndex].m_Arguments[j], false, procDescriptor.m_ulNumArgs);
                            }
                            str += ") ";
                            g_ofstream << str;
                        }
                        else
                        {
                            g_ofstream << GetIndentString(nIndentLevel) << GetSource(m_ProcBodies[i][nNodeIndex], false, procDescriptor.m_ulNumArgs) << " do ";
                        }
                        break;

                    default:
                        g_ofstream << GetIndentString(nIndentLevel) << GetSource(m_ProcBodies[i][nNodeIndex], false, procDescriptor.m_ulNumArgs) << ";" << std::endl;

                        if ((m_ProcBodies[i][nNodeIndex].m_Type != CNode::TYPE_BEGIN_OF_BLOCK) &&
                            (m_ProcBodies[i][nNodeIndex].m_Type != CNode::TYPE_END_OF_BLOCK))
                        {
                            bLocalVar = false;
                        }
                }
            }
        }

        g_ofstream << std::endl;
    }
}

std::string CFalloutScript::GetSource(CNode& node, bool bLabel, uint32_t ulNumArgs)
{
    std::string c_strArgumentTemplate("arg%u");
    std::string c_strLocalVarTemplate("LVar%u");

    std::string strResult("Damn!!!");

    if (node.m_Type == CNode::TYPE_OMITTED_ARGUMENT)
    {
        return "/* Omitted argument */";
    }

    uint16_t wOperator = node.m_Opcode.GetOperator();
    uint32_t ulArgument = node.m_Opcode.GetArgument();

    // sslc additions:
    if (wOperator == COpcode::O_JMP)
    {
        if (node.m_Type == CNode::TYPE_BREAK)
        {
            return "break";
        }
        else if (node.m_Type == CNode::TYPE_CONTINUE)
        {
            return "continue";
        }
    }
    switch(wOperator)
    {
        case COpcode::O_STRINGOP:
            try
            {
                if (bLabel)
                {
                    strResult = m_Namespace[ulArgument];
                }
                else
                {
                    strResult = "\"";
                    strResult += escape_str(m_Stringspace[ulArgument]);
                    strResult += "\"";
                }
            }
            catch(const std::exception& e)
            {
                std::cout << "Warning: Restoration after exception. Object name replaced with '/* Fake object name */'" << std::endl;
                strResult = "/* Fake object name */";
            }

            break;

        case COpcode::O_FLOATOP:
            strResult = format("%.5f", *((float*)(&ulArgument)));
            break;

        case COpcode::O_INTOP:
            try
            {
                if (bLabel)
                {
                    strResult = m_Namespace[ulArgument];
                }
                else
                {
                    strResult = format("%d", (long)ulArgument);
                }
            }
            catch(const std::exception& e)
            {
                std::cout << "Warning: Restoration after exception. Object name replaced with '/* Fake object name */'" << std::endl;
                strResult = "/* Fake object name */";
            }
            break;

        case COpcode::O_POP_RETURN:
            strResult = "return ";
            strResult += GetSource(node.m_Arguments[0], false, ulNumArgs);
            break;

        case COpcode::O_LOOKUP_STRING_PROC:
            strResult = GetSource(node.m_Arguments[0], false, ulNumArgs);
            break;

        case COpcode::O_FETCH_GLOBAL:
            if (node.m_Arguments[0].m_Opcode.GetOperator() != COpcode::O_INTOP)
            {
                std::cout << "Error: Invalid argument to O_FETCH_GLOBAL opcode" << std::endl;
                throw std::exception();
            }

            if (uint32_t(node.m_Arguments[0].m_Opcode.GetArgument()) > m_GlobalVarsNames.size() - 1)
            {
                printf("Error: Invalid index of global variable\n");
                throw std::exception();
            }

            strResult = m_GlobalVarsNames[node.m_Arguments[0].m_Opcode.GetArgument()];
            break;

        case COpcode::O_STORE_GLOBAL:
            if (node.m_Arguments[1].m_Opcode.GetOperator() != COpcode::O_INTOP)
            {
                printf("Error: Invalid argument to O_STORE_GLOBAL opcode\n");
                throw std::exception();
            }

            if (uint32_t(node.m_Arguments[1].m_Opcode.GetArgument()) > m_GlobalVarsNames.size() - 1)
            {
                printf("Error: Invalid index of global variable\n");
                throw std::exception();
            }

            strResult = m_GlobalVarsNames[node.m_Arguments[1].m_Opcode.GetArgument()];
            strResult += " := ";
            strResult += GetSource(node.m_Arguments[0], false, ulNumArgs);
            break;

        case COpcode::O_FETCH_EXTERNAL:
            {
                uint16_t wOperator = node.m_Arguments[0].m_Opcode.GetOperator();

                if ((wOperator != COpcode::O_STRINGOP) && (wOperator != COpcode::O_INTOP))
                {
                    printf("Error: Invalid argument to O_FETCH_EXTERNAL opcode\n");
                    throw std::exception();
                }
            }

            strResult = GetSource(node.m_Arguments[0], true, ulNumArgs);
            break;

        case COpcode::O_STORE_EXTERNAL:
            {
                uint16_t wOperator = node.m_Arguments[1].m_Opcode.GetOperator();

                if ((wOperator != COpcode::O_STRINGOP) && (wOperator != COpcode::O_INTOP))
                {
                    printf("Error: Invalid argument to O_STORE_EXTERNAL opcode\n");
                    throw std::exception();
                }
            }

            strResult = GetSource(node.m_Arguments[1], true, ulNumArgs);
            strResult += " := ";
            strResult += GetSource(node.m_Arguments[0], false, ulNumArgs);
            break;

        case COpcode::O_FETCH:
            if (node.m_Arguments[0].m_Opcode.GetOperator() != COpcode::O_INTOP)
            {
                printf("Error: Invalid argument to O_FETCH opcode\n");
                throw std::exception();
            }

            {
                uint32_t ulVarNum = node.m_Arguments[0].m_Opcode.GetArgument();

                if (ulVarNum < ulNumArgs)
                {
                    strResult = format(c_strArgumentTemplate.c_str(), ulVarNum);
                }
                else
                {
                    strResult = format(c_strLocalVarTemplate.c_str(), ulVarNum);
                }
            }

            break;

        case COpcode::O_STORE:
            if (node.m_Arguments[1].m_Opcode.GetOperator() != COpcode::O_INTOP)
            {
                printf("Error: Invalid argument to O_STORE opcode\n");
                throw std::exception();
            }

            {
                uint32_t ulVarNum = node.m_Arguments[1].m_Opcode.GetArgument();
                if (ulVarNum < ulNumArgs)
                {
                    strResult = format(c_strArgumentTemplate.c_str(), ulVarNum);
                }
                else
                {
                    strResult = format(c_strLocalVarTemplate.c_str(), ulVarNum);
                }
                strResult += " := ";
                strResult += GetSource(node.m_Arguments[0], false, ulNumArgs);
            }

            break;

        case COpcode::O_POP:
            strResult = GetSource(node.m_Arguments[0], false, ulNumArgs);

            if (node.m_Arguments[0].m_Opcode.GetOperator() == COpcode::O_CALL)
            {
                strResult = "call " + strResult;
            }

            break;

        case COpcode::O_CALL:
            if (node.m_Arguments[node.m_Arguments.size() - 1].m_Opcode.GetOperator() == COpcode::O_INTOP)
            {
                strResult = m_Namespace[m_ProcTable[node.m_Arguments[node.m_Arguments.size() - 1].m_Opcode.GetArgument()].m_ulNameOffset];
            }
            else
            {
                strResult = GetSource(node.m_Arguments[node.m_Arguments.size() - 1], false, ulNumArgs);
            }

            strResult += "(";

            for(uint32_t nArgIndex = 0; nArgIndex < node.m_Arguments.size() - 1 - 1; nArgIndex++)
            {
                if (nArgIndex == 0)
                {
                    strResult += GetSource(node.m_Arguments[nArgIndex], false, ulNumArgs);
                }
                else 
                {
                    strResult += ", ";
                    strResult +=  GetSource(node.m_Arguments[nArgIndex], false, ulNumArgs);
                }
            }

            strResult += ")";

            break;

        case COpcode::O_CALL_AT:
            strResult = "call ";

            if (node.m_Arguments[1].m_Opcode.GetOperator() == COpcode::O_INTOP)
            {
                strResult += m_Namespace[m_ProcTable[node.m_Arguments[1].m_Opcode.GetArgument()].m_ulNameOffset];
            }
            else
            {
                strResult += GetSource(node.m_Arguments[1], false, ulNumArgs);
            }

            strResult += " in (";
            strResult +=  GetSource(node.m_Arguments[0], false, ulNumArgs) + ")";
            break;

        case COpcode::O_CALL_CONDITION:
            strResult = "call ";

            if (node.m_Arguments[1].m_Opcode.GetOperator() == COpcode::O_INTOP)
            {
                strResult += m_Namespace[m_ProcTable[node.m_Arguments[1].m_Opcode.GetArgument()].m_ulNameOffset];
            }
            else
            {
                strResult += GetSource(node.m_Arguments[1], false, ulNumArgs);
            }

            strResult += " when (";
            strResult +=  GetSource(node.m_Arguments[0], false, ulNumArgs) + ")";
            break;

        case COpcode::O_ADDREGION:
            strResult = "addRegion ";
            strResult += GetSource(node.m_Arguments[0], false, ulNumArgs) + " { ";

            for(uint32_t nArgIndex = 1; nArgIndex < node.m_Arguments.size() - 1; nArgIndex++)
            {
                if (nArgIndex == 1)
                {
                    strResult += GetSource(node.m_Arguments[nArgIndex], false, ulNumArgs);
                }
                else
                {
                    strResult += ", ";
                    strResult += GetSource(node.m_Arguments[nArgIndex], false, ulNumArgs);
                }
            }

            strResult += " }";
            break;

        case COpcode::O_REFRESHMOUSE:
            {
                uint32_t aulProcArg[1] = { 1 };
                strResult = GetSource(node, bLabel, ulNumArgs, aulProcArg, 1);
            }

            break;

        case COpcode::O_ADDBUTTONPROC:
            {
                uint32_t aulProcArg[4] = { 2, 3, 4, 5 };
                strResult = GetSource(node, bLabel, ulNumArgs, aulProcArg, 4);
            }

            break;

        case COpcode::O_ADDBUTTONRIGHTPROC:
            {
                uint32_t aulProcArg[2] = { 2, 3 };
                strResult = GetSource(node, bLabel, ulNumArgs, aulProcArg, 2);
            }

            break;

        case COpcode::O_SAYOPTION:
            {
                if (node.m_Arguments[1].m_Opcode.GetOperator() == COpcode::O_INTOP)
                {
                    uint32_t aulProcArg[2] = { 2 };
                    strResult = GetSource(node, bLabel, ulNumArgs, aulProcArg, 1);
                }
                else
                {
                    strResult = "sayOption(";
                    strResult += GetSource(node.m_Arguments[0], false, ulNumArgs) + ", " + GetSource(node.m_Arguments[1], false, ulNumArgs) + ")";
                }
            }

            break;

        case COpcode::O_ADDREGIONPROC:
            {
                uint32_t aulProcArg[4] = { 2, 3, 4, 5 };
                strResult = GetSource(node, bLabel, ulNumArgs, aulProcArg, 4);
            }

            break;

        case COpcode::O_ADDREGIONRIGHTPROC:
            {
                uint32_t aulProcArg[2] = { 2, 3 };
                strResult = GetSource(node, bLabel, ulNumArgs, aulProcArg, 2);
            }

            break;

        case COpcode::O_ADDNAMEDEVENT:
            {
                uint32_t aulProcArg[1] = { 2 };
                strResult = GetSource(node, bLabel, ulNumArgs, aulProcArg, 1);
            }

            break;

        case COpcode::O_ADDNAMEDHANDLER:
            {
                uint32_t aulProcArg[1] = { 2 };
                strResult = GetSource(node, bLabel, ulNumArgs, aulProcArg, 1);
            }

            break;

        case COpcode::O_ADDKEY:
            {
                uint32_t aulProcArg[1] = { 2 };
                strResult = GetSource(node, bLabel, ulNumArgs, aulProcArg, 1);
            }

            break;

        case COpcode::O_GSAY_OPTION:
            {
                uint32_t aulProcArg[1] = { 3 };
                strResult = GetSource(node, bLabel, ulNumArgs, aulProcArg, 1);
            }

            break;

        case COpcode::O_GIQ_OPTION:
            {
                uint32_t aulProcArg[1] = { 4 };
                strResult = GetSource(node, bLabel, ulNumArgs, aulProcArg, 1);
            }

            break;

        case COpcode::O_CANCEL:
            if (node.m_Arguments[0].m_Opcode.GetOperator() != COpcode::O_INTOP)
            {
                printf("Error: Invalid argument to O_CANCEL opcode\n");
                throw std::exception();
            }

            strResult = "cancel(";
            strResult += m_Namespace[m_ProcTable[node.m_Arguments[0].m_Opcode.GetArgument()].m_ulNameOffset] + ")";
            break;

        case COpcode::O_NEGATE:
            if (node.m_Arguments[0].m_Opcode.GetAttributes().m_Category == COpcode::COpcodeAttributes::CATEGORY_INFIX)
            {
                strResult = "-(";
                strResult += GetSource(node.m_Arguments[0], bLabel, ulNumArgs) + ")";
            }
            else
            {
                strResult = "-";
                strResult += GetSource(node.m_Arguments[0], bLabel, ulNumArgs);
            }

            break;
            
        default:
            COpcode::COpcodeAttributes attributes = node.m_Opcode.GetAttributes();
            uint32_t *procArgs = attributes.m_procArgs;
            uint32_t numProcArgs = attributes.m_numProcArgs;
            if (numProcArgs > 0)
            {
                strResult = GetSource(node, bLabel, ulNumArgs, procArgs, numProcArgs);
                break;
            }
            if (node.m_Type == CNode::TYPE_CONDITIONAL_EXPRESSION)
            {
                if (node.m_Arguments.size() != 3)
                {
                    printf("Error: Invalid number of arguments in conditional expression\n");
                    throw std::exception();
                }
                std::string sPostfix[] = { " if ", " else ", ""};
                strResult = "";
                for(uint32_t i = 0; i < node.m_Arguments.size(); i++)
                {
                    bool bParens = ArgNeedParens(node, node.m_Arguments[i], CFalloutScript::RIGHT_ASSOC);
                    strResult += (bParens ? "(" : "") + GetSource(node.m_Arguments[i], bLabel, ulNumArgs) + (bParens ? ")" : "") + sPostfix[i];
                }
                break;
            }
            switch(attributes.m_Category)
            {
                case COpcode::COpcodeAttributes::CATEGORY_INFIX:
                    if (ArgNeedParens(node, node.m_Arguments[0], CFalloutScript::LEFT_ASSOC))
                    {
                        strResult = "(";
                        strResult += GetSource(node.m_Arguments[0], false, ulNumArgs) + ")";
                    }
                    else
                    {
                        strResult = GetSource(node.m_Arguments[0], false, ulNumArgs);
                    }

                    strResult += " ";
                    strResult += attributes.m_strName + " ";

                    
                    if (ArgNeedParens(node, node.m_Arguments[1], CFalloutScript::RIGHT_ASSOC))
                    {
                        strResult += "(";
                        strResult += GetSource(node.m_Arguments[1], false, ulNumArgs) + ")";
                    }
                    else
                    {
                        strResult += GetSource(node.m_Arguments[1], false, ulNumArgs);
                    }

                    break;

                case COpcode::COpcodeAttributes::CATEGORY_PREFIX:
                    strResult = attributes.m_strName;

                    if (node.m_Arguments.size() != 0)
                    {
                        if (wOperator == COpcode::O_IF || wOperator == COpcode::O_WHILE)
                        {
                            strResult += " ";
                        }

                        strResult += "(";

                        for(uint32_t i = 0; i < node.m_Arguments.size(); i++)
                        {
                            if (i == 0)
                            {
                                strResult += GetSource(node.m_Arguments[i], false, ulNumArgs);
                            }
                            else
                            {
                                strResult += ", ";
                                strResult += GetSource(node.m_Arguments[i], false, ulNumArgs);
                            }
                        }

                        strResult += ")";
                    }

                    break;
            }
    }

    return strResult;
}

std::string CFalloutScript::GetSource( CNode& node, bool bLabel, uint32_t ulNumArgs, uint32_t aulProcArg[], uint32_t ulProcArgCount)
{
    COpcode::COpcodeAttributes attributes = node.m_Opcode.GetAttributes();
    std::string strResult = attributes.m_strName + "(";
    std::string strArgument;
    bool bIsProcArg;

    for(uint32_t nArgIndex = 0; nArgIndex < node.m_Arguments.size(); nArgIndex++)
    {
        bIsProcArg = false;

        for(uint32_t ulProcArgIndex = 0; ulProcArgIndex < ulProcArgCount; ulProcArgIndex++)
        {
            if (nArgIndex == aulProcArg[ulProcArgIndex] - 1)
            {
                bIsProcArg = true;
                break;
            }
        }

        if (bIsProcArg)
        {
            if (node.m_Arguments[nArgIndex].m_Opcode.GetOperator() == COpcode::O_INTOP)
            {
                try
                {
                    strArgument = m_Namespace[m_ProcTable[node.m_Arguments[nArgIndex].m_Opcode.GetArgument()].m_ulNameOffset];
                }
                catch(const std::exception& e)
                {
                    printf("Warning: Restoration after exception. Object name replaced with '/* Fake object name */'\n");
                    strArgument = format("/* Fake object name: %u (%d)*/", node.m_Arguments[nArgIndex].m_Opcode.GetArgument(), node.m_Arguments[nArgIndex].m_Opcode.GetArgument());
                }
            }
            else
            {
                strArgument = GetSource(node.m_Arguments[nArgIndex], false, ulNumArgs);
            }
        }
        else
        {
            strArgument = GetSource(node.m_Arguments[nArgIndex], false, ulNumArgs);
        }

        if (nArgIndex == 0)
        {
            strResult += strArgument;
        }
        else
        {
            strResult += ", ";
            strResult += strArgument;
        }
    }

    strResult += ")";

    return strResult;
}

std::string CFalloutScript::GetIndentString(int32_t nLevel)
{
    std::string strResult;
    
    for(; nLevel > 0; nLevel--)
    {
        strResult += g_strIndentFill;
    }

    return strResult;
}

int CFalloutScript::GetPriority(uint16_t wOperator)
{
    switch(wOperator)
    {
        case COpcode::O_IF:
            return 0;
        case COpcode::O_OR:
        case COpcode::O_AND:
            return 2;

        case COpcode::O_GREATER:
        case COpcode::O_LESS:
        case COpcode::O_GREATER_EQUAL:
        case COpcode::O_LESS_EQUAL:
        case COpcode::O_EQUAL:
        case COpcode::O_NOT_EQUAL:
            return 3;

        case COpcode::O_ADD:
        case COpcode::O_SUB:
        case COpcode::O_BWXOR:
        case COpcode::O_BWOR:
        case COpcode::O_BWAND:
            return 4;

        case COpcode::O_MUL:
        case COpcode::O_DIV:
        case COpcode::O_MOD:
        case COpcode::O_TS_POW:
            return 5;
        
        default:
            return 6;
    }
}

CFalloutScript::Assoc CFalloutScript::GetAssociation(uint16_t wOperator)
{
    switch(wOperator)
    {
        case COpcode::O_GREATER:
        case COpcode::O_LESS:
        case COpcode::O_GREATER_EQUAL:
        case COpcode::O_LESS_EQUAL:
        case COpcode::O_EQUAL:
        case COpcode::O_NOT_EQUAL:
            return CFalloutScript::NON_ASSOC;

        case COpcode::O_OR:
        case COpcode::O_AND:
        case COpcode::O_ADD:
        case COpcode::O_SUB:
        case COpcode::O_BWXOR:
        case COpcode::O_BWOR:
        case COpcode::O_BWAND:
        case COpcode::O_MUL:
        case COpcode::O_DIV:
        case COpcode::O_MOD:
            return CFalloutScript::LEFT_ASSOC;
        
        default:
            return CFalloutScript::NON_ASSOC;
    }
}

