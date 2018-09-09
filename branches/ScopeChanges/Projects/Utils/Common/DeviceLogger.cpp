
// Header
#include "DeviceLogger.h"

// Library includes

// Project includes

// Namespace declarations


namespace Utils {
namespace Common {


DeviceLogger::DeviceLogger(const std::string& /*file*/)
{
}

void DeviceLogger::Log(const std::string& loglevel, const std::string& message, char *file, unsigned int line)
{
	(void)loglevel;
	(void)message;
	(void)file;
	(void)line;
/*
	std::string msg; //= getDateTime()
	msg += "[" + loglevel + "] ";
	if ( !mClassName.empty() ) {
	msg += mClassName;
	if ( !mKey.empty() ) {
	msg += "[" + mKey + "]";
	}
	msg += ": ";
	}
	msg += message;
	msg += "   [" + toString(file) + ":" + toString(line) + "]";

	mContext->write(msg.c_str());
*/
}

}
}

