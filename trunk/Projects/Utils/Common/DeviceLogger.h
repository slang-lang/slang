
#ifndef Utils_Common_DeviceLogger_h
#define Utils_Common_DeviceLogger_h


// Library includes
#include <string.h>

// Project includes
#include "Context.h"
#include <Interfaces/Common/ILogger.h>

// Forward declarations

// Namespace declarations


namespace Utils {
namespace Common {


class DeviceLogger : public ILogger
{
public:
	DeviceLogger(const std::string& file);
	~DeviceLogger();

public:
	void Log(const std::string& loglevel, const std::string& message, char *file, unsigned int line);

protected:

private:

};


}
}


#endif
