
#ifndef Core_Common_StringTools_h
#define Core_Common_StringTools_h


// Library includes
#include <stdlib.h>
#include <string.h>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Common {


extern int MaxInt;


class Strings
{
public:
	/* Duplicates the specified string mValue.
	 * @param mValue Pointer to the string to duplicate. Must be zero-terminated if
	 *              length is "unknown".
	 * @param length Length of the mValue. if equals to unknown, then it will be
	 *               computed using strlen(mValue).
	 * @return Pointer on the duplicate instance of string.
	 */
	static inline char* duplicateStringValue(const char* value, size_t length) {
		// Avoid an integer overflow in the call to malloc below by limiting length
		// to a sane mValue.
		if ( length >= static_cast<size_t>(MaxInt) ) {
			length = MaxInt - 1;
		}

		char* newString = static_cast<char*>(malloc(length + 1));
		if ( newString == NULL ) {
			//throwRuntimeError("in Json::Value::duplicateStringValue(): Failed to allocate string mValue buffer");
		}

		memcpy(newString, value, length);
		newString[length] = 0;
		return newString;
	}

	static inline void releaseStringValue(char* value, unsigned /*length*/)  {
		free(value);
	}
};


}
}


#endif
