
// Header
#include "AssertMsg.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {


Assert::Assert()
: Runtime::Method(0, "assert", Designtime::VoidObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("condition", Designtime::BoolObject::TYPENAME, BOOL_FALSE));
	params.push_back(Parameter("message", Designtime::StringObject::TYPENAME, VALUE_NONE, true));

	setSignature(params);
}

Runtime::ControlFlow::E Assert::execute(const ParameterList& params, Runtime::Object* /*result*/, const TokenIterator& token)
{
	if ( params.size() < 1 && params.size() > 2 ) {
		throw Utils::Exceptions::ParameterCountMissmatch("2 parameters expected, but " + ::Utils::Tools::toString(params.size()) + " parameter(s) found", token->position());
	}

	Runtime::Object condition = *params.front().pointer();
	std::string text;

	if ( params.size() == 2 ) {
		text = "with message \"" + params.back().value() + "\"";
	}

	if ( !isTrue(condition) ) {
		throw Utils::Exceptions::AssertionFailed(text, token->position());
	}

	return Runtime::ControlFlow::Normal;
}


AssertMsg::AssertMsg()
: Runtime::Method(0, "assertmsg", Designtime::VoidObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("condition", Designtime::BoolObject::TYPENAME, BOOL_FALSE));
	params.push_back(Parameter("message", Designtime::StringObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E AssertMsg::execute(const ParameterList& params, Runtime::Object* /*result*/, const TokenIterator& token)
{
	Runtime::Object condition = *params.front().pointer();
	std::string msg = params.back().value();

	if ( !isTrue(condition) ) {
		throw Utils::Exceptions::AssertionFailed("failed with message \"" + msg + "\"", token->position());
	}

	return Runtime::ControlFlow::Normal;
}


}
}
