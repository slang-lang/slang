
// Header
#include "Reference.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {


Reference::Reference()
: mAddress(0)
{
}

Reference::Reference(unsigned int address)
: mAddress(address)
{
}

unsigned int Reference::getAddress() const
{
	return mAddress;
}

bool Reference::isValid() const
{
	return mAddress != 0;
}

bool Reference::operator< (const Reference& other) const
{
	return getAddress() < other.getAddress();
}

bool Reference::operator== (const Reference& other) const
{
	return getAddress() == other.getAddress();
}


}