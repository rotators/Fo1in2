/**
 *
 * Copyright (c) 2005-2009 Anchorite (TeamX), <anchorite2001@yandex.ru>
 * Copyright (c) 2014-2015 Nirran, phobos2077
 * Copyright (c) 2015 alexeevdv <mail@alexeevdv.ru>
 * Distributed under the GNU GPL v3. For full terms see the file license.txt
 *
 */

#ifndef OBJECT_ATTRIBUTES_H
#define OBJECT_ATTRIBUTES_H

// ProcedureAttributes
enum ProcAttributes {
    P_TIMED          = 0x01,
    P_CONDITIONAL    = 0x02,
    P_IMPORT         = 0x04,
    P_EXPORT         = 0x08,
    P_CRITICAL       = 0x10,

    P_NOTIMPLEMENTED = 0x80000000
};

// VariableAtributes
enum VariableAtributes {
    V_GLOBAL = 0x00010000,
    V_IMPORT = 0x00020000,
    V_EXPORT = 0x00040000
};

#endif //OBJECT_ATTRIBUTES_H
