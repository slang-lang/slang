
#ifndef Slang_Core_Core_Types_h
#define Slang_Core_Core_Types_h

// Defines
#include "Defines.h"

// Library includes
#include <list>
#include <set>
#include <string>

// Project includes
#include <Core/Runtime/Reference.h>
#include "Parameter.h"

// Forward declarations

// Namespace declarations


typedef std::list<std::string> StringList;
typedef std::set<std::string> StringSet;


namespace Slang {

bool isAtomicType(const std::string& type);

std::string toString(const Parameter& param);
std::string toString(const ParameterList& list);
std::string toString(const Runtime::ReferencesList& list);
std::string toString(const StringList& list);

StringSet provideAccessMode();
StringSet provideAtomicTypes();
StringSet provideLanguageFeatures();
StringSet provideKeyWords();
StringSet provideModifier();
StringSet provideMutability();
StringSet provideReservedWords();


}


#endif
