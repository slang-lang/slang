
#ifndef ObjectiveScript_Attributes_Attributes_h
#define ObjectiveScript_Attributes_Attributes_h


// Library includes

// Project includes
#include "LanguageFeatureState.h"
#include "Visibility.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
//namespace Attributes {


class Attributes
{
public:
	Attributes();

public:
	bool isSealed() const;
	void seal();

public:
	bool isConst() const;
	void setConst(bool state);

	bool isStatic() const;
	void setStatic(bool state);

	LanguageFeatureState::E languageFeatureState() const;
	void setLanguageFeatureState(LanguageFeatureState::E s);

	Visibility::E visibility() const;
	void setVisibility(Visibility::E v);

protected:

private:
	void checkSealState();

private:
	bool mIsConst;
	bool mIsStatic;
	LanguageFeatureState::E mLanguageFeatureState;
	bool mSealed;
	Visibility::E mVisibility;
};


//}
}


#endif
