
#ifndef Utils_Common_StdOutLogger_h
#define Utils_Common_StdOutLogger_h


// Library includes
#include <string>

// Project includes
#include "Logger.h"

// Forward declarations

// Namespace declarations

namespace Utils {
namespace Common {


class StdOutLogger : public Logger
{
public:
	StdOutLogger(const Logger *parent = 0);
	StdOutLogger(const Logger *parent, const std::string& className);

public:
	IContext* getContext() const;

public:
	void LogDebug(const std::string& message, char* file, unsigned int line);
	void LogError(const std::string& message, char* file, unsigned int line);
	void LogFatal(const std::string& message, char* file, unsigned int line);
	void LogInfo (const std::string& message, char *file, unsigned int line);
	void LogWarn (const std::string& message, char* file, unsigned int line);

protected:

private:

};


}
}


#endif
