#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <fstream>

#include "FOClassic/Ini.h"

#include "ReDefine.h"

constexpr unsigned short MAX_LOGTEXT = 4096;

static unsigned int StrLength( const char* str )
{
    const char* str_ = str;
    while( *str )
        str++;
    return (uint)(str - str_);
}

static void Print( ReDefine* self, const char* prefix, const char* function, const char* format, va_list& args, bool lineInfo )
{
    std::string full;
    std::string log = "ReDefine";

    // prefix is part of message and logfile name
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
    if( lineInfo && self && !self->Status.Current.File.empty() )
    {
        // use "fileline<F:L>" if line number is available
        // use "file<F>" if line number is not available

        full += " : file";
        if( self->Status.Current.LineNumber )
            full += "line";
        full += "<";

        full += self->Status.Current.File;
        if( self->Status.Current.LineNumber )
        {
            full += ":";
            full += std::to_string( (long long)self->Status.Current.LineNumber );
        }
        full += ">";
    }

    // append currently processed line
    if( self && !self->Status.Current.Line.empty() )
    {
        full += " :: ";
        full += self->TextGetTrimmed( self->Status.Current.Line );
    }

    // show...
    std::printf( "%s\n", full.c_str() );

    // ...and save
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
    Config( nullptr )
{}

ReDefine::~ReDefine()
{
    Finish();
}

void ReDefine::Init()
{
    Finish();

    // create config
    Config = new Ini();
    Config->KeepKeysOrder = true;

    // remove logfiles from previous run
    std::remove( "ReDefine.DEBUG.log" );
    std::remove( "ReDefine.WARNING.log" );
    std::remove( "ReDefine.log" );

    // extern initialization
    InitOperators();
}

void ReDefine::Finish()
{
    if( Config )
    {
        delete Config;
        Config = nullptr;
    }

    Status.Clear();

    // extern cleanup
    FinishDefines();
    FinishOperators();
    FinishVariables();
}

// logging

void ReDefine::DEBUG( const char* function, const char* format, ... )
{
    va_list list;
    va_start( list, format );
    Print( this, "DEBUG", function, format, list, true );
    va_end( list );
}

void ReDefine::WARNING( const char* func, const char* format, ... )
{
    va_list list;
    va_start( list, format );
    Print( this, "WARNING", nullptr, format, list, true );
    va_end( list );
}

void ReDefine::LOG( const char* format, ... )
{
    va_list list;
    va_start( list, format );
    Print( this, nullptr, nullptr, format, list, false );
    va_end( list );
}

// generic file reading
bool ReDefine::ReadFile( const std::string& filename, std::vector<std::string>& lines )
{
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
        WARNING( nullptr, "cannot read file<%s>", filename.c_str() );

    return result;
}

bool ReDefine::ReadConfig( const std::string& defines, const std::string& variablePrefix, const std::string& functionPrefix )
{
    if( !ReadConfigDefines( defines ) )
        return false;

    if( !ReadConfigVariables( variablePrefix ) )
        return false;

    // if( !ReadConfigFunctions( functionPrefix ) )
    //     return false;

    return true;
}

void ReDefine::ProcessHeaders( const std::string& path )
{
    for( const auto& header : Headers )
    {
        ProcessHeader( path, header );
    }
}

void ReDefine::ProcessScripts( const std::string& path, bool readOnly /* = false */ )
{
    // LOG( "Process scripts..." );
}
