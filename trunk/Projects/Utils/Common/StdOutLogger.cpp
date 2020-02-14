
// Header
#include "StdOutLogger.h"

// Library includes
#include <cassert>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

// Project includes
#include <Tools/Strings.h>

// Namespace declarations
using Utils::Tools::toString;


namespace Utils {
namespace Common {


StdOutLogger::StdOutLogger()
: mContext(NULL),
  mHasParent(false),
  mLoudness(ILogger::LoudnessDebug)
{
	mContext = new StdOutContext();
}

StdOutLogger::StdOutLogger(const ILogger *parent, const std::string& className, const std::string& key)
: mContext(NULL),
  mHasParent(false),
  mKey(key),
  mLoudness(ILogger::LoudnessDebug)
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

const std::string& StdOutLogger::getClassName() const
{
	return mClassName;
}

IContext* StdOutLogger::getContext() const
{
	return mContext;
}

ILogger* StdOutLogger::getLogger()
{
	return this;
}

void StdOutLogger::Log(const std::string& logLevel, const std::string& message, char* file, unsigned int line)
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
	msg += "   [" + toString(file) + ":" + toString(line) + "]";

	mContext->write(msg.c_str());
}

void StdOutLogger::LogDebug(const std::string& message, char* file, unsigned int line)
{
	if ( mLoudness < LoudnessDebug ) {
		return;
	}

	Log("DEBUG", message, file, line);
}

void StdOutLogger::LogDeprecate(const std::string& message, char* file, unsigned int line)
{
	if ( mLoudness < LoudnessDeprecated ) {
		return;
	}

	Log("DEPRECATED", message, file, line);
}

void StdOutLogger::LogError(const std::string& message, char* file, unsigned int line)
{
	if ( mLoudness < LoudnessError ) {
		return;
	}

	Log("ERROR", message, file, line);
}

void StdOutLogger::LogFatal(const std::string& message, char* file, unsigned int line)
{
	Log("FATAL", message, file, line);

	assert(!"Fatal error occurred!");
	exit(1);
}

void StdOutLogger::LogInfo(const std::string& message, char* file, unsigned int line)
{
	if ( mLoudness < LoudnessInfo ) {
		return;
	}

	Log("INFO", message, file, line);
}

void StdOutLogger::LogMethod(const std::string& message, char* file, unsigned int line)
{
	if ( mLoudness < LoudnessMethod ) {
		return;
	}

	Log("METHOD", message, file, line);
}

void StdOutLogger::LogWarn (const std::string& message, char* file, unsigned int line)
{
	if ( mLoudness < LoudnessWarning ) {
		return;
	}

	Log("WARN ", message, file, line);
}

void StdOutLogger::setKey(const std::string& key)
{
	mKey = key;
}

void StdOutLogger::setLoudness(int loudness)
{
	mLoudness = loudness;
}


}
}
