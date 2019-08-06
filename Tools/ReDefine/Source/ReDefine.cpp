#include <algorithm>
#include <fstream>

#if defined (HAVE_FILESYSTEM)
# include <filesystem>
# if _MSC_VER == 1900 || _MSC_VER == 1800 || _MSC_VER == 1700
namespace std_filesystem = std::tr2::sys;
# else
namespace std_filesystem = std::filesystem;
# endif
#elif defined (HAVE_EXPERIMENTAL_FILESYSTEM)
# include <experimental/filesystem>
namespace std_filesystem = std::experimental::filesystem;
#else
# error "std::filesystem"
#endif

#include "FOClassic/Ini.h"

#include "ReDefine.h"

//

ReDefine::SStatus::SCurrent::SCurrent()
{
    Clear();
}

void ReDefine::SStatus::SCurrent::Clear()
{
    File = Line = "";
    LineNumber = 0;
}

//

ReDefine::SStatus::SProcess::SProcess()
{
    Clear();
}

void ReDefine::SStatus::SProcess::Clear()
{
    Files = FilesChanges = Lines = LinesChanges = 0;
}

//

void ReDefine::SStatus::Clear()
{
    Current.Clear();
    Process.Clear();
}

//

ReDefine::ReDefine() :
    Config( nullptr )
{}

ReDefine::~ReDefine()
{
    Finish();
}

void ReDefine::Init()
{
    Finish();

    // create config
    Config = new Ini();
    Config->KeepKeysOrder = true;

    // remove logfiles from previous run
    std::remove( "ReDefine.DEBUG.log" );
    std::remove( "ReDefine.WARNING.log" );
    std::remove( "ReDefine.log" );

    // extern initialization
    InitOperators();
    InitScript();
}

void ReDefine::Finish()
{
    if( Config )
    {
        delete Config;
        Config = nullptr;
    }

    Status.Clear();

    // extern cleanup
    FinishDefines();
    FinishFunctions();
    FinishOperators();
    FinishRaw();
    FinishScript();
    FinishVariables();
}

// files reading

bool ReDefine::ReadFile( const std::string& filename, std::vector<std::string>& lines )
{
    lines.clear();

    // don't waste time on empty files
    // also, while( !std::ifstream::eof() ) goes wild on empty files
    if( std_filesystem::file_size( filename ) == 0 )
        return true;

    std::ifstream fstream;
    fstream.open( filename, std::ios_base::in | std::ios_base::binary );

    bool result = fstream.is_open();
    if( result )
    {
        // skip bom
        char bom[3] = { 0, 0, 0 };
        fstream.read( bom, sizeof(bom) );
        if( bom[0] != (char)0xEF || bom[1] != (char)0xBB || bom[2] != (char)0xBF )
            fstream.seekg( 0, fstream.beg );

        std::string line;
        while( !fstream.eof() )
        {
            getline( fstream, line );

            line.erase( std::remove( line.begin(), line.end(), '\r' ), line.end() );
            line.erase( std::remove( line.begin(), line.end(), '\n' ), line.end() );

            lines.push_back( line );
        }
    }
    else
        WARNING( nullptr, "cannot read file<%s>", filename.c_str() );

    return result;
}

bool ReDefine::ReadConfig( const std::string& defines, const std::string& variablePrefix, const std::string& functionPrefix, const std::string& raw, const std::string& script )
{
    if( !defines.empty() && !ReadConfigDefines( defines ) )
        return false;

    if( !variablePrefix.empty() && !ReadConfigVariables( variablePrefix ) )
        return false;

    if( !functionPrefix.empty() && !ReadConfigFunctions( functionPrefix ) )
        return false;

    if( !raw.empty() && !ReadConfigRaw( raw ) )
        return false;

    if( !script.empty() && !ReadConfigScript( script ) )
        return false;

    return true;
}

// files processing

