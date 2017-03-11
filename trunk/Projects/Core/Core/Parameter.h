
#ifndef ObjectiveScript_Core_Parameter_h
#define ObjectiveScript_Core_Parameter_h


// Library includes
#include <list>
#include <string>

// Project includes
#include <Core/Attributes/AccessMode.h>
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
									  const TypeDeclaration& type,
									  Runtime::AtomicValue value = Runtime::AtomicValue(),
									  bool hasDefaultValue = false,
									  bool isConst = false,
									  AccessMode::E access = AccessMode::ByValue);
	static Parameter CreateRuntime(const std::string& type,
								   Runtime::AtomicValue value,
								   Runtime::Reference reference = Runtime::Reference());

public:
	Parameter();
	Parameter(const std::string& name,
			  const TypeDeclaration& type,
			  Runtime::AtomicValue value,
			  bool hasDefaultValue = false,
			  bool isConst = false,
			  AccessMode::E access = AccessMode::ByValue,
			  Runtime::Reference reference = Runtime::Reference());

public:
	AccessMode::E access() const;
	bool hasDefaultValue() const;
	bool isConst() const;
	const std::string& name() const;
	const Runtime::Reference& reference() const;
	const std::string& type() const;
	const PrototypeConstraints& typeConstraints() const;
	Runtime::AtomicValue value() const;

private:
	AccessMode::E mAccessMode;
	bool mHasDefaultValue;
	bool mIsConst;
	std::string mName;
	Runtime::Reference mReference;
	TypeDeclaration mType;
	Runtime::AtomicValue mValue;
};

typedef std::list<Parameter> ParameterList;


}


#endif

