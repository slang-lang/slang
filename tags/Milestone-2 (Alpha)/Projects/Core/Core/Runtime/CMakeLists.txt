INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	AtomicValue.cpp
	ExceptionData.cpp
	Namespace.cpp
	OperatorOverloading.cpp
	TypeCast.cpp
)

SET(HEADERS
	AtomicValue.h
	ControlFlow.h
	ExceptionData.h
	Exceptions.h
	Namespace.h
	OperatorOverloading.h
	TypeCast.h
)

SET(DEPENDENCIES
	CoreBuildInObjects
)

add_include(Projects/Core)
add_include(Projects/Utils)

build_static_lib(CoreRuntime "")
