INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(AST)
ADD_SUBDIRECTORY(Attributes)
ADD_SUBDIRECTORY(BuildInObjects)
ADD_SUBDIRECTORY(Common)
ADD_SUBDIRECTORY(Designtime)
ADD_SUBDIRECTORY(Extensions)
#ADD_SUBDIRECTORY(Interfaces)
ADD_SUBDIRECTORY(Runtime)
ADD_SUBDIRECTORY(VirtualMachine)

SET(SOURCES
	Interpreter.cpp
	Object.cpp
	Parameter.cpp
	Scope.cpp
	Symbol.cpp
	Tools.cpp
	Types.cpp
)

SET(HEADERS
	Consts.h
	Defines.h
	Interpreter.h
	Object.h
	ObjectiveScript.h
	Parameter.h
	Scope.h
	Symbol.h
	Tools.h
	Types.h
)

SET(DEPENDENCIES
	CoreVirtualMachine
	CoreRuntime
	CoreExtensions
	CoreDebugger
	CoreDesigntimeParser
	CoreDesigntimeBuildInTypes
	CoreDesigntime
	CoreCommon
	CoreBuildInObjects
	CoreAttributes
	CoreAST
	Utils
)

add_include(Projects/Core)
add_include(Projects/Debugger)
add_include(Projects/Utils)

build_static_lib(Core "")
