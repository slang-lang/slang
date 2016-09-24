
// Header
#include "AClient.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {


AClient::AClient()
: mSettings(0)
{
}

AClient::~AClient()
{
}

void AClient::connectSettings(Settings *s)
{
	assert(s);
	assert(!mSettings);

	mSettings = s;
}


}
