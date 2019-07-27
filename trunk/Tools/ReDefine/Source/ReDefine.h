#ifndef __REDEFINE__
#define __REDEFINE__    // :)

#include <map>
#include <regex>
#include <string>
#include <vector>

#include "Types.h"

class CmdLine;
class Ini;

class ReDefine
{
public:

    //
    // ReDefine
    //

    CmdLine* CommandLine;
    Ini*     Config;

    struct SStatus
    {
        struct SCurrent
        {
            std::string File;
            std::string Line;
            uint        LineNumber;

            SCurrent();
            void        Clear();
        }
        Current;

        void Clear();
    }
    Status;


    ReDefine();
    virtual ~ReDefine();

    bool Init( int argc = 0, char** argv = nullptr );
    void Finish();

    void DEBUG( const char* func, const char* format, ... );
    void WARNING( const char* func, const char* format, ... );
    void LOG( const char* format, ... );

    bool ReadFile( const std::string& path, std::vector<std::string>& lines );
    bool ReadConfig( const std::string& config );

    //
    // Defines
    //

    std::map<std::string, std::map<int, std::string>> RegularDefines;
    std::map<std::string, std::vector<std::string>>   VirtualDefines;


    bool ReadConfigDefines();
    bool ReadDefines( const std::string& filename, const std::string& type, const std::string& prefix, const std::string& group = std::string() );
    void FinishDefines();

    //
    // Text
    //

    bool TextIsComment( const std::string& text );
    bool TextGetInt( const std::string& text, int& result, const unsigned char& base = 10 );

    bool       TextIsDefine( const std::string& text );
    bool       TextGetDefine( const std::string& text, const std::regex& pattern, std::string& name, int& value );
    std::regex TextGetDefinePattern( const std::string& prefix, bool paren );
};

#endif // __REDEFINE__ //
