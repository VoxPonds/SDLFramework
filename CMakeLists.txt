message(STATUS "The CMAKE_VERSION is ${CMAKE_VERSION}.")
cmake_minimum_required(VERSION 4.4.2)

include(cmake/ProjectConfig.cmake)
project (SDLFramework LANGUAGES C CXX VERSION 0.0.1)

include(cmake/OutputDirectories.cmake)
include(cmake/CompilerConfig.cmake)
include(cmake/Dependencies.cmake)

add_subdirectory(src)
add_subdirectory(examples)

if(MSVC)
    message(STATUS "Using MSVC")

    # close /showIncludes
    string(REPLACE "/showIncludes" "" CMAKE_DEPFILE_FLAGS_C "${CMAKE_DEPFILE_FLAGS_C}")
    string(REPLACE "/showIncludes" "" CMAKE_DEPFILE_FLAGS_CXX "${CMAKE_DEPFILE_FLAGS_CXX}")
endif()
