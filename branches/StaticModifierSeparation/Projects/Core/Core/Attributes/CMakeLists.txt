INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	AccessMode.cpp
	Attributes.cpp
	ImplementationType.cpp
	LanguageFeatureState.cpp
	Mutability.cpp
	ObjectType.cpp
)

SET(HEADERS
	AccessMode.h
	Attributes.h
	ImplementationType.h
	LanguageFeatureState.h
	Mutability.h
	ObjectType.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)

build_static_lib(CoreAttributes "")
