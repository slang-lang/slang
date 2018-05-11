INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	BoolObject.cpp
	DoubleObject.cpp
	EnumerationObject.cpp
	FloatObject.cpp
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
	IntegerObject.h
	StringObject.h
	UserObject.h
	VoidObject.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)
add_include(Projects/Utils)

build_static_lib(CoreBuildInObjects "")
