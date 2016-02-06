
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
	virtual bool isConst() const;
	virtual void setConst(bool state);

	virtual bool isFinal() const;
	virtual void setFinal(bool state);

	virtual LanguageFeatureState::E getLanguageFeatureState() const;
	virtual void setLanguageFeatureState(LanguageFeatureState::E s);

	virtual Visibility::E getVisibility() const;
	virtual void setVisibility(Visibility::E v);

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
};


class MemberAttributes : public GenericAttributes
{
public:
	MemberAttributes();
};


class MethodAttributes : public GenericAttributes
{
public:
	MethodAttributes();

public:
	virtual bool isAbstract() const;
	virtual void setAbstract(bool state);

	virtual bool isRecursive() const;
	virtual void setRecursive(bool state);

protected:
	bool mIsAbstract;
	bool mIsRecursive;
};


class NamespaceAttributes : public GenericAttributes
{
public:
	NamespaceAttributes();

public:
	virtual bool isSealed() const;
	virtual void setSealed(bool state);
};


class ObjectAttributes : public GenericAttributes
{
public:
	ObjectAttributes();

public:
	virtual bool isMember() const;
	virtual void setMember(bool state);

	virtual bool isSealed() const;
	virtual void setSealed(bool state);

protected:
	bool mIsMember;
};


}


#endif
