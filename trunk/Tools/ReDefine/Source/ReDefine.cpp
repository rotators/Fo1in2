#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <istream>
#include <memory>
#include <sstream>

#include "ReDefine.h"
#include "Defines.h"
#include "Types.h"

#include "FOClassic/CommandLine.h"
#include "FOClassic/Ini.h"

enum LogType
{
    Debug = 0,
    Warning,
    Normal
};

constexpr uint16  MAX_LOGTEXT = 4096;

CmdLine*          ReDefine::CommandLine = nullptr;
Ini*              ReDefine::Config = nullptr;
ReDefine::SStatus ReDefine::Status;

uint StrLength( const char* str )
{
    const char* str_ = str;
    while( *str )
        str++;
    return (uint)(str - str_);
}

void StrInsert( char* to, const char* from )
{
    if( !to || !from )
        return;

    int flen = StrLength( from );
    if( !flen )
        return;

    char* end_to = to;
    while( *end_to )
        ++end_to;

    for( ; end_to >= to; --end_to )
        *(end_to + flen) = *end_to;

    while( *from )
    {
        *to = *from;
        ++to;
        ++from;
    }
}

static void Print( const char* prefix, const char* function, const char* frmt, va_list& list, bool lineInfo = true )
{
    char str[MAX_LOGTEXT] = { 0 };

    if( function )
    {
        StrInsert( str, ") " );
        StrInsert( str, function );
        StrInsert( str, "(" );
    }

    if( prefix )
    {
        StrInsert( str, " " );
        StrInsert( str, prefix );
    }

    size_t len = StrLength( str );
    std::vsnprintf( &str[len], MAX_LOGTEXT - len, frmt, list );
    str[MAX_LOGTEXT - 1] = 0;

    if( StrLength( str ) == (prefix ? StrLength( prefix ) + 1 : 0) + (function ? StrLength( function ) + 3 : 0) )
        return;

	if (lineInfo && !ReDefine::Status.CurrentFile.empty() && ReDefine::Status.CurrentLineNumber)
		std::snprintf(str, sizeof(str), "%s : fileline<%s:%u>", str, ReDefine::Status.CurrentFile.c_str(), ReDefine::Status.CurrentLine);

	std::printf("%s\n", str);
}

//

void ReDefine::SStatus::Clear()
{
    CurrentFile.clear();
    CurrentLine.clear();
    CurrentLineNumber = 0;
}

//

void ReDefine::DEBUG( const char* function, const char* format, ... )
{
    va_list list;
    va_start( list, format );
    Print( "DEBUG", function, format, list );
    va_end( list );
}

void ReDefine::WARNING( const char* func, const char* format, ... )
{
    va_list list;
    va_start( list, format );
    Print( "WARNING", nullptr, format, list );
    va_end( list );
}

void ReDefine::LOG( const char* format, ... )
{
    va_list list;
    va_start( list, format );
    Print( nullptr, nullptr, format, list );
    va_end( list );
}

bool ReDefine::ReadFile(const std::string& path, std::vector<std::string>& lines)
{
	lines.clear();

	ifstream fstream;
	fstream.open(fname, ios_base::in | ios_base::binary);

	if (fstream.is_open())
	{
		char bom[3] = { 0, 0, 0 };
		fstream.read(bom, sizeof(bom));
		if (bom[0] != (char)0xEF || bom[1] != (char)0xBB || bom[2] != (char)0xBF)
			fstream.seekg(0, fstream.beg);

	}

bool ReDefine::Init( int argc, char** argv, const char* config )
{
    Exit( -1 );

    CommandLine = new CmdLine( argc, argv );
    Config = new Ini();
    Config->KeepKeysOrder = true;

    return Config->LoadFile( config );
}

int ReDefine::Exit( int returnValue )
{
    if( CommandLine )
        delete CommandLine;

    if( Config )
        delete Config;

    FinishDefines();

    return returnValue;
}

#if !defined(REDEFINE_NO_MAIN)

int main( int argc, char** argv )
{
    std::setvbuf( stdout, NULL, _IONBF, 0 );

    ReDefine::LOG( "ReDefine <3 FO1@2" );
    ReDefine::LOG( " " );

    if( !ReDefine::Init( argc, argv, "ReDefine.cfg" ) )
        return ReDefine::Exit( EXIT_FAILURE );

    return ReDefine::Exit( EXIT_SUCCESS );
}

#endif // !REDEFINE_NO_MAIN
