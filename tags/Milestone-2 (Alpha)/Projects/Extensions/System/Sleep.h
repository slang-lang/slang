
#ifndef ObjectiveScript_Extensions_System_Sleep_h
#define ObjectiveScript_Extensions_System_Sleep_h


// Library includes
#ifdef _WIN32
#	include <stdlib.h>
#else
	#include <chrono>
	#include <thread>
#endif

// Project includes
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
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


class Sleep : public Runtime::Method
{
public:
	Sleep()
	: Runtime::Method(0, "sleep", Designtime::VoidObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter("millis", Designtime::IntegerObject::TYPENAME, 0));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* /*result*/, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			long param_millis = (*it++).value().toInt();

#ifdef _WIN32
			_sleep(param_millis);
#else
			std::this_thread::sleep_for(std::chrono::milliseconds(param_millis));
#endif
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