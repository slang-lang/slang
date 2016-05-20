
#ifndef ObjectiveScript_Utils_Utils_h
#define ObjectiveScript_Utils_Utils_h


// Library includes

// Project includes

// Forward declarations

// Namespace declarations


#define OSdebug(message) (const char*)message;
#define OSerror(message) (const char*)message;
#define OSinfo(message) (const char*)message;
#define OSwarn(message) (const char*)message;

#ifdef LOG_LEVEL
#	include <iostream>
#
#	if LOG_LEVEL >= 1
#		undef OSerror
#		ifdef LOG_FILE_AND_POSITION
#			define OSerror(message) std::cout << "[ERROR] " << message << "   " << __FILE__ << ":" << __LINE__ << std::endl;
#		else
#			define OSerror(message) std::cout << "[ERROR] " << message << std::endl;
#		endif
#	endif
#
#	if LOG_LEVEL >= 2
#		undef OSwarn
#		ifdef LOG_FILE_AND_POSITION
#			define OSwarn(message)  std::cout << "[WARN ] " << message << "   " << __FILE__ << ":" << __LINE__ << std::endl;
#		else
#			define OSwarn(message)  std::cout << "[WARN ] " << message << std::endl;
#		endif
#	endif
#
#	if LOG_LEVEL >= 3
#		undef OSinfo
#		ifdef LOG_FILE_AND_POSITION
#			define OSinfo(message)  std::cout << "[INFO ] " << message << "   " << __FILE__ << ":" << __LINE__ << std::endl;
#		else
#			define OSinfo(message)  std::cout << "[INFO ] " << message << std::endl;
#		endif
#	endif
#
#	if LOG_LEVEL >= 4
#		undef OSdebug
#		ifdef LOG_FILE_AND_POSITION
#			define OSdebug(message) std::cout << "[DEBUG] " << message << "   " << __FILE__ << ":" << __LINE__ << std::endl;
#		else
#			define OSdebug(message) std::cout << "[DEBUG] " << message << std::endl;
#		endif
#	endif
#endif


#endif
