#include "FOClassic/Ini.h"

#include "ReDefine.h"

int main( int argc, char** argv )
{
    int result = EXIT_SUCCESS;

    std::setvbuf( stdout, NULL, _IONBF, 0 );

    ReDefine* redefine = new ReDefine();

    redefine->LOG( "ReDefine <3 FO1@2" );
    redefine->LOG( " " );

    // prepare internals, remove old logs
    redefine->Init();

    const std::string config = "ReDefine.cfg";
    const std::string section = "ReDefine";

    if( redefine->Config->LoadFile( config ) )
    {
        const std::string headers = redefine->Config->GetStr( section, "ScriptsDir" );     // TODO HeadersDir
        const std::string scripts = redefine->Config->GetStr( section, "ScriptsDir" );

        if( redefine->ReadConfig( "Defines", "Variable", "Function" ) )
        {
            // process headers
            //
            redefine->ProcessHeaders( headers );

            redefine->ProcessScripts( scripts, true );
        }
        else
        {
            redefine->Status.Current.File = config;
            redefine->WARNING( nullptr, "cannot parse configuration" );
            result = EXIT_FAILURE;
        }
    }
    else
    {
        redefine->Status.Current.File = config;
        redefine->WARNING( nullptr, "cannot read configuration", config.c_str() );
        result = EXIT_FAILURE;
    }

    redefine->Finish();
    delete redefine;

    return result;
}
