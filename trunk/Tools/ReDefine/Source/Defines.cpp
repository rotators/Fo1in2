#include "FOClassic/Ini.h"

#include "ReDefine.h"

ReDefine::Header::Header( const std::string& filename, const std::string& type, const std::string& prefix, const std::string& group ) :
    Filename( filename ),
    Type( type ),
    Prefix( prefix ),
    Group( group )
{}

//

void ReDefine::FinishDefines()
{
    Headers.clear();
    RegularDefines.clear();
    VirtualDefines.clear();
}

bool ReDefine::ReadConfigDefines( const std::string& section )
{
    FinishDefines();

    if( !Config->IsSection( section ) )
    {
        WARNING( __FUNCTION__, "config section<%s> is missing", section.c_str() );
        return false;
    }

    std::vector<std::string> types;
    if( !Config->GetSectionKeys( section, types, true ) )
    {
        WARNING( __FUNCTION__, "config section<%s> is empty", section.c_str() );
        return false;
    }

    for( const auto& type : types )
    {
        std::vector<std::string> values = Config->GetStrVec( section, type );

        if( values.size() < 2 || values.size() > 3 )
        {
            WARNING( __FUNCTION__, "invalid setting<[%s]->%s>", section.c_str(), type.c_str() );
            continue;
        }

        Headers.push_back( Header( values[0], type, values[1], values.size() == 3 ? values[2] : std::string() ) );
    }

    return true;
}

bool ReDefine::IsDefineType( const std::string& type )
{
    return RegularDefines.find( type ) != RegularDefines.end() || VirtualDefines.find( type ) != VirtualDefines.end();
}

bool ReDefine::ProcessHeader( const std::string& path, const ReDefine::Header& header )
{
    if( IsDefineType( header.Type ) )
    {
        WARNING( __FUNCTION__, "define type<%s> already in use", header.Type.c_str() );
        return false;
    }

    // read content
    std::vector<std::string> lines;
    if( !ReadFile( path + std::string( "/" ) + header.Filename, lines ) )
        return false;

    // update status
    Status.Current.Clear();
    Status.Current.File = header.Filename;
    Status.Current.LineNumber = 0;

    // cache patterns
    std::regex  reParen = TextGetDefinePattern( header.Prefix, true );
    std::regex  reNoParen = TextGetDefinePattern( header.Prefix, false );

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
            if( RegularDefines[header.Type].find( value ) != RegularDefines[header.Type].end() )
            {
                WARNING( nullptr, "value<%d> already used by define<%s>, current define<%s> ignored", value, RegularDefines[header.Type][value].c_str(), name.c_str() );
                continue;
            }

            RegularDefines[header.Type][value] = name;

            if( !header.Group.empty() )
                VirtualDefines[header.Group].push_back( header.Type );
        }
    }

    Status.Current.Clear();

    LOG( "Process %s ... %u %s define%s%s%s",
         header.Filename.c_str(),
         RegularDefines[header.Type].size(),
         header.Prefix.c_str(),
         RegularDefines[header.Type].size() != 1 ? "s" : "",
         !header.Group.empty() ? " +> " : "",
         header.Group.c_str()
         );

    return true;
}
