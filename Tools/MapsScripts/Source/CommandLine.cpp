#ifdef FOCLASSIC_ENGINE
# include "Core.h"
#endif

#include <algorithm>
#include <climits>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>

#include "CommandLine.hpp"

CommandLine::CommandLine( int argc, char** argv ) : App( argv[0] )
{
    for( int arg = 1; arg < argc; arg++ )
    {
        Cache.push_back( std::string( argv[arg] ) );
    }
}

CommandLine::~CommandLine()
{
    Cache.clear();
}

//

bool CommandLine::IsOption( const std::string& option )
{
    return std::ranges::find( Cache, "--" + option ) != Cache.end();
}

bool CommandLine::IsOptionEmpty( const std::string& option )
{
    return GetStr( option ).empty();
}

//

std::string CommandLine::Get()
{
    static const std::string empty;

    switch( Cache.size() )
    {
        case 0:
            return empty;
        case 1:
            return Cache[0];
        default:
            std::ostringstream os;
            copy( Cache.begin(), Cache.end() - 1, std::ostream_iterator<std::string>( os, " " ) );
            os << *Cache.rbegin();
            return os.str();
    }
}

std::string CommandLine::GetArg( unsigned int arg )
{
    static const std::string empty;

    if( Cache.size() > arg )
        return Cache[arg];

    return empty;
}

int CommandLine::GetInt( const std::string& option, const int& default_value, const unsigned char& base /* = 10 */ )
{
    int    result = default_value;
    std::string str = GetStr( option );

    if( !str.empty() )
    {
        const char* cstr = str.c_str();
        char*       end;
        long        l;
        errno = 0;
        l = strtol( cstr, &end, base );
        if( ( (errno == ERANGE && l == LONG_MAX) || l > INT_MAX ) ||
            ( (errno == ERANGE && l == LONG_MIN) || l < INT_MIN ) ||
            (*cstr == '\0' || *end != '\0') )
            result = default_value;
        else
            result = l;
    }

    return result;
}

std::string CommandLine::GetStr( const std::string& option )
{
    static const std::string empty;

    return GetStr( option, empty );
}

std::string CommandLine::GetStr( const std::string& option, const std::string& default_value )
{
    std::vector<std::string>::const_iterator it = std::ranges::find( Cache, "--" + option );

    if( it != Cache.end() && ++it != Cache.end() )
    {
        std::string value = *it;

        if( value.size() >= 2 && value[0] == '-' && value[1] == '-' )
            return default_value;

        return value;
    }

    return default_value;
}

std::vector<std::string> CommandLine::GetStrVec( const std::string& option, char separator )
{
    std::string              value = GetStr(option);
    std::vector<std::string> result;

    if( !value.empty() )
    {
        std::string        tmp;
        std::istringstream f( value );
        while(std::getline( f, tmp, separator ) )
        {
            result.push_back( tmp );
        }
    }

    return result;
}
