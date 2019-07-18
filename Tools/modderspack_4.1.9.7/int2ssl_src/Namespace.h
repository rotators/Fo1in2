/**
 *
 * Copyright (c) 2005-2009 Anchorite (TeamX), <anchorite2001@yandex.ru>
 * Copyright (c) 2014-2015 Nirran, phobos2077
 * Copyright (c) 2015 alexeevdv <mail@alexeevdv.ru>
 * Distributed under the GNU GPL v3. For full terms see the file license.txt
 *
 */

#ifndef NAMESPACE_H
#define NAMESPACE_H

// C++ standard includes
#include <vector>

// int2ssl includes
#include "Hacks/CMap.h"

// Third party includes

class CNamespace
{
public:
    CNamespace();
    virtual ~CNamespace();

public:
    virtual void Serialize();

public:
    int32_t GetSize() const;
    std::string GetStringByIndex(int32_t nIndex) ;
    uint32_t GetOffsetByIndex(int32_t nIndex) ;

    void Dump();

public:
    std::string operator [] (uint32_t ulOffset) const;

private:    
    typedef CMap<uint32_t, uint32_t, std::string, const char*> CMapDWordToString;

    CMapDWordToString m_Map;
    std::vector<uint32_t> m_Order;
};

#endif //NAMESPACE_H
