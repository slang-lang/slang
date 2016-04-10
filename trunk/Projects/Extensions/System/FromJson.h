
#ifndef ObjectiveScript_Extensions_System_FromJson_h
#define ObjectiveScript_Extensions_System_FromJson_h


// Library includes
#include <Json/Parser.h>
#include <Json/Value.h>

// Project includes
#include <Core/BuildInObjects/GenericObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/GenericObject.h>
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


class FromJson : public Runtime::Method
{
public:
	FromJson()
	: Runtime::Method(0, "FromJsonString", Designtime::VoidObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter("object", Designtime::GenericObject::TYPENAME, VALUE_NONE));
		params.push_back(Parameter("value", Designtime::StringObject::TYPENAME, VALUE_NONE));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token)
	{
		(void)result;
		(void)token;

		try {
			ParameterList::const_iterator it = params.begin();

			Runtime::Object *obj = (*it++).pointer();
			std::string jsonStr = (*it++).value();

			obj->FromJson(Json::Parser::parse(jsonStr));
		}
		catch ( std::exception &e ) {
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

#endif
