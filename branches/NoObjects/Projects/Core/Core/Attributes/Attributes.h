
#ifndef ObjectiveScript_Attributes_Attributes_h
#define ObjectiveScript_Attributes_Attributes_h


// Library includes

// Project includes
#include "LanguageFeatureState.h"
#include "Visibility.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class GenericAttributes
{
public:
	GenericAttributes();
	virtual ~GenericAttributes();

public:
	bool isConst() const;
	void setConst(bool state);

	bool isStatic() const;
	void setStatic(bool state);

	LanguageFeatureState::E languageFeatureState() const;
	void setLanguageFeatureState(LanguageFeatureState::E s);

	Visibility::E visibility() const;
	void visibility(Visibility::E v);

protected:
	void checkSealState();

protected:
	bool mSealed;

private:
	bool mIsConst;
	bool mIsStatic;
	LanguageFeatureState::E mLanguageFeatureState;
	Visibility::E mVisibility;
};

class ObjectAttributes : public GenericAttributes
{
public:
	bool isSealed() const;
	void seal();
};


}


#endif
