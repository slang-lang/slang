INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	stdlib.cpp
)

SET(HEADERS
	stdlib.hpp
)

SET(DEPENDENCIES
	Utils
	Core
)

SET(MODULES
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/Utils)

build_static_lib(ExtensionsLIBCStdlib "${MODULES}")
