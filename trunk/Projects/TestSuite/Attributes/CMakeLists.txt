INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
    Fixture.cpp
    PrototypeTest.cpp
)

SET(HEADERS
    Fixture.h
    PrototypeTest.h
)

SET(DEPENDENCIES
	Core
)

build_static_lib(Test_Prototype "")

