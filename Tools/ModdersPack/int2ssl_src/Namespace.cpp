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
#include <algorithm>

// int2ssl includes
#include "Namespace.h"
#include "Utility.h"

// Third party includes

extern std::ifstream g_ifstream;
extern std::ofstream g_ofstream;

CNamespace::CNamespace()
{
    m_Map.InitHashTable(128);
}

CNamespace::~CNamespace()
{
}

void CNamespace::Serialize()
{
    m_Map.RemoveAll();
    m_Order.clear();

    uint32_t ulLength;
    g_ifstream.read((char*)&ulLength, sizeof(ulLength));
    std::reverse((char*)&ulLength, (char*)&ulLength + sizeof(ulLength));

    if (!g_ifstream)
    {
        std::cout << "Error: Unable read length of namespace" << std::endl;
        throw std::exception();
    }

    if (ulLength == 0xFFFFFFFF) return;

    uint32_t ulTotalRead = 0;
    uint16_t wLengthOfString;
    char*  lpszNewString;

    while(ulTotalRead < ulLength)
    {
        std::string strNewString;

        g_ifstream.read((char*)&wLengthOfString, sizeof(wLengthOfString));
        std::reverse((char*)&wLengthOfString, (char*)&wLengthOfString + sizeof(wLengthOfString));

        if (!g_ifstream)
        {
            std::cout << "Error: Unable read length of string" << std::endl;
            throw std::exception();
        };

        if ((wLengthOfString < 2) || (wLengthOfString & 0x0001))
        {
            std::cout << "Error: Invalid length of string" << std::endl;
            throw std::exception();
        }

        strNewString.resize(wLengthOfString);
        lpszNewString = (char*)strNewString.data();

        g_ifstream.read(lpszNewString, wLengthOfString);
        if (!g_ifstream)
        {
            strNewString.resize(0);
            std::cout << "Error: Unable read string in namespace" << std::endl;
            throw std::exception();
        }

        if ((lpszNewString[wLengthOfString - 1] != '\x00') && (lpszNewString[wLengthOfString - 2] != '\x00'))
        {
            strNewString.resize(0);
            std::cout << "Error: Invalid end of string in namespace" << std::endl;
            throw std::exception();
        }

        std::string tmpString(lpszNewString);
        strNewString = tmpString.c_str();

        // Convert Nongraphic Characters to Escape sequence
        std::string strNonGraph("\\\a\b\f\n\r\t\"");
        std::string strEscape("\\abfnrt\"");

        for(uint32_t i = 0; i < strNonGraph.length(); i++)
        {
            strNewString = replace(strNewString, std::string() + strNonGraph[i], std::string("\\") + strEscape[i]);
        }

        m_Map.SetAt(ulTotalRead + 6, strNewString);
        m_Order.push_back(ulTotalRead + 6);

        ulTotalRead += (2 + wLengthOfString);
    }

    uint32_t ulTerminator;

    g_ifstream.read((char*)&ulTerminator, sizeof(ulTerminator));
    std::reverse((char*)&ulTerminator, (char*)&ulTerminator + sizeof(ulTerminator));

    if (!g_ifstream)
    {
        std::cout << "Error: Unable read terminator of namespace" << std::endl;
        throw std::exception();
    }

    if (ulTerminator != 0xFFFFFFFF)
    {
        printf("Error: Invalid terminator of namespace\n");
        throw std::exception();
    }

//          //For debugging only
//          for(int32_t i = 0; i < GetSize(); i++) {
//              printf("Offset: 0x%08X (%9d), string: %s\n", m_Order[i], m_Order[i], GetStringByIndex(i));
//          }
//
//          printf("\n");
}

int32_t CNamespace::GetSize() const
{
    return m_Map.GetSize();
}

std::string CNamespace::GetStringByIndex(int32_t nIndex)
{
    return (this->operator [] (m_Order[nIndex]));
}

uint32_t CNamespace::GetOffsetByIndex(int32_t nIndex)
{
    return m_Order[nIndex];
}

void CNamespace::Dump()
{
    if (m_Order.empty())
    {
        g_ofstream << "Empty" << std::endl;
    }
    else
    {
        for(unsigned int i = 0; i < m_Order.size(); i++)
        {
            g_ofstream << format("0x%08X: \"%s\"", m_Order[i], GetStringByIndex(i).c_str()) << std::endl;
        }

        g_ofstream << "==================" << std::endl;
        g_ofstream << format("%d item(s)\n", m_Order.size()) << std::endl;
    }
}

std::string CNamespace::operator [] (uint32_t ulOffset) const
{
    std::string strResult;

    if (!m_Map.Lookup(ulOffset, strResult))
    {
        printf("Error: No string at offset 0x%08x\n", ulOffset);
        throw std::exception();
    }

    return strResult;
}
