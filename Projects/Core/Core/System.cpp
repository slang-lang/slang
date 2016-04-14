
// Header
#include "System.h"

// Library includes
#include <iostream>

// Project includes
#include <Core/Utils/Exceptions.h>
#include <Tools/Printer.h>
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {
namespace System {


void Assert(const Runtime::Object& condition, const Utils::Position& position)
{
	if ( !isTrue(condition) ) {
		throw Utils::Exceptions::AssertionFailed(condition.ToString(), position);
	}
}

void Print(const std::string& text, const Utils::Position& position)
{
	::Utils::PrinterDriver::getInstance()->print(text, position.mFile, position.mLine);
}


}
}
