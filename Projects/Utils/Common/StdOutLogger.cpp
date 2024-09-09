
// Header
#include "StdOutLogger.h"

// Library includes
#include <cassert>
#include <cstdlib>
#include <utility>

// Project includes
#include <Tools/Strings.h>

// Namespace declarations
using Utils::Tools::toString;


namespace Utils {
namespace Common {


StdOutLogger::StdOutLogger()
{
	mContext = new StdOutContext();
}

StdOutLogger::StdOutLogger( const ILogger* parent, const std::string& className, const std::string& key )
: Logger( parent, className, key )
{
	if ( parent ) {
		mContext = parent->getContext();
		mHasParent = true;

		if ( parent->getClassName().length() > 0 ) {
			mClassName = parent->getClassName() + "::";
		}
	}

	mClassName += className;

	if ( !mContext ) {
		mContext = new StdOutContext();
	}
}

StdOutLogger::~StdOutLogger()
{
	if ( !mHasParent ) {
		delete mContext;
	}
}


}
}
