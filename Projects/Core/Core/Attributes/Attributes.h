
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

	LanguageFeatureState::E getLanguageFeatureState() const;
	void setLanguageFeatureState(LanguageFeatureState::E s);

	Visibility::E getVisibility() const;
	void setVisibility(Visibility::E v);

protected:
	void checkSealState();

protected:
	bool mIsConst;
	bool mIsFinal;
	bool mIsSealed;
	LanguageFeatureState::E mLanguageFeatureState;
	Visibility::E mVisibility;
};


class LocalAttributes : public GenericAttributes
{
public:
	LocalAttributes();

public:
	bool isStatic() const;
	void setStatic(bool state);

private:
	bool mIsStatic;
};


class MemberAttributes : public GenericAttributes
{
public:
	MemberAttributes();

public:

};


class MethodAttributes : public GenericAttributes
{
public:
	MethodAttributes();

public:
	bool isAbstract() const;
	void setAbstract(bool state);

protected:
	bool mIsAbstract;
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
	bool isMember() const;
	void setMember(bool state);

	bool isSealed() const;
	void setSealed(bool state);

protected:
	bool mIsMember;
};


}


#endif
