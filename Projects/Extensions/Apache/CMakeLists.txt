INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	ApacheExtension.cpp
	Defs.cpp
)

SET(HEADERS
	ApacheExtension.h
	Defs.h
	Get.h
	Post.h
)

SET(DEPENDENCIES
	ExtensionsSystemIO
	Utils
	Core
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/Utils)

build_static_lib(ExtensionsApache "")
