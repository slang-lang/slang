INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(IO)
ADD_SUBDIRECTORY(Strings)

SET(SOURCES
	AssertMsg.cpp
	SystemExtension.cpp
)

SET(HEADERS
	AssertMsg.h
	GetEnv.h
	Print.h
	Sleep.h
	SystemExtension.h
	Write.h
	WriteLn.h
)

SET(DEPENDENCIES
	ExtensionsSystemStrings
	ExtensionsSystemIO
	Utils
	Core
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/Utils)

build_static_lib(ExtensionsSystem "")
