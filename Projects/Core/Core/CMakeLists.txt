INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(AST)
ADD_SUBDIRECTORY(Attributes)
ADD_SUBDIRECTORY(Common)
ADD_SUBDIRECTORY(Designtime)
ADD_SUBDIRECTORY(Extensions)
#ADD_SUBDIRECTORY(Interfaces)
ADD_SUBDIRECTORY(Runtime)
ADD_SUBDIRECTORY(VirtualMachine)

SET(SOURCES
	Object.cpp
	Scope.cpp
	Symbol.cpp
)

SET(HEADERS
	Consts.h
	Defines.h
	MemleakCheck.h
	Object.h
	Slang.h
	Scope.h
	Symbol.h
	Version.h
)

SET(DEPENDENCIES
	CoreVirtualMachine
	CoreRuntimeBuildInTypes
	CoreRuntime
	CoreExtensions
	CoreDebugger
	CoreDesigntimeParser
	CoreDesigntimeBuildInTypes
	CoreDesigntime
	CoreCommon
	CoreAttributes
	CoreAST
	Utils
)

SET(MODULES
)

add_include(Projects/Core)
add_include(Projects/Utils)

build_static_lib(Core "${MODULES}")

