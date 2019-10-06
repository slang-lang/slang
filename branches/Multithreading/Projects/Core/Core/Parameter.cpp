
// Header
#include "Parameter.h"

// Library includes

// Project includes
#include <Core/Consts.h>

// Namespace declarations


namespace ObjectiveScript {


Parameter Parameter::CreateDesigntime(const std::string& name,
									  const Common::TypeDeclaration& type,
									  const Runtime::AtomicValue& value,
									  bool hasDefaultValue,
									  Mutability::E mutability,
									  AccessMode::E access)
{
	return Parameter(
		name,
		type,
		value,
		hasDefaultValue,
		mutability,
		access,
		Runtime::Reference()
	);
}

Parameter Parameter::CreateRuntime(const std::string& type,
								   const Runtime::AtomicValue& value,
								   const Runtime::Reference& reference)
{
	if ( reference.isValid() ) {
		return Parameter(
				ANONYMOUS_OBJECT,
				Common::TypeDeclaration(type),
				value,
				false,
				Mutability::Modify,
				AccessMode::ByReference,
				reference
		);
	}

	return Parameter(
		ANONYMOUS_OBJECT,
		Common::TypeDeclaration(type),
		value,
		false,
		Mutability::Modify,
		AccessMode::ByValue,
		Runtime::Reference()
	);
}

Parameter::Parameter()
: mAccessMode(AccessMode::Unspecified),
  mHasDefaultValue(false),
  mMutability(Mutability::Unknown)
{
}

Parameter::Parameter(const std::string& name,
					 const Common::TypeDeclaration& type,
					 const Runtime::AtomicValue& value,
					 bool hasDefaultValue,
					 Mutability::E mutability,
					 AccessMode::E access,
					 const Runtime::Reference& reference)
: mAccessMode(access),
  mHasDefaultValue(hasDefaultValue),
  mMutability(mutability),
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

Mutability::E Parameter::mutability() const
{
	return mMutability;
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

const Common::TypeDeclaration& Parameter::typeDeclaration() const
{
	return mType;
}

const Runtime::AtomicValue& Parameter::value() const
{
	return mValue;
}


}
