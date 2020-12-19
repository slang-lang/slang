INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	TimeExtension.cpp
)

SET(HEADERS
	StdTime.h
	TimeExtension.h
)

SET(DEPENDENCIES
	Utils
	Core
)

SET(MODULES
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/Utils)

build_static_lib(ExtensionsSystemTime "${MODULES}")
