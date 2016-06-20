
// Header
#include "LocalClient.h"

// Library includes
#include <iostream>

// Project includes
//#include <Backend/IBackend.h>

// Namespace declarations


namespace ObjectiveScript {


LocalClient::LocalClient()
: //mBackend(0),
  mSettings(0)
{
}

LocalClient::~LocalClient()
{
}

/*
void LocalClient::connectBackend(IBackend* backend)
{
	assert(backend);
	assert(!mBackend);

	mBackend = backend;
}
*/

void LocalClient::connectSettings(Settings* settings)
{
	assert(settings);
	assert(!mSettings);

	mSettings = settings;
}

std::string LocalClient::read() const
{
	std::string result;

	getline(std::cin >> std::ws, result);
	std::cin.clear();

	return result;
}

void LocalClient::write(const std::string& text)
{
	std::cout << text;
}

void LocalClient::writeln(const std::string& text)
{
	std::cout << text << std::endl;
}


}
