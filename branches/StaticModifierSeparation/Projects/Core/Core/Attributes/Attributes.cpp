
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
  mMutability(Mutability::Const)
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

void GenericAttributes::setConst(bool state)
{
	checkSealState();

	mMutability = state ? Mutability::Const : Mutability::Modify;
}

void GenericAttributes::setStatic(bool state)
{
	checkSealState();

	mMemoryLayout = state ? MemoryLayout::Static : MemoryLayout::Instance;
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

bool MethodAttributes::isFinal() const
{
	return mVirtuality == Virtuality::Final;
}

bool MethodAttributes::isStatic() const
{
	return mMemoryLayout == MemoryLayout::Static;
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
: mImplementationType(ImplementationType::Unspecified),
  mIsMember(false)
{
	setMutability(Mutability::Modify);
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
