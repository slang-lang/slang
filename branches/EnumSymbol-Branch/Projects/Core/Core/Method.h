
#ifndef ObjectiveScript_Method_h
#define ObjectiveScript_Method_h


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

class Method : public SymbolScope,
			   public MethodSymbol
{
public:
	Method(IScope *parent, const std::string& name, const std::string& type);
	~Method();

public: // overloaded operators
	bool operator()(const Method& first, const Method& second) const;
	bool operator< (const Method& other) const;
	void operator= (const Method& other);

public:	// Symbol::IType implementation
	const std::string& QualifiedTypename() const { return mQualifiedTypename; }
	const std::string& Typename() const { return mTypeName; }
	std::string ToString() const;

	void setQualifiedTypename(const std::string& type) { mQualifiedTypename = type; }

public: // Execution
	virtual ControlFlow::E execute(const ParameterList& params, Object *result, const Token& token);
	virtual const ExceptionData& getExceptionData() const;

	virtual Symbol* resolveMethod(const std::string& name, const ParameterList& params, bool onlyCurrentScope = false) const;

public: // Signature
	bool isSignatureValid(const ParameterList& params) const;
	const ParameterList& provideSignature() const;

public: // Setup
	void setParent(IScope *scope);
	void setRepository(Repository *repository);
	void setSignature(const ParameterList& params);
	void setTokens(const TokenList& tokens);

protected:
	ParameterList mergeParameters(const ParameterList& params) const;

protected:
	ExceptionData mExceptionData;
	Repository *mRepository;

private: // private types
	typedef std::list<IScope*> ScopeStack;
	typedef std::list<TokenList> TokenStack;

private: // Deinit
	void garbageCollector();
	ControlFlow::E processControlFlow(ControlFlow::E controlflow, Object *result);

private:
	IScope* mOwner;
	std::string mQualifiedTypename;
	ParameterList mSignature;
	TokenList mTokens;
	std::string mTypeName;
};


}
}


#endif
