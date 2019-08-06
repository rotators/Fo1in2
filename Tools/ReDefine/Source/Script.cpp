#include <fstream>

#include "FOClassic/Ini.h"

#include "ReDefine.h"

ReDefine::ScriptCode::ScriptCode() : ScriptCode( nullptr )
{}

ReDefine::ScriptCode::ScriptCode( ReDefine* parent ) :
    Parent( parent ),
    File( nullptr ),
    Flags( 0 ),
    Full( "" ),
    Name( "" ),
    Arguments(),
    ArgumentsTypes(),
    Operator( "" ),
    OperatorArgument( "" )
{}

bool ReDefine::ScriptCode::IsFlag( unsigned int flag ) const
{
    return (Flags & flag) != 0;
}

void ReDefine::ScriptCode::SetFlag( unsigned int flag )
{
    Flags = Flags | flag;
}

void ReDefine::ScriptCode::UnsetFlag( unsigned int flag )
{
    Flags = (Flags | flag) ^ flag;
}

//

bool ReDefine::ScriptCode::IsFunction( const char* caller ) const
{
    if( Name.empty() )
    {
        if( caller )
            Parent->WARNING( caller, "name not set" );

        return false;
    }

    if( !IsFlag( SCRIPT_CODE_FUNCTION ) )
    {
        if( caller )
            Parent->WARNING( caller, "script code<%s> is not a function", Name.c_str() );

        return false;
    }

    return true;
}

bool ReDefine::ScriptCode::IsFunctionKnown( const char* caller ) const
{
    if( !Parent )
        return false;

    if( !IsFunction( caller ) )
        return false;

    if( Parent->FunctionsArguments.find( Name ) == Parent->FunctionsArguments.end() )
    {
        if( caller )
            Parent->WARNING( caller, "function<%s> must be added to configuration before using this action", Name.c_str() );

        return false;
    }

    return true;
}

//

bool ReDefine::ScriptCode::GetINDEX( const char* caller, const std::string& value, unsigned int& val ) const
{
    if( !Parent )
        return false;

    unsigned int tmp;
    if( !GetUINT( caller, value, tmp, "INDEX" ) )
        return false;

    if( tmp >= Arguments.size() )
    {
        if( caller )
            Parent->WARNING( caller, "INDEX<%u> out of range", tmp );

        return false;
    }

    val = tmp;
    return true;
}

bool ReDefine::ScriptCode::GetTYPE( const char* caller, const std::string& value, bool allowUnknown /* = true */ ) const
{
    if( !Parent )
        return false;

    if( value.empty() )
    {
        if( caller )
            Parent->WARNING( caller, "TYPE is empty" );

        return false;
    }

    if( allowUnknown && Parent->IsMysteryDefineType( value ) )
        return true;

    if( !Parent->IsDefineType( value ) )
    {
        if( caller )
            Parent->WARNING( caller, "unknown TYPE<%s>", value.c_str() );

        return false;
    }

    return true;
}

bool ReDefine::ScriptCode::GetUINT( const char* caller, const std::string& value, unsigned int& val, const std::string& name /* = "UINT" */ ) const
{
    if( !Parent )
        return false;

    int tmp = -1;
    if( !Parent->TextIsInt( value ) || !Parent->TextGetInt( value, tmp ) )
    {
        if( caller )
            Parent->WARNING( caller, "invalid %s<%s>", name.c_str(), value.c_str() );

        return false;
    }

    if( tmp < 0 )
    {
        if( caller )
            Parent->WARNING( caller, "invalid %s<%s> : value < 0", name.c_str(), value.c_str() );

        return false;
    }

    val = tmp;
    return true;
}


// checks if given edit action exists before trying to call it
// as EditIf/EditDo should be free to modify by main application at any point,
// it can use EditIf["IfThing"](...) like there's no tomorrow, but ReDefine class doing same thing is Bad Idea (TM)

bool ReDefine::ScriptCode::CallEditIf( const std::string& name, std::vector<std::string> values /* = std::vector<std::string>() */ ) const
{
    auto it = Parent->EditIf.find( name );
    if( it == Parent->EditIf.end() )
    {
        Parent->WARNING( __FUNCTION__, "script action condition<%s> not found", name.c_str() );
        return false;
    }

    return it->second( *this, values );
}

