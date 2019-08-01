#include <fstream>

#include "ReDefine.h"

ReDefine::ScriptCode::ScriptCode() :
    Function( false ),
    Full( "" ),
    Name( "" ),
    Arguments(),
    Operator( "" ),
    OperatorArgument( "" )
{}

//

std::string ReDefine::GetFullString( const ScriptCode& code )
{
    std::string result;

    if( !code.Name.length() )
        return result;

    result = code.Name;

    if( code.Function || code.Arguments.size() )
    {
        result += "(";

        if( code.Arguments.size() )
            result += " " + TextGetJoined( code.Arguments, ", " ) + " ";

        result += ")";
    }

    if( code.Operator.length() && code.OperatorArgument.length() )
        result += " " + code.Operator + " " + code.OperatorArgument;

    return result;
}

void ReDefine::SetFullString( ScriptCode& code )
{
    code.Full = GetFullString( code );
}

//

void ReDefine::ProcessScript( const std::string& path, const std::string& filename, bool readOnly /* = false */ )
{
    std::vector<std::string> lines;
    if( !ReadFile( TextGetFilename( path, filename ), lines ) )
        return;

    Status.Process.Files++;
    Status.Current.Clear();

    Status.Current.File = filename;

    bool              updateFile = false;
    std::string       content;
    unsigned int      changed = 0;

    SStatus::SCurrent previous;

    for( auto& line : lines )
    {
        // update status
        Status.Process.Lines++;
        Status.Current.Line = line;
        Status.Current.LineNumber++;

        // skip empty/fully commented
        if( !line.size() || TextIsComment( line ) )
        {
            content += line + "\r\n";
            continue;
        }

        // save original line
        const std::string lineOld = line;

        // process variables
        for( const ScriptCode& var : TextGetVariables( line ) )
        {
            ScriptCode varUpdate = var;

            ProcessOperator( VariablesOperators, varUpdate );

            if( VariablesOperators.find( varUpdate.Name ) == VariablesOperators.end() && varUpdate.Operator.length() && varUpdate.OperatorArgument.length() )
                ProcessValueGuessing( varUpdate.OperatorArgument );

            // update if needed
            SetFullString( varUpdate );
            if( TextGetPacked( var.Full ) != TextGetPacked( varUpdate.Full ) )
                line = TextGetReplaced( line, var.Full, varUpdate.Full );
        }

        // process functions
        for( const ScriptCode& func : TextGetFunctions( line ) )
        {
            ScriptCode funcUpdate = func;

            ProcessFunctionArguments( funcUpdate );
            ProcessOperator( FunctionsOperators, funcUpdate );

            if( FunctionsOperators.find( funcUpdate.Name ) == FunctionsOperators.end() && funcUpdate.Operator.length() && funcUpdate.OperatorArgument.length() )
                ProcessValueGuessing( funcUpdate.OperatorArgument );

            // update line if needed
            SetFullString( funcUpdate );
            if( TextGetPacked( func.Full ) != TextGetPacked( funcUpdate.Full ) )
                line = TextGetReplaced( line, func.Full, funcUpdate.Full );
        }

        // process raw replacement
        ProcessRaw( line );

        // detect line change, ignore meaningless changes
        if( TextGetPacked( line ) != TextGetPacked( lineOld ) )
        {
            // modify status
            previous = Status.Current;
            Status.Current.Line.clear();

            // log changes
            ILOG( "@@" );

            Status.Current.Clear();
            // DEBUG( nullptr, "<- %s", TextGetPacked( lineOld ).c_str() );
            // DEBUG( nullptr, "-> %s", TextGetPacked( line ).c_str() );

            LOG( "<- %s", lineOld.c_str() );
            LOG( "-> %s", line.c_str() );

            // restore status
            Status.Current = previous;

            changed++;
            updateFile = true;
        }

        // we did it, rotators!
        content += line + "\r\n";
    }

    Status.Current.Clear();

    if( readOnly )
        return;

    if( updateFile )
    {
        std::ofstream file;
        file.open( TextGetFilename( path, filename ), std::ios::out );

        if( file.is_open() )
        {
            file << content;
            file.close();

            Status.Process.FilesChanged++;
            Status.Process.LinesChanged += changed;
        }
        else
            WARNING( __FUNCTION__, "cannot write file<%s>", TextGetFilename( path, filename ) );
    }
}
