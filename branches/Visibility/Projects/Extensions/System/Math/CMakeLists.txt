INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Math.cpp
)

SET(HEADERS
	Abs.h
	Ceil.h
	Floor.h
	Math.h
	Rand.h
	Round.h
	Sqrt.h
	Srand.h
	Trunc.h
)

SET(DEPENDENCIES
	Utils
	Core
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/Utils)

build_static_lib(ExtensionsSystemMath "")
