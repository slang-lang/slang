
#ifndef ObjectiveScript_Extensions_System_Assert_h
#define ObjectiveScript_Extensions_System_Assert_h


// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/BoolObject.h>
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


class AssertMsg : public Runtime::Method
{
public:
	AssertMsg()
	: Runtime::Method(0, "assertmsg", Designtime::VoidObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter(ANONYMOUS_OBJECT, Designtime::BoolObject::TYPENAME, FALSE));
		params.push_back(Parameter(ANONYMOUS_OBJECT, Designtime::StringObject::TYPENAME, VALUE_NONE));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* /*result*/) {
		std::string text;

		if ( params.size() != 2 ) {
			throw Utils::Exceptions::ParameterCountMissmatch("1 parameter expected, but " + ::Utils::Tools::toString(params.size()) + " parameter(s) found");
		}

		Runtime::Object condition = *params.front().pointer();

		if ( !isTrue(condition) ) {
			throw Utils::Exceptions::AssertionFailed(condition.ToString() + ", with message: \"" + params.back().value() + "\"");
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};


}
}

#endif
