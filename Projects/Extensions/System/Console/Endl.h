
#ifndef ObjectiveScript_Extensions_System_Console_Endl_h
#define ObjectiveScript_Extensions_System_Console_Endl_h


// Library includes

// Project includes
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Method.h>
#include <Core/Repository.h>
#include <Core/Tools.h>
#include <Core/Utils/Exceptions.h>
#include <Tools/Strings.h>
#include "Console.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {
namespace Console {


class Endl : public Runtime::Method
{
public:
	Endl()
	: Runtime::Method(0, "endl", Designtime::StringObject::TYPENAME)
	{
		ParameterList params;

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(const ParameterList& /*params*/, Runtime::Object* /*result*/, const Token& token)
	{
		try {
			if ( mOutMode == CERR ) {
				std::cerr << std::endl;
			}
			else if ( mOutMode == COUT ) {
				std::cout << std::endl;
			}
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
