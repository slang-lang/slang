INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(Attributes)
ADD_SUBDIRECTORY(BuildInObjects)
#ADD_SUBDIRECTORY(Interfaces)
ADD_SUBDIRECTORY(Keywords)
#ADD_SUBDIRECTORY(Plugins)
ADD_SUBDIRECTORY(Utils)

SET(SOURCES
	Analyser.cpp
	BluePrint.cpp
	Method.cpp
	Object.cpp
	Preprocessor.cpp
	Prototype.cpp
	Repository.cpp
	Script.cpp
	Token.cpp
	Tokenizer.cpp
	Tools.cpp
	Types.cpp
	Variable.cpp
	VirtualMachine.cpp
)

SET(HEADERS
	Analyser.h
	BluePrint.h
	Method.h
	Object.h
#	ObjectiveScript.h
	Preprocessor.h
	Prototype.h
	Repository.h
	Script.h
	Token.h
	Tokenizer.h
	Tools.h
	Types.h
	Variable.h
	VirtualMachine.h
)

SET(DEPENDENCIES
#	CoreUtils
	CorePlugins
	CoreKeywords
	CoreBuildInObjects
	CoreAttributes
)

add_include(Projects/Core)

build_static_lib(Core "")

