
#ifndef Core_BuildInObjects_Number_h
#define Core_BuildInObjects_Number_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Number : public Object
{
public:
	Number()
	: Object("", "SYSTEM.OS", "Number", "")
	{
/*
		Variable mValue("mValue", "atomic_number", "0");
		mValue.visibility(Visibility::Private);
		addMember(mValue);

		Method get("number", "get", "atmoic_number"); {
			VariablesList get_signature;
			get_signature.push_back(Variable("n", "atomic_number", ""));
			get.setSignature(get_signature);

			TokenList get_tokens; {
				get_tokens.push_back(Token(Token::Type::IDENTIFER, "mValue"));
				get_tokens.push_back(Token(Token::Type::ASSIGN, "="));
				get_tokens.push_back(Token(Token::Type::IDENTIFER, "n"));
			} get.setTokens(get_tokens);

		} addMethod(get);
*/
	}

	Number(const std::string& value)
	: Object("", "SYSTEM.OS", "Number", value)
	{ }

public:
	void setTokens(const TokenList& tokens) {
		(void)tokens;
	}

protected:

private:

};


}


#endif
