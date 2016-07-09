
#ifndef ObjectiveScript_Extensions_System_Strings_StrFind_h
#define ObjectiveScript_Extensions_System_Strings_StrFind_h


// Library includes
#include <stdlib.h>

// Project includes
#include <Core/BuildInObjects/IntegerObject.h>
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


class StrFind : public Runtime::Method
{
public:
	StrFind()
	: Runtime::Method(0, "strfind", Designtime::IntegerObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter("source", Designtime::StringObject::TYPENAME, VALUE_NONE));
		params.push_back(Parameter("target", Designtime::StringObject::TYPENAME, VALUE_NONE));
		params.push_back(Parameter("position", Designtime::IntegerObject::TYPENAME, 0, true));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			std::string param_source = (*it++).value().toStdString();
			std::string param_target = (*it++).value().toStdString();
			int param_position = (*it).value().toInt();

			int my_result = param_source.find(param_target, param_position);

			*result = Runtime::IntegerObject(my_result);
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
