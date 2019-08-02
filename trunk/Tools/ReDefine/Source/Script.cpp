#include <fstream>

#include "FOClassic/Ini.h"

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

ReDefine::ScriptEdit::ScriptEdit() :
    Name( "" ),
    Before( false ),
    After( false ),
    Conditions(),
    Results()
{}

static bool IfFunction( ReDefine*, const std::vector<std::string>&, const ReDefine::ScriptCode& code )
{
    return code.Function == true;
}

static bool IfVariable( ReDefine*, const std::vector<std::string>&, const ReDefine::ScriptCode& code )
{
    return code.Function == false;
}

static bool IfName( ReDefine*, const std::vector<std::string>& values, const ReDefine::ScriptCode& code )
{
    if( values.size() < 1 || !values[0].size() )
        return false;

    return code.Name == values[0];
}

static bool IfArgumentValue( ReDefine* self, const std::vector<std::string>& values, const ReDefine::ScriptCode& code )
{
    if( !self || values.size() < 2 || !values[0].size() || !values[1].size() )
        return false;

    int idx = -1;
    if( !self->TextIsInt( values[0] ) || !self->TextGetInt( values[0], idx ) || idx < 0 )
        return false;

    if( code.Arguments.size() < (unsigned int)idx + 1 )
        return false;

    return code.Arguments[idx] == values[1];
}

static void DoNameChange( ReDefine*, const std::string& value, ReDefine::ScriptCode& code )
{
    if( !value.length() )
        return;

    code.Name = value;
}

static void DoArgumentsResize( ReDefine* self, const std::string& value, ReDefine::ScriptCode& code )
{
    int size = -1;
    if( !value.size() || !self->TextIsInt( value ) || !self->TextGetInt( value, size ) || size < 0 )
        return;

    code.Arguments.resize( size );
}

//

void ReDefine::InitScript()
{
    // must start with "If"
    EditIf["IfFunction"] = &IfFunction;
    EditIf["IfVariable"] = &IfVariable;
    EditIf["IfName"] = &IfName;
    EditIf["IfArgumentValue"] = &IfArgumentValue;

    // must start with "Do"
    EditDo["DoNameChange"] = &DoNameChange;
    EditDo["DoArgumentsResize"] = &DoArgumentsResize;
}

void ReDefine::FinishScript( bool finishCallbacks /* = true */ )
{
    if( finishCallbacks ) // we kinda need them between config resets :)
    {
        EditIf.clear();
        EditDo.clear();
    }

    EditBefore.clear();
    EditAfter.clear();
}

//

