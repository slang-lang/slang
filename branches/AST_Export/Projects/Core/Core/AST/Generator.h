
#ifndef ObjectiveScript_Core_AST_Generator_h
#define ObjectiveScript_Core_AST_Generator_h


// Library includes
#include <string>

// Project includes
#include "NodeIdentifier.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Common {
	class Method;
	class Namespace;
}
namespace Designtime {
	class BluePrintObject;
}
class MethodScope;

namespace AST {

class Generator
{
public:
	Generator();
	~Generator();

public:
	void process(MethodScope* base);
	void store(const std::string& filename);

private:
	void processBluePrint(Designtime::BluePrintObject* object);
	void processMethod(Common::Method* method);
	void processNamespace(Common::Namespace* space);

private:
	NodeIdentifier mNodeIdentifier;
};


}
}


#endif
