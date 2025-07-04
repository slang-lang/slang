
// Header
#include "Attributes.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>

// Namespace declarations


namespace Slang {


GenericAttributes::GenericAttributes()
: mIsSealed(false),
  mLanguageFeatureState(LanguageFeatureState::Stable),
  mMemoryLayout(MemoryLayout::Virtual),
  mMutability(Mutability::Modify)
{
}

void GenericAttributes::checkSealState() const
{
	if ( mIsSealed ) {
		throw Common::Exceptions::Exception("can not update sealed attribute");
	}
}

LanguageFeatureState::E GenericAttributes::getLanguageFeatureState() const
{
	return mLanguageFeatureState;
}

MemoryLayout::E GenericAttributes::getMemoryLayout() const
{
	return mMemoryLayout;
}

Mutability::E GenericAttributes::getMutability() const
{
	return mMutability;
}

bool GenericAttributes::isConst() const
{
	return mMutability == Mutability::Const;
}

bool GenericAttributes::isStatic() const
{
	return mMemoryLayout == MemoryLayout::Static;
}

void GenericAttributes::setLanguageFeatureState(LanguageFeatureState::E value)
{
	checkSealState();

	mLanguageFeatureState = value;
}

void GenericAttributes::setMemoryLayout(MemoryLayout::E value)
{
	checkSealState();

	mMemoryLayout = value;
}

void GenericAttributes::setMutability(Mutability::E value)
{
	checkSealState();

	mMutability = value;
}


MethodAttributes::MethodAttributes()
: mAlgorithm(Algorithm::Heuristic),
  mCheckedExceptions(CheckedExceptions::Nothrow),
  mMethodMutability(Mutability::Const),
  mMethodType(MethodType::Method)
{
	setMutability(Mutability::Const);
}

Algorithm::E MethodAttributes::getAlgorithm() const
{
	return mAlgorithm;
}

CheckedExceptions::E MethodAttributes::getExceptions() const
{
	return mCheckedExceptions;
}

Mutability::E MethodAttributes::getMethodMutability() const
{
	return mMethodMutability;
}

MethodType::E MethodAttributes::getMethodType() const
{
	return mMethodType;
}

bool MethodAttributes::isAbstractMethod() const
{
	return mMemoryLayout == MemoryLayout::Abstract;
}

bool MethodAttributes::isConstMethod() const
{
	return mMethodMutability == Mutability::Const;
}

bool MethodAttributes::isFinalMethod() const
{
	return mMemoryLayout == MemoryLayout::Final;
}

bool MethodAttributes::isNotImplemented() const
{
	return mLanguageFeatureState == LanguageFeatureState::NotImplemented;
}

void MethodAttributes::setAlgorithm(Algorithm::E value)
{
	checkSealState();

	mAlgorithm = value;
}

void MethodAttributes::setExceptions(CheckedExceptions::E value)
{
	checkSealState();

	mCheckedExceptions = value;
}

void MethodAttributes::setMethodMutability(Mutability::E value)
{
	mMethodMutability = value;
}

void MethodAttributes::setMethodType(MethodType::E value)
{
	checkSealState();

	mMethodType = value;
}

bool MethodAttributes::throws() const
{
	return mCheckedExceptions == CheckedExceptions::Throw;
}

NamespaceAttributes::NamespaceAttributes()
{
	setMutability(Mutability::Modify);
}

bool NamespaceAttributes::isSealed() const
{
	return mIsSealed;
}

void NamespaceAttributes::setSealed(bool state)
{
	checkSealState();

	// after seal has been called no language feature can get modified anymore
	mIsSealed = state;
}


ObjectAttributes::ObjectAttributes()
: mBluePrintType(BlueprintType::Unknown),
  mIsMember(false)
{
	setMutability(Mutability::Modify);
}

BlueprintType::E ObjectAttributes::getBluePrintType() const
{
	return mBluePrintType;
}

bool ObjectAttributes::isMember() const
{
	return mIsMember;
}

bool ObjectAttributes::isSealed() const
{
	return mIsSealed;
}

void ObjectAttributes::setBluePrintType(BlueprintType::E value)
{
	mBluePrintType = value;
}

void ObjectAttributes::setMember(bool state)
{
	checkSealState();

	mIsMember = state;
}

void ObjectAttributes::setSealed(bool state)
{
	checkSealState();

	// after seal has been called no language feature can get modified anymore
	mIsSealed = state;
}



}
