INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	MyUnit.cpp
)

SET(HEADERS
	GenericTest.h
	MyUnit.h
	TestFixture.h
	TestFramework.h
)

SET(DEPENDENCIES )

add_include( Projects/Utils )

build_static_lib( UtilsMyUnit "" )
