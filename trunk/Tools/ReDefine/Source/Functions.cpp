#include "FOClassic/Ini.h"

#include "ReDefine.h"

void ReDefine::FinishFunctions()
{
    FunctionsArguments.clear();
    FunctionsOperators.clear();
}

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
        else if( section == sectionPrefix )
        {
            DEBUG( __FUNCTION__, "TODO %s", section.c_str() );
        }
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
