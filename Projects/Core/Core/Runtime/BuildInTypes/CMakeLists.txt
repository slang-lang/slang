INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	BoolType.cpp
	DoubleType.cpp
	EnumerationType.cpp
	FloatObject.cpp
	Int16Type.cpp
	Int32Type.cpp
	Int64Type.cpp
	StringObject.cpp
	UserObject.cpp
	VoidObject.cpp
)

SET(HEADERS
	BoolType.h
	DoubleType.h
	EnumerationType.h
	FloatObject.h
	Int16Type.h
	Int32Type.h
	Int64Type.h
	StringObject.h
	UserObject.h
	VoidObject.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)
add_include(Projects/Utils)

build_static_lib(CoreRuntimeBuildInTypes "")
