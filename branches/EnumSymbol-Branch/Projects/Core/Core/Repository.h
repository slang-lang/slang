
#ifndef ObjectiveScript_Repository_h
#define ObjectiveScript_Repository_h


// Library includes
#include <map>
#include <string>

// Project includes
#include <Core/Designtime/BluePrint.h>
#include <Core/Designtime/Prototype.h>
#include "Object.h"
#include "Reference.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Runtime {
	class Object;
}
class GlobalScope;

class Repository
{
public:
	Repository();
	~Repository();

public:
	GlobalScope* getGlobalScope() const;

public:
	void addBluePrint(const Designtime::BluePrint &object);
	void addPrototype(const Designtime::Prototype& prototype);

	Runtime::Object* createInstance(const std::string& type, const std::string& name = ANONYMOUS_OBJECT, bool initialize = true);
	Runtime::Object* createInstance(Designtime::BluePrint* blueprint, const std::string& name = ANONYMOUS_OBJECT, bool initialize = true);

	void addReference(Runtime::Object *object);
	void removeReference(Runtime::Object *object);

	bool isAlreadyKnown(const std::string& name) const;

	void rebuildBluePrints();

protected:

private:
	typedef std::map<Runtime::Object*, int> ReferenceCountedObjects;

private: // hide me from public
	void CollectGarbage();

private:
	Runtime::Object* createObject(const std::string& name, Designtime::BluePrint* blueprint, bool initialize);
	Runtime::Object* createUserObject(const std::string& name, Designtime::BluePrint* blueprint, bool initialize);

	void createDefaultMethods(Runtime::Object *object);
	void initializeObject(Runtime::Object *object, Designtime::BluePrint* blueprint);
	void insertBluePrintsIntoScopes();

private:
	Designtime::BluePrintMap mBluePrints;
	ReferenceCountedObjects mInstances;
	Designtime::PrototypeMap mPrototypes;
	GlobalScope *mScope;
};


}


#endif
