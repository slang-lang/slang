INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Defines.cpp
	MathExtension.cpp
)

SET(HEADERS
	Abs.h
	Ceil.h
	Defines.h
	Floor.h
	MathExtension.h
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

SET(MODULES
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/Utils)

build_static_lib(ExtensionsSystemMath "${MODULES}")
