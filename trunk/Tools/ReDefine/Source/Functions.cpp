#include "FOClassic/Ini.h"

#include "ReDefine.h"

ReDefine::Function::Function( const std::string& full, const std::string& name, const std::vector<std::string>& arguments /* = std::vector<std::string>() */, const std::string& op /* = std::string() */, const std::string& opArgument /* = std::string() */ ) :
    Full( full ),
    Name( name ),
    Arguments( arguments ),
    Operator( op ),
    OperatorArgument( opArgument )
{}

void ReDefine::FinishFunctions()
{
    FunctionsArguments.clear();
    FunctionsOperators.clear();
}

//

bool ReDefine::ReadConfigFunctions( const std::string& sectionPrefix )
{
    FinishFunctions();

    std::vector<std::string> sections;
    if( !Config->GetSections( sections ) )
        return true;

    for( const auto& section : sections )
    {
        if( section.length() < sectionPrefix.length() )
            continue;
        // [Function]
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
        else if( section.substr( 0, sectionPrefix.length() ) == sectionPrefix )
        {
            const std::string opName = section.substr( sectionPrefix.length(), section.length() - sectionPrefix.length() );

            // Operators map should be available at this point, if initialized correctly
            if( !IsOperatorName( opName ) )
            {
                DEBUG( __FUNCTION__, "config section<%s> ignored", section.c_str() );
                continue;
            }

            std::vector<std::string> keys;
            if( !Config->GetSectionKeys( section, keys ) )
            {
                WARNING( "config section<%s> is empty", section.c_str() );
                continue;
            }

            for( const auto& variable : keys )
            {
                if( Config->GetStrVec( section, variable ).size() != 1 )
                    continue;

                std::string type = Config->GetStr( section, variable );

                // type validation is part of ProcessHeaders(),
                // as at this point *Defines maps might not be initialized yet,
                FunctionsOperators[variable][opName] = type;
            }
        }
    }

    return true;
}

//

std::string ReDefine::GetFullString( const ReDefine::Function& function )
{
    std::string result = function.Name;

    result += "(";

    if( function.Arguments.size() )
        result += " " + TextGetJoined( function.Arguments, ", " ) + " ";

    result += ")";

    if( function.Operator.length() && function.OperatorArgument.length() )
        result += " " + function.Operator + " " + function.OperatorArgument;

    return result;
}

//

void ReDefine::ProcessFunctionArguments( ReDefine::Function& function )
{
    auto it = FunctionsArguments.find( function.Name );
    if( it == FunctionsArguments.end() )
        return;

    if( it->second.size() != function.Arguments.size() )
    {
        WARNING( __FUNCTION__, "invalid number of arguments : found<%u> expected<%u>", function.Arguments.size(), it->second.size() );

        return;
    }

    if( !function.Arguments.size() )
        return;

    for( unsigned int idx = 0, len = function.Arguments.size(); idx < len; idx++ )
    {
        if( it->second[idx] == "?" )
        {
            ProcessValueGuessing( function.Arguments[idx] );
            continue;
        }

        ProcessValue( it->second[idx], function.Arguments[idx] );
    }
}
