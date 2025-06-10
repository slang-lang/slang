INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	math.cpp
)

SET(HEADERS
	math.hpp
)

SET(DEPENDENCIES
	CoreExtensions
)

SET(MODULES
	json
)

SET(MODULES
)

add_include(Projects/Core)
add_include(Projects/Extensions)

build_static_lib(ExtensionsLIBCMath "${MODULES}")
