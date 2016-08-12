
#ifndef ObjectiveScript_Repository_h
#define ObjectiveScript_Repository_h


// Library includes
#include <map>
#include <string>

// Project includes
#include "Object.h"
#include "Reference.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Designtime {
	class BluePrintEnum;
	class BluePrintGeneric;
	class BluePrintObject;
	class Prototype;
}
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
	void addBluePrint(Designtime::BluePrintEnum* blueprint);
	void addBluePrint(Designtime::BluePrintObject* object);
	void addPrototype(Designtime::Prototype* prototype);

	Runtime::Object* createInstance(const std::string& type, const std::string& name = ANONYMOUS_OBJECT, bool initialize = true);
	Runtime::Object* createInstance(Designtime::BluePrintGeneric* blueprint, const std::string& name = ANONYMOUS_OBJECT, bool initialize = true);

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
	Runtime::Object* createEnum(const std::string& name, Designtime::BluePrintEnum* blueprint, bool initialize);
	Runtime::Object* createObject(const std::string& name, Designtime::BluePrintObject* blueprint, bool initialize);
	Runtime::Object* createUserObject(const std::string& name, Designtime::BluePrintObject* blueprint, bool initialize);

	void createDefaultMethods(Runtime::Object *object);
	void initializeObject(Runtime::Object *object, Designtime::BluePrintObject* blueprint);
	void insertBluePrintEnumsIntoScopes();
	void insertBluePrintObjectsIntoScopes();
	void rebuildBluePrintEnums();
	void rebuildBluePrintObjects();

private:
	typedef std::map<std::string, Designtime::BluePrintEnum*> BluePrintEnumMap;
	typedef std::map<std::string, Designtime::BluePrintObject*> BluePrintObjectMap;

private:
	BluePrintEnumMap mBluePrintEnums;
	BluePrintObjectMap mBluePrintObjects;
	ReferenceCountedObjects mInstances;
	//Designtime::PrototypeMap mPrototypes;
	GlobalScope *mScope;
};


}


#endif
