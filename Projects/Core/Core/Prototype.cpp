
// Header
#include "Prototype.h"

// Library includes

// Project includes
#include "Types.h"

// Namespace declarations


namespace ObjectiveScript {


Prototype::Prototype(const ObjectBluePrint& blue)
: mBluePrint(blue)
{
}

Prototype::~Prototype()
{
}

ObjectBluePrint Prototype::generateBluePrint(const std::string& type)
{
	// get tokens from blue print and replace all occurences
	// of type "Unknown" with our new given type

	TokenList tokens = mBluePrint.getTokens();

	TokenList::iterator it = tokens.begin();
	while ( it != tokens.end() ) {
		if ( it->type() == Token::Type::TYPE && it->content() == PROTOTYPE_TYPE ) {
			it->resetContentTo(type);
		}

		it++;
	}

	ObjectBluePrint blue = mBluePrint;
	blue.setTokens(tokens);
	return blue;
}

const std::string& Prototype::type() const
{
	return mBluePrint.objectType();
}


}
