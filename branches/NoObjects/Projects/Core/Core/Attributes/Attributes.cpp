
// Header
#include "Attributes.h"

// Library includes
#include <cassert>

// Project includes
#include <Core/Utils/Exceptions.h>

// Namespace declarations


namespace ObjectiveScript {


GenericAttributes::GenericAttributes()
: mIsConst(false),
  mIsStatic(false),
  mLanguageFeatureState(LanguageFeatureState::Stable),
  mSealed(false),
  mVisibility(Visibility::Private)
{
}

GenericAttributes::~GenericAttributes()
{
}

void GenericAttributes::checkSealState()
{
	if ( mSealed ) {
		throw Utils::Exception("can not update sealed attribute");
	}
}

bool GenericAttributes::isConst() const
{
	return mIsConst;
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

void GenericAttributes::setLanguageFeatureState(LanguageFeatureState::E s)
{
	checkSealState();

	mLanguageFeatureState = s;
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



bool ObjectAttributes::isSealed() const
{
	return mSealed;
}

void ObjectAttributes::seal()
{
	// after seal has been called no language feature can get modified anymore
	mSealed = true;
}


}
