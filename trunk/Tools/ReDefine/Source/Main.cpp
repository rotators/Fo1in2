#include "FOClassic/CommandLine.h"
#include "FOClassic/Ini.h"

#include "ReDefine.h"

int main( int argc, char** argv )
{
    int result = EXIT_SUCCESS;

    // boring stuff
    std::setvbuf( stdout, NULL, _IONBF, 0 );
    ReDefine* redefine = new ReDefine();
    CmdLine*  cmd = new CmdLine( argc, argv );

    // most important stuff
    const bool readOnly = cmd->IsOption( "ro" ) || cmd->IsOption( "read" ) || cmd->IsOption( "read-only" );

    // called before ReDefine::Init() so it won't be visible in logfile (as it's deleted then)
    redefine->LOG( "ReDefine <3 FO1@2" );
    redefine->LOG( " " );

    //
    // Init() / Finish() can be called at any point to completely reset object
    //
    // Init() recreates all internals and removes all log files
    // Finish() does cleanup only; called by Init() and destructor
    //
    redefine->Init();

    const std::string config = "ReDefine.cfg";
    const std::string section = "ReDefine";

    //
    // load config
    // config can be either loaded from ini-like file,
    // or set "manually" if main application is storing configuration in different format
    //
    // in both cases it has to be done before any ReadConfig*() call(s), which checks ReDefine::Config content without touching any files
    //
    if( redefine->Config->LoadFile( config ) )
    {
        // read directories configuration
        std::string headers = redefine->Config->GetStr( section, "HeadersDir" );
        std::string scripts = redefine->Config->GetStr( section, "ScriptsDir" );
        bool        debugEdit = redefine->Config->GetBool( section, "DebugEdit", false );

        // override settings from command line
        if( !cmd->IsOptionEmpty( "headers" ) )
            headers = cmd->GetStr( "headers" );
        if( !cmd->IsOptionEmpty( "scripts" ) )
            scripts = cmd->GetStr( "scripts" );
        if( cmd->IsOption( "debug-edit" ) )
            debugEdit = true;

        if( headers.empty() )
        {
            redefine->WARNING( nullptr, "headers directory not set" );
            result = EXIT_FAILURE;
        }
        else if( scripts.empty() )
        {
            redefine->WARNING( nullptr, "scripts directory not set" );
            result = EXIT_FAILURE;
        }
        //
        // validate config and convert settings to internal structures
        //
        // sections can be loaded separetely by either calling ReadConfig() and changing unwanted sections names to empty strings,
        // or calling related ReadConfig*() function only
        //
        // defines section needs to be processed before other settings
        //
        else if( redefine->ReadConfig( "Defines", "Variable", "Function", "Raw", "Script" ) )
        {
            // unload config
            // added here to make sure Process*() functions are independent o ReadConfig*()
            // in long-running applications it might be a good idea to keep config alive
            redefine->Config->Unload();

            // additional tuning
            redefine->EditDebug = debugEdit;

            // process headers
            //
            redefine->ProcessHeaders( headers );

            // process scripts
            //
            redefine->ProcessScripts( scripts, readOnly );
        }
        else
        {
            redefine->Status.Current.File = config;
            redefine->WARNING( nullptr, "cannot parse config" );
            result = EXIT_FAILURE;
        }
    }
    else
    {
        redefine->Status.Current.File = config;
        redefine->WARNING( nullptr, "cannot read config" );
        result = EXIT_FAILURE;
    }

    if( redefine->Status.Process.Lines && redefine->Status.Process.Files )
    {
        redefine->LOG( "Process scripts ... %u line%s in %u file%s",
                       redefine->Status.Process.Lines, redefine->Status.Process.Lines != 1 ? "s" : "",
                       redefine->Status.Process.Files, redefine->Status.Process.Files != 1 ? "s" : "" );
    }

    if( redefine->Status.Process.LinesChanges && redefine->Status.Process.FilesChanges )
    {
        redefine->LOG( "%sed scripts ... %u line%s in %u file%s%s",
                       readOnly ? "Check" : "Chang",
                       redefine->Status.Process.LinesChanges, redefine->Status.Process.LinesChanges != 1 ? "s" : "",
                       redefine->Status.Process.FilesChanges, redefine->Status.Process.FilesChanges != 1 ? "s" : "",
                       readOnly ? " can be changed" : "" );
    }

    if( redefine->Status.Process.Unknown.size() )
    {
        redefine->WARNING( nullptr, " " );
        for( const auto& type : redefine->Status.Process.Unknown )
        {
            redefine->WARNING( nullptr, "Unknown %s", type.first.c_str() );
            for( const auto& value : type.second )
            {
                redefine->WARNING( nullptr, "        %s (%u hit%s)", value.first.c_str(), value.second, value.second != 1 ? "s" : "" );
            }
        }
    }

    // cleanup
    delete redefine;
    delete cmd;

    return result;
}
