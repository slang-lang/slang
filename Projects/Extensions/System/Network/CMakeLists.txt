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
	Read.h
	#Receive.h
	#Send.h
	Shutdown.h
	Socket.h
	Write.h
)

SET(DEPENDENCIES
	Utils
	Core
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/Utils)

build_static_lib(ExtensionsSystemNetwork "")
