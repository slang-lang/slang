INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Exceptions.cpp
	Position.cpp
	Utils.cpp
)

SET(HEADERS
	Exceptions.h
	Position.h
	Utils.h
)

SET(DEPENDENCIES
)

build_static_lib(CoreUtils "")
