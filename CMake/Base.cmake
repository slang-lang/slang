# directories
SET( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )   # binary root
SET( LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib )      # library root

SET( CMAKE_CXX_FLAGS "-std=c++14 -pedantic -fPIC" )
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wunused" )
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-long-long -Wno-deprecated-copy -Wnon-virtual-dtor -Wno-undef -Wno-type-limits" )
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-endif-labels" ) # allow endif with label

if( "${BUILD}" STREQUAL "" OR "${BUILD}" MATCHES "Debug" )

    # by default we build debug!
    # MESSAGE( "Setting default build to: Debug" )
    SET( CMAKE_BUILD_TYPE "Debug" )

    add_definitions( -DDEBUG ) # do more logging
    add_definitions( -Wno-unused-result )
    add_definitions( -Wno-unused-value )
    add_definitions( -Wno-unused-variable )
    add_definitions( -Wno-write-strings ) # suppress "deprecated conversion from string constant to ‘char*’ [-Werror=write-strings]"

    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g" )

elseif( "${BUILD}" MATCHES "Release" )

    # MESSAGE( "Setting default build to: Release" )
    SET( CMAKE_BUILD_TYPE "Release" )

    add_definitions( -Wno-unused-result )
    add_definitions( -Wno-unused-value )
    add_definitions( -Wno-unused-variable )
    add_definitions( -Wno-write-strings ) # suppress "deprecated conversion from string constant to ‘char*’ [-Werror=write-strings]"

    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-strict-aliasing -O4" )

else( )

    MESSAGE( FATAL_ERROR "Specify a valid build type: cmake -DBUILD=Release|Debug" )

endif( )


# specify default includes for the project
SET( CMAKE_INCLUDE_CURRENT_DIR ON )

# additional definitions
add_definitions( -DLOG_LEVEL=3 )
#add_definitions( -DLOG_FILE_AND_POSITION )

# common used functionality and functions
INCLUDE( ${PROJECT_SOURCE_DIR}/CMake/Common.cmake )

# now run the build that takes care of other arguments
INCLUDE( ${PROJECT_SOURCE_DIR}/CMake/Builder.cmake )

# include custom dependencies
INCLUDE( ${PROJECT_SOURCE_DIR}/CMake/Dependencies.cmake )

#include custom extensions
INCLUDE( ${PROJECT_SOURCE_DIR}/CMake/Extensions.cmake )
INCLUDE( ${PROJECT_SOURCE_DIR}/CMake/Extensions.cmake )
