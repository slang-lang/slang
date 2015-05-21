
#ifndef Utils_Common_Logger_h
#define Utils_Common_Logger_h


#ifdef _MSC_VER
	#pragma warning(disable : 4127)
	#pragma warning(disable : 4996)
#endif


// Library includes
#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>

#define UnstreamLogMessage(msgstr, ostream_expr) \
    do {\
        std::ostringstream _ostr_; \
        _ostr_ << ostream_expr; \
        msgstr = _ostr_.str(); \
    } while (false)


// Project includes
#include <Interfaces/Common/ILogger.h>
#include "Context.h"

// Forward declarations

// Namespace declarations


#define debug(ostream_expr) do { \
            if ( this->getLogger() ) { \
                std::string _msg_; \
                UnstreamLogMessage(_msg_, ostream_expr); \
				this->LogDebug(_msg_, __FILE__, __LINE__); \
            } \
        } \
        while( false )

#define deprecate(ostream_expr) do { \
            if ( this->getLogger() ) { \
                std::string _msg_; \
                UnstreamLogMessage(_msg_, ostream_expr); \
				this->LogDeprecate(_msg_, __FILE__, __LINE__); \
            } \
        } \
        while( false )

#define error(ostream_expr) do { \
            if ( this->getLogger() ) { \
                std::string _msg_; \
                UnstreamLogMessage(_msg_, ostream_expr); \
				this->LogError(_msg_, __FILE__, __LINE__); \
            } \
        } \
        while( false )

#define fatal(ostream_expr) do { \
            if ( this->getLogger() ) { \
                std::string _msg_; \
                UnstreamLogMessage(_msg_, ostream_expr); \
				this->LogFatal(_msg_, __FILE__, __LINE__); \
            } \
        } \
        while( false )

#define info(ostream_expr) do { \
            if ( this->getLogger() ) { \
                std::string _msg_; \
                UnstreamLogMessage(_msg_, ostream_expr); \
				this->LogInfo(_msg_, __FILE__, __LINE__); \
            } \
        } \
        while( false )

#define method(ostream_expr) do { \
            if ( this->getLogger() ) { \
                std::string _msg_; \
                UnstreamLogMessage(_msg_, ostream_expr); \
				this->LogMethod(_msg_, __FILE__, __LINE__); \
            } \
        } \
        while( false )

#define warn(ostream_expr) do { \
            if ( this->getLogger() ) { \
                std::string _msg_; \
                UnstreamLogMessage(_msg_, ostream_expr); \
				this->LogWarn(_msg_, __FILE__, __LINE__); \
            } \
        } \
        while( false )


namespace Utils {
namespace Common {


class Logger : public ILogger
{
public:
	Logger(char* logfile = "logger.log");
	Logger(const ILogger *parent, const std::string& className, const std::string& key = "");
	virtual ~Logger();

public:
	const std::string& getClassName() const;
	IContext* getContext() const;
	ILogger* getLogger();

	void LogDebug(const std::string& message, char *file, unsigned int line);
	void LogDeprecate(const std::string& message, char *file, unsigned int line);
	void LogError(const std::string& message, char *file, unsigned int line);
	void LogFatal(const std::string& message, char *file, unsigned int line);
	void LogInfo(const std::string& message, char *file, unsigned int line);
	void LogMethod(const std::string& message, char *file, unsigned int line);
	void LogWarn(const std::string& message, char *file, unsigned int line);

	void setKey(const std::string& key);
	void setLoudness(int loudness);

protected:
	IContext* mContext;

private:
	std::string getDateTime();
	void Log(const std::string& loglevel, const std::string& message, char *file, unsigned int line);

private:
	std::string mClassName;
	bool mHasParent;
	std::string mKey;
	std::string mLogFile;
	int mLoudness;
};


}
}


#endif
