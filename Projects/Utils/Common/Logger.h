
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

#define UnstreamLogMessage(msgstr, ostream_expr) \
	std::ostringstream _ostr_; \
	_ostr_ << ostream_expr; \
	msgstr = _ostr_.str();


// Project includes
#include <Interfaces/Common/ILogger.h>
#include "Context.h"

// Forward declarations

// Namespace declarations


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

	void LogDebug( const std::string& message, char* file, unsigned int line );
	void LogDeprecate( const std::string& message, char* file, unsigned int line );
	void LogError( const std::string& message, char* file, unsigned int line );
	void LogFatal( const std::string& message, char* file, unsigned int line );
	void LogInfo( const std::string& message, char* file, unsigned int line );
	void LogMethod( const std::string& message, char* file, unsigned int line );
	void LogWarn( const std::string& message, char* file, unsigned int line );

	void setKey( const std::string& key );
	void setLoudness( int loudness );

protected:
	Logger();
	Logger( const ILogger* parent, const std::string& className, const std::string& key = "" );

	void Log( const std::string& logLevel, const std::string& message, char* file, unsigned int line );

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
