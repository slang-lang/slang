
#ifndef ObjectiveScript_Extensions_System_Strings_StrLTrim_h
#define ObjectiveScript_Extensions_System_Strings_StrLTrim_h


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


class StrLTrim : public Runtime::Method
{
public:
	StrLTrim()
	: Runtime::Method(0, "strltrim", Designtime::StringObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter("value", Designtime::StringObject::TYPENAME, 0));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			std::string param_value = (*it++).value().toStdString();

			*result = Runtime::StringObject(::Utils::Tools::stringTrimLeft(param_value));
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = mRepository->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			mExceptionData = Runtime::ExceptionData(data, token.position());
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
