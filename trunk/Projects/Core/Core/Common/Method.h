
#ifndef ObjectiveScript_Core_Core_Common_Method_h
#define ObjectiveScript_Core_Core_Common_Method_h


// Library includes
#include <map>

// Project includes
#include <Core/Attributes/Attributes.h>
#include <Core/Common/TypeDeclaration.h>
#include <Core/Object.h>
#include <Core/Parameter.h>
#include <Core/Scope.h>
#include <Core/Types.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace AST {
	class Statements;
}
class IPrinter;
class Memory;
class Repository;

namespace Runtime {
	class Object;
}

namespace Common {

class Method : public NamedScope,
			   public MethodSymbol
{
public:
	Method(IScope* parent, const std::string& name, const std::string& type);
	Method(const Method& other);
	virtual ~Method();

public: // overloaded operators
	bool operator()(const Method& first, const Method& second) const;
	bool operator< (const Method& other) const;
	Method& operator= (const Method& other);

public:	// Symbol::IType implementation
	const std::string& QualifiedTypename() const;
	void setQualifiedTypename(const std::string& type);

	const TypeDeclaration& ReturnType() const;

	void initialize(const PrototypeConstraints& constraints = PrototypeConstraints());

public: // Signature
	bool isSignatureValid(const ParameterList& params) const;
	const ParameterList& provideSignature() const;

public: // Setup
	void setParent(IScope* scope);
	void setSignature(const ParameterList& params);

	const PrototypeConstraints& getPrototypeConstraints() const;
	void setPrototypeConstraints(const PrototypeConstraints& constraints);

	AST::Statements* getRootNode() const;
	void setRootNode(AST::Statements* node);

	const TokenList& getTokens() const;
	void setTokens(const TokenList& tokens);

public:
	bool isEmpty() const;
	bool isExtensionMethod() const;
	bool isPrototype() const;

	std::string ToString(unsigned int indent = 0) const;

public:
	ParameterList mergeParameters(const ParameterList& params) const;

protected:
	bool mIsExtensionMethod;

private:
	bool mAllowDelete;
	TypeDeclaration mReturnType;
	AST::Statements* mRootNode;
	ParameterList mSignature;
	TokenList mTokens;
};


}
}


#endif
