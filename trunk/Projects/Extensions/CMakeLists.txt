INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(System)

SET(SOURCES
	Extensions.cpp
)

SET(HEADERS
	Extensions.h
)

SET(DEPENDENCIES
	ExtensionsSystem
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/Utils)

build_static_lib(Extensions "")
