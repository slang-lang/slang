INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(Console)
ADD_SUBDIRECTORY(IO)
ADD_SUBDIRECTORY(Math)
ADD_SUBDIRECTORY(Network)
ADD_SUBDIRECTORY(Reflection)
ADD_SUBDIRECTORY(Strings)
ADD_SUBDIRECTORY(Time)

SET(SOURCES
	System.cpp
	SystemExtension.cpp
)

SET(HEADERS
	Ascii.h
	AssertMsg.h
	Fork.h
	GetChar.h
	GetEnv.h
	PutEnv.h
	SetEnv.h
	SetKeyboardBlockingMode.h
	Sleep.h
	System.h
	SystemExtension.h
	Write.h
	WriteLn.h
)

SET(DEPENDENCIES
	ExtensionsSystemTime
	ExtensionsSystemStrings
	ExtensionsSystemReflection
	ExtensionsSystemNetwork
	ExtensionsSystemMath
	ExtensionsSystemIO
	ExtensionsSystemConsole
	CoreExtensions
)

SET(MODULES
)

add_include(Projects/Core)
add_include(Projects/Extensions)

build_static_lib(ExtensionsSystem "${MODULES}")
