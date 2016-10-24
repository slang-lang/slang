
#ifndef ObjectiveScript_Core_VirtualMachine_Repository_h
#define ObjectiveScript_Core_VirtualMachine_Repository_h


// Library includes
#include <map>
#include <string>

// Project includes
#include <Core/Object.h>
#include <Core/Reference.h>

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

class Repository
{
public:
	Repository();
	~Repository();

public:
	void deinit();
	void init();

public:
	void addBluePrint(Designtime::BluePrintEnum* blueprint);
	void addBluePrint(Designtime::BluePrintObject* object);
	void addPrototype(Designtime::Prototype* prototype);

	Runtime::Object* createInstance(const std::string& type, const std::string& name, bool initialize = false);
	Runtime::Object* createInstance(Designtime::BluePrintObject* blueprint, const std::string& name, bool initialize = false);

private:
	Runtime::Object* createObject(const std::string& name, Designtime::BluePrintObject* blueprint, bool initialize);
	Runtime::Object* createUserObject(const std::string& name, Designtime::BluePrintObject* blueprint, bool initialize);

	Designtime::BluePrintGeneric* findBluePrint(const std::string& type) const;
	Designtime::BluePrintEnum* findBluePrintEnum(const std::string& type) const;
	Designtime::BluePrintObject* findBluePrintObject(const std::string& type) const;

	void initialize();
	void initializeObject(Runtime::Object *object, Designtime::BluePrintObject* blueprint);

private:
	typedef std::map<std::string, Designtime::BluePrintEnum*> BluePrintEnumMap;
	typedef std::map<std::string, Designtime::BluePrintObject*> BluePrintObjectMap;

private:
	BluePrintEnumMap mBluePrintEnums;
	BluePrintObjectMap mBluePrintObjects;
	//PrototypeMap mPrototypes;
};


}


#endif
