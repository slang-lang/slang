
#ifndef ObjectiveScript_Types_h
#define ObjectiveScript_Types_h


// Library includes
#include <list>
#include <string>

// Project includes
#include "Parameter.h"
#include "Reference.h"
#include "Token.h"

// Forward declarations

// Namespace declarations


typedef std::list<std::string> StringList;


namespace ObjectiveScript {


std::string toString(const Parameter& param);
std::string toString(const ParameterList& list);
std::string toString(const ReferencesList& list);
std::string toString(const StringList& list);
std::string toString(const TokenList& list);

StringList provideAtomicTypes();
StringList provideLanguageFeatures();
StringList provideKeyWords();
StringList provideModifiers();
StringList providePredefinedIdentifiers();
StringList provideReservedWords();


}


#endif
