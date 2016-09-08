
#ifndef ObjectiveScript_Attributes_Attributes_h
#define ObjectiveScript_Attributes_Attributes_h


// Library includes

// Project includes
#include "ImplementationType.h"
#include "LanguageFeatureState.h"
#include "Mutability.h"
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

	virtual Mutability::E getMutability() const;
	virtual void setMutability(Mutability::E m);

	virtual Visibility::E getVisibility() const;
	virtual void setVisibility(Visibility::E v);

protected:
	void checkSealState();

protected:
	bool mIsFinal;
	bool mIsSealed;
	LanguageFeatureState::E mLanguageFeatureState;
	Mutability::E mMutability;
	Visibility::E mVisibility;
};


class MethodAttributes : public GenericAttributes
{
public:
	class MethodType
	{
	public:
		enum E {
			Constructor,
			Destructor,
			Function,
			Method
		};
	};

public:
	MethodAttributes();

public:
	virtual bool isAbstract() const;
	virtual void setAbstract(bool state);

	virtual bool isRecursive() const;
	virtual void setRecursive(bool state);

	virtual MethodType::E getMethodType() const;
	virtual void setMethodType(MethodType::E type);

	virtual bool isStatic() const;
	virtual void setStatic(bool state);

	virtual bool throws() const;
	virtual void setThrows(bool state);

protected:
	ImplementationType::E mImplementationType;
	bool mIsRecursive;
	bool mIsStatic;
	MethodType::E mMethodType;
	bool mThrows;
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
	virtual bool isAbstract() const;
	virtual void setAbstract(bool state);

	virtual bool isMember() const;
	virtual void setMember(bool state);

	virtual bool isSealed() const;
	virtual void setSealed(bool state);

protected:
	bool mIsAbstract;
	bool mIsMember;
};


}


#endif
