# ReDefine build script
# Based on FOClassic setup
cmake_minimum_required( VERSION 3.7.2 FATAL_ERROR ) 

#> AutomatedBuild.cmake <#

# Prepare build directory
function( CreateBuildDirectory dir generator tool file )

	# use full path
	file( TO_CMAKE_PATH "${CMAKE_CURRENT_LIST_DIR}/${dir}" dir )
	file( TO_NATIVE_PATH "${dir}" dir_native )

	message( STATUS "Checking ${dir_native}" )
	if( NOT EXISTS "${dir}" )
		message( STATUS "Creating ${dir_native}" )
		file( MAKE_DIRECTORY "${dir}" )
	endif()

	if( NOT EXISTS "${dir}/${file}" )
		if( UNIX AND tool )
			set( info ", toolchain: ${tool}" )
			set( toolchain -DCMAKE_TOOLCHAIN_FILE=${CMAKE_CURRENT_LIST_DIR}/CMake/Toolchain/${tool}.cmake )
		elseif( WIN32 AND tool )
			set( info ", toolset: ${tool}" )
			set( toolset -T ${tool} )
		endif()
		message( STATUS "Starting generator (${generator}${info})" )
		execute_process(
			COMMAND ${CMAKE_COMMAND} ${toolchain} -G "${generator}" ${toolset} -S "${CMAKE_CURRENT_LIST_DIR}"
			RESULT_VARIABLE result
			WORKING_DIRECTORY "${dir}"
		)
		if( NOT result EQUAL 0 )
			list( APPEND BUILD_FAIL "${dir}" )
			set( BUILD_FAIL "${BUILD_FAIL}" PARENT_SCOPE )
			return()
		endif()
	endif()

	if( EXISTS "${dir}/${file}" )
		list( APPEND BUILD_DIRS "${dir}" )
		set( BUILD_DIRS "${BUILD_DIRS}" PARENT_SCOPE )
	else()
		list( APPEND BUILD_FAIL "${dir}" )
		set( BUILD_FAIL "${BUILD_FAIL}" PARENT_SCOPE )
	endif()

endfunction()

function( RunAllBuilds )

	foreach( dir IN LISTS BUILD_DIRS )
		file( TO_NATIVE_PATH "${dir}" dir_native )
		message( STATUS "Starting build (${dir_native})" )
		execute_process(
			COMMAND ${CMAKE_COMMAND} --build "${dir}" --config Release
			RESULT_VARIABLE result
		)
		if( NOT result EQUAL 0 )
			list( APPEND BUILD_FAIL "${dir}" )
			set( BUILD_FAIL "${BUILD_FAIL}" PARENT_SCOPE )
		endif()
	endforeach()

endfunction()

#> FormatSource.cmake <#

function( FormatSource filename )

	set( root "." )
	set( uncrustemp "${root}/FormatSource.tmp" )
	set( uncrustify "${root}/SourceTools/uncrustify" )
	set( uncrustcfg "${root}/SourceTools/uncrustify.cfg" )

	if( UNCRUSTIFY_EXECUTABLE )
		set( uncrustify "${UNCRUSTIFY_EXECUTABLE}" )
	endif()

	# CMAKE_EXECUTABLE_SUFFIX is not reliable
	if( WIN32 AND NOT "${uncrustify}" MATCHES "\.[Ee][Xx][Ee]" )
		string( APPEND uncrustify ".exe" )
	endif()

	# in case of cancelled FormatSource runs
	if( EXISTS "${uncrustemp}" )
		file( REMOVE "${uncrustemp}" )
	endif()

	if( EXISTS "${uncrustify}" )
		execute_process( COMMAND "${uncrustify}" -c "${uncrustcfg}" -l CPP -f "${filename}" -o "${uncrustemp}" -q --if-changed )

		if( EXISTS "${uncrustemp}" )
			file( RENAME "${uncrustemp}" "${filename}" )
		endif()
	endif()

endfunction() 

#> ReDefine <#

if( UNIX )
	set( BUILD_FILE      "Makefile" )
	set( BUILD_GENERATOR "Unix Makefiles" )
#	set( BUILD_TOOL      "Linux32" )
elseif( WIN32 )
	set( BUILD_FILE      "ReDefine.sln" )
	set( BUILD_GENERATOR "Visual Studio 15 2017" )
endif()

FormatSource( "Defines.cpp" )
FormatSource( "Functions.cpp" )
FormatSource( "Main.cpp" )
FormatSource( "Operators.cpp" )
FormatSource( "Raw.cpp" )
FormatSource( "ReDefine.cpp" )
FormatSource( "ReDefine.h" )
FormatSource( "Script.cpp" )
FormatSource( "Text.cpp" )
FormatSource( "Variables.cpp" )

CreateBuildDirectory( "Build" "${BUILD_GENERATOR}" "${BUILD_TOOL}" "${BUILD_FILE}" )
if( BUILD_FAIL )
	message( FATAL_ERROR "Build error" )
endif()

RunAllBuilds()
if( BUILD_FAIL )
	message( FATAL_ERROR "Build error" )
endif()
