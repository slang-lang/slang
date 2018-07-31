
#ifndef Utils_Utils_h
#define Utils_Utils_h


// Library includes

// Project includes

// Forward declarations

// Namespace declarations


#define OSdebug(message) (const char*)message;
#define OSdeprecated(message) (const char*)message;
#define OSerror(message) (const char*)message;
#define OSexperimental(message) (const char*)message;
#define OSinfo(message) (const char*)message;
#define OSwarn(message) (const char*)message;

#ifdef LOG_LEVEL
#	include <iostream>
#
#	if LOG_LEVEL >= 1
#		undef OSerror
#		ifdef LOG_FILE_AND_POSITION
#			define OSerror(message) std::cerr << "[ERROR] " << message << "   " << __FILE__ << ":" << __LINE__ << std::endl;
#		else
#			define OSerror(message) std::cerr << "[ERROR] " << message << std::endl;
#		endif
#	endif
#
#	if LOG_LEVEL >= 2
#		undef OSexperimental
#		ifdef LOG_FILE_AND_POSITION
#			define OSexperimental(message)  std::cerr << "[EXPER] " << message << "   " << __FILE__ << ":" << __LINE__ << std::endl;
#		else
#			define OSexperimental(message)  std::cerr << "[EXPER] " << message << std::endl;
#		endif
#
#		undef OSwarn
#		ifdef LOG_FILE_AND_POSITION
#			define OSwarn(message)  std::cerr << "[WARN ] " << message << "   " << __FILE__ << ":" << __LINE__ << std::endl;
#		else
#			define OSwarn(message)  std::cerr << "[WARN ] " << message << std::endl;
#		endif
#	endif
#
#	if LOG_LEVEL >= 3
#		undef OSdeprecated
#		ifdef LOG_FILE_AND_POSITION
#			define OSdeprecated(message)  std::cerr << "[DEPR ] " << message << "   " << __FILE__ << ":" << __LINE__ << std::endl;
#		else
#			define OSdeprecated(message)  std::cerr << "[DEPR ] " << message << std::endl;
#		endif
#
#		undef OSinfo
#		ifdef LOG_FILE_AND_POSITION
#			define OSinfo(message)  std::cerr << "[INFO ] " << message << "   " << __FILE__ << ":" << __LINE__ << std::endl;
#		else
#			define OSinfo(message)  std::cerr << "[INFO ] " << message << std::endl;
#		endif
#	endif
#
#	if LOG_LEVEL >= 4
#		undef OSdebug
#		ifdef LOG_FILE_AND_POSITION
#			define OSdebug(message) std::cerr << "[DEBUG] " << message << "   " << __FILE__ << ":" << __LINE__ << std::endl;
#		else
#			define OSdebug(message) std::cerr << "[DEBUG] " << message << std::endl;
#		endif
#	endif
#endif
 

#endif

