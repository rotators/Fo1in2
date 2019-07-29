#include <climits>
#include <cerrno>
#include <cstdlib>
#include <functional>
#include <regex>

#if defined (HAVE_FILESYSTEM)
# include <filesystem>
# if _MSC_VER == 1900 || _MSC_VER == 1800 || _MSC_VER == 1700
namespace std_filesystem = std::tr2::sys;
# else
namespace std_filesystem = std::filesystem;
# endif
#elif defined (HAVE_EXPERIMENTAL_FILESYSTEM)
# include <experimental/filesystem>
namespace std_filesystem = std::experimental::filesystem;
#else
# error "std::filesystem"
#endif

#include "ReDefine.h"

static std::regex IsComment( "^[\\t\\ ]*\\/\\/" );
static std::regex IsDefine( "^[\\t\\ ]*\\#define[\\t\\ ]+" );

bool ReDefine::TextIsComment( const std::string& text )
{
    return std::regex_search( text, IsComment );
}

std::string ReDefine::TextGetFilename( const std::string& path, const std::string& filename )
{
    std::string spath = path;
    std::string sfilename = filename;

    sfilename.erase( 0, sfilename.find_first_not_of( "\\/" ) ); // trim left
    spath.erase( spath.find_last_not_of( "\\/" ) + 1 );         // trim right

    std_filesystem::path full = std_filesystem::path( spath ) / sfilename;

    // DEBUG( __FUNCTION__, "[%s][%s] -> [%s][%s] -> [%s]", path.c_str(), filename.c_str(), spath.c_str(), sfilename.c_str(), full.string().c_str() );

    return full.string();
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

std::string ReDefine::TextGetJoined( const std::vector<std::string>& text, const std::string& delimeter )
{
    static const std::string empty;

    switch( text.size() )
    {
        case 0:
            return empty;
        case 1:
            return text[0];
        default:
            std::ostringstream oss;
            copy( text.begin(), text.end() - 1, std::ostream_iterator<std::string>( oss, delimeter.c_str() ) );
            oss << *text.rbegin();
            return oss.str();
    }
}


std::string ReDefine::TextGetLower( const std::string& text )
{
    std::string result = text;

    transform( result.begin(), result.end(), result.begin(), ::tolower );

    return result;
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
