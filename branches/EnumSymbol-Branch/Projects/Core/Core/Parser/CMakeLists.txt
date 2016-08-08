INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Parser.cpp
)

SET(HEADERS
	Parser.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)

build_static_lib(CoreParser "")
