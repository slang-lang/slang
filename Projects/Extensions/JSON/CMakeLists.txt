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
	CoreExtensions
)

add_include(Projects/Core)
add_include(Projects/Extensions)

build_static_lib(ExtensionsJson "json")
