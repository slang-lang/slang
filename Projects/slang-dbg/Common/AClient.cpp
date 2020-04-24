
// Header
#include "AClient.h"

// Library includes

// Project includes

// Namespace declarations


namespace Slang {


AClient::AClient()
: mSettings(nullptr)
{
}

void AClient::connectSettings(Settings *s)
{
	assert(s);
	assert(!mSettings);

	mSettings = s;
}


}
