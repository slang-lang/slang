INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	TimeExtension.cpp
)

SET(HEADERS
	StdTime.h
	TimeExtension.h
)

SET(DEPENDENCIES
	CoreExtensions
)

SET(MODULES
)

SET(MODULES
)

add_include(Projects/Core)
add_include(Projects/Extensions)

build_static_lib(ExtensionsSystemTime "${MODULES}")
