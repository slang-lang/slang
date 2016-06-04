INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
    Fixture.cpp
    LibraryTest.cpp
)

SET(HEADERS
    Fixture.h
    LibraryTest.h
)

SET(DEPENDENCIES
	ExtensionsSystem
	Core
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/TestSuite)
add_include(Projects/Utils)

build_static_lib(Test_Library "")

