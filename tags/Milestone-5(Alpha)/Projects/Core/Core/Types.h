
#ifndef ObjectiveScript_Core_Types_h
#define ObjectiveScript_Core_Types_h

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


namespace ObjectiveScript {

bool isAtomicType(const std::string& type);

std::string toString(const Parameter& param);
std::string toString(const ParameterList& list);
std::string toString(const Runtime::ReferencesList& list);
std::string toString(const StringList& list);

StringSet provideAtomicTypes();
StringSet provideLanguageFeatures();
StringSet provideKeyWords();
StringSet provideModifiers();
StringSet provideReservedWords();


}


#endif