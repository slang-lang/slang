INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Configurator.cpp
)

SET(HEADERS
	Configurator.h
)

SET(DEPENDENCIES
	UtilsTools
	UtilsParsers
)

add_include(Projects/Utils)

build_static_lib(UtilsCommonConfiguration "")
