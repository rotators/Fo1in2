/**
 *
 * Copyright (c) 2005-2009 Anchorite (TeamX), <anchorite2001@yandex.ru>
 * Copyright (c) 2014-2015 Nirran, phobos2077
 * Copyright (c) 2015 alexeevdv <mail@alexeevdv.ru>
 * Distributed under the GNU GPL v3. For full terms see the file license.txt
 *
 */

#ifndef UTILITY_H
#define UTILITY_H

// C++ standard includes
#include <stdarg.h>
#include <string>

// int2ssl includes

// Third party includes

std::string format(std::string format, ...);
std::string format(std::string format, std::string value);
std::string replace(std::string subject, std::string search, std::string replacement);
std::string escape_str(std::string input);

#endif
