cmake_minimum_required(VERSION 3.10)

PROJECT(Slang)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/Modules/")

# verbose makefiles
# SET(CMAKE_VERBOSE_MAKEFILE ON)

# this helps debugging dependencies - a lot :)
# SET_PROPERTY(GLOBAL PROPERTY GLOBAL_DEPENDS_DEBUG_MODE 1)

INCLUDE(CMake/Base.cmake)
INCLUDE(CMake/Modules/LibFindMacros.cmake)
INCLUDE(CMake/Modules/FindFCGI.cmake)
INCLUDE(CMake/Modules/Findjsoncpp.cmake)
INCLUDE(CMake/Modules/Options.cmake)


message(STATUS "=======================================================")
set_option(ENABLE_CPPCHECK "Set to ON to enable cppcheck static analysis." OFF)
set_option(ENABLE_LINTING  "Set to ON to enable clang linting."            OFF)
message(STATUS "=======================================================")


# Cppcheck
if(ENABLE_CPPCHECK)
    include(CMake/Modules/cppcheck.cmake)
endif()

# Linting
if(ENABLE_LINTING)
    include(CMake/Modules/clang-tidy.cmake)
endif()


ADD_SUBDIRECTORY(Projects)

