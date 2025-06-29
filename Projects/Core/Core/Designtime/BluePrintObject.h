
#ifndef Slang_Core_Core_Designtime_BluePrintObject_h
#define Slang_Core_Core_Designtime_BluePrintObject_h


// Library includes
#include <list>
#include <map>
#include <string>

// Project includes
#include <Core/Common/PrototypeConstraint.h>
#include <Core/Common/Token.h>
#include <Core/Common/Types.h>
#include <Core/Common/Visibility.h>
#include <Core/Consts.h>
#include <Core/Runtime/AtomicValue.h>
#include <Core/Scope.h>
#include <Core/Symbol.h>
#include "Ancestor.h"

// Forward declarations

// Namespace declarations


namespace Slang {

// Forward declarations
class Repository;

namespace Designtime {


class BluePrintObject : public BlueprintSymbol,
						public MethodScope
{
public:
	static BluePrintObject* FromParent(BluePrintObject* parent, const std::string& unqualifiedTypename, const std::string& filename);

public:
	BluePrintObject();
	BluePrintObject(const std::string& unqualifiedTypename, std::string filename, const std::string& name = ANONYMOUS_OBJECT);
	BluePrintObject(const BluePrintObject& other) = default;
	~BluePrintObject() override = default;

public:
	const std::string& Filename() const;
	const std::string& QualifiedTypename() const override;

	void setQualifiedTypename(const std::string& name);

public:	// MethodScope
	void defineMethod(const std::string& name, Common::Method* method) override;

public:
	// Inheritance
	// {
	Ancestors getAncestors() const;
	Ancestors getInheritance() const;
	Ancestors getImplementations() const;

	bool inheritsFrom(const std::string& type) const;

	void addInheritance(const Ancestor& inheritance);
	// }

	const PrototypeConstraints& getPrototypeConstraints() const;
	void setPrototypeConstraints(const PrototypeConstraints& constraints);

	const TokenList& getTokens() const;
	void setTokens(const TokenList& tokens);


	void setParent(IScope* parent);

	bool hasConstructor() const;
	bool hasDefaultConstructor() const;

	bool isAtomicType() const;
	bool isAbstract() const;
	bool isEnumeration() const;
	bool isInterface() const;
	bool isIterable() const;
	bool isOfType(const std::string& type) const;
	bool isPrototype() const;

	bool isPrepared() const;
	void prepareParents(Repository* repository);

	bool isReference() const;
	void setIsReference(bool state);

	Runtime::AtomicValue getValue() const;
	void setValue(const Runtime::AtomicValue& value);

	std::string ToString(unsigned int indent) const override;

public:
	BluePrintObject* fromPrototype(const PrototypeConstraints& constraints) const;
	BluePrintObject* replicate( const std::string& newType, const std::string& filename, BluePrintObject* target = nullptr ) const;

public:
	MethodCollection provideMethods() const;
	Symbols provideSymbols() const;

protected:
	bool mIsAtomicType;

private:
	std::string mBasedOnType;
	std::string mFilename;
	Ancestors mInheritance;
	bool mIsPrepared;
	bool mIsReference;
	PrototypeConstraints mPrototypeConstraints;
	std::string mQualifiedTypename;
	TokenList mTokens;
	std::string mUnqualifiedTypename;
	Runtime::AtomicValue mValue;
};


}
}


#endif
