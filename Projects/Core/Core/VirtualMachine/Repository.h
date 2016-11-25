
#ifndef ObjectiveScript_Core_VirtualMachine_Repository_h
#define ObjectiveScript_Core_VirtualMachine_Repository_h


// Library includes
#include <map>
#include <string>

// Project includes
#include <Core/Common/PrototypeConstraint.h>
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

	Runtime::Object* createInstance(const std::string& type, const std::string& name, const PrototypeConstraints& constraints = PrototypeConstraints(), InitilizationType::E initialize = InitilizationType::None);
	Runtime::Object* createInstance(Designtime::BluePrintGeneric* blueprint, const std::string& name, const PrototypeConstraints& constraints, InitilizationType::E initialize = InitilizationType::None);
	Runtime::Object* createReference(Designtime::BluePrintGeneric* blueprint, const std::string& name, const PrototypeConstraints& constraints, InitilizationType::E initialize = InitilizationType::None);

private:
	// Prototypes
	// {
	Designtime::BluePrintObject* createBluePrintFromPrototype(Designtime::BluePrintObject* blueprint, const PrototypeConstraints& constraints);
	std::string extractType(const PrototypeConstraints& blueprintConstraints, const PrototypeConstraints& implConstraints) const;
	std::string lookupType(const std::string& type, const PrototypeConstraints& blueprintConstraints, const PrototypeConstraints& implConstraints) const;
	// }

	Runtime::Object* createObject(const std::string& name, Designtime::BluePrintObject* blueprint, InitilizationType::E initialize);
	Runtime::Object* createUserObject(const std::string& name, Designtime::BluePrintObject* blueprint, InitilizationType::E initialize);

	Designtime::BluePrintGeneric* findBluePrint(const std::string& type) const;
	Designtime::BluePrintEnum* findBluePrintEnum(const std::string& type) const;
	Designtime::BluePrintObject* findBluePrintObject(const std::string& type) const;

	void initialize();
	void initializeObject(Runtime::Object* object, Designtime::BluePrintObject* blueprint);

private:
	typedef std::map<std::string, Designtime::BluePrintEnum*> BluePrintEnumMap;
	typedef std::map<std::string, Designtime::BluePrintObject*> BluePrintObjectMap;
	typedef std::set<Designtime::BluePrintGeneric*> ForwardDeclarationTomb;

private:
	BluePrintEnumMap mBluePrintEnums;
	BluePrintObjectMap mBluePrintObjects;
	ForwardDeclarationTomb mForwardDeclarations;
};


}


#endif
