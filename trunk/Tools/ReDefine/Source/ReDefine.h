#ifndef __REDEFINE__
#define __REDEFINE__    // :)

#include <map>
#include <string>
#include <vector>

#include "Types.h"

class CmdLine;
class Define;
class Ini;

namespace ReDefine
{
    struct SStatus
    {
        std::string CurrentFile;
        std::string CurrentLine;
        uint        CurrentLineNumber;

        void        Clear();
    };

    extern CmdLine* CommandLine;
    extern Ini*     Config;

    extern SStatus  Status;

    void DEBUG( const char* func, const char* format, ... );
    void WARNING( const char* func, const char* format, ... );
    void LOG( const char* format, ... );

	bool ReadFile( const std::string& path, std::vector<std::string>& lines );

    bool Init( int argc, char** argv, const char* config );
    int  Exit( int returnValue );
};

#endif // __REDEFINE__ //
