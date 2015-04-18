INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	BooleanEvaluations.cpp
	Math.cpp
	Strings.cpp
)

SET(HEADERS
	BooleanEvaluations.h
	Math.h
	Strings.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)

build_static_lib(CoreHelpers "")
