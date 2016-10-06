
#ifndef ObjectiveScript_Extensions_System_WriteLn_h
#define ObjectiveScript_Extensions_System_WriteLn_h


// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Method.h>
#include <Core/Repository.h>
#include <Core/Tools.h>
#include <Core/Common/Exceptions.h>
#include <Tools/Strings.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {


class WriteLn : public Runtime::Method
{
public:
	WriteLn()
	: Runtime::Method(0, "writeln", Designtime::VoidObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter("text", Designtime::StringObject::TYPENAME, VALUE_NONE, true));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* /*result*/, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			std::string param_text = (*it++).value().toStdString();

			std::cout << param_text << std::endl;
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


#endif
