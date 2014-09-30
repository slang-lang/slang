
// Header
#include "Reference.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {


Reference::Reference(size_t address)
: mAddress(address)
{
}

size_t Reference::getAddress() const
{
	return mAddress;
}

bool Reference::operator< (const Reference& other) const
{
	return this->getAddress() < other.getAddress();
}

bool Reference::operator== (const Reference& other) const
{
	return this->getAddress() == other.getAddress();
}


}
