
// Header
#include "StdOutLogger.h"

// Library includes
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
: mContext(0),
  mHasParent(false),
  mLoudness(Logger::LoudnessMethod)
{
	mContext = new StdOutContext();
}

StdOutLogger::StdOutLogger(const Logger *parent, const std::string& className, const std::string& key)
: mContext(0),
  mHasParent(false),
  mKey(key),
  mLoudness(Logger::LoudnessMethod)
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

const std::string& StdOutLogger::getClassName() const
{
	return mClassName;
}

std::string StdOutLogger::getDateTime()
{
	time_t t = time(0);
	tm *lt = localtime(&t);

	char dateStr[11];
	sprintf(dateStr, "%04d-%02d-%02d", lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday);

	char timeStr[9];
	sprintf(timeStr, "%02d:%02d:%02d", lt->tm_hour, lt->tm_min, lt->tm_sec);

	return std::string(dateStr) + " " + std::string(timeStr);
}

IContext* StdOutLogger::getContext() const
{
	return mContext;
}

ILogger* StdOutLogger::getLogger()
{
	return this;
}

void StdOutLogger::Log(const std::string& loglevel, const std::string& message, char *file, unsigned int line)
{
	std::string msg = getDateTime() + " ";
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
}

void StdOutLogger::LogDebug(const std::string& message, char* file, unsigned int line)
{
	if ( mLoudness < LoudnessDebug ) {
		return;
	}

	Log("DEBUG", message, file, line);
}

void StdOutLogger::LogDeprecate(const std::string& message, char *file, unsigned int line)
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

	assert(!"Fatal error occured!");
	exit(1);
}

void StdOutLogger::LogInfo(const std::string& message, char* file, unsigned int line)
{
	if ( mLoudness < LoudnessInfo ) {
		return;
	}

	Log("INFO", message, file, line);
}

void StdOutLogger::LogMethod(const std::string& message, char *file, unsigned int line)
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
