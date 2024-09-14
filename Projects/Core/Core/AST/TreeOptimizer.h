
#ifndef Slang_Core_Core_AST_TreeOptimizer_h
#define Slang_Core_Core_AST_TreeOptimizer_h


// Library includes

// Project includes

// Forward declarations

// Namespace declarations


namespace Slang {

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
	TreeOptimizer() = default;
	virtual ~TreeOptimizer() = default;

public:
	virtual void process(MethodScope* base);

private:
	virtual void processBluePrint(Designtime::BluePrintObject* object);
	virtual void processMethod(Common::Method* method);
	virtual void processNamespace(Common::Namespace* space);
};


}
}


#endif
