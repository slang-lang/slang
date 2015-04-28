
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
	void addBlueprint(const BluePrint& object);
	void addPrototype(const Prototype& prototype);

	Object* createInstance(const std::string& type, const std::string& name);
	Object* createInstanceFromPrototype(const std::string& prototype, const std::string& type, const std::string& name);
	bool isAlreadyKnown(const std::string& name) const;

	const Reference& createReference(const std::string& type, const std::string& name);
	const Reference& createReferenceFromPrototype(const std::string& prototype, const std::string& type, const std::string& name);

protected:

private:
	typedef std::map<std::string, BluePrint> BluePrints;
	typedef std::map<std::string, Prototype> Prototypes;
	typedef std::set<Object*> Objects;

private:
	Object* createInstance(const BluePrint& blueprint, const std::string& type, const std::string& name);
	const Reference& createReference(const BluePrint& blueprint, const std::string& type, const std::string& name);

private:
	BluePrints mBluePrints;
	Objects mInstances;
	Prototypes mPrototypes;

	Memory *mMemory;
};


}


#endif
