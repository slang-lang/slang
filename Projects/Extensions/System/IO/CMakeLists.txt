INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	IO.cpp
)

SET(HEADERS
	FileClose.h
#	FileEOF.h
	FileOpen.h
	FileRead.h
	FileSeek.h
	FileWrite.h
	IO.h
)

SET(DEPENDENCIES
	Utils
	Core
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/Utils)

build_static_lib(ExtensionsSystemIO "")
