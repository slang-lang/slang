
#ifndef ObjectiveScript_Utils_Utils_h
#define ObjectiveScript_Utils_Utils_h


// Library includes

// Project includes

// Forward declarations

// Namespace declarations


//#define WRITE_LOGS
#ifdef WRITE_LOGS
#define OSdebug(message) std::cout << "[DEBUG] " << message << " in " << __FUNCTION__ << std::endl;
#define OSerror(message) std::cout << "[ERROR] " << message << " in " << __FUNCTION__ << std::endl;
#define OSinfo(message) std::cout << "[INFO ] " << message << " in " << __FUNCTION__ << std::endl;
#define OSwarn(message) std::cout << "[WARN ] " << message << " in " << __FUNCTION__ << std::endl;
#else
#define OSdebug(message)
#define OSerror(message)
#define OSinfo(message)
#define OSwarn(message)
#endif


namespace ObjectiveScript {





}


#endif
