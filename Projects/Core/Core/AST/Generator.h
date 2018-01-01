
#ifndef ObjectiveScript_Core_AST_Generator_h
#define ObjectiveScript_Core_AST_Generator_h


// Library includes
#include <list>

// Project includes
#include <Core/Common/Exceptions.h>
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
class Repository;
namespace Runtime {
	class Object;
}

namespace AST {


class Generator
{
public:
	explicit Generator(bool collectErrors = false);
	~Generator();

public:
	size_t hasErrors() const;
	void process(MethodScope* base);

private:
	void processBluePrint(Designtime::BluePrintObject* object);
	void processMethod(Common::Method* method, Runtime::Object* thisObject);
	void processNamespace(Common::Namespace* space);

private:
	typedef std::list<Common::Exceptions::Exception> ErrorList;

private:
	bool mCollectErrors;
	size_t mErrorCount;
	Repository* mRepository;
};


}
}


#endif
