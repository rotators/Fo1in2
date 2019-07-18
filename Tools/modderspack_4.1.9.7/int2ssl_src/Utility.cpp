/**
 *
 * Copyright (c) 2005-2009 Anchorite (TeamX), <anchorite2001@yandex.ru>
 * Copyright (c) 2014-2015 Nirran, phobos2077
 * Copyright (c) 2015 alexeevdv <mail@alexeevdv.ru>
 * Distributed under the GNU GPL v3. For full terms see the file license.txt
 *
 */

// C++ standard includes
#include <stdio.h>

// int2ssl includes
#include "Utility.h"

// Third party includes

std::string format(std::string format, ...)
{
    char buffer[1024]; // big enough for any string that will be formated
    int size;

    va_list args;
    va_start( args, format );

    size = vsprintf(buffer, format.c_str(), args);
    return std::string(buffer, size);
}

std::string format(std::string format, std::string value)
{
    char buffer[1024]; // big enough for any string that will be formated
    int size;
    size = sprintf(buffer, format.c_str(), value.c_str());
    return std::string(buffer, size);
}

std::string replace(std::string subject, std::string search, std::string replacement)
{
    size_t pos = 0;
    while((pos = subject.find(search, pos)) != std::string::npos)
    {
        subject.replace(pos, search.length(), replacement);
        pos += replacement.length();
    }
    return subject;
}

std::string escape_str(std::string input)
{
    std::string output;
    output.reserve(input.length());

    for (std::string::size_type i = 0; i < input.length(); ++i)
    {
        switch (input[i])
        {
            case '\n':
                output += "\\n";
                break;

            case '\r':
                output += "\\r";
                break;

            default:
                output += input[i];
                break;
        }
    }
    return output;
}
