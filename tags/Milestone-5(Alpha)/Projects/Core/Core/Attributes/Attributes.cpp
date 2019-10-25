
// Header
#include "Attributes.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>

// Namespace declarations


namespace ObjectiveScript {


GenericAttributes::GenericAttributes()
: mIsSealed(false),
  mLanguageFeatureState(LanguageFeatureState::Stable),
  mMemoryLayout(MemoryLayout::Instance),
  mMutability(Mutability::Modify)
{
}

GenericAttributes::~GenericAttributes()
{
}

void GenericAttributes::checkSealState()
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
  mMethodType(MethodType::Method),
  mVirtuality(Virtuality::Virtual)
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

MethodAttributes::MethodType::E MethodAttributes::getMethodType() const
{
	return mMethodType;
}

Virtuality::E MethodAttributes::getVirtuality() const
{
	return mVirtuality;
}

bool MethodAttributes::isAbstract() const
{
	return mVirtuality == Virtuality::Abstract;
}

bool MethodAttributes::isConstMethod() const
{
	return mMethodMutability == Mutability::Const;
}

bool MethodAttributes::isFinal() const
{
	return mVirtuality == Virtuality::Final;
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

void MethodAttributes::setVirtuality(Virtuality::E value)
{
	checkSealState();

	mVirtuality = value;
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
: mBluePrintType(BluePrintType::Unknown),
  mImplementationType(ImplementationType::Unspecified),
  mIsMember(false)
{
	setMutability(Mutability::Modify);
}

BluePrintType::E ObjectAttributes::getBluePrintType() const
{
	return mBluePrintType;
}

ImplementationType::E ObjectAttributes::getImplementationType() const
{
	return mImplementationType;
}

bool ObjectAttributes::isMember() const
{
	return mIsMember;
}

bool ObjectAttributes::isSealed() const
{
	return mIsSealed;
}

void ObjectAttributes::setBluePrintType(ObjectiveScript::BluePrintType::E value)
{
	mBluePrintType = value;
}

void ObjectAttributes::setImplementationType(ImplementationType::E value)
{
	checkSealState();

	mImplementationType = value;
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
