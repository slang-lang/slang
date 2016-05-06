
#ifndef ObjectiveScript_Extensions_System_Print_h
#define ObjectiveScript_Extensions_System_Print_h


// Library includes

// Project includes
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Method.h>
#include <Core/Repository.h>
#include <Core/Tools.h>
#include <Core/Utils/Exceptions.h>
#include <Tools/Strings.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {


class Printf : public Runtime::Method
{
public:
	Printf()
	: Runtime::Method(0, "printf", Designtime::VoidObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter("text", Designtime::StringObject::TYPENAME, VALUE_NONE));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* /*result*/, const TokenIterator& /*token*/)
	{
		std::string text = params.front().value();

		std::cout << "printf: " << text;

		return Runtime::ControlFlow::Normal;
	}
};


}
}

#endif
