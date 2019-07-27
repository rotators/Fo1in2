#include "FOClassic/CommandLine.h"

#include "ReDefine.h"

int main( int argc, char** argv )
{
    std::setvbuf( stdout, NULL, _IONBF, 0 );

    ReDefine* reDefine = new ReDefine();
    reDefine->CommandLine = new CmdLine( argc, argv );

    reDefine->LOG( "ReDefine <3 FO1@2" );
    reDefine->LOG( " " );

    if( reDefine->Init() && reDefine->ReadConfig( "ReDefine.cfg" ))
    {
    }

    reDefine->Finish();
    delete reDefine;

    return EXIT_SUCCESS;
}
