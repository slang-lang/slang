
#ifndef ObjectiveScript_Preprocessor_h
#define ObjectiveScript_Preprocessor_h


// Library includes
#include <list>
#include <string>

// Project includes
#include "Parameter.h"
#include "Token.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Designtime {
	class BluePrint;
}
class IScope;
class MethodScope;
namespace Runtime {
	class Method;
	class Object;
}
class Repository;

class Preprocessor
{
public:
	Preprocessor(Repository *repo);

public:
	void process(Designtime::BluePrint* blueprint);

private:
	Designtime::BluePrint* createMember(TokenIterator start) const;
	Runtime::Method* createMethod(TokenIterator start) const;

	void generateObject();
	void generateTokens(const std::string& content);

private:
	std::string mFilename;
	Designtime::BluePrint *mBluePrint;
	Repository *mRepository;
	IScope *mScope;
	TokenList mTokens;
};


}


#endif
