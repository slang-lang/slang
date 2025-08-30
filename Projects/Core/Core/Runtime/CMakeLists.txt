INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(BuildInTypes)

SET(SOURCES
	AtomicValue.cpp
	ExceptionData.cpp
#	Interpreter.cpp
	OperatorOverloading.cpp
	Object.cpp
	Reference.cpp
	TypeCast.cpp
	Types.cpp
	Utils.cpp
)

SET(HEADERS
	AtomicValue.h
	ControlFlow.h
	ExceptionData.h
	Exceptions.h
#	Interpreter.h
	OperatorOverloading.h
	Object.h
	Reference.h
	TypeCast.h
	Types.h
	Utils.h
)

SET(DEPENDENCIES
	CoreRuntimeBuildInTypes
	Utils
)

add_include(Projects/Core)
add_include(Projects/Utils)

build_static_lib(CoreRuntime "")
