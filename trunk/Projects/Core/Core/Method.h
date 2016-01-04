
#ifndef ObjectiveScript_Method_h
#define ObjectiveScript_Method_h


// Library includes
#include <map>

// Project includes
#include <Core/Attributes/Attributes.h>
#include "Object.h"
#include "Parameter.h"
#include "Reference.h"
#include "Scope.h"
#include "Types.h"
#include "Variable.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class IPrinter;
class Memory;
class Object;
class Repository;

class Method : public LocalScope,
			   //public MethodAttributes,
			   public MethodSymbol,
			   public Variable
{
public:
	Method(IScope *parent, const std::string& name, const std::string& type);
	~Method();

public:
	bool operator() (const Method& first, const Method& second) const;
	bool operator< (const Method& other) const;
	void operator= (const Method& other);

public:
	Object* getOwner() const;

	void setOwner(Object *owner);
	void setRepository(Repository *repository);
	void setSignature(const ParameterList& params);
	void setTokens(const TokenList& tokens);

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

public: // Deinit
	void garbageCollector(bool force = false);

public:
	bool isSignatureValid(const ParameterList& params) const;
	const ParameterList& provideSignature() const;

public: // Execution
	void execute(const ParameterList& params, Object *result);

private:
	typedef std::map<std::string, Object*> MemberCollection;

	class ControlFlow
	{
	public:
		typedef enum {
			Break,
			Continue,
			None,
			Return
		} E;
	};

private: // Construction
	void addIdentifier(const std::string& name, Object *object);			// throws DuplicateIdentifer exception

private: // Execution
	bool isMember(const std::string& token) const;
	bool isMethod(const std::string& token) const;
	bool isMethod(const std::string& token, const ParameterList& params) const;

	// token processing
	// {
	void process(Object *result, TokenIterator& start, TokenIterator end, Token::Type::E terminator = Token::Type::NIL);
	void process_assert(TokenIterator& token);
	void process_break(TokenIterator& token);
	void process_continue(TokenIterator& token);
	void process_delete(TokenIterator& token);
	void process_for(TokenIterator& token);
	void process_identifier(TokenIterator& token);
	void process_if(TokenIterator& token);
	void process_keyword(TokenIterator& token, Object *result);
	void process_method(TokenIterator& token, Object *result);
	void process_new(TokenIterator& token, Object *result);
	void process_print(TokenIterator& token);
	void process_return(TokenIterator& token, Object *result);
	void process_scope(TokenIterator& token, Object *result);
	void process_type(TokenIterator& token);
	void process_switch(TokenIterator& token);
	void process_while(TokenIterator& token);
	// }

	Object* getObject(const std::string& symbol) const;
	Symbol* resolve(const std::string& name, bool onlyCurrentScope = false) const;

	// expression parsing
	// {
	void expression(Object *result, TokenIterator& start);
	void parseCondition(Object *result, TokenIterator& start);
	void parseExpression(Object *result, TokenIterator& start);
	void parseFactors(Object *result, TokenIterator& start);
	void parseTerm(Object *result, TokenIterator& start);
	// }

	// Scope stack
	// {
	IScope* getScope() const;
	void popScope(bool deleteScope = false);
	void pushScope(const std::string& name);
	void pushScope(IScope *scope);
	// }

	// Token stack
	// {
	const TokenList& getTokens() const;
	void popTokens();
	void pushTokens(const TokenList& tokens);
	// }

private:
	typedef std::list<IScope*> ScopeStack;
	typedef std::list<TokenList> TokenStack;

private:
	MemberCollection mLocalSymbols;
	Object *mOwner;
	ParameterList mParameter;
	Repository *mRepository;
	ScopeStack mScopeStack;
	ParameterList mSignature;
	TokenList mTokens;
	TokenStack mTokenStack;

private:
	ControlFlow::E mControlFlow;
};


}


#endif
