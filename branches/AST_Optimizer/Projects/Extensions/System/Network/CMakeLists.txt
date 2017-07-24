INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Defines.cpp
	NetworkExtension.cpp
)

SET(HEADERS
	Accept.h
	Bind.h
	Close.h
	Connect.h
	Defines.h
	Listen.h
	NetworkExtension.h
	Receive.h
	Send.h
	Socket.h
)

SET(DEPENDENCIES
	Utils
	Core
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/Utils)

build_static_lib(ExtensionsSystemNetwork "")
