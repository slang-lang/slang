INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	FileClose.cpp
	FileOpen.cpp
	FileRead.cpp
	FileWrite.cpp
)

SET(HEADERS
	FileClose.h
	FileOpen.h
	FileRead.h
	FileWrite.h
)

SET(DEPENDENCIES
	Utils
	Core
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/Utils)

build_static_lib(ExtensionsSystemIO "")
