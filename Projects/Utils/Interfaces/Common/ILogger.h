
#ifndef Utils_Interfaces_Common_ILogger_h
#define Utils_Interfaces_Common_ILogger_h


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace Utils {
namespace Common {

// Forward declarations
class IContext;


class ILogger
{
public:
	virtual ~ILogger() = default;

public:
	static constexpr int LoudnessMute = -1;
	static constexpr int LoudnessError = 0;
	static constexpr int LoudnessWarning = 1;
	static constexpr int LoudnessInfo = 2;
	static constexpr int LoudnessMethod = 3;
	static constexpr int LoudnessDeprecated = 4;
	static constexpr int LoudnessDebug = 5;

public:
	virtual const std::string& getClassName() const = 0;
	virtual IContext* getContext() const = 0;
	virtual ILogger* getLogger() = 0;

	virtual void LogDebug(const std::string& message, const std::string& file, unsigned int line) = 0;
	virtual void LogDeprecate(const std::string& message, const std::string& file, unsigned int line) = 0;
	virtual void LogError(const std::string& message, const std::string& file, unsigned int line) = 0;
	virtual void LogFatal(const std::string& message, const std::string& file, unsigned int line) = 0;
	virtual void LogInfo(const std::string& message, const std::string& file, unsigned int line) = 0;
	virtual void LogMethod(const std::string& message, const std::string& file, unsigned int line) = 0;
	virtual void LogWarn(const std::string& message, const std::string& file, unsigned int line) = 0;

	virtual void setLoudness(int loudness) = 0;
};


}
}


#endif
