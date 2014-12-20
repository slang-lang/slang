
// Header
#include "Token.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {


Token::Token(Type::E type, bool isOptional)
: mIsOptional(isOptional),
  mType(type)
{
}

Token::Token(Type::E type, const std::string& content)
: mContent(content),
  mIsOptional(false),
  mType(type)
{
}

Token::Token(Type::E type, const std::string& content, const Position& pos)
: mContent(content),
  mIsOptional(false),
  mPosition(pos),
  mType(type)
{
}

const std::string& Token::content() const
{
	return mContent;
}

bool Token::isOptional() const
{
	return mIsOptional;
}

const Token::Position& Token::position() const
{
	return mPosition;
}

void Token::resetContentTo(const std::string& c)
{
	mContent = c;
}

void Token::resetTypeTo(Type::E type)
{
	mType = type;
}

void Token::setOptional(bool state)
{
	mIsOptional = state;
}

Token::Type::E Token::type() const
{
	return mType;
}


}
