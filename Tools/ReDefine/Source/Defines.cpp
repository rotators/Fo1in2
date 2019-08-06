#include "FOClassic/Ini.h"

#include "ReDefine.h"

static std::regex IsSimpleMath( "^([\\-]?[0-9]+)[\\t\\ ]*(\\*|\\/|\\+|\\-)[\\t\\ ]*([\\-]?[0-9]+)$" );

ReDefine::Header::Header( const std::string& filename, const std::string& type, const std::string& prefix, const std::string& suffix, const std::string& group ) :
    Filename( filename ),
    Type( type ),
    Prefix( prefix ),
    Suffix( suffix ),
    Group( group )
{}

//

void ReDefine::FinishDefines()
{
    Headers.clear();
    RegularDefines.clear();
    ProgramDefines.clear();
    VirtualDefines.clear();
}

// reading

bool ReDefine::ReadConfigDefines( const std::string& sectionPrefix )
{
    FinishDefines();

    std::vector<std::string> sections;
    if( !Config->GetSections( sections ) )
    {
        WARNING( __FUNCTION__, "config is empty (?)" );
        return false;
    }

    bool definesFound = false;

    for( const auto& section : sections )
    {
        // [???] //
        if( section.substr( 0, sectionPrefix.length() ) != sectionPrefix )
            continue;
        // [Defines] //
        else if( section == sectionPrefix )
        {
            definesFound = true;
            std::vector<std::string> keys;

            if( !Config->GetSectionKeys( section, keys, true ) )
            {
                WARNING( __FUNCTION__, "config section<%s> is empty", section.c_str() );
                return false;
            }

            for( const auto& type : keys )
            {
                std::vector<std::string> values = Config->GetStrVec( section, type );

                if( values.size() < 2 || values.size() > 4 )
                {
                    WARNING( __FUNCTION__, "invalid setting<[%s]->%s> : found<%u> values, required<2-4>", section.c_str(), type.c_str(), values.size() );
                    continue;
                }

                // [0] filename
                // [1] prefix (ignored if "-")
                // [2] suffix (optional; ignored if "-")
                // [3] group  (optional)

                if( values[1] == "-" )
                    values[1].clear();
                if( values.size() >= 3 && values[2] == "-" )
                    values[2].clear();

                if( values[1].empty() && values[2].empty() )
                {
                    WARNING( __FUNCTION__, "invalid setting<[%s]->%s> : neither prefix or suffix is set", section.c_str(), type.c_str() );
                    continue;
                }

                Headers.push_back( Header( values[0], type, values[1], values.size() >= 3 ? values[2] : std::string(), values.size() >= 4 ? values[3] : std::string() ) );
            }
        }
        // [Defines:TYPE] //
        else if( section.length() >= sectionPrefix.length() + 2 && section.substr( sectionPrefix.length(), 1 ) == ":" )
        {
            const std::string        type = section.substr( sectionPrefix.length() + 1 );
            std::vector<std::string> keys;

            if( !Config->GetSectionKeys( section, keys, true ) )
            {
                WARNING( __FUNCTION__, "config section<%s> is empty", section );
                continue;
            }

            for( const auto& value : keys )
            {
                if( Config->IsSectionKeyEmpty( section, value ) )
                    continue;

                int val = 0;
                if( TextIsInt( value ) && TextGetInt( value, val ) )
                    ProgramDefines[type][val] = Config->GetStr( section, value );
                else
                    WARNING( __FUNCTION__, "config setting<%s->%s> invalid", section.c_str(), value.c_str() );
            }
        }
    }

    if( !definesFound )
        WARNING( __FUNCTION__, "config section<%s> is missing", sectionPrefix.c_str() );

    return definesFound;
}

// utils

bool ReDefine::IsDefineType( const std::string& type )
{
    return RegularDefines.find( type ) != RegularDefines.end() || ProgramDefines.find( type ) != ProgramDefines.end() || VirtualDefines.find( type ) != VirtualDefines.end();
}

bool ReDefine::IsRegularDefineType( const std::string& type )
{
    return RegularDefines.find( type ) != RegularDefines.end();
}

bool ReDefine::IsMysteryDefineType( const std::string& type )
{
    return !type.empty() && type.front() == '?' && type.back() == '?';
}

