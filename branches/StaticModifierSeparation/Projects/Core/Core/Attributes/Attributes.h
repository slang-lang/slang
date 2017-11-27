
#ifndef ObjectiveScript_Attributes_Attributes_h
#define ObjectiveScript_Attributes_Attributes_h


// Library includes

// Project includes
#include "Types.h"

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

	virtual bool isStatic() const;
	virtual void setStatic(bool state);

	virtual LanguageFeatureState::E getLanguageFeatureState() const;
	virtual void setLanguageFeatureState(LanguageFeatureState::E value);

	virtual MemoryLayout::E getMemoryLayout() const;
	virtual void setMemoryLayout(MemoryLayout::E value);

	virtual Mutability::E getMutability() const;
	virtual void setMutability(Mutability::E value);

protected:
	void checkSealState();

protected:
	bool mIsSealed;
	LanguageFeatureState::E mLanguageFeatureState;
	MemoryLayout::E mMemoryLayout;
	Mutability::E mMutability;
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
	virtual bool isFinal() const;
	virtual bool isStatic() const;
	virtual bool throws() const;

	virtual Algorithm::E getAlgorithm() const;
	virtual void setAlgorithm(Algorithm::E value);

	virtual CheckedExceptions::E getExceptions() const;
	virtual void setExceptions(CheckedExceptions::E value);

	virtual MethodType::E getMethodType() const;
	virtual void setMethodType(MethodType::E value);

	virtual Virtuality::E getVirtuality() const;
	virtual void setVirtuality(Virtuality::E value);

protected:
	Algorithm::E mAlgorithm;
	CheckedExceptions::E mCheckedExceptions;
	MethodType::E mMethodType;
	Virtuality::E mVirtuality;
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
	virtual ImplementationType::E getImplementationType() const;
	virtual void setImplementationType(ImplementationType::E value);

	virtual bool isMember() const;
	virtual void setMember(bool state);

	virtual bool isSealed() const;
	virtual void setSealed(bool state);

protected:
	ImplementationType::E mImplementationType;
	bool mIsMember;
};


}


#endif
