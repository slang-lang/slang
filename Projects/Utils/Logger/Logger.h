
#ifndef Utils_Common_Logger_h
#define Utils_Common_Logger_h


#ifdef _MSC_VER
	#pragma warning(disable : 4127)
	#pragma warning(disable : 4996)
#endif


// Library includes
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


// Project includes
#include <Interfaces/Common/ILogger.h>
#include "Context.h"

// Forward declarations

// Namespace declarations


#define UnstreamLogMessage(msgstr, ostream_expr) \
	std::ostringstream _ostr_; \
	_ostr_ << ostream_expr; \
	msgstr = _ostr_.str();

#define OSdebug(message) (const char*)message;
#define OSdeprecated(message) (const char*)message;
#define OSerror(message) (const char*)message;
#define OSexperimental(message) (const char*)message;
#define OSinfo(message) (const char*)message;
#define OSwarn(message) (const char*)message;

#ifdef LOG_LEVEL
#	include <iostream>
#
#	if LOG_LEVEL >= 1
#		undef OSerror
#		ifdef LOG_FILE_AND_POSITION
#			define OSerror(message) std::cerr << "[ERROR] " << message << "   " << __FILE__ << ":" << __LINE__ << std::endl;
#		else
#			define OSerror(message) std::cerr << "[ERROR] " << message << std::endl;
#		endif
#	endif
#
#	if LOG_LEVEL >= 2
#		undef OSexperimental
#		ifdef LOG_FILE_AND_POSITION
#			define OSexperimental(message)  std::cerr << "[EXPER] " << message << "   " << __FILE__ << ":" << __LINE__ << std::endl;
#		else
#			define OSexperimental(message)  std::cerr << "[EXPER] " << message << std::endl;
#		endif
#
#		undef OSwarn
#		ifdef LOG_FILE_AND_POSITION
#			define OSwarn(message)  std::cerr << "[WARN ] " << message << "   " << __FILE__ << ":" << __LINE__ << std::endl;
#		else
#			define OSwarn(message)  std::cerr << "[WARN ] " << message << std::endl;
#		endif
#	endif
#
#	if LOG_LEVEL >= 3
#		undef OSdeprecated
#		ifdef LOG_FILE_AND_POSITION
#			define OSdeprecated(message)  std::cerr << "[DEPR ] " << message << "   " << __FILE__ << ":" << __LINE__ << std::endl;
#		else
#			define OSdeprecated(message)  std::cerr << "[DEPR ] " << message << std::endl;
#		endif
#
#		undef OSinfo
#		ifdef LOG_FILE_AND_POSITION
#			define OSinfo(message)  std::cerr << "[INFO ] " << message << "   " << __FILE__ << ":" << __LINE__ << std::endl;
#		else
#			define OSinfo(message)  std::cerr << "[INFO ] " << message << std::endl;
#		endif
#	endif
#
#	if LOG_LEVEL >= 4
#		undef OSdebug
#		ifdef LOG_FILE_AND_POSITION
#			define OSdebug(message) std::cerr << "[DEBUG] " << message << "   " << __FILE__ << ":" << __LINE__ << std::endl;
#		else
#			define OSdebug(message) std::cerr << "[DEBUG] " << message << std::endl;
#		endif
#	endif
#endif


namespace Utils {
namespace Common {


class Logger : public ILogger
{
public:
	virtual ~Logger() = default;

public:
	const std::string& getClassName() const;
	IContext* getContext() const;
	ILogger* getLogger();

	void LogDebug( const std::string& message, const std::string& file, unsigned int line );
	void LogDeprecate( const std::string& message, const std::string& file, unsigned int line );
	void LogError( const std::string& message, const std::string& file, unsigned int line );
	void LogFatal( const std::string& message, const std::string& file, unsigned int line );
	void LogInfo( const std::string& message, const std::string& file, unsigned int line );
	void LogMethod( const std::string& message, const std::string& file, unsigned int line );
	void LogWarn( const std::string& message, const std::string& file, unsigned int line );

	void setKey( const std::string& key );
	void setLoudness( int loudness );

protected:
	Logger();
	Logger( const ILogger* parent, const std::string& className, std::string key = "" );

	void Log( const std::string& logLevel, const std::string& message, const std::string& file, unsigned int line );

protected:
	std::string mClassName;
	IContext* mContext;
	bool mHasParent;
	std::string mKey;
	int mLoudness;
};


}
}


#endif
