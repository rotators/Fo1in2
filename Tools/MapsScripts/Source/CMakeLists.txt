cmake_minimum_required( VERSION 3.22 FATAL_ERROR )

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

if( MSVC )
    set_property( TARGET ${PROJECT_NAME} APPEND_STRING PROPERTY LINK_FLAGS "/INCREMENTAL:NO /OPT:REF " )
elseif( UNIX )
    set(CMAKE_BUILD_TYPE RelWithDebInfo)

    include( CheckCXXCompilerFlag )
    check_cxx_compiler_flag( -Wall      COMPILER_FLAG_WALL )
    check_cxx_compiler_flag( -Werror    COMPILER_FLAG_WERROR )
    check_cxx_compiler_flag( -Wextra    COMPILER_FLAG_WEXTRA )
    check_cxx_compiler_flag( -Wpedantic COMPILER_FLAG_WPEDANTIC )

    if( COMPILER_FLAG_WALL )
        target_compile_options( ${PROJECT_NAME} PRIVATE -Wall )
    endif()
    if( COMPILER_FLAG_WERROR )
        target_compile_options( ${PROJECT_NAME} PRIVATE -Werror )
    endif()
    if( COMPILER_FLAG_WEXTRA )
        target_compile_options( ${PROJECT_NAME} PRIVATE -Wextra )
    endif()
    if( COMPILER_FLAG_WPEDANTIC )
        target_compile_options( ${PROJECT_NAME} PRIVATE -Wpedantic )
    endif()

    check_cxx_compiler_flag( -static-libgcc    COMPILER_FLAG_STATIC_LIBGCC )
    check_cxx_compiler_flag( -static-libstdc++ COMPILER_FLAG_STATIC_LIBSTDCPP )

    if( COMPILER_FLAG_STATIC_LIBGCC )
        target_link_libraries( ${PROJECT_NAME} PRIVATE -static-libgcc )
    endif()
    if( COMPILER_FLAG_STATIC_LIBSTDCPP )
        target_link_libraries( ${PROJECT_NAME} PRIVATE -static-libstdc++ )
    endif()
endif()

set_property( GLOBAL PROPERTY USE_FOLDERS ON )
set_property( GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake" )

source_group( " "         REGULAR_EXPRESSION "\.([CcHh]|[CcHh][Pp][Pp])$" )
source_group( "CMake"     REGULAR_EXPRESSION "[Cc][Mm][Aa][Kk][Ee]" )
