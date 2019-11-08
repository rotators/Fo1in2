/**
 *
 * Copyright (c) 2005-2009 Anchorite (TeamX), <anchorite2001@yandex.ru>
 * Copyright (c) 2014-2015 Nirran, phobos2077
 * Copyright (c) 2015 alexeevdv <mail@alexeevdv.ru>
 * Distributed under the GNU GPL v3. For full terms see the file license.txt
 *
 */

#ifndef STARTUP_CODE_H
#define STARTUP_CODE_H

// C++ standard includes

// int2ssl includes
#include "Opcode.h"

// Third party includes

class CStartupCode
{
public:

    enum Defaults {
        c_nDefaultSize = 42
    };

    CStartupCode();
    virtual ~CStartupCode();
    virtual void Serialize();

private:
    COpcode m_Code[17];
};

#endif // STARTUP_CODE_H
