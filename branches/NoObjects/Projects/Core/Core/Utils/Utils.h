
#ifndef ObjectiveScript_Utils_Utils_h
#define ObjectiveScript_Utils_Utils_h


// Library includes

// Project includes

// Forward declarations

// Namespace declarations


#define WRITE_LOGS
//#define WRITE_LOGS_WITH_FILENAMES

#ifdef WRITE_LOGS
	#define OSdebug(message) std::cout << "[DEBUG] " << message << std::endl;
	#define OSerror(message) std::cout << "[ERROR] " << message << std::endl;
	#define OSinfo(message) std::cout << "[INFO ] " << message << std::endl;
	#define OSwarn(message) std::cout << "[WARN ] " << message << std::endl;
#else
	#ifdef WRITE_LOGS_WITH_FILENAMES
		#define OSdebug(message) std::cout << "[DEBUG] " << message << "   " << __FILE__ << ":" << __LINE__ << std::endl;
		#define OSerror(message) std::cout << "[ERROR] " << message << "   " << __FILE__ << ":" << __LINE__ << std::endl;
		#define OSinfo(message) std::cout << "[INFO ] " << message << "   " << __FILE__ << ":" << __LINE__ << std::endl;
		#define OSwarn(message) std::cout << "[WARN ] " << message << "   " << __FILE__ << ":" << __LINE__ << std::endl;
	#else
		#define OSdebug(message) (const char*)message;
		#define OSerror(message) (const char*)message;
		#define OSinfo(message) (const char*)message;
		#define OSwarn(message) (const char*)message;
	#endif
#endif


namespace ObjectiveScript {




}


#endif
