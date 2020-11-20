
// Header
#include "Context.h"

// Library includes

// Project includes

// Namespace declarations


namespace Utils {
namespace Common {


FileContext::FileContext(const std::string& file)
{
	mLogFile.open( file.c_str(), std::ios::app );
}

FileContext::~FileContext()
{
	mLogFile.close();
}

void FileContext::write(const std::string& msg)
{
	mLogFile << msg << std::endl;
	mLogFile << std::flush;
}


void StdOutContext::write( const std::string& msg )
{
	std::cout << msg << std::endl;
}


}
}
