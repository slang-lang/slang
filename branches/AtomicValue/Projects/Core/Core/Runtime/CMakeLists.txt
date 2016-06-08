INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	AtomicValue.cpp
	ExceptionData.cpp
	OperatorOverloading.cpp
	TypeCast.cpp
)

SET(HEADERS
	AtomicValue.h
	ControlFlow.h
	ExceptionData.h
	OperatorOverloading.h
	TypeCast.h
)

SET(DEPENDENCIES
	CoreCommon
)

add_include(Projects/Core)

build_static_lib(CoreRuntime "")
