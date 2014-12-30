
#ifndef Core_BuildInObjects_String_h
#define Core_BuildInObjects_String_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class String : public Object
{
public:
	String()
	: Object("", "SYSTEM.OS", "String", "")
	{
		//init();
	}

	String(const std::string& value)
	: Object("", "SYSTEM.OS", "String", value)
	{
		//init();
	}

public:

protected:

private:
	void init() {
/*
		Object mValue("mValue", "SYSTEM.OS", "string", "");
		mValue.visibility(Visibility::Private);
		addMember(mValue);

		Method get("String", "get", "String"); {
			VariablesList get_signature;
			get_signature.push_back(Variable("value", "String", ""));
			get.setSignature(get_signature);

			TokenList get_tokens; {
				get_tokens.push_back(Token(Token::Type::IDENTIFER, "mValue"));
				get_tokens.push_back(Token(Token::Type::ASSIGN, "="));
				get_tokens.push_back(Token(Token::Type::IDENTIFER, "value"));
				get_tokens.push_back(Token(Token::Type::SEMICOLON, ";"));
			} get.setTokens(get_tokens);

		} addMethod(get);
*/
		TokenList tokens; {
			// public object String
			// {
			tokens.push_back(Token(Token::Type::VISIBILITY, "public"));
			tokens.push_back(Token(Token::Type::TYPE, "object"));
			tokens.push_back(Token(Token::Type::IDENTIFER, "String"));
			tokens.push_back(Token(Token::Type::BRACKET_CURLY_OPEN, "{"));

				// private string mValue;
				tokens.push_back(Token(Token::Type::VISIBILITY, "private"));
				tokens.push_back(Token(Token::Type::TYPE, "string"));
				tokens.push_back(Token(Token::Type::IDENTIFER, "mValue"));
				tokens.push_back(Token(Token::Type::SEMICOLON, ";"));

				// public void String(string value)
				// {
				// mValue = value;
				// }
				tokens.push_back(Token(Token::Type::VISIBILITY, "public"));
				tokens.push_back(Token(Token::Type::TYPE, "void"));
				tokens.push_back(Token(Token::Type::IDENTIFER, "String"));
				tokens.push_back(Token(Token::Type::PARENTHESIS_OPEN, "("));
				tokens.push_back(Token(Token::Type::TYPE, "string"));
				tokens.push_back(Token(Token::Type::IDENTIFER, "value"));
				tokens.push_back(Token(Token::Type::PARENTHESIS_CLOSE, ")"));
				tokens.push_back(Token(Token::Type::BRACKET_CURLY_OPEN, "{"));
					tokens.push_back(Token(Token::Type::IDENTIFER, "mValue"));
					tokens.push_back(Token(Token::Type::ASSIGN, "="));
					tokens.push_back(Token(Token::Type::IDENTIFER, "value"));
					tokens.push_back(Token(Token::Type::SEMICOLON, ";"));
				tokens.push_back(Token(Token::Type::BRACKET_CURLY_CLOSE, "}"));

			// }
			tokens.push_back(Token(Token::Type::BRACKET_CURLY_CLOSE, "}"));
		} setTokens(tokens);
	}
};


}


#endif
