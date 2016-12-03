
// Header
#include "Parameter.h"
#include "Consts.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {


Parameter Parameter::CreateDesigntime(const std::string& name, const std::string& type, Runtime::AtomicValue value,
									  bool hasDefaultValue, bool isConst, AccessMode::E access, Reference reference)
{
	return Parameter(
		name,
		type,
		value,
		hasDefaultValue,
		isConst,
		access,
		reference
	);
}

Parameter Parameter::CreateRuntime(const std::string& type, Runtime::AtomicValue value, Reference reference)
{
	if ( reference.isValid() ) {
		return Parameter(
				ANONYMOUS_OBJECT,
				type,
				Runtime::AtomicValue(),
				false,
				false,
				AccessMode::ByReference,
				reference
		);
	}

	return Parameter(
		ANONYMOUS_OBJECT,
		type,
		value,
		false,
		false,
		AccessMode::ByValue,
		Reference()
	);
}

Parameter::Parameter()
: mAccessMode(AccessMode::Unspecified),
  mHasDefaultValue(false),
  mIsConst(false)
{
}

Parameter::Parameter(const std::string& name, const std::string& type, Runtime::AtomicValue value, bool hasDefaultValue,
					 bool isConst, AccessMode::E access, Reference reference)
: mAccessMode(access),
  mHasDefaultValue(hasDefaultValue),
  mIsConst(isConst),
  mName(name),
  mReference(reference),
  mType(type),
  mValue(value)
{
}

Parameter::AccessMode::E Parameter::access() const
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

const Reference& Parameter::reference() const
{
	return mReference;
}

const std::string& Parameter::type() const
{
	return mType;
}

Runtime::AtomicValue Parameter::value() const
{
	return mValue;
}


}
