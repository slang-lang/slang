INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Bool.cpp
	Number.cpp
	String.cpp
	UserObject.cpp
	Void.cpp
)

SET(HEADERS
	Bool.h
	Number.h
	String.h
	UserObject.h
	Void.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)

build_static_lib(CoreBuildInObjects "")
