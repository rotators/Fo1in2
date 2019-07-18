/**
 *
 * Copyright (c) 2005-2009 Anchorite (TeamX), <anchorite2001@yandex.ru>
 * Copyright (c) 2014-2015 Nirran, phobos2077
 * Copyright (c) 2015 alexeevdv <mail@alexeevdv.ru>
 * Distributed under the GNU GPL v3. For full terms see the file license.txt
 *
 */

// C++ standard includes

// int2ssl includes
#include "FalloutScript.h"

// Third party includes

CFalloutScript::CDefObject::CDefObject(ObjectType type, uint32_t ulAttributes, uint32_t ulObjectData)
{
    m_ulAttributes = ulAttributes;

    switch(m_ObjectType = type)
    {
        case OBJECT_VARIABLE:
            m_ulVarValue = ulObjectData;
            break;

        case OBJECT_PROCEDURE:
            m_ulProcIndex = ulObjectData;
    }
}
