
#ifndef ObjectiveScript_Method_h
#define ObjectiveScript_Method_h


// Library includes
#include <map>
//#include <ostream>

// Project includes
#include "Object.h"
#include "Types.h"
#include "Variable.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class IPrinter;
class Object;
class Repository;

class Method : public Variable
{
public:
	Method(const std::string& name, const std::string& type);
	~Method();

public:	// Setup
	void setOwner(Object *owner);
	void setRepository(Repository *repository);
	void setSignature(const VariablesList& params);
	void setTokens(const TokenList& tokens);

public:
	bool isSignatureValid(const VariablesList& params) const;
	const VariablesList& provideSignature() const;

public:	// Execution
	Object execute(const VariablesList& params);

public:
	bool operator() (const Method& first, const Method& second) const {
		if ( first.name() == second.name() ) {
			VariablesList firstList = first.provideSignature();
			VariablesList secondList = second.provideSignature();

			// unable to identify return value during method call
			//if ( this->type() != other.type() ) {
			//	return this->type() < other.type();
			//}

			if ( firstList.size() == secondList.size() ) {
				VariablesList::const_iterator fIt = firstList.begin();
				VariablesList::const_iterator sIt = secondList.begin();

				for ( ; fIt != firstList.end(), sIt != secondList.end(); ++fIt, ++sIt ) {
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
			VariablesList firstList = this->provideSignature();
			VariablesList secondList = other.provideSignature();

			// unable to identify return value during method call
			//if ( this->type() != other.type() ) {
			//	return this->type() < other.type();
			//}

			if ( firstList.size() == secondList.size() ) {
				VariablesList::const_iterator fIt = firstList.begin();
				VariablesList::const_iterator sIt = secondList.begin();

				for ( ; fIt != firstList.end(), sIt != secondList.end(); ++fIt, ++sIt ) {
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
	typedef std::map<std::string, Object> MemberMap;

private:	// Construction
	void addIdentifier(Object v);		// throws DuplicateIdentifer exception

private:	// Destruction
	void garbageCollector();

private:	// Execution
	bool isLocal(const std::string& token);
	bool isMember(const std::string& token);
	bool isMethod(const std::string& token);
	bool isMethod(const std::string& token, const VariablesList& params);

	void handleType(TokenIterator& token);

	bool isBooleanConst(const std::string& v) const;
	bool isFalse(const std::string& s) const;
	bool isFalse(const Object& v) const;
	bool isTrue(const std::string& s) const;
	bool isTrue(const Object& v) const;

	// token processing
	// {
	Object process(TokenIterator start, TokenIterator end, Token::Type::E terminator = Token::Type::NIL);
	void process_assert(TokenIterator& token);
	void process_for(TokenIterator& token);
	void process_if(TokenIterator& token);
	Object process_method(TokenIterator& token);
	Object process_new(TokenIterator& token);
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

	Object& getVariable(const std::string& name);

	// condition evaluation
	// {
	Object parseCondition(TokenIterator& start);
	// }

	// expression evaluation
	// {
	Object parseAtom(TokenIterator& start);
	Object parseExpression(TokenIterator& start);
	Object parseFactors(TokenIterator& start);
	Object parseSummands(TokenIterator& start);

	Object math_add(const Object& v1, const Object& v2);
	Object math_divide(const Object& v1, const Object& v2);
	Object math_multiply(const Object& v1, const Object& v2);
	Object math_subtract(const Object& v1, const Object& v2);
	Object string_concat(const Object& v1, const Object& v2);
	// }

private:
	Object			*mOwner;
	VariablesList	mParameters;
	Repository		*mRepository;
	VariablesList	mSignature;
	StringList		mStack;
	TokenList		mTokens;
	MemberMap		mVariables;
};

/*
friend std::ostream &operator<<(std::ostream &out, const Method& m)
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
