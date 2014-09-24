
// Header
#include "Token.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {


Token::Token(Type::E type)
: mType(type)
{
}

Token::Token(Type::E type, const std::string& content)
: mContent(content),
  mType(type)
{
}

Token::Token(Type::E type, const std::string& content, const Position& pos)
: mContent(content),
  mPosition(pos),
  mType(type)
{
}

const std::string& Token::content() const
{
	return mContent;
}

const Token::Position& Token::position() const
{
	return mPosition;
}

void Token::resetTypeTo(Type::E type)
{
	mType = type;
}

Token::Type::E Token::type() const
{
	return mType;
}


}
