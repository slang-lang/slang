
#ifndef ObjectiveScript_Core_Method_h
#define ObjectiveScript_Core_Method_h


// Library includes
#include <map>

// Project includes
#include <Core/Attributes/Attributes.h>
#include <Core/Runtime/ExceptionData.h>
#include "Interpreter.h"
#include "Object.h"
#include "Parameter.h"
#include "Reference.h"
#include "Scope.h"
#include "Types.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class IPrinter;
class Memory;
class Repository;

namespace Runtime {

// Forward declarations
class Object;

class Method : public NamedScope,
			   public MethodSymbol
{
public:
	Method(IScope* parent, const std::string& name, const std::string& type);
	~Method();

public: // overloaded operators
	bool operator()(const Method& first, const Method& second) const;
	bool operator< (const Method& other) const;
	void operator= (const Method& other);

public:	// Symbol::IType implementation
	const std::string& QualifiedTypename() const { return mQualifiedTypename; }
	const std::string& Typename() const { return mQualifiedTypename; }

	void setQualifiedTypename(const std::string& type) { mQualifiedTypename = type; }

	std::string ToString(unsigned int indent = 0) const;

public: // Execution
	virtual ControlFlow::E execute(const ParameterList& params, Object* result, const Token& token);
	virtual const ExceptionData& getExceptionData() const;
	virtual bool isExtensionMethod() const;

public:
	virtual Symbol* resolveMethod(const std::string& name, const ParameterList& params, bool onlyCurrentScope = false) const;

public: // Signature
	bool isSignatureValid(const ParameterList& params) const;
	const ParameterList& provideSignature() const;

public: // Setup
	void setParent(IScope* scope);
	void setSignature(const ParameterList& params);
	void setTokens(const TokenList& tokens);

public:
	const TokenList& getTokens() const { return mTokens; }

public:
	ParameterList mergeParameters(const ParameterList& params) const;

protected:
	ExceptionData mExceptionData;
	bool mIsExtensionMethod;

private:
	std::string mQualifiedTypename;
	ParameterList mSignature;
	TokenList mTokens;
};


}
}


#endif