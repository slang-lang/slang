
// Header
#include "LocalClient.h"

// Library includes
#include <iostream>

// Project includes

// Namespace declarations


namespace ObjectiveScript {


LocalClient::LocalClient()
{
}

LocalClient::~LocalClient()
{
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