bool ReDefine::GetDefineName( const std::string& type, const int value, std::string& result, bool skipVirtual /* = false */ )
{
    // if define is virtual, check regular and custom defines
    if( !skipVirtual )
    {
        auto itVirtual = VirtualDefines.find( type );
        if( itVirtual != VirtualDefines.end() )
        {
            for( const auto& realType : itVirtual->second )
            {
                if( GetDefineName( realType, value, result, true ) )
                    return true;
            }

            return false;
        }
    }

    auto itRegular = RegularDefines.find( type );
    if( itRegular != RegularDefines.end() )
    {
        auto itVal = itRegular->second.find( value );
        if( itVal != itRegular->second.end() )
        {
            result = itVal->second;
            return true;
        }
    }

    auto itProg = ProgramDefines.find( type );
    if( itProg != ProgramDefines.end() )
    {
        auto itProgVal = itProg->second.find( value );
        if( itProgVal != itProg->second.end() )
        {
            result = itProgVal->second;
            return true;
        }
    }

    return false;
}

// processing

bool ReDefine::ProcessHeader( const std::string& path, const ReDefine::Header& header )
{
    if( IsDefineType( header.Type ) )
    {
        WARNING( __FUNCTION__, "define type<%s> already in use", header.Type.c_str() );
        return false;
    }
    else if( header.Prefix.empty() && header.Suffix.empty() )
    {
        WARNING( __FUNCTION__, "prefix/suffix missing" );
        return false;
    }

    // read content
    std::vector<std::string> lines;
    if( !ReadFile( TextGetFilename( path, header.Filename ), lines ) )
        return false;

    // update status
    Status.Current.Clear();
    Status.Current.File = header.Filename;
    Status.Current.LineNumber = 0;

    // cache patterns
    std::regex  reParen = TextGetDefineRegex( header.Prefix, header.Suffix, true );
    std::regex  reNoParen = TextGetDefineRegex( header.Prefix, header.Suffix, false );

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

    std::string what;
    if( !header.Prefix.empty() && !header.Suffix.empty() )
        what = header.Prefix + "*" + header.Suffix;
    else if( !header.Prefix.empty() && header.Suffix.empty() )
        what = header.Prefix;
    else if( header.Prefix.empty() && !header.Suffix.empty() )
        what = header.Suffix;
    else
        what = "?!?";

    LOG( "Process %s ... %u %s define%s%s%s",
         header.Filename.c_str(),
         RegularDefines[header.Type].size(),
         what.c_str(),
         RegularDefines[header.Type].size() != 1 ? "s" : "",
         !header.Group.empty() ? " +> " : "",
         header.Group.c_str()
         );

    return true;
}

bool ReDefine::ProcessValue( const std::string& type, std::string& value, const bool silent /* = false */ )
{
    std::smatch match;

    if( !IsDefineType( type ) )
    {
        if( !silent )
            WARNING( __FUNCTION__, "unknown define type<%s>", type.c_str() );

        return false;
    }

    bool useVal = false;
    int  val = 0;

    if( TextIsInt( value ) && TextGetInt( value, val ) )
        useVal = true;

    // check for raw number
    if( useVal )
    {
        if( GetDefineName( type, val, value ) )
            return true;
    }
    // check if it's just simple math
    else if( std::regex_match( value, match, IsSimpleMath ) )
    {
        int               left, right;
        const std::string math = match.str( 2 );

        if( TextGetInt( match.str( 1 ), left ) && TextGetInt( match.str( 3 ), right ) )
        {
            if( math == "*" )
                val = left * right;
            else if( math == "/" )
            {
                // don't get into trouble due to shitty modders
                if( right == 0 )
                {
                    if( !silent )
                        WARNING( nullptr, "DIVISION BY ZERO" );
                    return false;
                }

                val = left / right;
            }
            else if( math == "+" )
                val = left + right;
            else if( math == "-" )
                val = left - right;
            else
            {
                if( !silent )
                    WARNING( __FUNCTION__, "???" );

                return false;
            }

            if( GetDefineName( type, val, value ) )
                return true;        // great success!
            else
                useVal = true;      // math failed us
        }
    }
    else
        return false;

    if( !silent )
    {
        std::string unknown = useVal ? std::to_string( (long long)val ) : value;

        WARNING( nullptr, "unknown %s<%s>", type.c_str(), unknown.c_str() );
        Status.Process.Unknown[type][unknown]++;
    }

    return false;
}

void ReDefine::ProcessValueGuessing( std::string& value )
{
    if( !VariablesGuessing.size() )
        return;

    int val = 0;
    if( TextIsInt( value ) && TextGetInt( value, val ) )
    {
        for( const auto& type : VariablesGuessing )
        {
            if( ProcessValue( type, value, true ) )
                return;
        }
    }
}
