
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
	class BluePrintObject;
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
	void process(Designtime::BluePrintObject* blueprint);

private:
	bool buildQualifiedNames(TokenIteratorMutable& token, bool skipFirstToken);
	Designtime::BluePrintObject* createMember(TokenIterator start) const;
	Runtime::Method* createMethod(TokenIterator start) const;

	void generateBluePrintObject();
	void generateBluePrintEnum();
	void generateTokens(const std::string& content);
	void rebuildBluePrintObject();

private:
	std::string mFilename;
	Designtime::BluePrintObject *mBluePrint;
	Repository *mRepository;
	IScope *mScope;
	TokenList mTokens;
};


}


#endif