void ReDefine::ProcessHeaders( const std::string& path )
{
    // move program defines to function scope
    DefinesMap programDefines = ProgramDefines;
    ProgramDefines.clear();

    for( const auto& header : Headers )
    {
        ProcessHeader( path, header );
    }

    // won't need that until next ReadConfig()/ReadConfigDefines() call
    Headers.clear();

    // restore program defines
    // if type has been added by header, put it in RegularDefines (possibly overriding value from header),
    // otherwise, use ProgramDefines
    for( const auto& itProg : programDefines )
    {
        auto itRegular = RegularDefines.find( itProg.first );
        bool is = IsRegularDefineType( itProg.first );

        for( const auto& itVal : itProg.second )
        {
            if( is )
                itRegular->second[itVal.first] = itVal.second;
            else
                ProgramDefines[itProg.first][itVal.first] = itVal.second;

            LOG( "Added %s define ... %s = %d", itProg.first.c_str(), itVal.second.c_str(), itVal.first );
        }
    }

    GenericOperatorsMap validatedOperators;
    StringVectorMap     validatedFunctions;

    // validate variables configuration
    // virtual ? types are not valid for variables

    for( const auto& var : VariablesOperators )
    {
        for( const auto& opName : var.second )
        {
            if( !IsDefineType( opName.second ) )
            {
                WARNING( __FUNCTION__, "unknown define type<%s> : variable<%s> operatorName<%s>", opName.second.c_str(), var.first.c_str(), opName.first.c_str() );
                continue;
            }

            LOG( "Added variable %s ... %s %s %s", TextGetLower(  opName.first ).c_str(), var.first.c_str(), GetOperator( opName.first ).c_str(), opName.second.c_str() );
            validatedOperators[var.first][opName.first] = opName.second;
        }
    }

    for( const auto& type : VariablesGuessing )
    {
        if( !IsDefineType( type ) )
        {
            WARNING( __FUNCTION__, "unknown define type<%s> : variable guessing", type.c_str() );
            VariablesGuessing.clear(); // zero tolerance policy
            break;
        }
    }

    // TODO validate
    if( VariablesGuessing.size() )
        LOG( "Added variable guessing ... %s", TextGetJoined( VariablesGuessing, ", " ).c_str() );

    // keep valid settings only
    VariablesOperators = validatedOperators;
    validatedOperators.clear();

    // validate functions configuration
    // virtual ? types are valid for functions arguments only

    for( const auto& var : FunctionsOperators )
    {
        for( const auto& opName : var.second )
        {
            if( !IsDefineType( opName.second ) )
            {
                WARNING( __FUNCTION__, "unknown define type<%s> : function<%s> operatorName<%s>", opName.second.c_str(), var.first.c_str(), opName.first.c_str() );
                continue;
            }

            LOG( "Added function %s ... %s(...) %s %s", TextGetLower(  opName.first ).c_str(), var.first.c_str(), GetOperator( opName.first ).c_str(), opName.second.c_str() );
            validatedOperators[var.first][opName.first] = opName.second;
        }
    }

    for( const auto& func : FunctionsArguments )
    {
        bool         valid = true;
        unsigned int argument = 0;

        for( const auto& type : func.second )
        {
            argument++;
            if( !IsMysteryDefineType( type ) && !IsDefineType( type ) )
            {
                WARNING( __FUNCTION__, "unknown define type<%s> : function<%s> argument<%u>", type.c_str(), func.first.c_str(), argument );
                valid = false;
            }
        }

        if( !valid )
            continue;

        LOG( "Added function ... %s( %s )", func.first.c_str(), TextGetJoined( func.second, ", " ).c_str() );
        validatedFunctions[func.first] = func.second;
    }

    // keep valid settings only
    FunctionsOperators = validatedOperators;
    FunctionsArguments = validatedFunctions;

    // log raw replacement
    for( const auto& from : Raw )
    {
        LOG( "Added raw ... %s", from.first.c_str() );
    }

    // log script editing

    for( const ScriptEdit& before : EditBefore )
    {
        LOG( "Added preprocess action ... %s", before.Name.c_str() );
    }

    for( const ScriptEdit& after : EditAfter )
    {
        LOG( "Added postprocess action ... %s", after.Name.c_str() );
    }
}

void ReDefine::ProcessScripts( const std::string& path, const bool readOnly /* = false */ )
{
    LOG( "Process scripts%s ...", readOnly ? " (read only)" : "" );

    std::vector<std::string> scripts;


    for( const auto& file : std_filesystem::recursive_directory_iterator( path ) )
    {
        if( !std_filesystem::is_regular_file( file ) ) // TODO? symlinks
            continue;

        if( TextGetLower( file.path().extension() ) != ".ssl" )
            continue;

        scripts.push_back( file.path().string().substr( path.length(), file.path().string().length() - path.length() ) );
        scripts.back().erase( 0, scripts.back().find_first_not_of( "\\/" ) );  // trim left
    }

    std::sort( scripts.begin(), scripts.end() );

    for( auto& script : scripts )
    {
        ProcessScript( path, script, readOnly );
    }
}
