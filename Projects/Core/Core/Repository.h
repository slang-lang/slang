
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
	void CollectGarbage();
	GlobalScope* getGlobalScope() const;

public:
	void addBlueprint(const Designtime::BluePrint& object);
	void addPrototype(const Designtime::Prototype& prototype);

	Runtime::Object* createInstance(const std::string& type, const std::string& name, const std::string& prototype = "");

	void addReference(Runtime::Object *object);
	void removeReference(Runtime::Object *object);

	bool isAlreadyKnown(const std::string& name) const;

protected:

private:
	typedef std::map<Runtime::Object*, int> ReferenceCountedObjects;

private:
	Runtime::Object* createObject(const std::string& name, Designtime::BluePrint* blueprint);
	Runtime::Object* createUserObject(const std::string& name, Designtime::BluePrint* blueprint);
	void initializeObject(Runtime::Object *object, Designtime::BluePrint* blueprint);

private:
	Designtime::BluePrintMap mBluePrints;
	ReferenceCountedObjects mInstances;
	Designtime::PrototypeMap mPrototypes;
	GlobalScope *mScope;
};


}


#endif
