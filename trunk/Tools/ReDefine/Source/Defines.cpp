#include "FOClassic/Ini.h"

#include "ReDefine.h"
#include "Defines.h"

bool ReDefine::ReadDefines( const std::string& path, const std::string& filename, const std::string& type, const std::string& prefix, const std::string& group )
{
    if( type.empty() )
    {
        WARNING( __FUNCTION__, "missing type name%s", "" );
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

    if( Defines.find( type ) != Defines.end() || VirtualDefines.find( type ) != VirtualDefines.end() )
    {
        WARNING( __FUNCTION__, "type<%s> already in use", type.c_str() );
        return false;
    }

    Ini header;
    header.KeepComments = true;
    header.KeepSectionsRaw = true;

    header.LoadFile( filename );

    for( auto& line : header.GetSectionRaw( "" ) )
    {
        if( line.empty() )
            continue;

        DEBUG( __FUNCTION__, line.c_str() );
    }

    return true;
}

void ReDefine::FinishDefines()
{
    Defines.clear();
    VirtualDefines.clear();
}
