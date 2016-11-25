INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	JsonExtension.cpp
)

SET(HEADERS
	FromJson.h
	JsonExtension.h
	ToJson.h
)

SET(DEPENDENCIES
	Utils
	Core
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/Utils)

build_static_lib(ExtensionsJson "")
