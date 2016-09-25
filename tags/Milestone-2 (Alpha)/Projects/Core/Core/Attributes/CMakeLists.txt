INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Attributes.cpp
	ImplementationType.cpp
	LanguageFeatureState.cpp
	Mutability.cpp
	ObjectType.cpp
	Visibility.cpp
)

SET(HEADERS
	Attributes.h
	ImplementationType.h
	LanguageFeatureState.h
	Mutability.h
	ObjectType.h
	Visibility.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)

build_static_lib(CoreAttributes "")
