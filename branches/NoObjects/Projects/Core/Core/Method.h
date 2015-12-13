
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
			   public MethodAttributes,
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

public:	// Setup
	void setOwner(Object *owner);
	void setRepository(Repository *repository);
	void setSignature(const ParameterList& params);
	void setTokens(const TokenList& tokens);

public: // Deinit
	void garbageCollector(bool force = false);

public:
	bool isSignatureValid(const ParameterList& params) const;
	const ParameterList& provideSignature() const;

public:	// Execution
	void execute(const ParameterList& params, Object *result);

protected:

private:
	typedef std::map<std::string, Object*> MemberCollection;

private:	// Construction
	void addIdentifier(const std::string& name, Object *object);			// throws DuplicateIdentifer exception

private:	// Execution
	bool isMember(const std::string& token) const;
	bool isMethod(const std::string& token);
	bool isMethod(const std::string& token, const ParameterList& params);

	// token processing
	// {
	void process(Object *result, TokenIterator& start, TokenIterator end, Token::Type::E terminator = Token::Type::NIL);
	void process_assert(TokenIterator& token);
	void process_assign(TokenIterator& token, Object *result);
	void process_delete(TokenIterator& token);
	void process_for(TokenIterator& token);
	void process_if(TokenIterator& token, Object *result);
	void process_keyword(TokenIterator& token, Object *result);
	void process_method(TokenIterator& token, Object *result);
	void process_new(TokenIterator& token, Object *result);
	void process_print(TokenIterator& token);
	void process_type(TokenIterator& token);
	void process_switch(TokenIterator& token);
	void process_while(TokenIterator& token);
	// }

	Object* getSymbol(const std::string& token);

	// condition evaluation
	// {
	bool parseCondition(TokenIterator& start);
	// }

	// expression evaluation
	// {
	void parseExpression(Object *result, TokenIterator& start);
	void parseFactors(Object *result, TokenIterator& start);
	void parseTerm(Object *result, TokenIterator& start);
	// }

private:
	MemberCollection mLocalSymbols;
	Object *mOwner;
	ParameterList mParameter;
	Repository *mRepository;
	ParameterList mSignature;
	TokenList mTokens;

private:
	bool mStopProcessing;
};


}


#endif
