
// Header
#include "Context.h"

// Library includes

// Project includes

// Namespace declarations


namespace Utils {
namespace Common {


Context::Context(const char* file)
{
	mLogFile.open(file, std::ios::app);
}

Context::~Context()
{
	mLogFile.close();
}

void Context::write(const char* msg)
{
	mLogFile << msg << std::endl;
	mLogFile << std::flush;
}


void StdOutContext::write(const char* msg)
{
	std::cout << msg << std::endl;
}


}
}
