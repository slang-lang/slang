
#ifndef ObjectiveScript_Method_h
#define ObjectiveScript_Method_h


// Library includes
#include <map>
//#include <ostream>

// Project includes
#include "Object.h"
#include "Parameter.h"
#include "Reference.h"
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

class Method : public Variable
{
public:
	Method(const std::string& name, const std::string& type);
	~Method();

public:	// Setup
	void setMemory(Memory *memory);
	void setOwner(Object *owner);
	void setRepository(Repository *repository);
	void setSignature(const ParameterList& params);
	void setTokens(const TokenList& tokens);

public:
	bool isSignatureValid(const ParameterList& params) const;
	const ParameterList& provideSignature() const;

public:	// Execution
	Variable execute(const ParameterList& params);

public:
	bool operator() (const Method& first, const Method& second) const {
		if ( first.name() == second.name() ) {
			ParameterList firstList = first.provideSignature();
			ParameterList secondList = second.provideSignature();

			// unable to identify return value during method call
			//if ( this->type() != other.type() ) {
			//	return this->type() < other.type();
			//}

			if ( firstList.size() == secondList.size() ) {
				ParameterList::const_iterator fIt = firstList.begin();
				ParameterList::const_iterator sIt = secondList.begin();

				for ( ; fIt != firstList.end() && sIt != secondList.end(); ++fIt, ++sIt ) {
					if ( fIt->type() != sIt->type() ) {
						return fIt->type() < sIt->type();
					}
				}
			}

			return firstList.size() < secondList.size();
		}

		return first.name() < second.name();
	}

	bool operator< (const Method& other) const {
		if ( this->name() == other.name() ) {
			ParameterList firstList = this->provideSignature();
			ParameterList secondList = other.provideSignature();

			// unable to identify return value during method call
			//if ( this->type() != other.type() ) {
			//	return this->type() < other.type();
			//}

			if ( firstList.size() == secondList.size() ) {
				ParameterList::const_iterator fIt = firstList.begin();
				ParameterList::const_iterator sIt = secondList.begin();

				for ( ; fIt != firstList.end() && sIt != secondList.end(); ++fIt, ++sIt ) {
					if ( fIt->type() != sIt->type() ) {
						return fIt->type() < sIt->type();
					}
				}
			}

			return firstList.size() < secondList.size();
		}

		return this->name() < other.name();
	}

protected:

private:
	//typedef std::map<std::string, Object> MemberMap;
	//typedef std::map<std::string, Reference> MemberMap;
	typedef std::map<std::string, Variable> MemberMap;

private:	// Construction
	//void addIdentifier(Object object);			// throws DuplicateIdentifer exception
	//void addIdentifier(const Reference& r);		// throws DuplicateIdentifer exception
	void addIdentifier(Variable object);			// throws DuplicateIdentifer exception

private:	// Destruction
	void garbageCollector();

private:	// Execution
	bool isLocal(const std::string& token);
	bool isMember(const std::string& token);
	bool isMethod(const std::string& token);
	bool isMethod(const std::string& token, const ParameterList& params);

	void handleType(TokenIterator& token);

	bool isBooleanConst(const std::string& v) const;
	bool isFalse(const std::string& s) const;
	bool isFalse(const Variable& v) const;
	bool isTrue(const std::string& s) const;
	bool isTrue(const Variable& v) const;

	// token processing
	// {
	Variable process(TokenIterator& start, TokenIterator end, Token::Type::E terminator = Token::Type::NIL);
	void process_assert(TokenIterator& token);
	void process_for(TokenIterator& token);
	void process_if(TokenIterator& token);
	Variable process_method(TokenIterator& token);
	//Object process_new(TokenIterator& token);
	Reference process_new(TokenIterator& token);
	void process_print(TokenIterator& token);
	void process_switch(TokenIterator& token);
	void process_while(TokenIterator& token);
	// }

	// scope
	// {
	std::string scope(const std::string& name) const;
	void push_stack(const std::string& scope);
	void pop_stack();
	// }

	const Reference& getLocale(const std::string& name) const;
	Variable& getVariable(const std::string& name);

	// condition evaluation
	// {
	Variable parseCondition(TokenIterator& start);
	// }

	// expression evaluation
	// {
	Variable parseAtom(TokenIterator& start);
	Variable parseExpression(TokenIterator& start);
	Variable parseFactors(TokenIterator& start);
	Variable parseSummands(TokenIterator& start);
	// }

private:
	MemberMap		mLocales;
	Memory			*mMemory;
	Object			*mOwner;
	ParameterList	mParameter;
	Repository		*mRepository;
	ParameterList	mSignature;
	StringList		mStack;
	TokenList		mTokens;
};


/*
friend std::ostream& operator<<(std::ostream &out, const Method& m)
{
	out << m.name() << "(";
	for ( VariablesList::const_iterator it = m.provideSignature().begin(); it != m.provideSignature().end(); ++it ) {
		out << it->type() << " " << it->name() << ": " << it->value();
	out << ")";
	return out;
}
*/


}


#endif