bool ReDefine::ScriptCode::CallEditDo( const std::string& name, std::vector<std::string> values /* = std::vector<std::string>() */ )
{
    auto it = Parent->EditDo.find( name );
    if( it == Parent->EditDo.end() )
    {
        Parent->WARNING( __FUNCTION__, "script action result<%s> not found", name.c_str() );
        return false;
    }

    return it->second( *this, values );
}

//

ReDefine::ScriptEdit::ScriptEdit() :
    Debug( false ),
    Name( "" ),
    Conditions(),
    Results()
{}

// script edit conditions

// ? IfArgumentIs:INDEX,DEFINE
// ? IfArgumentIs:INDEX,DEFINE,TYPE
static bool IfArgumentIs( const ReDefine::ScriptCode& code, const std::vector<std::string>& values )
{
    if( values.size() < 2 || values[0].empty() || values[1].empty() )
        return false;

    if( !code.IsFunctionKnown( __FUNCTION__ ) )
        return false;

    unsigned int idx;
    if( !code.GetINDEX( __FUNCTION__, values[0], idx ) )
        return false;

    if( code.Parent->TextIsInt( code.Arguments[idx] ) )
    {
        int         val = -1;
        std::string type = code.ArgumentsTypes[idx], value;

        if( values.size() >= 3 )
        {
            if( !code.GetTYPE( __FUNCTION__, values[2] ) )
                type = values[2];
            else
                return false;
        }

        if( !code.Parent->TextGetInt( code.Arguments[idx], val ) || !code.Parent->GetDefineName( type, val, value ) )
            return false;

        // code.Parent->DEBUG( __FUNCTION__, "parsed compare: %s == %s", value.c_str(), values[1].c_str() );
        return value == values[1];
    }

    // code.Parent->DEBUG( __FUNCTION__, "raw compare: %s == %s", code.Arguments[idx].c_str(), values[1].c_str() );
    return code.Arguments[idx] == values[1];
}

// ? IfArgumentValue:INDEX,STRING
static bool IfArgumentValue( const ReDefine::ScriptCode& code, const std::vector<std::string>& values )
{
    if( values.size() < 2 || values[0].empty() || values[1].empty() )
        return false;

    unsigned int idx = -1;
    if( !code.GetINDEX( __FUNCTION__, values[0], idx ) )
        return false;

    return code.Arguments[idx] == values[1];
}

// ? IfEdited
static bool IfEdited( const ReDefine::ScriptCode& code, const std::vector<std::string>& )
{
    return code.IsFlag( ReDefine::SCRIPT_CODE_EDITED );
}

// ? IfFileDefined:STRING
static bool IfFileDefined( const ReDefine::ScriptCode& code, const std::vector<std::string>& values )
{
    if( values.size() < 1 || values[0].empty() )
        return false;

    return std::find( code.File->Defines.begin(), code.File->Defines.end(), values[0] ) != code.File->Defines.end();
}

// ? IfFileName:STRING
static bool IfFileName( const ReDefine::ScriptCode& code, const std::vector<std::string>& values )
{
    if( values.size() < 1 || values[0].empty() )
        return false;

    return code.Parent->Status.Current.File == values[0];
}

// ? IfFunction
// ? IfFunction:STRING
// > IfName
static bool IfFunction( const ReDefine::ScriptCode& code, const std::vector<std::string>& values )
{
    if( !code.IsFlag( ReDefine::SCRIPT_CODE_FUNCTION ) )
        return false;

    if( values.size() )
        return code.CallEditIf( "IfName", { values[0] } );

    return true;
}

// ? IfName:STRING
static bool IfName(  const ReDefine::ScriptCode& code, const std::vector<std::string>& values )
{
    if( values.size() < 1 || values[0].empty() )
        return false;

    return code.Name == values[0];
}

// ? IfNotEdited
static bool IfNotEdited(  const ReDefine::ScriptCode& code, const std::vector<std::string>& )
{
    return !code.IsFlag( ReDefine::SCRIPT_CODE_EDITED );
}

// ? IfOperator
static bool IfOperator(  const ReDefine::ScriptCode& code, const std::vector<std::string>& )
{
    return code.Operator.length() > 0;
}

// ? IfOperatorName:STRING
static bool IfOperatorName(  const ReDefine::ScriptCode& code, const std::vector<std::string>& values )
{
    if(  values.size() < 1 || values[0].empty() || !code.Operator.length() )
        return false;

    return code.Parent->GetOperatorName( code.Operator ) == values[0];
}

