
#ifndef ObjectiveScript_Repository_h
#define ObjectiveScript_Repository_h


// Library includes
#include <map>
#include <string>

// Project includes
#include "Object.h"
#include "Prototype.h"
#include "Reference.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class Memory;
namespace Runtime {
	class Object;
}

class Repository
{
public:
	Repository(Memory *m);
	~Repository();

public:
	void CollectGarbage();

public:
	void addBlueprint(const Designtime::BluePrint& object);
	void addPrototype(const Prototype& prototype);

	Runtime::Object* createInstance(const std::string& type, const std::string& name, const std::string& prototype = "");
	const Reference& createReference(const std::string& type, const std::string& name, const std::string& prototype = "");

	void addReference(Runtime::Object *object);
	void removeReference(Runtime::Object *object);

	bool isAlreadyKnown(const std::string& name) const;

protected:

private:
	typedef std::map<std::string, Designtime::BluePrint> BluePrints;
	typedef std::map<std::string, Prototype> Prototypes;
	typedef std::map<Runtime::Object*, int> ReferenceCountedObjects;

private:
	Runtime::Object* createObject(const std::string& name, Designtime::BluePrint* blueprint);
	const Reference& createReference(const Designtime::BluePrint& blueprint, const std::string& type, const std::string& name);

private:
	BluePrints mBluePrints;
	ReferenceCountedObjects mInstances;
	Memory *mMemory;
	Prototypes mPrototypes;
};


}


#endif
