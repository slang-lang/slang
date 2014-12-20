
// Header
#include "Attributes.h"

// Library includes
#include <cassert>
#include <exception>

// Project includes

// Namespace declarations


namespace ObjectiveScript {


Attributes::Attributes()
: mIsConst(false),
  mIsStatic(false),
  mLanguageFeatureState(LanguageFeatureState::Stable),
  mSealed(false),
  mVisibility(Visibility::Private)
{
}

void Attributes::checkSealState()
{
	if ( mSealed ) {
		throw std::exception("cannot update sealed attribute");
	}
}

bool Attributes::isConst() const
{
	return mIsConst;
}

bool Attributes::isSealed() const
{
	return mSealed;
}

bool Attributes::isStatic() const
{
	return mIsStatic;
}

LanguageFeatureState::E Attributes::languageFeatureState() const
{
	return mLanguageFeatureState;
}

void Attributes::seal()
{
	// after seal has been called no language feature can be modified anymore
	mSealed = true;
}

void Attributes::setConst(bool state)
{
	checkSealState();

	mIsConst = state;
}

void Attributes::setLanguageFeatureState(LanguageFeatureState::E s)
{
	checkSealState();

	mLanguageFeatureState = s;
}

void Attributes::setStatic(bool state)
{
	checkSealState();

	mIsStatic = state;
}

void Attributes::setVisibility(Visibility::E v)
{
	checkSealState();

	mVisibility = v;
}

Visibility::E Attributes::visibility() const
{
	return mVisibility;
}


}
