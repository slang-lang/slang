
#ifndef Slang_Core_Core_VirtualMachine_Repository_h
#define Slang_Core_Core_VirtualMachine_Repository_h


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


namespace Slang {

// Forward declarations
namespace Designtime {
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
	~Repository() = default;

public:
	void deinit();
	void init();

	// asynchronous initialization of blueprints
	void initializeBlueprints();

public:
	void addBluePrint(Designtime::BluePrintObject* object);

	Runtime::Object* createInstance(const std::string& type, const std::string& name = std::string(), const PrototypeConstraints& constraints = PrototypeConstraints(), InitilizationType::E initialize = InitilizationType::None);
	Runtime::Object* createInstance(Designtime::BluePrintObject* blueprint, const std::string& name, PrototypeConstraints constraints, InitilizationType::E initialize = InitilizationType::None);
	Runtime::Object* createReference(const std::string& type, const std::string& name, const PrototypeConstraints& constraints, InitilizationType::E initialize = InitilizationType::None);
	Runtime::Object* createReference(Designtime::BluePrintObject* blueprint, const std::string& name, const PrototypeConstraints& constraints, InitilizationType::E initialize = InitilizationType::None);

	Designtime::BluePrintObject* findBluePrintObject(const std::string& type) const;
	Designtime::BluePrintObject* findBluePrintObject(const Common::TypeDeclaration& typeDeclaration) const;

	void prepareType(const Common::TypeDeclaration& type);

private:
	typedef std::map<std::string, Designtime::BluePrintObject*> BluePrintObjectMap;

private:
	Designtime::BluePrintObject* createBluePrintFromPrototype(Designtime::BluePrintObject* blueprint, PrototypeConstraints constraints);
	Runtime::Object* createObject(const std::string& name, Designtime::BluePrintObject* blueprint, InitilizationType::E initialize);
	Runtime::Object* createUserObject(const std::string& name, Designtime::BluePrintObject* blueprint, InitilizationType::E initialize);

	void initBluePrintObject(Designtime::BluePrintObject* blueprint);
	void initTypeSystem(Designtime::BluePrintObject* blueprint);

private:
	BluePrintObjectMap mBluePrintObjects;

private:	// Virtual machine stuff
	TypeSystem* mTypeSystem;
};


}


#endif
