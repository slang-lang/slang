
#ifndef ObjectiveScript_Core_Types_h
#define ObjectiveScript_Core_Types_h


// Library includes
#include <list>
#include <set>
#include <string>

// Project includes
#include <Core/Designtime/Parser/Token.h>
#include "Parameter.h"
#include "Reference.h"

// Forward declarations

// Namespace declarations


typedef std::list<std::string> StringList;
typedef std::set<std::string> StringSet;


namespace ObjectiveScript {


std::string toString(const Parameter& param);
std::string toString(const ParameterList& list);
std::string toString(const ReferencesList& list);
std::string toString(const StringList& list);
std::string toString(const TokenList& list);

StringSet provideAtomicTypes();
StringSet provideLanguageFeatures();
StringSet provideKeyWords();
StringSet provideModifiers();
StringSet providePredefinedIdentifiers();
StringSet provideReservedWords();


}


#endif
