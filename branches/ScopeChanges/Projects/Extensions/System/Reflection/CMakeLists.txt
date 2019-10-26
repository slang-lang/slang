INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	ReflectionExtension.cpp
)

SET(HEADERS
	CreateInstance.h
	IsKnownType.h
	ReflectionExtension.h
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

build_static_lib(ExtensionsSystemReflection "${MODULES}")