// ? IfOperatorValue:STRING
static bool IfOperatorValue(  const ReDefine::ScriptCode& code, const std::vector<std::string>& values )
{
    if( values.size() < 1 || values[0].empty() || !code.OperatorArgument.length() )
        return false;

    return code.OperatorArgument == values[0];
}

// ? IfVariable
// ? IfVariable:STRING
// >IfName
static bool IfVariable(  const ReDefine::ScriptCode& code, const std::vector<std::string>& values )
{
    if( code.IsFlag( ReDefine::SCRIPT_CODE_FUNCTION ) )
        return false;

    if( values.size() )
        return code.CallEditIf( "IfName", { values[0] } );

    return true;
}

// script edit results

// ? DoArgumentsSetType:INDEX,TYPE
static bool DoArgumentSetType(  ReDefine::ScriptCode& code, const std::vector<std::string>& values )
{
    if(  values.size() < 2 || values[0].empty() || values[1].empty() || !code.IsFlag( ReDefine::SCRIPT_CODE_FUNCTION ) )
        return false;

    unsigned int idx;
    if( !code.GetINDEX( __FUNCTION__, values[0], idx ) )
        return false;


    code.ArgumentsTypes[idx] = values[1];

    return true;
}

// ? DoArgumentsClear
static bool DoArgumentsClear(  ReDefine::ScriptCode& code, const std::vector<std::string>& )
{
    code.Arguments.clear();
    code.ArgumentsTypes.clear();

    return true;
}

// ? DoArgumentsErase:INDEX
static bool DoArgumentsErase(  ReDefine::ScriptCode& code, const std::vector<std::string>& values  )
{
    if( !values.size() )
        return false;

    unsigned int idx;
    if( !code.GetINDEX( __FUNCTION__, values[0], idx ) )
        return false;

    code.Arguments.erase( code.Arguments.begin() + idx );
    code.ArgumentsTypes.erase( code.ArgumentsTypes.begin() + idx );

    return true;
}

// ? DoArgumentsMoveBack:INDEX
// > DoArgumentsErase
// > DoArgumentsPushBack
static bool DoArgumentsMoveBack( ReDefine::ScriptCode& code, const std::vector<std::string>& values )
{
    if( values.empty() )
        return false;

    unsigned int idx;
    if( !code.GetINDEX( __FUNCTION__, values[0], idx ) )
        return false;

    std::string arg = code.Arguments[idx], type = code.ArgumentsTypes[idx];

    if( !code.CallEditDo( "DoArgumentsErase", { values[0] } ) )
        return false;

    if( !code.CallEditDo( "DoArgumentsPushBack", { arg, type } ) )
        return false;

    return true;
}

// ? DoArgumentsMoveFront:INDEX
// > DoArgumentsErase
// > DoArgumentsPushFront
static bool DoArgumentsMoveFront( ReDefine::ScriptCode& code, const std::vector<std::string>& values )
{
    if( values.empty() )
        return false;

    unsigned int idx;
    if( !code.GetINDEX( __FUNCTION__, values[0], idx ) )
        return false;

    std::string argument = code.Arguments[idx], type = code.ArgumentsTypes[idx];

    if( !code.CallEditDo( "DoArgumentsErase", { values[0] } ) )
        return false;

    if( !code.CallEditDo( "DoArgumentsPushFront", { argument, type } ) )
        return false;

    return true;
}

// ? DoArgumentsPushBack:STRING
// ? DoArgumentsPushBack:STRING,TYPE
static bool DoArgumentsPushBack( ReDefine::ScriptCode& code, const std::vector<std::string>& values )
{
    if( !values.size() || values[0].empty() )
        return false;

    std::string type = values.size() >= 2 ? values[1] : "?";
    if( !code.GetTYPE( __FUNCTION__, type, true ) )
        return false;

    code.Arguments.push_back( values[0] );
    code.ArgumentsTypes.push_back( type );

    return true;
}

// ? DoArgumentsPushFront:STRING,
// ? DoArgumentsPushFront:STRING,TYPE
static bool DoArgumentsPushFront( ReDefine::ScriptCode& code, const std::vector<std::string>& values  )
{
    if( !values.size() || values[0].empty() )
        return false;

    std::string type = values.size() >= 2 ? values[1] : "?";
    if( !code.GetTYPE( __FUNCTION__, type, true ) )
        return false;

    code.Arguments.insert( code.Arguments.begin(), values[0] );
    code.ArgumentsTypes.insert( code.ArgumentsTypes.begin(), type );

    return true;
}

