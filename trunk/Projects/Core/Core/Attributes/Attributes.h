
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

	bool isFinal() const;
	void setFinal(bool state);

	bool isModifiable() const;
	void setModifiable(bool state);

	bool isStatic() const;
	void setStatic(bool state);

	LanguageFeatureState::E languageFeatureState() const;
	void setLanguageFeatureState(LanguageFeatureState::E s);

	Visibility::E visibility() const;
	void visibility(Visibility::E v);

protected:
	void checkSealState();

protected:
	bool mIsSealed;

private:
	bool mIsConst;
	bool mIsFinal;
	bool mIsStatic;
	LanguageFeatureState::E mLanguageFeatureState;
	Visibility::E mVisibility;
};

class MethodAttributes : public GenericAttributes
{
public:
	MethodAttributes();

public:
	bool isSealed() const;
	void setSealed(bool state);
};

class NamespaceAttributes : public GenericAttributes
{
public:
	NamespaceAttributes();

public:
	bool isSealed() const;
	void setSealed(bool state);
};

class ObjectAttributes : public GenericAttributes
{
public:
	ObjectAttributes();

public:
	bool isSealed() const;
	void setSealed(bool state);
};


}


#endif
