
#ifndef ObjectiveScript_Core_Preprocessor_h
#define ObjectiveScript_Core_Preprocessor_h


// Library includes
#include <string>

// Project includes
#include "Token.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Designtime {
	class BluePrintGeneric;
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
	void process(Designtime::BluePrintGeneric* blueprint);

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
	Designtime::BluePrintGeneric* mBluePrint;
	Repository *mRepository;
	IScope *mScope;
	TokenList mTokens;
};


}


#endif
