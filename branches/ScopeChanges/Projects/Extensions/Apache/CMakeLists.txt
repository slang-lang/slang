INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	ApacheExtension.cpp
	Defs.cpp
)

SET(HEADERS
	ApacheExtension.h
	Defs.h
	Get.h
	IsSet.h
	Post.h
	Pre.h
)

SET(DEPENDENCIES
	CoreExtensions
)

SET(MODULES
)

add_include(Projects/Core)
add_include(Projects/Extensions)

build_static_lib(ExtensionsApache "${MODULES}")
