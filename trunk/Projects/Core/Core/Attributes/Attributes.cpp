
// Header
#include "Attributes.h"

// Library includes

// Project includes
#include <Core/Utils/Exceptions.h>

// Namespace declarations


namespace ObjectiveScript {


GenericAttributes::GenericAttributes()
: mIsConst(true),
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
		throw Utils::Exceptions::Exception("can not update sealed attribute");
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
	return mIsConst;
	//return mMutability == Mutability::Const;
}

bool GenericAttributes::isFinal() const
{
	return mIsFinal;
}

void GenericAttributes::setConst(bool state)
{
	checkSealState();

	mIsConst = state;
}

void GenericAttributes::setFinal(bool state)
{
	mIsFinal = state;
}

void GenericAttributes::setLanguageFeatureState(LanguageFeatureState::E s)
{
	checkSealState();

	mLanguageFeatureState = s;
}

void GenericAttributes::setMutability(Mutability::E m)
{
	mMutability = m;
}

void GenericAttributes::setVisibility(Visibility::E v)
{
	checkSealState();

	mVisibility = v;
}


MethodAttributes::MethodAttributes()
: mIsAbstract(false),
  mIsRecursive(false),
  mMethodType(MethodType::Method)
{
}

MethodAttributes::MethodType::E MethodAttributes::getMethodType() const
{
	return mMethodType;
}

bool MethodAttributes::isAbstract() const
{
	return mIsAbstract;
}

bool MethodAttributes::isRecursive() const
{
	return mIsRecursive;
}

void MethodAttributes::setAbstract(bool state)
{
	mIsAbstract = state;
}

void MethodAttributes::setRecursive(bool state)
{
	mIsRecursive = state;
}

void MethodAttributes::setMethodType(MethodType::E type)
{
	mMethodType = type;
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
	// after seal has been called no language feature can get modified anymore
	mIsSealed = state;
}


ObjectAttributes::ObjectAttributes()
: mIsAbstract(false),
  mIsMember(false)
{
	setConst(false);
}

bool ObjectAttributes::isAbstract() const
{
	return mIsAbstract;
}

bool ObjectAttributes::isMember() const
{
	return mIsMember;
}

bool ObjectAttributes::isSealed() const
{
	return mIsSealed;
}

void ObjectAttributes::setAbstract(bool state)
{
	mIsAbstract = state;
}

void ObjectAttributes::setMember(bool state)
{
	mIsMember = state;
}

void ObjectAttributes::setSealed(bool state)
{
	// after seal has been called no language feature can get modified anymore
	mIsSealed = state;
}



}
