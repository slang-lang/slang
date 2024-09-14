
#ifndef Utils_Common_StdOutLogger_h
#define Utils_Common_StdOutLogger_h


// Library includes

// Project includes
#include "Logger.h"

// Forward declarations

// Namespace declarations

namespace Utils {
namespace Common {


class StdOutLogger : public Logger
{
public:
	StdOutLogger();
	StdOutLogger( const ILogger* parent, const std::string& className, const std::string& key = "" );
	~StdOutLogger();
};


}
}


#endif
