INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	BoolType.cpp
	DoubleType.cpp
	EnumerationType.cpp
	FloatType.cpp
	Int16Type.cpp
	Int32Type.cpp
	Int64Type.cpp
	StringType.cpp
	UserType.cpp
	VoidType.cpp
)

SET(HEADERS
	BoolType.h
	DoubleType.h
	EnumerationType.h
	FloatType.h
	Int16Type.h
	Int32Type.h
	Int64Type.h
	StringType.h
	UserType.h
	VoidType.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)
add_include(Projects/Utils)

build_static_lib(CoreRuntimeBuildInTypes "")
