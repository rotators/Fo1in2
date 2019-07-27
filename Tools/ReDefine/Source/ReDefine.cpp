#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <istream>
#include <memory>
#include <sstream>

#include "FOClassic/CommandLine.h"
#include "FOClassic/Ini.h"

#include "ReDefine.h"
#include "Types.h"

constexpr uint16 MAX_LOGTEXT = 4096;

static uint StrLength( const char* str )
{
    const char* str_ = str;
    while( *str )
        str++;
    return (uint)(str - str_);
}

static void Print( const char* prefix, const char* function, const char* format, va_list& args, bool lineInfo, ReDefine::SStatus::SCurrent& current )
{
    std::string full;
    std::string log = "ReDefine";

    // prefix is part of both message and logfile name

    if( prefix )
    {
        full += std::string( prefix );
        full += " ";

        log += ".";
        log += std::string( prefix );
    }

    log += ".log";

    // add current function

    if( function )
    {
        full += "(";
        full += std::string( function );
        full += ") ";
    }

    // prepare text

    char text[MAX_LOGTEXT] = { 0 };
    std::vsnprintf( text, sizeof(text), format, args );
    text[MAX_LOGTEXT - 1] = 0;

    // skip empty text

    if( !StrLength( text ) )
        return;

    full += std::string( text );

    // append filename/line number, if available
    if( lineInfo && !current.File.empty() && current.LineNumber )
    {
        full += " : fileline<";
        full += current.File;
        full += ":";
        full += std::to_string( (long long)current.LineNumber );
        full += ">";
    }

    // append currently processed line

    if( !current.Line.empty() )
    {
        full += " :: ";
        full += current.Line;
    }

    // show && save

    std::printf( "%s\n", full.c_str() );

    std::ofstream flog;
    flog.open( log, std::ios::out | std::ios::app );
    if( flog.is_open() )
    {
        flog << full;
        flog << std::endl;

        flog.close();
    }
}

//

ReDefine::SStatus::SCurrent::SCurrent()
{
    Clear();
}

void ReDefine::SStatus::SCurrent::Clear()
{
    File = "";
    Line = "";
    LineNumber = 0;
}

//

void ReDefine::SStatus::Clear()
{
    Current.Clear();
}

//

ReDefine::ReDefine() :
    CommandLine( nullptr ),
    Config( nullptr )
{}

ReDefine::~ReDefine()
{
    Finish();
}

bool ReDefine::Init( int argc /* = 0 */, char** argv /* = nullptr */ )
{
    Finish();

    if( argc && argv )
        CommandLine = new CmdLine( argc, argv );

    // create config
    Config = new Ini();
    Config->KeepKeysOrder = true;

    // remove logfiles from previous run
    std::remove( "ReDefine.DEBUG.log" );
    std::remove( "ReDefine.WARNING.log" );
    std::remove( "ReDefine.log" );

    return true;
}

void ReDefine::Finish()
{
    if( CommandLine )
    {
        delete CommandLine;
        CommandLine = nullptr;
    }

    if( Config )
    {
        delete Config;
        Config = nullptr;
    }

    Status.Clear();

    // extern cleanup

    FinishDefines();
}

// logging

void ReDefine::DEBUG( const char* function, const char* format, ... )
{
    va_list list;
    va_start( list, format );
    Print( "DEBUG", function, format, list, true, Status.Current );
    va_end( list );
}

void ReDefine::WARNING( const char* func, const char* format, ... )
{
    va_list list;
    va_start( list, format );
    Print( "WARNING", nullptr, format, list, true, Status.Current );
    va_end( list );
}

void ReDefine::LOG( const char* format, ... )
{
    va_list list;
    va_start( list, format );
    Print( nullptr, nullptr, format, list, false, Status.Current );
    va_end( list );
}

// generic file reading

bool ReDefine::ReadFile( const std::string& path, std::vector<std::string>& lines )
{
    std::string filename = Config->GetStr( "ReDefine", "ScriptsDir" ) + std::string( "/" ) + path;
    lines.clear();

    std::ifstream fstream;
    fstream.open( filename, std::ios_base::in | std::ios_base::binary );

    bool result = fstream.is_open();
    if( result )
    {
        // skip bom
        char bom[3] = { 0, 0, 0 };
        fstream.read( bom, sizeof(bom) );
        if( bom[0] != (char)0xEF || bom[1] != (char)0xBB || bom[2] != (char)0xBF )
            fstream.seekg( 0, fstream.beg );

        std::string line;
        while( !fstream.eof() )
        {
            getline( fstream, line );

            line.erase( std::remove( line.begin(), line.end(), '\r' ), line.end() );
            line.erase( std::remove( line.begin(), line.end(), '\n' ), line.end() );

            lines.push_back( line );
        }
    }
    else
        WARNING( "cannot read file<[%s]/%s>", Config->GetStr( "ReDefine", "ScriptsDir" ).c_str(), path.c_str() );

    return result;
}


bool ReDefine::ReadConfig( const std::string& config )
{
    if( config.empty() )
    {
        WARNING( __FUNCTION__, "empty config filename" );
        return false;
    }

    if( !Config->LoadFile( config ) )
    {
        WARNING( __FUNCTION__, "cannot read config<%s>", config.c_str() );
        return false;
    }

    if( Config->IsSectionKeyEmpty( "ReDefine", "ScriptsDir" ) )
    {
        WARNING( __FUNCTION__, "config setting<[ReDefine]->ScriptsDir> is empty or missing" );
        return false;
    }

    if( !ReadConfigDefines() )
        return false;

    return true;
}
