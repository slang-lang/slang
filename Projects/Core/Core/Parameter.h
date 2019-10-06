
#ifndef ObjectiveScript_Core_Parameter_h
#define ObjectiveScript_Core_Parameter_h


// Library includes
#include <list>
#include <string>

// Project includes
#include <Core/Attributes/Types.h>
#include <Core/Common/TypeDeclaration.h>
#include <Core/Runtime/AtomicValue.h>
#include <Core/Runtime/Reference.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Runtime {
	class Object;
}

class Parameter
{
public:
	static Parameter CreateDesigntime(const std::string& name,
									  const Common::TypeDeclaration& type,
									  const Runtime::AtomicValue& value = Runtime::AtomicValue(),
									  bool hasDefaultValue = false,
									  Mutability::E mutability = Mutability::Modify,
									  AccessMode::E access = AccessMode::ByValue);
	static Parameter CreateRuntime(const std::string& type,
								   const Runtime::AtomicValue& value,
								   const Runtime::Reference& reference = Runtime::Reference());

public:
	Parameter();
	Parameter(const std::string& name,
			  const Common::TypeDeclaration& type,
			  const Runtime::AtomicValue& value,
			  bool hasDefaultValue,
			  Mutability::E mutability,
			  AccessMode::E access,
			  const Runtime::Reference& reference);

public:
	AccessMode::E access() const;
	bool hasDefaultValue() const;
	Mutability::E mutability() const;
	const std::string& name() const;
	const Runtime::Reference& reference() const;
	const std::string& type() const;
	const PrototypeConstraints& typeConstraints() const;
	const Common::TypeDeclaration& typeDeclaration() const;
	const Runtime::AtomicValue& value() const;

public:
	AccessMode::E mAccessMode;
	bool mHasDefaultValue;
	Mutability::E mMutability;
	std::string mName;
	Runtime::Reference mReference;
	Common::TypeDeclaration mType;
	Runtime::AtomicValue mValue;
};

typedef std::list<Parameter> ParameterList;


}


#endif

