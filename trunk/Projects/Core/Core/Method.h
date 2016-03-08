
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

class Method : public LocalScope,
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
	const std::string& Typename() const;
	std::string ToString() const;

public: // Execution
	ControlFlow::E execute(const ParameterList& params, Object *result);
	const ExceptionData& getExceptionData() const;

	Symbol* resolve(const std::string& name, bool onlyCurrentScope = false) const;
	Symbol* resolveMethod(const std::string& name, const ParameterList& params, bool onlyCurrentScope = false) const;

public: // Signature
	bool isSignatureValid(const ParameterList& params) const;
	const ParameterList& provideSignature() const;

public: // Setup
	void setRepository(Repository *repository);
	void setSignature(const ParameterList& params);
	void setTokens(const TokenList& tokens);

private: // private types
	typedef std::list<IScope*> ScopeStack;
	typedef std::list<TokenList> TokenStack;

private: // Deinit
	void garbageCollector();
	ControlFlow::E processControlFlow(ControlFlow::E controlflow, Object *result);

private:
	ExceptionData mExceptionData;
	Repository *mRepository;
	ParameterList mSignature;
	TokenList mTokens;
	std::string mTypeName;
};


}
}


#endif
