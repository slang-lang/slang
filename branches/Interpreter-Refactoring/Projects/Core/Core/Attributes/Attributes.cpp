
// Header
#include "Attributes.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>

// Namespace declarations


namespace ObjectiveScript {


GenericAttributes::GenericAttributes()
: //mIsConst(true),
  mIsFinal(false),
  mIsSealed(false),
  mLanguageFeatureState(LanguageFeatureState::Stable),
  mMutability(Mutability::Const),
  mVisibility(Visibility::Private)
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

Mutability::E GenericAttributes::getMutability() const
{
	return mMutability;
}

Visibility::E GenericAttributes::getVisibility() const
{
	return mVisibility;
}

bool GenericAttributes::isConst() const
{
	return mMutability == Mutability::Const;
}

bool GenericAttributes::isFinal() const
{
	//return mIsFinal;
	return mMutability == Mutability::Final;
}

void GenericAttributes::setConst(bool state)
{
	checkSealState();

	mMutability = state ? Mutability::Const : Mutability::Modify;
}

void GenericAttributes::setFinal(bool state)
{
	checkSealState();

	mIsFinal = state;
	//mMutability = state ? Mutability::Final : Mutability::Modify;
}

void GenericAttributes::setLanguageFeatureState(LanguageFeatureState::E s)
{
	checkSealState();

	mLanguageFeatureState = s;
}

void GenericAttributes::setMutability(Mutability::E m)
{
	checkSealState();

	mMutability = m;
}

void GenericAttributes::setVisibility(Visibility::E v)
{
	checkSealState();

	mVisibility = v;
}


MethodAttributes::MethodAttributes()
: mImplementationType(ImplementationType::FullyImplemented),
  mIsRecursive(false),
  mIsStatic(false),
  mMethodType(MethodType::Method),
  mThrows(false)
{
}

MethodAttributes::MethodType::E MethodAttributes::getMethodType() const
{
	return mMethodType;
}

bool MethodAttributes::isAbstract() const
{
	return mImplementationType == ImplementationType::Abstract || mImplementationType == ImplementationType::Interface;
}

bool MethodAttributes::isRecursive() const
{
	return mIsRecursive;
}

void MethodAttributes::setAbstract(bool state)
{
	mImplementationType = state ? ImplementationType::Abstract : ImplementationType::FullyImplemented;
}

void MethodAttributes::setRecursive(bool state)
{
	mIsRecursive = state;
}

void MethodAttributes::setMethodType(MethodType::E type)
{
	mMethodType = type;
}

bool MethodAttributes::isStatic() const
{
	return mIsStatic;
}

void MethodAttributes::setStatic(bool state)
{
	mIsStatic = state;
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
	setConst(false);
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
	setConst(false);
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
	mImplementationType = type;
}

void ObjectAttributes::setMember(bool state)
{
	mIsMember = state;
}

void ObjectAttributes::setSealed(bool state)
{
	checkSealState();

	// after seal has been called no language feature can get modified anymore
	mIsSealed = state;
}



}
