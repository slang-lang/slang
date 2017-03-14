
#ifndef ObjectiveScript_Core_VirtualMachine_Repository_h
#define ObjectiveScript_Core_VirtualMachine_Repository_h


// Library includes
#include <map>
#include <set>
#include <string>
//#include <unordered_map>
//#include <unordered_set>

// Project includes
#include <Core/Common/PrototypeConstraint.h>
#include <Core/Object.h>
#include <Core/Runtime/Reference.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Designtime {
	class BluePrintEnum;
	class BluePrintGeneric;
	class BluePrintObject;
}
namespace Runtime {
	class Object;
}

class Repository
{
public:
	class InitilizationType {
	public:
		enum E {
			None,
			AllowAbstract,
			Final
		};
	};

public:
	Repository();
	~Repository();

public:
	void deinit();
	void init();

public:
	void addBluePrint(Designtime::BluePrintEnum* blueprint);
	void addBluePrint(Designtime::BluePrintObject* object);

	void cleanupForwardDeclarations();

	Runtime::Object* createInstance(const std::string& type, const std::string& name = std::string(), const PrototypeConstraints& constraints = PrototypeConstraints(), InitilizationType::E initialize = InitilizationType::None);
	Runtime::Object* createInstance(Designtime::BluePrintGeneric* blueprint, const std::string& name, PrototypeConstraints constraints, InitilizationType::E initialize = InitilizationType::None);
	Runtime::Object* createReference(const std::string& type, const std::string& name, PrototypeConstraints constraints, InitilizationType::E initialize = InitilizationType::None);
	Runtime::Object* createReference(Designtime::BluePrintGeneric* blueprint, const std::string& name, PrototypeConstraints constraints, InitilizationType::E initialize = InitilizationType::None);

	Designtime::BluePrintGeneric* findBluePrint(const std::string& type) const;

private:
	typedef std::map<std::string, Designtime::BluePrintEnum*> BluePrintEnumMap;
	typedef std::map<std::string, Designtime::BluePrintObject*> BluePrintObjectMap;
	typedef std::set<Designtime::BluePrintGeneric*> ForwardDeclarationTomb;

	//typedef std::unordered_map<std::string, Designtime::BluePrintEnum*> BluePrintEnumMap;
	//typedef std::unordered_map<std::string, Designtime::BluePrintObject*> BluePrintObjectMap;
	//typedef std::unordered_set<Designtime::BluePrintGeneric*> ForwardDeclarationTomb;

private:
	Designtime::BluePrintObject* createBluePrintFromPrototype(Designtime::BluePrintObject* blueprint, PrototypeConstraints constraints);

	Runtime::Object* createObject(const std::string& name, Designtime::BluePrintObject* blueprint, InitilizationType::E initialize);
	Runtime::Object* createUserObject(const std::string& name, Designtime::BluePrintObject* blueprint, InitilizationType::E initialize);

	void initTypeSystem(Designtime::BluePrintObject* blueprint);

	Designtime::BluePrintEnum* findBluePrintEnum(const std::string& type) const;
	Designtime::BluePrintObject* findBluePrintObject(const std::string& type) const;

	void initializeObject(Runtime::Object* object, Designtime::BluePrintObject* blueprint);

private:
	BluePrintEnumMap mBluePrintEnums;
	BluePrintObjectMap mBluePrintObjects;
	ForwardDeclarationTomb mForwardDeclarations;
};


}


#endif
