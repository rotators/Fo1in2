/**
 *
 * Copyright (c) 2005-2009 Anchorite (TeamX), <anchorite2001@yandex.ru>
 * Copyright (c) 2014-2015 Nirran, phobos2077
 * Copyright (c) 2015 alexeevdv <mail@alexeevdv.ru>
 * Distributed under the GNU GPL v3. For full terms see the file license.txt
 *
 */

#ifndef CMAP_H
#define CMAP_H

// C++ standard includes
#include <map>
#include <stdint.h>

// int2ssl includes

// Third party includes

template<typename A, typename B, typename C,typename D>
class CMap
{
    std::map<A, C> _map;

    public:
        CMap()
        {
        }

        uint32_t GetSize() const
        {
            return _map.size();
        }

        void RemoveAll()
        {
            _map.clear();
        }

        void SetAt(uint32_t offset, C value)
        {
            if (_map.find(offset) != _map.end())
            {
                _map.at(offset) = value;
            }

            _map.insert(std::pair<A, C>(offset, value));
        }

        bool Lookup(uint32_t offset, C& value) const
        {
            if (_map.find(offset) != _map.end())
            {
                value = _map.find(offset)->second;
                return true;
            }
            return false;
        }

        void InitHashTable(uint32_t n)
        {

        }
};

#endif // CMAP_H
