INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(Console)
ADD_SUBDIRECTORY(IO)
ADD_SUBDIRECTORY(Math)
ADD_SUBDIRECTORY(Strings)

SET(SOURCES
	System.cpp
	SystemExtension.cpp
)

SET(HEADERS
	AssertMsg.h
	GetChar.h
	GetEnv.h
	SetKeyboardBlockingMode.h
	Sleep.h
	StdTime.h
	System.h
	SystemExtension.h
	Write.h
	WriteLn.h
)

SET(DEPENDENCIES
	ExtensionsSystemStrings
	ExtensionsSystemMath
	ExtensionsSystemIO
    ExtensionsSystemConsole
	Utils
	Core
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/Utils)

build_static_lib(ExtensionsSystem "")