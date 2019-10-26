INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Defines.cpp
	StringsExtension.cpp
)

SET(HEADERS
	Defines.h
	StrFind.h
	StringsExtension.h
	StrLen.h
	StrLPad.h
	StrLTrim.h
	StrPos.h
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

SET(MODULES
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/Utils)

build_static_lib(ExtensionsSystemStrings "${MODULES}")
