
// Header
#include "FileLogger.h"

// Library includes

// Project include

// Namespace declarations


namespace Utils {
namespace Common {


FileLogger::FileLogger( const std::string& logfile )
: mLogFile( logfile )
{
	mContext = new FileContext( mLogFile );
}

FileLogger::FileLogger( const ILogger* parent, const std::string& className, const std::string& key )
: Logger( parent, className, key ),
  mLogFile( "logger.log" )
{
	if ( !mContext ) {
		mContext = new FileContext( mLogFile );
	}
}

FileLogger::~FileLogger()
{
	if ( !mHasParent ) {
		delete mContext;
	}
}


}
}
