INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Attributes.cpp
	LanguageFeatureState.cpp
	Mutability.cpp
	Visibility.cpp
)

SET(HEADERS
	Attributes.h
	LanguageFeatureState.h
	Mutability.h
	Visibility.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)

build_static_lib(CoreAttributes "")