bool ReDefine::ReadConfigScript( const std::string& sectionPrefix )
{
    FinishScript( false );

    if( !Config->IsSection( sectionPrefix ) )
        return true;

    std::vector<std::string> keys;
    if( !Config->GetSectionKeys( sectionPrefix, keys, true ) )
    {
        WARNING( __FUNCTION__, "config section<%s> is empty", sectionPrefix.c_str() );
        return true;
    }

    for( const auto& name : keys )
    {
        if( Config->IsSectionKeyEmpty( sectionPrefix, name ) )
            continue;

        ScriptEdit edit;
        edit.Name = name;

        bool ignore = false;

        for( const auto& action : Config->GetStrVec( sectionPrefix, name ) )
        {
            // split name from arguments
            std::vector<std::string> vals;
            std::vector<std::string> arg = TextGetSplitted( action, ':' );
            if( !arg.size() )
            {
                ignore = true;
                break;
            }
            else if( arg.size() == 1 )
            {}
            else if( arg.size() == 2 )
                vals = TextGetSplitted( arg[1], ',' );
            else
            {
                WARNING( __FUNCTION__, "script edit<%s> ignored : invalid action<%s>", name.c_str(), action.c_str() );
                ignore = true;
                break;
            }

            // DEBUG( __FUNCTION__, "%s -> [%s]=[%s]", name.c_str(), arg[0].c_str(), TextGetJoined( vals, "|" ).c_str() );

            if( arg[0] == "IGNORE" )
                ignore = true;
            else if( arg[0] == "RunBefore" )
                edit.Before = true;
            else if( arg[0] == "RunAfter" )
                edit.After = true;
            else if( arg[0].substr( 0, 2 ) == "If" )
            {
                ScriptEdit::Condition condition;
                condition.Name = arg[0];
                condition.Values = vals;

                edit.Conditions.push_back( condition );
            }
            else if( arg[0].substr( 0, 2 ) == "Do" )
            {
                ScriptEdit::Result result;
                result.Name = arg[0];
                if( arg.size() >= 2 )
                    result.Value = arg[1];

                edit.Results.push_back( result );
            }
            else
            {
                WARNING( __FUNCTION__, "script edit<%s> ignored : unknown action<%s>", name.c_str(), arg[0].c_str() );
                break;
            }
        }

        // DEBUG( __FUNCTION__, "%s : before<%s> after<%s> condition<%u>, result<%u>", edit.Name.c_str(), edit.Before ? "true" : "false", edit.After ? "true" : "false", edit.Conditions.size(), edit.Results.size() );

        // validation

        if( !edit.Before && !edit.After )
        {
            WARNING( nullptr, "script edit<%s> ignored : at least one of 'RunBefore' or 'RunAfter' must be set", edit.Name.c_str() );
            ignore = true;
        }

        if( !edit.Conditions.size() )
        {
            WARNING( nullptr, "script edit<%s> ignored : no conditions", edit.Name.c_str() );
            ignore = true;
        }

        if( !edit.Results.size() )
        {
            WARNING( nullptr, "script edit<%s> ignored : no results", edit.Name.c_str() );
            ignore = true;
        }

        if( ignore )
            continue;

        if( edit.Before )
            EditBefore.push_back( edit );
        if( edit.After )
            EditAfter.push_back( edit );
    }

    return true;
}

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
    unsigned int      changes = 0;

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

            // "preprocess" variable
            ProcessScriptEdit( EditBefore, varUpdate );

            ProcessOperator( VariablesOperators, varUpdate );

            // try to guess define name for right part only if variable isn't known
            if( VariablesOperators.find( varUpdate.Name ) == VariablesOperators.end() && varUpdate.Operator.length() && varUpdate.OperatorArgument.length() )
                ProcessValueGuessing( varUpdate.OperatorArgument );

            // "postprocess" variable
            ProcessScriptEdit( EditAfter, varUpdate );

            // update if needed
            SetFullString( varUpdate );
            if( TextGetPacked( var.Full ) != TextGetPacked( varUpdate.Full ) )
                line = TextGetReplaced( line, var.Full, varUpdate.Full );
        }

        // process functions
        for( const ScriptCode& func : TextGetFunctions( line ) )
        {
            ScriptCode funcUpdate = func;

            // "preprocess" function
            ProcessScriptEdit( EditBefore, funcUpdate );

            ProcessFunctionArguments( funcUpdate );
            ProcessOperator( FunctionsOperators, funcUpdate );

            // try to guess define name for right part only if function isn't known
            // guessing arguments is done by ProcessFunctionArguments()
            if( FunctionsOperators.find( funcUpdate.Name ) == FunctionsOperators.end() && funcUpdate.Operator.length() && funcUpdate.OperatorArgument.length() )
                ProcessValueGuessing( funcUpdate.OperatorArgument );

            // "postprocess" function
            ProcessScriptEdit( EditAfter, funcUpdate );

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
            // log changes
            // requires messing with Status.Current so log functions won't add unwanted info
            previous = Status.Current;
            Status.Current.Line.clear();
            ILOG( "@@" );

            Status.Current.Clear();
            // DEBUG( nullptr, "<- %s", TextGetPacked( lineOld ).c_str() );
            // DEBUG( nullptr, "-> %s", TextGetPacked( line ).c_str() );

            LOG( "<- %s", lineOld.c_str() );
            LOG( "-> %s", line.c_str() );

            Status.Current = previous;

            // update file status
            changes++;
            updateFile = true;
        }

        // we did it, Rotators!
        content += line + "\r\n";
    }

    Status.Current.Clear();

    if( updateFile )
    {
        Status.Process.FilesChanges++;
        Status.Process.LinesChanges += changes;
    }

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
        }
        else
        {
            WARNING( __FUNCTION__, "cannot write file<%s>", TextGetFilename( path, filename ) );

            Status.Process.FilesChanges--;
            Status.Process.LinesChanges -= changes;
        }
    }
}

void ReDefine::ProcessScriptEdit( const std::vector<ReDefine::ScriptEdit>& edits, ReDefine::ScriptCode& code )
{
    // editing must always works on backup to prevent massive screwup,
    // original code will be updated only if there's no problems with *any* condition/result function
    // that plus (intentional) massive spam in warning log should be enough to get user's attention (yeah, i don't belive that eiher... :P)
    ScriptCode codeUpdate = code;

    for( const ScriptEdit& edit : edits )
    {
        // DEBUG( __FUNCTION__, "edit %s<%s>", codeUpdate.Function ? "function" : "variable", GetFullString( codeUpdate ).c_str() );

        bool run = true;

        // all conditions needs to be satisfied
        for( const ScriptEdit::Condition& condition : edit.Conditions )
        {
            auto _if = EditIf.find( condition.Name );
            if( _if == EditIf.end() )
            {
                WARNING( __FUNCTION__, "script edit<%s> aborted : unknown condition<%s>", edit.Name.c_str(), condition.Name.c_str() );
                return;
            }

            bool ok = _if->second( this, condition.Values, codeUpdate );
            // DEBUG( __FUNCTION__, "condition<%s(%s)> = %s", condition.Name.c_str(), TextGetJoined( condition.Values, "," ).c_str(), ok ? "true" : "false" );

            if( !ok )
            {
                run = false;
                break;
            }
        }

        if( !run )
        {
            // DEBUG( __FUNCTION__, "skipped script edit<%s>", edit.Name.c_str() );
            continue;
        }

        // you are Result, you must Do
        for( const ScriptEdit::Result& result : edit.Results )
        {
            auto _do = EditDo.find( result.Name );
            if( _do == EditDo.end() )
            {
                WARNING( __FUNCTION__, "script edit<%s> aborted : unknown result<%s>", edit.Name.c_str(), result.Name.c_str() );
                return;
            }

            _do->second( this, result.Value, codeUpdate );
        }
    }

    code = codeUpdate;
}
