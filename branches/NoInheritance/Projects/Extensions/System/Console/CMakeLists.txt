INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Console.cpp
	Defines.cpp
)

SET(HEADERS
	Cerr.h
	Cin.h
	Console.h
	Cout.h
	Defines.h
	Endl.h
)

SET(DEPENDENCIES
	Utils
	Core
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/Utils)

build_static_lib(ExtensionsSystemConsole "")
