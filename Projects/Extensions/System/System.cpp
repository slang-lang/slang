
// Header
#include "System.h"

// Library includes
#include <iostream>

// Project includes
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Repository.h>
#include <Core/Utils/Exceptions.h>
#include <Tools/Strings.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {


Print::Print()
: Runtime::Method(0, "print", Designtime::VoidObject::TYPENAME)
{
}

Runtime::ControlFlow::E Print::execute(const ParameterList& params, Runtime::Object* /*result*/)
{
	std::string text;

	if ( params.size() != 1 ) {
		throw Utils::Exceptions::ParameterCountMissmatch("1 parameter expected, but " + ::Utils::Tools::toString(params.size()) + " parameter(s) found");
	}

	text = params.front().value();

	std::cout << "print: " << text;

	return Runtime::ControlFlow::Normal;
}


PrintLine::PrintLine()
: Runtime::Method(0, "println", Designtime::VoidObject::TYPENAME)
{
}

Runtime::ControlFlow::E PrintLine::execute(const ParameterList& params, Runtime::Object* /*result*/)
{
	std::string text;

	if ( params.size() != 1 ) {
		throw Utils::Exceptions::ParameterCountMissmatch("1 parameter expected, but " + ::Utils::Tools::toString(params.size()) + " parameter(s) found");
	}

	text = params.front().value();

	std::cout << "println: " << text << std::endl;

	return Runtime::ControlFlow::Normal;
}


}
}
