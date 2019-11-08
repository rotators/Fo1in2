/**
 *
 * Copyright (c) 2005-2009 Anchorite (TeamX), <anchorite2001@yandex.ru>
 * Copyright (c) 2014-2015 Nirran, phobos2077
 * Copyright (c) 2015 alexeevdv <mail@alexeevdv.ru>
 * Distributed under the GNU GPL v3. For full terms see the file license.txt
 *
 */

#ifndef PROC_TABLE_H
#define PROC_TABLE_H

// C++ standard includes
#include <stdint.h>

// int2ssl includes

// Third party includes

class CProcDescriptor
{
public:
    CProcDescriptor();
    CProcDescriptor(const CProcDescriptor& Item);
    virtual ~CProcDescriptor();

public:
    virtual void Serialize();

    void Dump();

public:
    CProcDescriptor& operator = (const CProcDescriptor& Item);

public:
    uint32_t m_ulNameOffset;           // Index into namespace for procedure name
    uint32_t m_ulType;                 // Type of function (P_TIMED, P_CONDITIONAL, none)
    uint32_t m_ulTime;                 // Time this proc should go off, if timed
    uint32_t m_ulExpressionOffset;     // Pointer to conditional code, if conditional
    uint32_t m_ulBodyOffset;           // Pointer to procedure
    uint32_t m_ulNumArgs;              // Number of args to procedure
};

class CProcTable
{
public:
    CProcTable();
    virtual ~CProcTable();

public:
    virtual void Serialize();

    uint32_t GetSize();
    uint32_t GetSizeOfProc(uint32_t nIndex);
    uint32_t GetOffsetOfProcSection();

    void Dump();

public:
    CProcDescriptor& operator [] (uint32_t nIndex);

private:
    // CProcTableArray
    typedef std::vector<CProcDescriptor> CProcTableArray;

    CProcTableArray m_Table;
    std::vector<uint32_t> m_ProcSize;
    uint32_t m_ulOffsetOfProcSection;
};

#endif //PROC_TABLE_H
