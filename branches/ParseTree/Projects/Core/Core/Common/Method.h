
#ifndef ObjectiveScript_Core_Core_Common_Method_h
#define ObjectiveScript_Core_Core_Common_Method_h


// Library includes
#include <map>

// Project includes
#include <Core/Attributes/Attributes.h>
#include <Core/Common/TypeDeclaration.h>
#include <Core/Interfaces/IRuntimeType.h>
#include <Core/Interpreter.h>
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
			   public MethodSymbol,
			   public IRuntimeType
{
public:
	Method(IScope* parent, const std::string& name, const std::string& type);
	~Method();

public: // overloaded operators
	bool operator()(const Method& first, const Method& second) const;
	bool operator< (const Method& other) const;
	Method& operator= (const Method& other);

public:	// Symbol::IType implementation
	const std::string& QualifiedTypename() const;
	void setQualifiedTypename(const std::string& type);

public: // IRuntimeType implementation
	void initialize();

public: // Execution
	virtual Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token);

public: // Signature
	bool isSignatureValid(const ParameterList& params) const;
	const ParameterList& provideSignature() const;

public: // Setup
	void setParent(IScope* scope);
	void setPrototypeConstraints(const PrototypeConstraints& constraints);
	void setSignature(const ParameterList& params);
	void setTokens(const TokenList& tokens);

	AST::Statements* getRootNode() const;
	void setRootNode(AST::Statements* node);

public:
	bool isExtensionMethod() const;
	const PrototypeConstraints& getPrototypeConstraints() const;
	const TokenList& getTokens() const;
	std::string ToString(unsigned int indent = 0) const;

public:
	ParameterList mergeParameters(const ParameterList& params) const;

protected:
	bool mIsExtensionMethod;

private:
	TypeDeclaration mReturnType;
	AST::Statements* mRootNode;
	ParameterList mSignature;
	TokenList mTokens;
};


}
}


#endif
