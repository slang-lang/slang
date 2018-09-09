INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Tools.cpp
	Vector3.cpp
)

SET(HEADERS
	Tools.h
	Vector2.h
	Vector3.h
	Vector4.h
)

SET(DEPENDENCIES )

build_static_lib(UtilsMath "")

