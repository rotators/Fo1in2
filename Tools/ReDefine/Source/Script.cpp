#include "ReDefine.h"

void ReDefine::ProcessScript( const std::string& path, const std::string& filename, bool readOnly /* = false */ )
{
    std::vector<std::string> lines;
    if( !ReadFile( TextGetFilename( path, filename ), lines ) )
        return;

    Status.Process.Files++;
    Status.Current.Clear();

    Status.Current.File = filename;

    bool        updateFile = false;
    std::string content;

    for( auto& line : lines )
    {
        // update status
        Status.Process.Lines++;
        Status.Current.LineNumber++;

        // skip empty/fully commented
        if( !line.size() || TextIsComment( line ) )
        {
            content += line + "\r\n";
            continue;
        }

        // save original line
        const std::string lineOld = line;

        // extract variables
        for( const TripleString& var : TextGetVariables( line ) )
        {
            if( !IsOperator( std::get<1>( var ) ) )
            {
                // DEBUG( __FUNCTION__, "unknown operator<%s>", std::get<1>( var ).c_str() );
                continue;
            }

            // TODO
        }

        // extract functions
        for( ExtractedFunction& func : TextGetFunctions( line ) )
        {
            // TODO
        }

        // ... //

        // detect line change, ignore meaningless changes
        if( line != lineOld && TextGetPacked( line ) != TextGetPacked( lineOld ) )
        {
            LOG( "@@" );
            LOG( "<- %s", lineOld.c_str() );
            LOG( "-> %s", line.c_str() );
            updateFile = true;
        }

        // we did it, rotators!
        content += line + "\r\n";
    }

    Status.Current.Clear();

    if( readOnly )
        updateFile = false;
}
