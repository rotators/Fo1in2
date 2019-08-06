#include "FOClassic/Ini.h"

#include "ReDefine.h"

void ReDefine::FinishFunctions()
{
    FunctionsArguments.clear();
    FunctionsOperators.clear();
}

// reading

bool ReDefine::ReadConfigFunctions( const std::string& sectionPrefix )
{
    FinishFunctions();

    std::vector<std::string> sections;
    if( !Config->GetSections( sections ) )
        return true;

    for( const auto& section : sections )
    {
        // [???] //
        if( section.substr( 0, sectionPrefix.length() ) != sectionPrefix )
            continue;
        // [Function] //
        else if( section == sectionPrefix )
        {
            std::vector<std::string> keys;
            if( !Config->GetSectionKeys( section, keys ) )
            {
                WARNING( "config section<%s> is empty", section.c_str() );
                continue;
            }

            for( const auto& name : keys )
            {
                std::vector<std::string> types = Config->GetStrVec( section, name );
                if( !types.size() )
                {
                    WARNING( "config setting<%s->%s> is empty", section.c_str(), name.c_str() );
                    continue;
                }

                // type validation is part of ProcessHeaders(),
                // as at this point *Defines maps might not be initialized yet,
                FunctionsArguments[name] = types;
            }
        }
        // [FunctionOPERATOR]
        // see InitOperators() for valid values for OPERATOR
        else if( section.length() >= sectionPrefix.length() + 1 )
        {
            const std::string opName = section.substr( sectionPrefix.length(), section.length() - sectionPrefix.length() );

            // Operators map should be available at this point, if initialized correctly
            if( !IsOperatorName( opName ) )
            {
                DEBUG( __FUNCTION__, "config section<%s> ignored : substr<%s>", section.c_str(), section.substr( sectionPrefix.length(), 1 ).c_str() );
                continue;
            }

            std::vector<std::string> keys;
            if( !Config->GetSectionKeys( section, keys ) )
            {
                WARNING( "config section<%s> is empty", section.c_str() );
                continue;
            }

            for( const auto& function : keys )
            {
                if( Config->GetStrVec( section, function ).size() != 1 )
                    continue;

                std::string type = Config->GetStr( section, function );

                // type validation is part of ProcessHeaders(),
                // as at this point *Defines maps might not be initialized yet,
                FunctionsOperators[function][opName] = type;
            }
        }
    }

    return true;
}

// processing

void ReDefine::ProcessFunctionArguments( ReDefine::ScriptCode& function )
{
    // make sure function is preconfigured properly
    std::string  badArgs;
    unsigned int found = 0, expected = 0;

    // known functions
    auto it = FunctionsArguments.find( function.Name );
    if( it != FunctionsArguments.end() )
    {
        expected = it->second.size();

        if( expected != function.Arguments.size() )
        {
            badArgs = "arguments";
            found = function.Arguments.size();
        }
        else if( expected != function.ArgumentsTypes.size() )
        {
            badArgs = "arguments types";
            found = function.ArgumentsTypes.size();
        }
    }
    // unknown functions
    else
    {
        expected = function.Arguments.size();

        if( expected != function.ArgumentsTypes.size() )
        {
            badArgs = "arguments types";
            found = function.ArgumentsTypes.size();
        }
    }

    if( !badArgs.empty() )
    {
        WARNING( __FUNCTION__, "invalid number of function<%s> %s : found<%u> expected<%u>", function.Name.c_str(), badArgs.c_str(), found, expected );
        return;
    }

    // called so late to always detect count mismatch
    if( !function.Arguments.size() )
        return;

    for( unsigned int idx = 0, len = function.Arguments.size(); idx < len; idx++ )
    {
        if( function.ArgumentsTypes[idx].empty() ) // can happen by using DoArgumentsResize without DoArgumentChangeType or other edit combinations
        {
            WARNING( __FUNCTION__, "argument<%u> type not set", idx );
            continue;
        }
        else if( function.ArgumentsTypes[idx] == "?" ) // skip other mystery types
        {
            ProcessValueGuessing( function.Arguments[idx] );
            continue;
        }

        ProcessValue( function.ArgumentsTypes[idx], function.Arguments[idx] );
    }
}
