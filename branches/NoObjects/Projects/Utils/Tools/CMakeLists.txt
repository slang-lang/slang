INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Files.cpp
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

build_static_lib(UtilsTools "")
