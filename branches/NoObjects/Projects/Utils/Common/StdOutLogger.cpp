
// Header
#include "StdOutLogger.h"

// Library includes

// Project includes

// Namespace declarations


namespace Utils {
namespace Common {


StdOutLogger::StdOutLogger(const Logger *parent)
: Logger(parent, "")
{
	mContext = new StdOutContext();
}

StdOutLogger::StdOutLogger(const Logger *parent, const std::string& className)
: Logger(parent, className)
{
	mContext = new StdOutContext();
}

IContext* StdOutLogger::getContext() const
{
	return mContext;
}

void StdOutLogger::LogDebug(const std::string& message, char* file, unsigned int line)
{
	std::cout << "[DEBUG] " << message << file << ":" << line << std::endl;
}

void StdOutLogger::LogError(const std::string& message, char* file, unsigned int line)
{
	std::cout << "[ERROR] " << message << file << ":" << line << std::endl;
}

void StdOutLogger::LogFatal(const std::string& message, char* file, unsigned int line)
{
	std::cout << "[FATAL] " << message << file << ":" << line << std::endl;

	assert(0);
}

void StdOutLogger::LogInfo(const std::string& message, char* file, unsigned int line)
{
	std::cout << "[INFO ] " << message << file << ":" << line << std::endl;
}

void StdOutLogger::LogWarn (const std::string& message, char* file, unsigned int line)
{
	std::cout << "[WARN ] " << message << file << ":" << line << std::endl;
}


}
}
