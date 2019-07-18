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
#include <vector>
#include <cstdlib>
#include <algorithm>

// int2ssl includes
#include "ProcTable.h"
#include "Utility.h"
#include "ObjectAttributes.h"

// Third party includes

extern std::ifstream g_ifstream;
extern std::ofstream g_ofstream;

CProcDescriptor::CProcDescriptor() :
    m_ulNameOffset(0),
    m_ulType(0),
    m_ulTime(0),
    m_ulExpressionOffset(0),
    m_ulBodyOffset(0),
    m_ulNumArgs(0)
{
}

CProcDescriptor::CProcDescriptor(const CProcDescriptor& Item) :
    m_ulNameOffset(Item.m_ulNameOffset),
    m_ulType(Item.m_ulType),
    m_ulTime(Item.m_ulTime),
    m_ulExpressionOffset(Item.m_ulExpressionOffset),
    m_ulBodyOffset(Item.m_ulBodyOffset),
    m_ulNumArgs(Item.m_ulNumArgs)
{
}


CProcDescriptor::~CProcDescriptor()
{
}

CProcDescriptor& CProcDescriptor::operator = (const CProcDescriptor& Item)
{
    if (&Item != this)
    {
        m_ulNameOffset = Item.m_ulNameOffset;
        m_ulType = Item.m_ulType;
        m_ulTime = Item.m_ulTime;
        m_ulExpressionOffset = Item.m_ulExpressionOffset;
        m_ulBodyOffset = Item.m_ulBodyOffset;
        m_ulNumArgs = Item.m_ulNumArgs;
    }

    return (*this);
}

void CProcDescriptor::Serialize()
{

    g_ifstream.read((char*)&m_ulNameOffset, sizeof(m_ulNameOffset));
    std::reverse((char*)&m_ulNameOffset, (char*)&m_ulNameOffset + sizeof(m_ulNameOffset));
    g_ifstream.read((char*)&m_ulType, sizeof(m_ulType));
    std::reverse((char*)&m_ulType, (char*)&m_ulType + sizeof(m_ulType));
    g_ifstream.read((char*)&m_ulTime, sizeof(m_ulTime));
    std::reverse((char*)&m_ulTime, (char*)&m_ulTime + sizeof(m_ulTime));
    g_ifstream.read((char*)&m_ulExpressionOffset, sizeof(m_ulExpressionOffset));
    std::reverse((char*)&m_ulExpressionOffset, (char*)&m_ulExpressionOffset + sizeof(m_ulExpressionOffset));
    g_ifstream.read((char*)&m_ulBodyOffset, sizeof(m_ulBodyOffset));
    std::reverse((char*)&m_ulBodyOffset, (char*)&m_ulBodyOffset + sizeof(m_ulBodyOffset));
    g_ifstream.read((char*)&m_ulNumArgs, sizeof(m_ulNumArgs));
    std::reverse((char*)&m_ulNumArgs, (char*)&m_ulNumArgs + sizeof(m_ulNumArgs));

    if (!g_ifstream)
    {
        std::cout << "Error: Unable read procedure descriptor" << std::endl;
        throw std::exception();
    }
}

void CProcDescriptor::Dump()
{
    std::string strType;

    if (m_ulType != 0x00000000)
    {
        strType = "( ";

        if (m_ulType & P_TIMED)
        {
            strType += "timed ";
        }

        if (m_ulType & P_CONDITIONAL)
        {
            strType += "conditional ";
        }

        if (m_ulType & P_IMPORT)
        {
            strType += "import ";
        }

        if (m_ulType & P_EXPORT) {
            strType += "export ";
        }

        if (m_ulType & P_CRITICAL) {
            strType += "critical ";
        }

        strType += ")";
    }
    else
    {
        strType = "No special types";
    }

    g_ofstream << format("Name offset:       0x%08X", m_ulNameOffset) << std::endl;
    g_ofstream << format("Type:              0x%08X  // %s", m_ulType, strType.c_str()) << std::endl;
    g_ofstream << format("Time:              0x%08X  // %d", m_ulTime, m_ulTime) << std::endl;
    g_ofstream << format("Expression offset: 0x%08X", m_ulExpressionOffset) << std::endl;
    g_ofstream << format("Body offset:       0x%08X", m_ulBodyOffset) << std::endl;
    g_ofstream << format("Number of args:    0x%08X  // %d", m_ulNumArgs, m_ulNumArgs) << std::endl;
}


CProcTable::CProcTable()
{
}

CProcTable::~CProcTable()
{
}

struct ProcBodyOffset {
    uint32_t m_ulProcIndex;
    uint32_t m_ulBodyOffset;
};

