
#ifndef ObjectiveScript_Core_VirtualMachine_Repository_h
#define ObjectiveScript_Core_VirtualMachine_Repository_h


// Library includes
#include <map>
#include <set>
#include <string>

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
class TypeSystem;

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

	// asynchronous initialization of blueprints
	void initializeBlueprints();

public:
	void addBluePrint(Designtime::BluePrintEnum* blueprint);
	void addBluePrint(Designtime::BluePrintObject* object);

	Runtime::Object* createInstance(const std::string& type, const std::string& name = std::string(), PrototypeConstraints constraints = PrototypeConstraints(), InitilizationType::E initialize = InitilizationType::None);
	Runtime::Object* createInstance(Designtime::BluePrintGeneric* blueprint, const std::string& name, PrototypeConstraints constraints, InitilizationType::E initialize = InitilizationType::None);
	Runtime::Object* createReference(const std::string& type, const std::string& name, PrototypeConstraints constraints, InitilizationType::E initialize = InitilizationType::None);
	Runtime::Object* createReference(Designtime::BluePrintGeneric* blueprint, const std::string& name, PrototypeConstraints constraints, InitilizationType::E initialize = InitilizationType::None);

	Designtime::BluePrintEnum* findBluePrintEnum(const std::string& type) const;
	Designtime::BluePrintGeneric* findBluePrintGeneric(const std::string &type) const;
	Designtime::BluePrintObject* findBluePrintObject(const std::string& type) const;
	Designtime::BluePrintObject* findBluePrintObject(const Common::TypeDeclaration& typeDeclaration) const;

	void prepareType(const Common::TypeDeclaration& type);

private:
	typedef std::map<std::string, Designtime::BluePrintEnum*> BluePrintEnumMap;
	typedef std::map<std::string, Designtime::BluePrintObject*> BluePrintObjectMap;
	typedef std::set<Designtime::BluePrintGeneric*> ForwardDeclarationTomb;

private:
	Designtime::BluePrintObject* createBluePrintFromPrototype(Designtime::BluePrintObject* blueprint, PrototypeConstraints constraints);
	Runtime::Object* createObject(const std::string& name, Designtime::BluePrintObject* blueprint, InitilizationType::E initialize);
	Runtime::Object* createUserObject(const std::string& name, Designtime::BluePrintObject* blueprint, InitilizationType::E initialize);

	void initBluePrintObject(Designtime::BluePrintObject* blueprint);
	void initTypeSystem(Designtime::BluePrintEnum* blueprint);
	void initTypeSystem(Designtime::BluePrintObject* blueprint);

	void initializeObject(Designtime::BluePrintObject* srcObj, Runtime::Object* destObj);

private:
	BluePrintEnumMap mBluePrintEnums;
	BluePrintObjectMap mBluePrintObjects;

private:	// Virtual machine stuff
	TypeSystem* mTypeSystem;
};


}


#endif