// ? DoArgumentsResize:UINT
// > DoArgumentsClear
static bool DoArgumentsResize( ReDefine::ScriptCode& code, const std::vector<std::string>& values  )
{
    if(  !values.size() || values[0].empty() )
        return false;

    unsigned int size;
    if( !code.GetUINT( __FUNCTION__, values[0], size ) )
        return false;

    if( !size )
        return code.CallEditDo( "DoArgumentsClear", {} );

    code.Arguments.resize( size );
    code.ArgumentsTypes.resize( size );

    return true;
}

// ? DoFunction
// ? DoFunction:STRING
// > DoNameSet
static bool DoFunction(  ReDefine::ScriptCode& code, const std::vector<std::string>& values )
{
    code.SetFlag( ReDefine::SCRIPT_CODE_FUNCTION );

    if( values.size() )
    {
        if( !code.CallEditDo( "DoNameSet", { values[0] } ) )
            return false;
    }

    return true;
}

static bool DoLogCurrentLine( ReDefine::ScriptCode& code, const std::vector<std::string>& values )
{
    ReDefine::SStatus::SCurrent previous = code.Parent->Status.Current;
    code.Parent->Status.Current.Line.clear();

    if( values.size() && values[0].length() )
    {

        if( values[0] == "DEBUG" )
        {
            code.Parent->DEBUG( nullptr, "%%%%" );
            code.Parent->Status.Current.Clear();
            code.Parent->DEBUG( nullptr, "   %s", previous.Line.c_str() );
        }
        else if( values[0] == "WARNING" )
        {
            code.Parent->WARNING( nullptr, "%%%%" );
            code.Parent->Status.Current.Clear();
            code.Parent->WARNING( nullptr, "   %s", previous.Line.c_str() );
        }

    }
    else
    {
        code.Parent->ILOG( "%%%%" );
        code.Parent->LOG( "   %s", previous.Line.c_str() );
    }

    code.Parent->Status.Current = previous;

    return true;
}

// ? DoNameSet:STRING
static bool DoNameSet( ReDefine::ScriptCode& code, const std::vector<std::string>& values )
{
    if( !values.empty() && !values[0].empty() )
        return false;

    code.Name = values[0];

    return true;
}

// ? DoOperatorClear
static bool DoOperatorClear( ReDefine::ScriptCode& code, const std::vector<std::string>& )
{
    code.Operator.clear();
    code.OperatorArgument.clear();

    return true;
}

// ? DoVariable
// ? DoVariable:STRING
// > DoNameSet
static bool DoVariable(  ReDefine::ScriptCode& code, const std::vector<std::string>& values )
{
    code.UnsetFlag( ReDefine::SCRIPT_CODE_FUNCTION );

    if( !code.CallEditDo( "DoArgumentsClear" ) )
        return false;

    if( !values.empty() )
    {
        if( !code.CallEditDo( "DoNameSet", { values[0] } ) )
            return false;
    }

    return true;
}

//

void ReDefine::InitScript()
{
    // must start with "If"
    EditIf["IfArgumentIs"] = &IfArgumentIs;
    EditIf["IfArgumentValue"] = &IfArgumentValue;
    EditIf["IfEdited"] = &IfEdited;
    EditIf["IfFileDefined"] = &IfFileDefined;
    EditIf["IfFileName"] = &IfFileName;
    EditIf["IfFunction"] = &IfFunction;
    EditIf["IfName"] = &IfName;
    EditIf["IfNotEdited"] = &IfNotEdited;
    EditIf["IfOperator"] = &IfOperator;
    EditIf["IfOperatorName"] = &IfOperatorName;
    EditIf["IfOperatorValue"] = &IfOperatorValue;
    EditIf["IfVariable"] = &IfVariable;

    // must start with "Do"
    EditDo["DoArgumentSetType"] = &DoArgumentSetType;
    EditDo["DoArgumentsClear"] = &DoArgumentsClear;
    EditDo["DoArgumentsErase"] = &DoArgumentsErase;
    EditDo["DoArgumentsMoveBack"] = &DoArgumentsMoveBack;
    EditDo["DoArgumentsMoveFront"] = &DoArgumentsMoveFront;
    EditDo["DoArgumentsPushBack"] = &DoArgumentsPushBack;
    EditDo["DoArgumentsPushFront"] = &DoArgumentsPushFront;
    EditDo["DoArgumentsResize"] = &DoArgumentsResize;
    EditDo["DoFunction"] = &DoFunction;
    EditDo["DoLogCurrentLine"] = &DoLogCurrentLine;
    EditDo["DoNameSet"] = &DoNameSet;
    EditDo["DoOperatorClear"] = &DoOperatorClear;
    EditDo["DoVariable"] = &DoVariable;
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
    EditDebug = false;
}

