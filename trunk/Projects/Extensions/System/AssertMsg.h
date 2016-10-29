
#ifndef ObjectiveScript_Extensions_System_Assert_h
#define ObjectiveScript_Extensions_System_Assert_h


// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/BoolObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Tools.h>
#include <Tools/Strings.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {


class Assert : public ExtensionMethod
{
public:
	Assert()
	: ExtensionMethod(0, "assert", Designtime::VoidObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter("condition", Designtime::BoolObject::TYPENAME, false));
		params.push_back(Parameter("message", Designtime::StringObject::TYPENAME, VALUE_NONE, true));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* /*result*/, const Token& token)
	{
		Runtime::Object condition = *params.front().pointer();
		std::string text;

		if ( params.size() == 2 ) {
			text = "with message \"" + params.back().value().toStdString() + "\"";
		}

		if ( !isTrue(condition) ) {
			throw Runtime::Exceptions::AssertionFailed(text, token.position());
		}

		return Runtime::ControlFlow::Normal;
	}
};


class AssertMsg : public ExtensionMethod
{
public:
	AssertMsg()
	: ExtensionMethod(0, "assertmsg", Designtime::VoidObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter("condition", Designtime::BoolObject::TYPENAME, false));
		params.push_back(Parameter("message", Designtime::StringObject::TYPENAME, VALUE_NONE));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* /*result*/, const Token& token)
	{
		Runtime::Object condition = *params.front().pointer();
		std::string msg = params.back().value().toStdString();

		if ( !isTrue(condition) ) {
			throw Runtime::Exceptions::AssertionFailed("failed with message \"" + msg + "\"", token.position());
		}

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}


#endif
