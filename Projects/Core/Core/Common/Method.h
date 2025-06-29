
#ifndef Slang_Core_Core_Common_Method_h
#define Slang_Core_Core_Common_Method_h


// Library includes

// Project includes
#include <Core/Scope.h>
#include "Parameter.h"
#include "TypeDeclaration.h"
#include "Types.h"
#include "Token.h"

// Forward declarations

// Namespace declarations


namespace Slang {

// Forward declarations
namespace AST {
	class Statements;
}
class IPrinter;
class Memory;
class Repository;


namespace Common {


class Method : public NamedScope,
			   public MethodSymbol
{
public:
	Method(IScope* parent, const std::string& name, TypeDeclaration type);
	Method(const Method& other, bool shallowCopy = false);
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
	bool isExtensionMethod() const;
	bool isPrototype() const;

	std::string ToString(unsigned int indent = 0) const;

public:
	ParameterList mergeParameters(const ParameterList& params) const;

protected:
	bool mIsExtensionMethod;

private:
	bool mAllowDelete;
	bool mIsInitialized;
	TypeDeclaration mReturnType;
	AST::Statements* mRootNode;
	ParameterList mSignature;
	TokenList mTokens;
};


}
}


#endif
