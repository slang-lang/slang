INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Module.cpp
	Repository.cpp
)

SET(HEADERS
	Consts.h
	Defines.h
	Dependency.h
	Module.h
	Repository.h
	Restriction.h
)

SET(DEPENDENCIES
	Core
	Utils
)

add_include(Projects/Core)
add_include(Projects/slang-pkg)
add_include(Projects/Utils)

build_static_lib(PackageCommon "json")
