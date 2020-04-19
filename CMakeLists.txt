PROJECT(Slang)

cmake_minimum_required(VERSION 3.0)

# cmake policy changes. use "cmake --help-policy <policyid>" for details
if ( CMAKE_VERSION VERSION_LESS "3.0.0" )
else()
    cmake_policy(SET CMP0011 NEW)
endif()

# verbose makefiles
# SET(CMAKE_VERBOSE_MAKEFILE ON)

#INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)
INCLUDE(CMake/Base.cmake)

# this helps debugging dependencies - a lot :)
# SET_PROPERTY(GLOBAL PROPERTY GLOBAL_DEPENDS_DEBUG_MODE 1)

ADD_SUBDIRECTORY(Projects)

