
#ifndef Core_Keywords_AKeyword_h
#define Core_Keywords_AKeyword_h


// Library includes
#include <string>

// Project includes
#include <Core/Token.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Keywords {


class AKeyword
{
public:
	virtual ~AKeyword() { }

public:
	const std::string& name() const {
		return mName;
	}

	const TokenList& tokens() const {
		return mTokens;
	}
	void tokens(const TokenList& tokens) {
		mTokens = tokens;
	}

protected:
	AKeyword(const std::string& name)
	: mName(name)
	{ }

private:
	std::string	mName;
	TokenList	mTokens;
};


}
}


#endif
