
#ifndef ObjectiveScript_Core_Types_h
#define ObjectiveScript_Core_Types_h

// Defines
#include "Defines.h"

// Library includes
#include <list>
#ifdef USE_ORDERED_COLLECTION
#	include <set>
#else
#	include <unordered_set>
#endif
#include <string>

// Project includes
#include "Parameter.h"
#include "Reference.h"

// Forward declarations

// Namespace declarations


typedef std::list<std::string> StringList;
#ifdef USE_ORDERED_COLLECTION
typedef std::set<std::string> StringSet;
#else
typedef std::unordered_set<std::string> StringSet;
#endif


namespace ObjectiveScript {


std::string toString(const Parameter& param);
std::string toString(const ParameterList& list);
std::string toString(const ReferencesList& list);
std::string toString(const StringList& list);

StringSet provideAtomicTypes();
StringSet provideLanguageFeatures();
StringSet provideKeyWords();
StringSet provideModifiers();
StringSet provideReservedWords();


}


#endif
