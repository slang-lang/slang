INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Version.cpp
)

SET(HEADERS
	Version.h
)

SET(DEPENDENCIES )

add_include( Projects/Utils )

build_static_lib( UtilsSemVer "" )
