
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


namespace ObjectiveScript {


static const std::string PROTOTYPE_TYPE = "UNKNOWN";


typedef std::list<std::string> StringList;


std::string toString(const ParameterList& list);
std::string toString(const ReferencesList& list);
std::string toString(const StringList& list);
std::string toString(const TokenList& list);

StringList provideAtomarTypes();
StringList provideKeyWords();
StringList provideReservedWords();


}


#endif
