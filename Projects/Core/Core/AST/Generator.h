
#ifndef ObjectiveScript_Core_AST_Generator_h
#define ObjectiveScript_Core_AST_Generator_h


// Library includes

// Project includes
#include <Core/Common/Namespace.h>

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
class Repository;
namespace Runtime {
	class Object;
}

namespace AST {


class Generator
{
public:
	explicit Generator(bool collectErrors = false);
	~Generator() = default;

public:
	size_t hasErrors() const;
	void process(MethodScope* base);

private:
	void processBluePrint(Designtime::BluePrintObject* object);
	void processMethod(Common::Method* method);
	void processNamespace(Common::Namespace* space);

private:
	bool mCollectErrors;
	size_t mErrorCount;
	Repository* mRepository;
};


}
}


#endif
