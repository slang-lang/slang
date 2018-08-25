INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Files.cpp
	Printer.cpp
	Strings.cpp
	Tools.cpp
)

SET(HEADERS
	Files.h
	Printer.h
	Strings.h
	Tools.h
)

SET(DEPENDENCIES )

add_include(Projects/Utils)

build_static_lib(UtilsTools "")
