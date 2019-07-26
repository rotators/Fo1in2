cmake_minimum_required( VERSION 3.7.2 FATAL_ERROR )

set( CMAKE_CONFIGURATION_TYPES    "Release" )
set( CMAKE_CXX_STANDARD           14 )
set( CMAKE_CXX_STANDARD_REQUIRED  YES )
set( CMAKE_SKIP_INSTALL_RULES     TRUE )

project( ReDefine )

add_executable( ReDefine "" )
target_sources( ReDefine
	PRIVATE
		${CMAKE_CURRENT_LIST_FILE}
		ReDefine.cpp
		ReDefine.h

		Defines.cpp
		Defines.h
		Types.h

		# FOClassic
		FOClassic/CommandLine.cpp
		FOClassic/CommandLine.h
		FOClassic/Ini.cpp
		FOClassic/Ini.h
)

if( MSVC )
	set( pdb "ReDefine.pdb" )
	set( pdb_public "ReDefine.pdb.PUBLIC" )

	set_property( TARGET ReDefine APPEND_STRING PROPERTY COMPILE_FLAGS "/Zi " )
	set_property( TARGET ReDefine APPEND_STRING PROPERTY LINK_FLAGS "/DEBUG /PDBSTRIPPED:$(ConfigurationName)/${pdb_public} /PDBALTPATH:${pdb} " )

	set_property( TARGET ReDefine APPEND_STRING PROPERTY LINK_FLAGS "/OPT:REF " )
endif() 

# Prettify IDE

set_property( GLOBAL PROPERTY USE_FOLDERS ON )
set_property( GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake" )

source_group( " "         REGULAR_EXPRESSION "\.([CcHh]|[CcHh][Pp][Pp])$" )
source_group( "CMake"     REGULAR_EXPRESSION "[Cc][Mm][Aa][Kk][Ee]" )
source_group( "FOClassic" REGULAR_EXPRESSION "FOClassic" )
