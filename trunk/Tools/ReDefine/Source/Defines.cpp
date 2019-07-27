#include "FOClassic/Ini.h"

#include "ReDefine.h"

// void ReDefine::InitDefines() {}

void ReDefine::FinishDefines()
{
    RegularDefines.clear();
    VirtualDefines.clear();
}

bool ReDefine::ReadConfigDefines()
{
    if( !Config->IsSection( "Defines" ) )
    {
        WARNING( __FUNCTION__, "config section<Defines> is missing" );
        return false;
    }

    std::vector<std::string> keys;

    if( !Config->GetSectionKeys( "Defines", keys, true ) )
    {
        WARNING( __FUNCTION__, "config section<Defines> is empty" );
        return false;
    }

    std::vector<std::string> values;
    for( auto& type : keys )
    {
        values = Config->GetStrVec( "Defines", type );

        if( values.size() == 2 )
            ReadDefines( values[0], type, values[1] );
        else if( values.size() == 3 )
            ReadDefines( values[0], type, values[1], values[2] );
        else
            WARNING( __FUNCTION__, "invalid setting<[Defines]->%s> :: %s", type.c_str(), Config->GetStr( "Defines", type ).c_str() );
    }

    return true;
}

bool ReDefine::ReadDefines( const std::string& filename, const std::string& type, const std::string& prefix, const std::string& group )
{
    if( type.empty() )
    {
        WARNING( __FUNCTION__, "missing type name" );
        return false;
    }
    else if( filename.empty() )
    {
        WARNING( __FUNCTION__, "missing filename : type<%s>", type.c_str() );
        return false;
    }
    else if( prefix.empty() )
    {
        WARNING( __FUNCTION__, "missing prefix : type<%s> filename<%s>", type.c_str(), filename.c_str() );
        return false;
    }

    if( RegularDefines.find( type ) != RegularDefines.end() || VirtualDefines.find( type ) != VirtualDefines.end() )
    {
        WARNING( __FUNCTION__, "define type<%s> already in use", type.c_str() );
        return false;
    }

    // read content
    std::vector<std::string> lines;
    if( !ReadFile( filename, lines ) )
        return false;

    // update status
    Status.Current.File = filename;
    Status.Current.LineNumber = 0;

    // cache patterns
    std::regex  reParen = TextGetDefinePattern( prefix, true );
    std::regex  reNoParen = TextGetDefinePattern( prefix, false );

    std::string name;
    int         value;

    for( const std::string& line : lines )
    {
        Status.Current.LineNumber++;

        // ignore random lines
        if( !TextIsDefine( line ) )
            continue;

        // find defines with given prefix
        if( TextGetDefine( line, reParen, name, value ) || TextGetDefine( line, reNoParen, name, value ) )
        {
            // human detection
            if( RegularDefines[type].find( value ) != RegularDefines[type].end() )
            {
                WARNING( nullptr, "value<%d> already used by define<%s>, current define<%s> ignored", value, RegularDefines[type][value].c_str(), name.c_str() );
                continue;
            }

            RegularDefines[type][value] = name;

            if( !group.empty() )
                VirtualDefines[group].push_back( type );
        }

    }

    Status.Current.Clear();

    LOG( "Reading %s... %u %s define%s%s%s", filename.c_str(), RegularDefines[type].size(), prefix.c_str(), RegularDefines[type].size() != 1 ? "s" : "", !group.empty() ? " -> " : "", group.c_str() );

    return true;
}
