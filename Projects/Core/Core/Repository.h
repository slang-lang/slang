
#ifndef ObjectiveScript_Repository_h
#define ObjectiveScript_Repository_h


// Library includes
#include <map>
#include <string>

// Project includes
#include "Object.h"
#include "Prototype.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class Object;

class Repository
{
public:
	Repository();
	~Repository();

public:
	void addBlueprint(const ObjectBluePrint& object);
	void addPrototype(const Prototype& prototype);

	Object createInstance(const std::string& type, const std::string& name);
	Object createInstanceFromPrototype(const std::string& prototype, const std::string& type, const std::string& name);
	bool isAlreadyKnown(const std::string& name) const;

protected:

private:
	typedef std::map<std::string, ObjectBluePrint> BluePrints;
	typedef std::map<std::string, Prototype> Prototypes;

private:
	BluePrints mBluePrints;
	Prototypes mPrototypes;
};


}


#endif
