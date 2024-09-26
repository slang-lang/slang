INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	BoolObject.cpp
	DoubleObject.cpp
	EnumerationObject.cpp
	FloatObject.cpp
	Int16Type.cpp
	Int64Type.cpp
	IntegerObject.cpp
	StringObject.cpp
	UserObject.cpp
	VoidObject.cpp
)

SET(HEADERS
	BoolObject.h
	DoubleObject.h
	EnumerationObject.h
	FloatObject.h
	Int16Type.h
	Int64Type.h
	IntegerObject.h
	StringObject.h
	UserObject.h
	VoidObject.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)

build_static_lib(CoreDesigntimeBuildInTypes "")
