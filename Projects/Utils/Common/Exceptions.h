
#ifndef Utils_Common_Exceptions_h
#define Utils_Common_Exceptions_h


// Library includes
#include <exception>
#include <string>
#include <utility>

// Project includes

// Forward declarations

// Namespace declarations


namespace Utils {
namespace Common {
namespace Exceptions {


class Exception : public std::exception
{
public:
	explicit Exception(std::string text)
	: mText(std::move(text))
	{ }

public:
#ifdef __WIN32
	const char* what() const {
		return mText.c_str();
	}
#elif defined __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
    // iOS Simulator
#elif TARGET_OS_IPHONE
    // iOS device
    const char* what() const throw() {
        return mText.c_str();
    }
#elif TARGET_OS_MAC
    // Other kinds of Mac OS
    const char* what() const _NOEXCEPT {
        return mText.c_str();
    }
#else
    // Unsupported platform
#endif
#elif defined __linux
	const char* what() const _NOEXCEPT () {
		return mText.c_str();
	}
#endif

protected:

private:
	std::string mText;
};


}
}
}


#endif
