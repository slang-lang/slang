
#ifndef ObjectiveScript_Extensions_System_StdTime_h
#define ObjectiveScript_Extensions_System_StdTime_h


// Library includes
#include <time.h>

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


class StdTime : public Runtime::Method
{
public:
	StdTime()
	: Runtime::Method(0, "time", Designtime::IntegerObject::TYPENAME)
	{
		ParameterList params;

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			*result = Runtime::IntegerObject((int)time(NULL));
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