
// Header
#include "StringTools.h"

// Library includes
#include <stdlib.h>

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace Common {


int MaxInt = int(unsigned(-1) / 2);


/*
char* Strings::duplicateStringValue(const char* mValue, size_t length)
{
	// Avoid an integer overflow in the call to malloc below by limiting length
	// to a sane mValue.
	if ( length >= static_cast<size_t>(MaxInt) ) {
		length = MaxInt - 1;
	}

	char* newString = static_cast<char*>(malloc(length + 1));
	if ( newString == NULL ) {
		//throwRuntimeError("in Json::Value::duplicateStringValue(): Failed to allocate string mValue buffer");
	}

	memcpy(newString, mValue, length);
	newString[length] = 0;
	return newString;
}

void Strings::releaseStringValue(char* mValue, unsigned length) {
	free(mValue);
}
*/


}
}
