cmake_minimum_required(VERSION 2.8)

# cmake policy changes. use "cmake --help-policy <policyid>" for details
if ( CMAKE_VERSION VERSION_LESS "2.8.0" )
else()
	cmake_policy(SET CMP0011 NEW)
endif()

# verbose makefiles
# SET(CMAKE_VERBOSE_MAKEFILE ON)

# directories
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)   # binary root
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)      # library root

SET(CMAKE_CXX_FLAGS "-pedantic -fPIC -Wall -Werror -Wextra -Wunused -Wno-long-long -Wnon-virtual-dtor -std=c++14") # -std=c++0x -std=c++11 ;-(

if( "${BUILD}" STREQUAL "" OR "${BUILD}" MATCHES "Debug")

    # by default we build debug!
    # MESSAGE("Setting default build to: Debug")
    SET(CMAKE_BUILD_TYPE "Debug")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable -Wno-unused-value")

    # do more logging
    add_definitions(-DDEBUG)

    # suppress "veraltete Konvertierung von Zeichenkettenkonstante in »char*« [-Werror=write-strings]"
    add_definitions(-Wno-write-strings -Wno-unused-variable)

    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -g")

elseif( "${BUILD}" MATCHES "Release")

    # MESSAGE("Setting default build to: Release")
    SET(CMAKE_BUILD_TYPE "Release")

    # suppress "veraltete Konvertierung von Zeichenkettenkonstante in »char*« [-Werror=write-strings]"
    add_definitions(-Wno-write-strings -Wno-unused-variable -Wno-unused-result -Wno-unused-value)

    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-strict-aliasing -O4")

else()

    MESSAGE(FATAL_ERROR "Specify a valid build type: cmake -DBUILD=Release|Debug")

endif()

# boost hack
#add_definitions(-DBOOST_NO_HASH)

# specify default includes for the project
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
#include_directories(
#    ${PROJECT_SOURCE_DIR}/Interfaces
#    ${PROJECT_SOURCE_DIR}/Utils
#)

add_definitions(-DLOG_LEVEL=3)

# common used functionality and functions
INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Common.cmake)

# now run the build that takes care of other arguments
INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Builder.cmake)

# include custom dependencies
INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Dependencies.cmake)

#include custom extensions
INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Extensions.cmake)

