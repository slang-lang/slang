INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Math.cpp
)

SET(HEADERS
	Math.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)

build_static_lib(CoreHelpers "")
