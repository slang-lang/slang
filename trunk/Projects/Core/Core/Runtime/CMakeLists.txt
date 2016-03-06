INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
)

SET(HEADERS
	ControlFlow.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)

build_static_lib(CoreRuntime "")
