INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	BoolObject.cpp
	DoubleObject.cpp
	FloatObject.cpp
	GenericObject.cpp
	IntegerObject.cpp
	NumberObject.cpp
	StringObject.cpp
	UserObject.cpp
	VoidObject.cpp
)

SET(HEADERS
	BoolObject.h
	DoubleObject.h
	FloatObject.h
	GenericObject.h
	IntegerObject.h
	NumberObject.h
	StringObject.h
	UserObject.h
	VoidObject.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)
add_include(Projects/Utils)

build_static_lib(CoreBuildInObjects "")
