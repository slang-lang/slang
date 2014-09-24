INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Bool.cpp
)

SET(HEADERS
	Bool.h
	Number.h
	String.h
)

SET(DEPENDENCIES
)

build_static_lib(CoreBuildInObjects "")

