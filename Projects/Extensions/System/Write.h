
#ifndef ObjectiveScript_Extensions_System_Write_h
#define ObjectiveScript_Extensions_System_Write_h


// Library includes

// Project includes
#include <Core/Interfaces/IExtension.h>
#include <Core/Method.h>

#include <Core/Designtime/BuildInTypes/BoolObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Repository.h>
#include <Core/Tools.h>
#include <Core/Utils/Exceptions.h>
#include <Tools/Strings.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {


class Write : public Runtime::Method
{
public:
	Write()
	: Runtime::Method(0, "write", Designtime::VoidObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter(ANONYMOUS_OBJECT, Designtime::StringObject::TYPENAME, VALUE_NONE));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* /*result*/, const TokenIterator& token)
	{
		std::string text;

		if ( params.size() != 1 ) {
			throw Utils::Exceptions::ParameterCountMissmatch("1 parameter expected, but " + ::Utils::Tools::toString(params.size()) + " parameter(s) found", token->position());
		}

		text = params.front().value();

		std::cout << text;

		return Runtime::ControlFlow::Normal;
	}
};


}
}

#endif
