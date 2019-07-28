#include <climits>
#include <cerrno>
#include <cstdlib>
#include <functional>
#include <regex>

#include "ReDefine.h"

static std::regex IsComment( "^[\\t\\ ]*\\/\\/" );
static std::regex IsDefine( "^[\\t\\ ]*\\#define[\\t\\ ]+" );

bool ReDefine::TextIsComment( const std::string& text )
{
    return std::regex_search( text, IsComment );
}

bool ReDefine::TextGetInt( const std::string& text, int& result, const unsigned char& base /* = 10 */ )
{
    // https://stackoverflow.com/a/6154614
    const char* cstr = text.c_str();
    char*       end;
    long        l;
    errno = 0;
    l = strtol( cstr, &end, base );
    if( ( (errno == ERANGE && l == LONG_MAX) || l > INT_MAX ) ||
        ( (errno == ERANGE && l == LONG_MIN) || l < INT_MIN ) ||
        (*cstr == '\0' || *end != '\0') )
        return false;

    result = l;

    return true;
}

std::string ReDefine::TextGetTrimmed( const std::string& text )
{
    std::string result = text;

    result.erase( result.begin(), find_if( result.begin(), result.end(), std::not1( std::ptr_fun<int, int>( isspace ) ) ) );
    result.erase( find_if( result.rbegin(), result.rend(), std::not1( std::ptr_fun<int, int>( isspace ) ) ).base(), result.end() );

    return result;
}

bool ReDefine::TextIsDefine( const std::string& text )
{
    return std::regex_search( text, IsDefine );
}

bool ReDefine::TextGetDefine( const std::string& text, const std::regex& pattern, std::string& name, int& value )
{
    std::smatch match;
    if( std::regex_search( text, match, pattern ) )
    {
        name = match.str( 1 );
        TextGetInt( match.str( 2 ), value );
        return true;
    }

    return false;
}

std::regex ReDefine::TextGetDefinePattern( const std::string& prefix, bool paren )
{
    return std::regex( "^[\\t\\ ]*\\#define[\\t\\ ]+(" + prefix + "_[A-Za-z0-9_]+)[\\t\\ ]+" + (paren ? "\\(" : "") + "([0-9]+)" + (paren ? "\\)" : "") );
}
