INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	ExceptionData.cpp
)

SET(HEADERS
	ControlFlow.h
	ExceptionData.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)

build_static_lib(CoreRuntime "")
