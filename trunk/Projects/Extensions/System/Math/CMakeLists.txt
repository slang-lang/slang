INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Math.cpp
)

SET(HEADERS
	Ceil.h
	Floor.h
	Math.h
	Round.h
)

SET(DEPENDENCIES
	Utils
	Core
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/Utils)

build_static_lib(ExtensionsSystemMath "")
