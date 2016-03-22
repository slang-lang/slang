INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	ExceptionData.cpp
	TypeCast.cpp
)

SET(HEADERS
	ControlFlow.h
	ExceptionData.h
	TypeCast.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)

build_static_lib(CoreRuntime "")
