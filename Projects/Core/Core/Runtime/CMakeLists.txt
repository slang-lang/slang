INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	AtomicValue.cpp
	ExceptionData.cpp
	OperatorOverloading.cpp
	Reference.cpp
	Script.cpp
	TypeCast.cpp
)

SET(HEADERS
	AtomicValue.h
	ControlFlow.h
	ExceptionData.h
	Exceptions.h
	OperatorOverloading.h
	Reference.h
	Script.h
	TypeCast.h
)

SET(DEPENDENCIES
	CoreBuildInObjects
)

add_include(Projects/Core)
add_include(Projects/Utils)

build_static_lib(CoreRuntime "")
