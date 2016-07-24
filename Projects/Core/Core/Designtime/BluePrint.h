
#ifndef ObjectiveScript_BluePrint_h
#define ObjectiveScript_BluePrint_h


// Library includes
#include <list>
#include <map>
#include <string>

// Project includes
#include <Core/Attributes/Attributes.h>
#include <Core/Attributes/Visibility.h>
#include <Core/Runtime/AtomicValue.h>
#include <Core/Consts.h>
#include <Core/Scope.h>
#include <Core/Symbol.h>
#include <Core/Types.h>
#include "Ancestor.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Runtime {
	class Object;
}

namespace Designtime {


class BluePrint : public MethodScope,
				  public BluePrintSymbol
{
public:
	BluePrint();
	BluePrint(const std::string& type, const std::string& filename, const std::string& name = ANONYMOUS_OBJECT);
	virtual ~BluePrint();

public:
	void cleanup();

public:	// RTTI
	const std::string& Filename() const { return mFilename; }
	const std::string& QualifiedTypename() const { return mQualifiedTypeName; }
	const std::string& Typename() const { return mTypename; }

public:
	// Inheritance
	// {
	Designtime::Ancestors getAncestors() const;
	Designtime::Ancestors getInheritance() const;
	Designtime::Ancestors getImplementations() const;

	void addInheritance(const Designtime::Ancestor& inheritance);
	// }

	const TokenList& getTokens() const;
	void setTokens(const TokenList& tokens);

	Visibility::E getVisibility() const;
	void setVisibility(Visibility::E v);

	bool isAbstract() const;
	void setAbstract(bool state);

	bool isInterface() const;
	void setInterface(bool state);

	void setParent(IScope* parent);

	void setQualifiedTypename(const std::string &name);

	Runtime::AtomicValue getValue() const;
	void setValue(Runtime::AtomicValue value);

	virtual std::string ToString() const;

public:
	MethodCollection provideMethods() const {
		return mMethods;
	}
	Symbols provideSymbols() const {
		return mSymbols;
	}

protected:
	const std::string& getTypeName() const {
		return Typename();
	}

private:
	std::string mFilename;
	Ancestors mInheritance;
	bool mIsInterface;
	std::string mQualifiedTypeName;
	TokenList mTokens;
	std::string mTypename;
	Runtime::AtomicValue mValue;
	Visibility::E mVisibility;
};

typedef std::list<BluePrint> BluePrintList;
typedef std::map<std::string, BluePrint> BluePrintMap;


}
}


#endif
