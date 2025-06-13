
#ifndef Slang_Core_Core_Common_Types_h
#define Slang_Core_Core_Common_Types_h


// Library includes
#include <list>
#include <set>
#include <unordered_set>

// Project includes
#include <Core/Runtime/Reference.h>
#include <Core/Runtime/Parameter.h>

// Forward declarations

// Namespace declarations


namespace Slang {


typedef unsigned int FrameId;
typedef unsigned int ThreadId;


typedef std::set<std::string> OrderedStringSet;
typedef std::list<std::string> StringList;
typedef std::unordered_set<std::string> StringSet;


bool isAtomicType(const std::string& type);

std::string toString(const Parameter& param);
std::string toString(const ParameterList& list);
std::string toString(const Runtime::ReferencesList& list);
std::string toString(const StringList& list);

StringSet provideAccessMode();
StringSet provideAtomicTypes();
StringSet provideLanguageFeatures();
StringSet provideKeyWords();
StringSet provideMemoryLayout();
StringSet provideModifier();
StringSet provideMutability();
StringSet provideReservedWords();


}


#endif
