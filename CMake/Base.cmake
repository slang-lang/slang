cmake_minimum_required(VERSION 2.6)

# cmake policy changes. use "cmake --help-policy <policyid>" for details
cmake_policy(SET CMP0000 OLD)
if ( CMAKE_VERSION VERSION_LESS "2.6.4" )
else()
	cmake_policy(SET CMP0011 NEW)
endif()

# verbose makefiles
# SET(CMAKE_VERBOSE_MAKEFILE ON)

# directories
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)   # binary root
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)      # library root

#SET(CMAKE_CXX_FLAGS "-ansi -pedantic -fPIC -Wall -Werror -Wunused -Wno-long-long -Wnon-virtual-dtor") # -std=c++0x ;-(
SET(CMAKE_CXX_FLAGS "-pedantic -fPIC -Wall -Werror -Wunused -Wno-long-long -Wnon-virtual-dtor") # -std=c++0x ;-(

if( "${ISC_BUILD}" STREQUAL "" OR "${ISC_BUILD}" MATCHES "Debug")

    # by default we build debug!
    # MESSAGE("Setting default build to: Debug")
    SET(CMAKE_BUILD_TYPE "Debug")

    # do more logging
    add_definitions(-DISC_DEBUG)

    # suppress "veraltete Konvertierung von Zeichenkettenkonstante in »char*« [-Werror=write-strings]"
    add_definitions(-Wno-write-strings)
    
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")

elseif("${ISC_BUILD}" MATCHES "Release")

    # MESSAGE("Setting default build to: Release")
    SET(CMAKE_BUILD_TYPE "Release")
    SET(CMAKE_CXX_FLAGS "")
    
    # do less logging
    add_definitions(-DISC_NO_DEBUG_LOG)

    # suppress "veraltete Konvertierung von Zeichenkettenkonstante in »char*« [-Werror=write-strings]"
    add_definitions(-Wno-write-strings)
    
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-strict-aliasing")

else()

    MESSAGE(FATAL_ERROR "Specify a valid build type: cmake -DISC_BUILD=Release|Debug")

endif()

# boost hack
#add_definitions(-DBOOST_NO_HASH)

# specify default includes for the project
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(
    ${PROJECT_SOURCE_DIR}/Interfaces
    ${PROJECT_SOURCE_DIR}/Utils
)

# make sure the user-settings file exists

SET(USER_ENV "$ENV{HOME}/.isc/Env.cmake")
INCLUDE(${USER_ENV} OPTIONAL RESULT_VARIABLE found)
if ( "${found}" STREQUAL "NOTFOUND" )
    MESSAGE(FATAL_ERROR "Your user-env file [${USER_ENV}] does not exist")
endif()

# common used functionality and functions
INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Common.cmake)

# now run the build that takes care of other arguments
INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Builder.cmake)
