
// Header
#include "Token.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {


Token::Token()
: mCategory(Category::None),
  mIsOptional(true),
  mType(Type::UNKNOWN)
{
	// invalid token
}

Token::Token(Type::E type, bool isOptional)
: mCategory(Category::None),
  mIsOptional(isOptional),
  mType(type)
{
}

Token::Token(Type::E type, const char* content)
: mCategory(Category::None),
  mContent(content),
  mIsOptional(false),
  mType(type)
{
}

Token::Token(Type::E type, const std::string& content)
: mCategory(Category::None),
  mContent(content),
  mIsOptional(false),
  mType(type)
{
}

Token::Token(Category::E category, Type::E type, const std::string& content, const Common::Position& pos, bool isOptional)
: mCategory(category),
  mContent(content),
  mIsOptional(isOptional),
  mPosition(pos),
  mType(type)
{
}

Token::Category::E Token::category() const
{
	return mCategory;
}

void Token::category(Category::E category)
{
	mCategory = category;
}

const std::string& Token::content() const
{
	return mContent;
}

bool Token::isOptional() const
{
	return mIsOptional;
}

const Common::Position& Token::position() const
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
