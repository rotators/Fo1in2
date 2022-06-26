cmake_minimum_required( VERSION 3.23 FATAL_ERROR )

set( CMAKE_CONFIGURATION_TYPES    "Release" )
set( CMAKE_SKIP_INSTALL_RULES     TRUE )
set( CMAKE_CXX_STANDARD           20 )
set( CMAKE_CXX_STANDARD_REQUIRED  YES )

project( MapsScripts LANGUAGES CXX)

add_executable( ${PROJECT_NAME} )
target_sources( ${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_FILE}
        CommandLine.cpp
        CommandLine.hpp
        Text.cpp
        Text.hpp
        MapsScripts.cpp

        subtypes.h
)

set_property( GLOBAL PROPERTY USE_FOLDERS ON )
set_property( GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake" )

source_group( " "         REGULAR_EXPRESSION "\.([CcHh]|[CcHh][Pp][Pp])$" )
source_group( "CMake"     REGULAR_EXPRESSION "[Cc][Mm][Aa][Kk][Ee]" )
