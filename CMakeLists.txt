cmake_minimum_required(VERSION 3.5)

PROJECT(Slang)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/Modules/")

# cmake policy changes. use "cmake --help-policy <policyid>" for details
if ( CMAKE_VERSION VERSION_LESS "3.0.0" )
else()
    cmake_policy(SET CMP0011 NEW)
endif()

# verbose makefiles
# SET(CMAKE_VERBOSE_MAKEFILE ON)

INCLUDE(CMake/Base.cmake)
INCLUDE(CMake/Modules/LibFindMacros.cmake)

# this helps debugging dependencies - a lot :)
# SET_PROPERTY(GLOBAL PROPERTY GLOBAL_DEPENDS_DEBUG_MODE 1)

ADD_SUBDIRECTORY(Projects)

