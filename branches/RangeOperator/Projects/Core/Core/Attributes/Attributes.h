
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
	bool isConst() const;
	void setConst(bool state);

	bool isStatic() const;
	void setStatic(bool state);

	LanguageFeatureState::E getLanguageFeatureState() const;
	void setLanguageFeatureState(LanguageFeatureState::E value);

	MemoryLayout::E getMemoryLayout() const;
	void setMemoryLayout(MemoryLayout::E value);

	Mutability::E getMutability() const;
	void setMutability(Mutability::E value);

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
	bool isAbstract() const;
	bool isConstMethod() const;
	bool isFinal() const;
	bool isStatic() const;
	bool throws() const;

	Algorithm::E getAlgorithm() const;
	void setAlgorithm(Algorithm::E value);

	CheckedExceptions::E getExceptions() const;
	void setExceptions(CheckedExceptions::E value);

	MethodType::E getMethodType() const;
	void setMethodType(MethodType::E value);

	Mutability::E getMethodMutability() const;
	void setMethodMutability(Mutability::E value);

	Virtuality::E getVirtuality() const;
	void setVirtuality(Virtuality::E value);

protected:
	Algorithm::E mAlgorithm;
	CheckedExceptions::E mCheckedExceptions;
	Mutability::E mMethodMutability;
	MethodType::E mMethodType;
	Virtuality::E mVirtuality;
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
	ImplementationType::E getImplementationType() const;
	void setImplementationType(ImplementationType::E value);

	bool isMember() const;
	void setMember(bool state);

	bool isSealed() const;
	void setSealed(bool state);

protected:
	ImplementationType::E mImplementationType;
	bool mIsMember;
};


}


#endif
