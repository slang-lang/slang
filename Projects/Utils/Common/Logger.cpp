
// Header
#include "Logger.h"

// Library includes
#include <cstdlib>

// Project include
#include <Tools/Strings.h>

// Namespace declarations
using Utils::Tools::toString;


namespace Utils {
namespace Common {


Logger::Logger()
: mContext( nullptr ),
  mHasParent( false ),
  mLoudness( LoudnessMethod )
{
}

Logger::Logger( const ILogger* parent, const std::string& className, const std::string& key )
: mContext( nullptr ),
  mHasParent( false ),
  mKey( key ),
  mLoudness( LoudnessMethod )
{
	if ( parent ) {
		mContext = parent->getContext();
		mHasParent = true;

		if ( parent->getClassName().length() > 0 ) {
			mClassName = parent->getClassName() + "::";
		}
	}

	mClassName += className;
}

const std::string& Logger::getClassName() const
{
	return mClassName;
}

IContext* Logger::getContext() const
{
	return mContext;
}

ILogger* Logger::getLogger()
{
	return this;
}

void Logger::Log( const std::string& logLevel, const std::string& message, char* file, unsigned int line )
{
	std::string msg = "[" + logLevel + "] ";
	if ( !mClassName.empty() ) {
		msg += mClassName;
		if ( !mKey.empty() ) {
			msg += "[" + mKey + "]";
		}
		msg += ": ";
	}
	msg += message;
	msg += "   [" + toString( file ) + ":" + toString( line ) + "]";

	mContext->write( msg );
}

void Logger::LogDebug( const std::string& message, char* file, unsigned int line )
{
	if ( mLoudness < LoudnessDebug ) {
		return;
	}

	Log( "DEBUG", message, file, line );
}

void Logger::LogDeprecate( const std::string& message, char* file, unsigned int line )
{
	if ( mLoudness < LoudnessDeprecated ) {
		return;
	}

	Log( "DEPRECATED", message, file, line );
}

void Logger::LogError( const std::string& message, char* file, unsigned int line )
{
	if ( mLoudness < LoudnessError ) {
		return;
	}

	Log( "ERROR", message, file, line );
}

void Logger::LogFatal( const std::string& message, char* file, unsigned int line )
{
	Log( "FATAL", message, file, line );

	assert( !"Fatal error occurred!" );
	exit( 1 );
}

void Logger::LogInfo( const std::string& message, char* file, unsigned int line )
{
	if ( mLoudness < LoudnessInfo ) {
		return;
	}

	Log( "INFO", message, file, line );
}

void Logger::LogMethod( const std::string& message, char* file, unsigned int line )
{
	if ( mLoudness < LoudnessMethod ) {
		return;
	}

	Log( "METHOD", message, file, line );
}

void Logger::LogWarn( const std::string& message, char* file, unsigned int line )
{
	if ( mLoudness < LoudnessWarning ) {
		return;
	}

	Log( "WARN ", message, file, line );
}

void Logger::setKey( const std::string& key )
{
	mKey = key;
}

void Logger::setLoudness( int loudness )
{
	mLoudness = loudness;
}


}
}
