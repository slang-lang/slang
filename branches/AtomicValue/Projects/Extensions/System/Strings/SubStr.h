
#ifndef ObjectiveScript_Extensions_System_Strings_SubStr_h
#define ObjectiveScript_Extensions_System_Strings_SubStr_h


// Library includes
#include <stdlib.h>

// Project includes
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
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
namespace System {
namespace Strings {


class SubStr : public Runtime::Method
{
public:
	SubStr()
	: Runtime::Method(0, "substr", Designtime::StringObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter("value", Designtime::StringObject::TYPENAME, VALUE_NONE));
		params.push_back(Parameter("start", Designtime::IntegerObject::TYPENAME, VALUE_NONE));
		params.push_back(Parameter("length", Designtime::IntegerObject::TYPENAME, "-1", true));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token)
	{
		try {
			int startIdx = -1;
			int endIdx = -1;

			ParameterList::const_iterator it = params.begin();

			std::string param_value = (*it++).value();
			std::string param_start = (*it++).value();
			startIdx = Tools::stringToInt(param_start);

			if ( params.size() >= 3 ) {
				std::string param_end = (*it++).value();
				endIdx = Tools::stringToInt(param_end);
			}

			std::string result_value = param_value.substr(startIdx, endIdx);

			*result = Runtime::StringObject(result_value);
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = mRepository->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(e.what());

			mExceptionData = Runtime::ExceptionData(data, token->position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
