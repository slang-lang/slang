cmake_minimum_required(VERSION 3.10)

PROJECT(Slang)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/Modules/")

# verbose makefiles
# SET(CMAKE_VERBOSE_MAKEFILE ON)

# this helps debugging dependencies - a lot :)
# SET_PROPERTY(GLOBAL PROPERTY GLOBAL_DEPENDS_DEBUG_MODE 1)

INCLUDE(CMake/Base.cmake)
INCLUDE(CMake/Modules/LibFindMacros.cmake)

ADD_SUBDIRECTORY(Projects)

