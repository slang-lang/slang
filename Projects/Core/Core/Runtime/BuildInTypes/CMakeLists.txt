INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	BoolType.cpp
	DoubleObject.cpp
	EnumerationObject.cpp
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
	DoubleObject.h
	EnumerationObject.h
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
