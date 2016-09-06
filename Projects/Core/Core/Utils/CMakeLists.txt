INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
		../Common/Exceptions.cpp
		../Common/Position.cpp
        )

SET(HEADERS
		../Common/Exceptions.h
		../Common/Position.h
        )

SET(DEPENDENCIES
)

build_static_lib(CoreUtils "")
