INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	AtomicValue.cpp
	ExceptionData.cpp
#	Interpreter.cpp
	OperatorOverloading.cpp
	Reference.cpp
	Script.cpp
	TypeCast.cpp
	Types.cpp
)

SET(HEADERS
	AtomicValue.h
	ControlFlow.h
	ExceptionData.h
	Exceptions.h
#	Interpreter.h
	OperatorOverloading.h
	Reference.h
	Script.h
	TypeCast.h
	Types.h
)

SET(DEPENDENCIES
	CoreDebugger
	CoreBuildInObjects
	Utils
)

add_include(Projects/Core)
add_include(Projects/Utils)

build_static_lib(CoreRuntime "")
