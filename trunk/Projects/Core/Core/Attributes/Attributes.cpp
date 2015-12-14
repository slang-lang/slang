
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
  mIsStatic(false),
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
		throw Utils::Exception("can not update sealed attribute");
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

bool GenericAttributes::isModifiable() const
{
	return !mIsConst;
}

bool GenericAttributes::isStatic() const
{
	return mIsStatic;
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

void GenericAttributes::setModifiable(bool state)
{
	mIsConst = state;
}

void GenericAttributes::setStatic(bool state)
{
	checkSealState();

	mIsStatic = state;
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


ObjectAttributes::ObjectAttributes()
{
	setConst(false);
}

bool ObjectAttributes::isSealed() const
{
	return mIsSealed;
}

void ObjectAttributes::setSealed(bool state)
{
	// after seal has been called no language feature can get modified anymore
	mIsSealed = state;
}


}
