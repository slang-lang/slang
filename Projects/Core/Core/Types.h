
#ifndef ObjectiveScript_Types_h
#define ObjectiveScript_Types_h


// Library includes
#include <list>
#include <string>

// Project includes
#include "Token.h"
#include "Variable.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


typedef std::list<std::string> StringList;


std::string toString(const VariablesList& list);
std::string toString(const StringList& list);
std::string toString(const TokenList& list);

StringList provideAtomarTypes();
StringList provideKeyWords();
StringList provideReservedWords();


}


#endif
