
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
		params.push_back(Parameter("text", Designtime::StringObject::TYPENAME, VALUE_NONE));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* /*result*/, const Token& token)
	{
		try {
			ParameterList::const_iterator it = params.begin();

			std::string param_text = (*it++).value().toStdString();

			std::cout << param_text;
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

#endif
