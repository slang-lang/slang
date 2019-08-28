INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Defines.cpp
	IO.cpp
)

SET(HEADERS
	Defines.h
	FileClose.h
	FileEOF.h
	FileOpen.h
	FileRead.h
	FileSeek.h
	FileTell.h
	FileWrite.h
	IO.h
)

SET(DEPENDENCIES
	Utils
	Core
)

SET(MODULES
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/Utils)

build_static_lib(ExtensionsSystemIO "${MODULES}")
