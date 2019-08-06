#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>

#include "ReDefine.h"

static unsigned int StrLength( const char* str )
{
    const char* str_ = str;
    while( *str )
        str++;
    return (unsigned int)(str - str_);
}

static void Print( ReDefine* redefine, const char* prefix, const char* caller, const char* format, va_list& args, bool lineInfo )
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

    // add caller function
    if( caller )
    {
        full += "(";
        full += std::string( caller );
        full += ") ";
    }

    // prepare text
    char text[4096];
    std::memset( text, 0, sizeof(text) );
    std::vsnprintf( text, sizeof(text), format, args );

    // skip empty text
    if( !StrLength( text ) )
        return;

    full += std::string( text );

    // append filename/line number, if available
    if( lineInfo && redefine && !redefine->Status.Current.File.empty() )
    {
        // use "fileline<F:L>" if line number is available
        // use "file<F>" if line number is not available

        full += " : file";
        if( redefine->Status.Current.LineNumber )
            full += "line";
        full += "<";

        full += redefine->Status.Current.File;
        if( redefine->Status.Current.LineNumber )
        {
            full += ":";
            full += std::to_string( (long long)redefine->Status.Current.LineNumber );
        }
        full += ">";
    }

    // append currently processed line
    if( redefine && !redefine->Status.Current.Line.empty() )
    {
        full += " :: ";
        full += redefine->TextGetTrimmed( redefine->Status.Current.Line );
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

void ReDefine::DEBUG( const char* caller, const char* format, ... )
{
    va_list list;
    va_start( list, format );
    Print( this, "DEBUG", caller, format, list, true );
    va_end( list );
}

void ReDefine::WARNING( const char* caller, const char* format, ... )
{
    va_list list;
    va_start( list, format );
    Print( this, "WARNING", caller, format, list, true );
    va_end( list );
}

void ReDefine::ILOG( const char* format, ... )
{
    va_list list;
    va_start( list, format );
    Print( this, nullptr, nullptr, format, list, true );
    va_end( list );
}

void ReDefine::LOG( const char* format, ... )
{
    va_list list;
    va_start( list, format );
    Print( this, nullptr, nullptr, format, list, false );
    va_end( list );
}
