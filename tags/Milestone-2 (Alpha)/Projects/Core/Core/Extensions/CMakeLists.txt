INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	AExtension.cpp
)

SET(HEADERS
	AExtension.h
)

SET(DEPENDENCIES
)

build_static_lib(CoreExtensions "")
