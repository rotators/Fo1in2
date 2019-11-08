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
#include "StartupCode.h"

// Third party includes

CStartupCode::CStartupCode()
{
}

CStartupCode::~CStartupCode()
{
}

void CStartupCode::Serialize()
{
    uint16_t wExpectOpcodes[17] = {
        COpcode::O_CRITICAL_START,
        COpcode::O_INTOP,
        COpcode::O_D_TO_A,
        COpcode::O_INTOP,
        COpcode::O_JMP,
        COpcode::O_EXIT_PROG,
        COpcode::O_POP,
        COpcode::O_POP_FLAGS_RETURN,
        COpcode::O_POP,
        COpcode::O_POP_FLAGS_EXIT,
        COpcode::O_POP,
        COpcode::O_POP_FLAGS_RETURN_EXTERN,
        COpcode::O_POP,
        COpcode::O_POP_FLAGS_EXIT_EXTERN,
        COpcode::O_POP_FLAGS_RETURN_VAL_EXTERN,
        COpcode::O_POP_FLAGS_RETURN_VAL_EXIT,
        COpcode::O_POP_FLAGS_RETURN_VAL_EXIT_EXTERN
    };

    for(uint32_t i = 0; i < 17; i++)
    {
        if (i == 1)
        {
            m_Code[i].Expect(wExpectOpcodes[i], true, 18);
        }
        else
        {
            m_Code[i].Expect(wExpectOpcodes[i]);
        }
    }
}
