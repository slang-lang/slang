
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
: mImplementationType(ImplementationType::FullyImplemented),
  mIsRecursive(false),
  mMethodType(MethodType::Method),
  mThrows(false),
  mVirtuality(Virtuality::Virtual)
{
	setMutability(Mutability::Const);
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
	return mImplementationType == ImplementationType::Abstract || mImplementationType == ImplementationType::Interface;
}

bool MethodAttributes::isFinal() const
{
	return mVirtuality == Virtuality::Final;
}

bool MethodAttributes::isRecursive() const
{
	return mIsRecursive;
}

bool MethodAttributes::isStatic() const
{
	return mMutability == Mutability::Static;
}

void MethodAttributes::setAbstract(bool state)
{
	checkSealState();

	mImplementationType = state ? ImplementationType::Abstract : ImplementationType::FullyImplemented;
}

void MethodAttributes::setMethodType(MethodType::E type)
{
	mMethodType = type;
}

void MethodAttributes::setRecursive(bool state)
{
	checkSealState();

	mIsRecursive = state;
}

void MethodAttributes::setVirtuality(Virtuality::E value)
{
	mVirtuality = value;
}

bool MethodAttributes::throws() const
{
	return mThrows;
}

void MethodAttributes::setThrows(bool state)
{
	mThrows = state;
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
: mImplementationType(ImplementationType::Unknown),
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

void ObjectAttributes::setImplementationType(ImplementationType::E type)
{
	checkSealState();

	mImplementationType = type;
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
