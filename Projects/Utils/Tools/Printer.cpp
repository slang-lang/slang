
// Header
#include "Printer.h"

// Library includes
#include <iostream>

// Project includes

// Namespace declarations

namespace Utils {


Printer::Printer()
: ActivatePrinter(true),
  AutomaticLineBreak(true),
  PrintFileAndLine(false)
{
}

void Printer::print(const std::string& text, const std::string& file, int line)
{
	if ( !ActivatePrinter ) {
		return;
	}

	std::cout << text;
	if ( PrintFileAndLine ) {
		std::cout << "   [" << file << ":" << line << "]" << std::endl;
	}

	if ( AutomaticLineBreak && !PrintFileAndLine ) {
		std::cout << std::endl;
	}
}

void Printer::println(const std::string& text, const std::string& file, int line)
{
	if ( !ActivatePrinter ) {
		return;
	}

	print(text, file, line);

	std::cout << std::endl;
}


}