int compareProcBodyOffsets(const void* elem0, const void* elem1)
{
    ProcBodyOffset offset0 = *((ProcBodyOffset*)elem0);
    ProcBodyOffset offset1 = *((ProcBodyOffset*)elem1);

    if (offset0.m_ulBodyOffset < offset1.m_ulBodyOffset)
    {
        return -1;
    }
    else if (offset0.m_ulBodyOffset > offset1.m_ulBodyOffset)
    {
        return 1;
    }
    else
    {
        if (offset0.m_ulProcIndex < offset1.m_ulProcIndex)
        {
            return -1;
        }
        else if (offset0.m_ulProcIndex > offset1.m_ulProcIndex)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

void CProcTable::Serialize()
{
    m_Table.clear();
    m_ProcSize.clear();

    uint32_t oldPosition = g_ifstream.tellg();
    g_ifstream.seekg(0, std::ios_base::end);

    uint32_t ulSizeOfFile = g_ifstream.tellg();
    g_ifstream.seekg(oldPosition, std::ios_base::beg);

    uint32_t ulSizeOfTable;
    g_ifstream.read((char*)&ulSizeOfTable, sizeof(ulSizeOfTable));
    std::reverse((char*)&ulSizeOfTable, (char*)&ulSizeOfTable + sizeof(ulSizeOfTable));

    if (!g_ifstream)
    {
        printf("Error: Unable read size of procedures table\n");
        throw std::exception();
    }

    m_Table.resize(ulSizeOfTable);
    m_ProcSize.resize(ulSizeOfTable);

    uint32_t ulIndexOfProcOffset = 0;
    ProcBodyOffset* pOffsets = new ProcBodyOffset[ulSizeOfTable + 1];

    if (pOffsets == NULL)
    {
        throw std::exception();
    }

    for(uint32_t i = 0; i < ulSizeOfTable; i++)
    {
//      printf("======== %u =========\n", i);
        m_Table[i].Serialize();
        m_ProcSize[i] = 0;       // Initialize size of procedure

        if (!(m_Table[i].m_ulType & P_IMPORT))
        {
            if ((m_Table[i].m_ulBodyOffset != 0) && (m_Table[i].m_ulBodyOffset != ulSizeOfFile))
            {
                pOffsets[ulIndexOfProcOffset].m_ulProcIndex = i;
                pOffsets[ulIndexOfProcOffset].m_ulBodyOffset = m_Table[i].m_ulBodyOffset;
                ulIndexOfProcOffset++;
            }
            else
            {
                m_Table[i].m_ulType |= P_NOTIMPLEMENTED;
            }
        }
    }

    pOffsets[ulIndexOfProcOffset].m_ulProcIndex = ulIndexOfProcOffset + 1;
    pOffsets[ulIndexOfProcOffset].m_ulBodyOffset = ulSizeOfFile;

    qsort(pOffsets, ulIndexOfProcOffset, sizeof(ProcBodyOffset), compareProcBodyOffsets);

    // Sizes of procedures
    for(uint32_t i = 0; i < ulIndexOfProcOffset; i++)
    {
        if (pOffsets[i + 1].m_ulBodyOffset >=  pOffsets[i].m_ulBodyOffset)
        {
            m_ProcSize[pOffsets[i].m_ulProcIndex] = pOffsets[i + 1].m_ulBodyOffset -  pOffsets[i].m_ulBodyOffset;
        }
        else
        {
            printf("Error: Procedures are not sorted in ascending address order\n");
            throw std::exception();
        }
    }

    delete [] pOffsets;

    for(uint32_t i = 0; i < ulSizeOfTable; i++)
    {
        if (m_Table[i].m_ulBodyOffset != 0)
        {
            m_ulOffsetOfProcSection = m_Table[i].m_ulBodyOffset;
            break;
        }
    }

//    // For debugging only
//    printf("Total: %d\n", m_Table.GetSize());

//    for(i = 0; i < ulSizeOfTable; i++)
//    {
//        printf("Offset: 0x%08X, size: 0x%08X\n", m_Table[i].m_ulBodyOffset, m_ProcSize[i]);
//    }

//    printf("m_ulOffsetOfProcSection: 0x%08X\n", m_ulOffsetOfProcSection);
}

uint32_t CProcTable::GetSize()
{
    return m_Table.size();
}

uint32_t CProcTable::GetSizeOfProc(uint32_t nIndex)
{
    if (nIndex >= m_ProcSize.size())
    {
        printf("Warning: Invalid index of procedure (%d). Exception will be thrown\n", nIndex);
        throw std::exception();
    }

    return m_ProcSize[nIndex];
}

uint32_t CProcTable::GetOffsetOfProcSection()
{
    return m_ulOffsetOfProcSection;
}


void CProcTable::Dump()
{
    for(unsigned int i = 0; i < m_Table.size(); i++)
    {
        g_ofstream << format("======== Procedure %d ========", i) << std::endl;
        m_Table[i].Dump();
        g_ofstream << std::endl;
    }
}


CProcDescriptor& CProcTable::operator [] (uint32_t nIndex)
{
    if (nIndex >= m_ProcSize.size())
    {
        printf("Warning: Invalid index of procedure (%d). Exception will be thrown\n", nIndex);
        throw std::exception();
    }

    return m_Table[nIndex];
}
