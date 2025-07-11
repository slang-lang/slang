
#ifndef Slang_Core_Core_Common_Attributes_Attributes_h
#define Slang_Core_Core_Common_Attributes_Attributes_h


// Library includes

// Project includes
#include "Types.h"

// Forward declarations

// Namespace declarations


namespace Slang {


class GenericAttributes
{
public:
	GenericAttributes();
	virtual ~GenericAttributes() = default;

public:
	bool isConst() const;
	bool isStatic() const;

	LanguageFeatureState::E getLanguageFeatureState() const;
	void setLanguageFeatureState(LanguageFeatureState::E value);

	MemoryLayout::E getMemoryLayout() const;
	void setMemoryLayout(MemoryLayout::E value);

	Mutability::E getMutability() const;
	void setMutability(Mutability::E value);

protected:
	void checkSealState() const;

protected:
	bool mIsSealed;
	LanguageFeatureState::E mLanguageFeatureState;
	MemoryLayout::E mMemoryLayout;
	Mutability::E mMutability;
};


class MethodAttributes : public GenericAttributes
{
public:
	MethodAttributes();

public:
	bool isAbstractMethod() const;
	bool isConstMethod() const;
	bool isFinalMethod() const;
	bool isNotImplemented() const;
	bool throws() const;

	Algorithm::E getAlgorithm() const;
	void setAlgorithm(Algorithm::E value);

	CheckedExceptions::E getExceptions() const;
	void setExceptions(CheckedExceptions::E value);

	MethodType::E getMethodType() const;
	void setMethodType(MethodType::E value);

	Mutability::E getMethodMutability() const;
	void setMethodMutability(Mutability::E value);

protected:
	Algorithm::E mAlgorithm;
	CheckedExceptions::E mCheckedExceptions;
	Mutability::E mMethodMutability;
	MethodType::E mMethodType;
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
	BlueprintType::E getBluePrintType() const;
	void setBluePrintType(BlueprintType::E value);

	bool isMember() const;
	void setMember(bool state);

	bool isSealed() const;
	void setSealed(bool state);

protected:
	BlueprintType::E mBluePrintType;
	bool mIsMember;
};


}


#endif
