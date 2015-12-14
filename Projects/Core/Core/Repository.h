
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
class Object;

class Repository
{
public:
	Repository(Memory *m);
	~Repository();

public:
	void CollectGarbage();
	Object* createObject(const std::string& name, const std::string& filename, const std::string& type, const std::string& value);

public:
	void addBlueprint(const BluePrint& object);
	void addPrototype(const Prototype& prototype);

	Object* createInstance(const std::string& type, const std::string& name, const std::string& prototype = "");
	const Reference& createReference(const std::string& type, const std::string& name, const std::string& prototype = "");

	void addReference(Object *object);
	void removeReference(Object *object);

	bool isAlreadyKnown(const std::string& name) const;

protected:

private:
	typedef std::map<std::string, BluePrint> BluePrints;
	typedef std::map<std::string, Prototype> Prototypes;
	typedef std::map<Object*, int> ReferenceCountedObjects;
	typedef std::set<Object*> Objects;

private:
	const Reference& createReference(const BluePrint& blueprint, const std::string& type, const std::string& name);

private:
	BluePrints mBluePrints;
	ReferenceCountedObjects mInstances;
	Memory *mMemory;
	Prototypes mPrototypes;
};


}


#endif
