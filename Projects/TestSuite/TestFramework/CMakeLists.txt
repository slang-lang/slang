INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Fixture.cpp
	TestFrameworkTest.cpp
)

SET(HEADERS
        Fixture.h
	TestFrameworkTest.h
)

SET(DEPENDENCIES
)

build_static_lib(Test_FrameworkTest "")

