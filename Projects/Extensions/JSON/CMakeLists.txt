INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	FromJson.cpp
	JsonExtension.cpp
	ToJson.cpp
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
