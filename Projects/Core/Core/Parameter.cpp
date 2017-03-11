
// Header
#include "Parameter.h"
#include "Consts.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {


Parameter Parameter::CreateDesigntime(const std::string& name,
									  const TypeDeclaration& type,
									  Runtime::AtomicValue value,
									  bool hasDefaultValue,
									  bool isConst,
									  AccessMode::E access)
{
	return Parameter(
		name,
		type,
		value,
		hasDefaultValue,
		isConst,
		access
	);
}

Parameter Parameter::CreateRuntime(const std::string& type, Runtime::AtomicValue value, Runtime::Reference reference)
{
	if ( reference.isValid() ) {
		return Parameter(
				ANONYMOUS_OBJECT,
				TypeDeclaration(type),
				Runtime::AtomicValue(),
				false,
				false,
				AccessMode::ByReference,
				reference
		);
	}

	return Parameter(
		ANONYMOUS_OBJECT,
		TypeDeclaration(type),
		value,
		false,
		false,
		AccessMode::ByValue,
		Runtime::Reference()
	);
}

Parameter::Parameter()
: mAccessMode(AccessMode::Unspecified),
  mHasDefaultValue(false),
  mIsConst(false)
{
}

Parameter::Parameter(const std::string& name, const TypeDeclaration& type, Runtime::AtomicValue value,
					 bool hasDefaultValue, bool isConst, AccessMode::E access, Runtime::Reference reference)
: mAccessMode(access),
  mHasDefaultValue(hasDefaultValue),
  mIsConst(isConst),
  mName(name),
  mReference(reference),
  mType(type),
  mValue(value)
{
}

AccessMode::E Parameter::access() const
{
	return mAccessMode;
}

bool Parameter::hasDefaultValue() const
{
	return mHasDefaultValue;
}

bool Parameter::isConst() const
{
	return mIsConst;
}

const std::string& Parameter::name() const
{
	return mName;
}

const Runtime::Reference& Parameter::reference() const
{
	return mReference;
}

const std::string& Parameter::type() const
{
	return mType.mName;
}

const PrototypeConstraints& Parameter::typeConstraints() const
{
	return mType.mConstraints;
}

Runtime::AtomicValue Parameter::value() const
{
	return mValue;
}


}