// reading

bool ReDefine::ReadConfigScript( const std::string& sectionPrefix )
{
    FinishScript( false );

    std::vector<std::string> sections;
    if( !Config->GetSections( sections ) )
    {
        WARNING( __FUNCTION__, "config is empty (?)" );
        return false;
    }

    for( const auto& section : sections )
    {
        // [???] //
        if( section.substr( 0, sectionPrefix.length() ) != sectionPrefix )
            continue;
        // [Script] or [Script:CATEGORY] //
        else if( section == sectionPrefix || (section.length() >= sectionPrefix.length() + 2 && section.substr( sectionPrefix.length(), 1 ) == ":") )
        {
            // DEBUG( nullptr, "section<%s>", section.c_str() );

            std::string category;
            if( section != sectionPrefix )
                category = section.substr( sectionPrefix.length() + 1 ) + ":";

            std::vector<std::string> keys;
            if( !Config->GetSectionKeys( section, keys, true ) )
            {
                WARNING( __FUNCTION__, "config section<%s> is empty", section.c_str() );
                return true;
            }

            for( const auto& name : keys )
            {
                if( Config->IsSectionKeyEmpty( section, name ) )
                    continue;

                ScriptEdit edit;
                edit.Name = category + name;

                bool ignore = false, before = false, after = false;

                for( const auto& action : Config->GetStrVec( section, name ) )
                {
                    // split name from arguments
                    std::vector<std::string> vals;
                    std::vector<std::string> arg = TextGetSplitted( action, ':' );
                    if( !arg.size() )
                    {
                        DEBUG( __FUNCTION__, "IGNORE [%s]", action.c_str() );
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
                    {
                        ignore = true;
                        break;
                    }
                    else if( arg[0] == "DEBUG" )
                        edit.Debug = true;
                    else if( arg[0] == "RunBefore" )
                        before = true;
                    else if( arg[0] == "RunAfter" )
                        after = true;
                    else if( arg[0].length() >= 3 && arg[0].substr( 0, 2 ) == "If" )
                    {
                        ScriptEdit::Action condition;
                        condition.Name = arg[0];
                        condition.Values = vals;

                        edit.Conditions.push_back( condition );
                    }
                    else if( arg[0].length() >= 3 && arg[0].substr( 0, 2 ) == "Do" )
                    {
                        ScriptEdit::Action result;
                        result.Name = arg[0];
                        result.Values = vals;

                        edit.Results.push_back( result );
                    }
                    else
                    {
                        WARNING( __FUNCTION__, "script edit<%s> ignored : unknown action<%s>", name.c_str(), arg[0].c_str() );
                        ignore = true;
                        break;
                    }
                }

                // DEBUG( __FUNCTION__, "%s : before<%s> after<%s> condition<%u>, result<%u>", edit.Name.c_str(), edit.Before ? "true" : "false", edit.After ? "true" : "false", edit.Conditions.size(), edit.Results.size() );

                // "IGNORE" or error
                if( ignore )
                    continue;

                // validation

                if( !before && !after )
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

                if( before )
                    EditBefore.push_back( edit );
                if( after )
                    EditAfter.push_back( edit );
            }
        }
    }

    return true;
}

// utils

std::string ReDefine::GetFullString( const ScriptCode& code )
{
    std::string result;

    if( !code.Name.length() )
        return result;

    result = code.Name;

    if( code.IsFlag( SCRIPT_CODE_FUNCTION ) )
    {
        result += "(";

        if( code.Arguments.size() )
            result += " " + TextGetJoined( code.Arguments, ", " ) + " ";

        result += ")";
    }

    if( code.Operator.length() && code.OperatorArgument.length() )
    {
        result += " " + code.Operator + " " + code.OperatorArgument;
    }

    return result;
}

void ReDefine::SetFullString( ScriptCode& code )
{
    code.Full = GetFullString( code );
}


// processing

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

    ScriptFile*       file = new ScriptFile();

    std::smatch       match;
    std::regex        define( "^[\\t\\ ]*\\#define[\\t\\ ]+([A-Za-z0-9_]+)(?:$|[\\t\\ ]+.*$)" );

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

        std::string defineName, defineValue;
        if( std::regex_match( line, match, define ) )
        {
            file->Defines.push_back( match.str( 1 ) );
            // DEBUG( __FUNCTION__, "DEFINE [%s]", file->Defines.back().c_str() );
        }

        // save original line
        const std::string lineOld = line;

        // process variables
        for( const ScriptCode& var : TextGetVariables( line ) )
        {
            ScriptCode varUpdate = var;
            varUpdate.File = file;

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
            funcUpdate.File = file;

            // prepare function arguments types, required by some RunBefore edits
            auto it = FunctionsArguments.find( funcUpdate.Name );
            if( it != FunctionsArguments.end() )
                funcUpdate.ArgumentsTypes = it->second;
            else if( !funcUpdate.Arguments.empty() )
            {
                funcUpdate.ArgumentsTypes.resize( funcUpdate.Arguments.size() );
                std::fill( funcUpdate.ArgumentsTypes.begin(), funcUpdate.ArgumentsTypes.end(), "?" );
            }

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
    delete file;

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
    codeUpdate.Parent = this;

    ReDefine::SStatus::SCurrent                      previous = Status.Current;
    std::vector<std::pair<std::string, std::string>> changelog;

    for( const ScriptEdit& edit : edits )
    {
        const bool        editDebug = edit.Debug ? edit.Debug : EditDebug;

        bool              run = false, first = true;
        const std::string editString = "script edit<" + edit.Name + ">";
        std::string       log;

        // all conditions needs to be satisfied
        for( const ScriptEdit::Action& condition: edit.Conditions )
        {
            run = codeUpdate.CallEditIf( condition.Name, condition.Values );

            if( editDebug && ( (first && run) || !first ) )
                changelog.push_back( std::make_pair( editString + " " + condition.Name + (condition.Values.size() ? (":" + TextGetJoined( condition.Values, "," ) ) : ""), run ? "true" : "false" ) );

            if( !run )
                break;

            first = false;
        }

        if( !run )
            continue;

        first = true;

        // you are Result, you must Do
        for( const ScriptEdit::Action& result : edit.Results )
        {
            std::string before, after, log;

            if( editDebug )
            {
                log = editString + " " + result.Name + (result.Values.size() ? (":" + TextGetJoined( result.Values, "," ) ) : "");

                if( first )
                {
                    changelog.push_back( std::make_pair( editString + " script code", GetFullString( codeUpdate ) ) );
                    first = false;
                }
            }

            run = codeUpdate.CallEditDo( result.Name, result.Values );

            if( !run )
            {
                if( editDebug )
                {
                    changelog.push_back( std::make_pair( log, "(ERROR)" ) );
                    ProcessScriptEditChangelog( changelog );
                }

                WARNING( nullptr, "script edit<%s> aborted : result<%s> failed", edit.Name.c_str(), result.Name.c_str() );

                return;
            }

            if( editDebug )
                changelog.push_back( std::make_pair( log, GetFullString( codeUpdate ) ) );

            codeUpdate.SetFlag( SCRIPT_CODE_EDITED );
        }

    }

    if( !changelog.empty() )
        ProcessScriptEditChangelog( changelog );

    codeUpdate.Parent = nullptr;
    code = codeUpdate;
}

void ReDefine::ProcessScriptEditChangelog( const std::vector<std::pair<std::string, std::string>>& changelog )
{
    // ugh

    unsigned int max = 0;
    for( const auto& change : changelog )
    {
        if( change.first.length() > max )
            max = change.first.length();
    }

    SStatus::SCurrent previous = Status.Current;
    Status.Current.Clear();

    for( const auto& change : changelog )
    {
        std::string dots = std::string( (max - change.first.length() ) + 3, '.' );
        DEBUG( nullptr, "%s %s %s", change.first.c_str(), dots.c_str(), change.second.c_str() );
    }

    Status.Current = previous;
}
