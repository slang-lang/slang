INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Normals.cpp
	Tools.cpp
	Trigonometrics.cpp
	Vector3.cpp
)

SET(HEADERS
	Matrix4.h
	Normals.h
	Tools.h
	Trigonometrics.h
	Tuple2.h
	Tuple3.h
	Tuple4.h
	Vector2.h
	Vector3.h
	Vector4.h
)

SET(DEPENDENCIES )

build_static_lib(UtilsMath "")
