INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Exceptions.cpp
	Position.h
)

SET(HEADERS
	Exceptions.h
	Position.h
)

SET(DEPENDENCIES
)

build_static_lib(CoreUtils "")
