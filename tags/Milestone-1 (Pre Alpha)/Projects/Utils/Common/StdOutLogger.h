
#ifndef Utils_Common_StdOutLogger_h
#define Utils_Common_StdOutLogger_h


// Library includes
#include <string>

// Project includes
#include <Interfaces/Common/ILogger.h>
#include "Context.h"

// Forward declarations

// Namespace declarations

namespace Utils {
namespace Common {


class StdOutLogger : public ILogger
{
public:
	StdOutLogger();
	StdOutLogger(const ILogger *parent, const std::string& className, const std::string& key = "");
	~StdOutLogger();

public:
	const std::string& getClassName() const;
	IContext* getContext() const;
	ILogger* getLogger();

public:
	void LogDebug(const std::string& message, char* file, unsigned int line);
	void LogDeprecate(const std::string& message, char *file, unsigned int line);
	void LogError(const std::string& message, char* file, unsigned int line);
	void LogFatal(const std::string& message, char* file, unsigned int line);
	void LogInfo (const std::string& message, char *file, unsigned int line);
	void LogMethod(const std::string& message, char *file, unsigned int line);
	void LogWarn (const std::string& message, char* file, unsigned int line);

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
	int mLoudness;
};


}
}


#endif
