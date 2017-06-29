
#ifndef ObjectiveScript_Core_AST_TreeOptimizer_h
#define ObjectiveScript_Core_AST_TreeOptimizer_h


// Library includes

// Project includes
#include <Core/Common/Namespace.h>

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


class TreeOptimizer
{
public:
	TreeOptimizer();
	~TreeOptimizer();

public:
	void process(MethodScope* base);

private:
	void processBluePrint(Designtime::BluePrintObject* object);
	void processMethod(Common::Method* method);
	void processNamespace(Common::Namespace* space);
};


}
}


#endif
