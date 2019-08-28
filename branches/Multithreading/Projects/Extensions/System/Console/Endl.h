
#ifndef ObjectiveScript_Extensions_System_Console_Endl_h
#define ObjectiveScript_Extensions_System_Console_Endl_h


// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Tools.h>
#include "Defines.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {
namespace Console {


class Endl : public ExtensionMethod
{
public:
	Endl()
	: ExtensionMethod(0, "endl", Designtime::StringObject::TYPENAME)
	{
		ParameterList params;

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& /*params*/, Runtime::Object* /*result*/, const Token& token)
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
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().thread(threadId)->exception() = Runtime::ExceptionData(data, token.position());
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
