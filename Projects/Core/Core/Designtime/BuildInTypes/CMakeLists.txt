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
	UserObject.cpp
	VoidObject.cpp
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
	UserObject.h
	VoidObject.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)

build_static_lib(CoreDesigntimeBuildInTypes "")
