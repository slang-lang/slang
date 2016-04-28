
#ifndef ObjectiveScript_Extensions_Apache_Post_h
#define ObjectiveScript_Extensions_Apache_Post_h


// Library includes

// Project includes
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Method.h>
#include <Core/Repository.h>
#include <Core/Tools.h>
#include <Core/Utils/Exceptions.h>
#include <Tools/Strings.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Apache {


class Post : public Runtime::Method
{
public:
	Post()
	: Runtime::Method(0, "post", Designtime::StringObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter("name", Designtime::StringObject::TYPENAME, VALUE_NONE));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const TokenIterator &token)
	{
		std::string text;

		if (params.size() != 1) {
			throw Utils::Exceptions::ParameterCountMissmatch("1 parameter expected, but " + ::Utils::Tools::toString(params.size()) + " parameter(s) found", token->position());
		}

		std::string param_name = params.front().value();
		std::string result_value;

		char *val = getenv(param_name.c_str());
		if ( val ) {
			result_value = std::string(val);
		}

		*result = Runtime::StringObject(result_value);

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}

#endif
