
// Header
#include "Prototype.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


Prototype::Prototype(const Designtime::BluePrintObject& blue)
: mBluePrint(blue)
{
}

Prototype::~Prototype()
{
}

Designtime::BluePrintObject Prototype::generateBluePrint(const std::string& type)
{
	// get tokens from blue print and replace all occurrences
	// of type "UNKNOWN" with our new given type

	TokenList tokens = mBluePrint.getTokens();

	TokenList::iterator it = tokens.begin();
	while ( it != tokens.end() ) {
		if ( it->type() == Token::Type::TYPE && it->content() == PROTOTYPE_TYPE ) {
			it->resetContentTo(type);
		}

		it++;
	}

	Designtime::BluePrintObject blue = mBluePrint;
	blue.setTokens(tokens);
	return blue;
}

const std::string& Prototype::type() const
{
	return mBluePrint.Typename();
}


}
}
