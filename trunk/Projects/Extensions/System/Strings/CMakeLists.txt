INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Strings.cpp
)

SET(HEADERS
	StrFind.h
	StrLen.h
	StrLPad.h
	StrLTrim.h
	StrRPad.h
	StrRTrim.h
	StrTrim.h
	SubStr.h
	ToLower.h
	ToUpper.h
)

SET(DEPENDENCIES
	Utils
	Core
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/Utils)

build_static_lib(ExtensionsSystemStrings "")
