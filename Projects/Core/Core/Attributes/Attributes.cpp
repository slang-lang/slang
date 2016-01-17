
// Header
#include "Attributes.h"

// Library includes
#include <cassert>

// Project includes
#include <Core/Utils/Exceptions.h>

// Namespace declarations


namespace ObjectiveScript {


GenericAttributes::GenericAttributes()
: mIsSealed(false),
  mIsConst(true),
  mIsFinal(false),
  mLanguageFeatureState(LanguageFeatureState::Stable),
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

bool GenericAttributes::isConst() const
{
	return mIsConst;
}

bool GenericAttributes::isFinal() const
{
	return mIsFinal;
}

LanguageFeatureState::E GenericAttributes::languageFeatureState() const
{
	return mLanguageFeatureState;
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

Visibility::E GenericAttributes::visibility() const
{
	return mVisibility;
}

void GenericAttributes::visibility(Visibility::E v)
{
	checkSealState();

	mVisibility = v;
}


LocalAttributes::LocalAttributes()
: mIsStatic(false)
{
}

bool LocalAttributes::isStatic() const
{
	return mIsStatic;
}

void LocalAttributes::setStatic(bool state)
{
	checkSealState();

	mIsStatic = state;
}


MemberAttributes::MemberAttributes()
{
}


MethodAttributes::MethodAttributes()
{
}

bool MethodAttributes::isSealed() const
{
	return mIsSealed;
}

void MethodAttributes::setSealed(bool state)
{
	// after seal has been called no language feature can get modified anymore
	mIsSealed = state;
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
: mIsMember(false),
  mIsStatic(false)
{
	setConst(false);
}

bool ObjectAttributes::isMember() const
{
	return mIsMember;
}

bool ObjectAttributes::isSealed() const
{
	return mIsSealed;
}

bool ObjectAttributes::isStatic() const
{
	return mIsStatic;
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

void ObjectAttributes::setStatic(bool state)
{
	checkSealState();

	mIsStatic = state;
}


}
