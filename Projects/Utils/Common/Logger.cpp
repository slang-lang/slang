
// Header
#include "Logger.h"

// Library includes
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

// Project include
#include <Tools/Strings.h>

// Namespace declarations
using Utils::Tools::toString;


namespace Utils {
namespace Common {


FileLogger::FileLogger(char* logfile)
: mContext(NULL),
  mHasParent(false),
  mLogFile(logfile),
  mLoudness(FileLogger::LoudnessMethod)
{
	if ( !mContext ) {
		mContext = new FileContext(mLogFile.c_str());
	}
}

FileLogger::FileLogger(const ILogger* parent, const std::string& className, const std::string& key)
: mContext(NULL),
  mHasParent(false),
  mKey(key),
  mLogFile("logger.log"),
  mLoudness(FileLogger::LoudnessMethod)
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
		mContext = new FileContext(mLogFile.c_str());
	}
}

FileLogger::~FileLogger()
{
	if ( !mHasParent ) {
		delete mContext;
	}
}

const std::string& FileLogger::getClassName() const
{
	return mClassName;
}

IContext* FileLogger::getContext() const
{
	return mContext;
}

ILogger* FileLogger::getLogger()
{
	return this;
}

void FileLogger::Log(const std::string& logLevel, const std::string& message, char* file, unsigned int line)
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

void FileLogger::LogDebug(const std::string& message, char* file, unsigned int line)
{
	if ( mLoudness < LoudnessDebug ) {
		return;
	}

	Log("DEBUG", message, file, line);
}

void FileLogger::LogDeprecate(const std::string& message, char* file, unsigned int line)
{
	if ( mLoudness < LoudnessDeprecated ) {
		return;
	}

	Log("DEPRECATED", message, file, line);
}

void FileLogger::LogError(const std::string& message, char* file, unsigned int line)
{
	if ( mLoudness < LoudnessError ) {
		return;
	}

	Log("ERROR", message, file, line);
}

void FileLogger::LogFatal(const std::string& message, char* file, unsigned int line)
{
	Log("FATAL", message, file, line);

	assert(!"Fatal error occurred!");
	exit(1);
}

void FileLogger::LogInfo(const std::string& message, char* file, unsigned int line)
{
	if ( mLoudness < LoudnessInfo ) {
		return;
	}

	Log("INFO", message, file, line);
}

void FileLogger::LogMethod(const std::string& message, char* file, unsigned int line)
{
	if ( mLoudness < LoudnessMethod ) {
		return;
	}

	Log("METHOD", message, file, line);
}

void FileLogger::LogWarn(const std::string& message, char* file, unsigned int line)
{
	if ( mLoudness < LoudnessWarning ) {
		return;
	}

	Log("WARN ", message, file, line);
}

void FileLogger::setKey(const std::string& key)
{
	mKey = key;
}

void FileLogger::setLoudness(int loudness)
{
	mLoudness = loudness;
}


}
}
