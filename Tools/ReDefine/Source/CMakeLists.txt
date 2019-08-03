cmake_minimum_required( VERSION 3.7.2 FATAL_ERROR )

set( CMAKE_CONFIGURATION_TYPES    "Release" )
set( CMAKE_CXX_STANDARD           14 )
set( CMAKE_CXX_STANDARD_REQUIRED  YES )
set( CMAKE_SKIP_INSTALL_RULES     TRUE )

project( ReDefine )

add_executable( ReDefine "" )
target_sources( ReDefine
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/ReDefine.h

	PRIVATE
		${CMAKE_CURRENT_LIST_FILE}
		Main.cpp

		Defines.cpp
		Functions.cpp
		Log.cpp
		Operators.cpp
		Raw.cpp
		ReDefine.cpp
		Script.cpp
		Text.cpp
		Variables.cpp

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
else()
	set(CMAKE_BUILD_TYPE RelWithDebInfo)

	include( CheckCXXCompilerFlag )
	check_cxx_compiler_flag( -Wall   COMPILER_FLAG_WALL )
	check_cxx_compiler_flag( -Werror COMPILER_FLAG__WERROR )
	check_cxx_compiler_flag( -Wextra COMPILER_FLAG_WEXTRA )
endif()

if( COMPILER_FLAG_WALL )
	target_compile_options( ReDefine PRIVATE -Wall )
endif()
if( COMPILER_FLAG_WERROR )
	target_compile_options( ReDefine PRIVATE -Werror )
endif()
if( COMPILER_FLAG_WEXTRA )
	target_compile_options( ReDefine PRIVATE -Wextra )
endif()

function( lib_filesystem target )
	if( NOT CMAKE_CXX_STANDARD )
		message( FATAL_ERROR "CMAKE_CXX_STANDARD not set" )
	endif()

	include(CheckIncludeFileCXX)

	set( CMAKE_REQUIRED_FLAGS_OLD "${CMAKE_REQUIRED_FLAGS}" )
	set( CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} ${CMAKE_CXX${CMAKE_CXX_STANDARD}_STANDARD_COMPILE_OPTION}" )

	check_include_file_cxx( filesystem HAVE_FILESYSTEM )
	if( NOT HAVE_FILESYSTEM )
		check_include_file_cxx( experimental/filesystem HAVE_EXPERIMENTAL_FILESYSTEM )
	endif()

	set( CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS_OLD}" )

	if( HAVE_FILESYSTEM )
		target_compile_definitions( ${target} PRIVATE HAVE_FILESYSTEM )
	elseif( HAVE_EXPERIMENTAL_FILESYSTEM )
		target_compile_definitions( ${target} PRIVATE HAVE_EXPERIMENTAL_FILESYSTEM )
		target_link_libraries( ${target} stdc++fs )
	else()
		message( FATAL_ERROR "Cannot find std::filesystem (neither standard or experimental)" )
		#set_target_properties( ${target} PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1 )
	endif()

endfunction()

lib_filesystem( ReDefine )

# Prettify IDE

set_property( GLOBAL PROPERTY USE_FOLDERS ON )
set_property( GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake" )

source_group( " "         REGULAR_EXPRESSION "\.([CcHh]|[CcHh][Pp][Pp])$" )
source_group( "CMake"     REGULAR_EXPRESSION "[Cc][Mm][Aa][Kk][Ee]" )
source_group( "FOClassic" REGULAR_EXPRESSION "FOClassic" )
