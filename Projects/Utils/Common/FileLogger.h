
#ifndef Utils_Common_FileLogger_h
#define Utils_Common_FileLogger_h


// Library includes

// Project includes
#include "Logger.h"

// Forward declarations

// Namespace declarations


namespace Utils {
namespace Common {


class FileLogger : public Logger
{
public:
	explicit FileLogger( const std::string& logfile );
	FileLogger( const ILogger* parent, const std::string& className, const std::string& key = "" );
	~FileLogger();

private:
	std::string mLogFile;
};


}
}


#endif