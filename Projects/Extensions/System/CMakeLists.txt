INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(IO)

SET(SOURCES
	AssertMsg.cpp
	SystemExtension.cpp
)

SET(HEADERS
	AssertMsg.h
	GetEnv.h
	Print.h
	SystemExtension.h
	Write.h
	WriteLn.h
)

SET(DEPENDENCIES
	ExtensionsSystemIO
	Utils
	Core
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/Utils)

build_static_lib(ExtensionsSystem "")
