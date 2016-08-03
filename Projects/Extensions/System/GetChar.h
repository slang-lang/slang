
#ifndef ObjectiveScript_Extensions_System_GetChar_h
#define ObjectiveScript_Extensions_System_GetChar_h


// Library includes
#include <stdlib.h>

// Project includes
#include <Core/BuildInObjects/StringObject.h>
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


class GetChar : public Runtime::Method
{
public:
	GetChar()
	: Runtime::Method(0, "getchar", Designtime::StringObject::TYPENAME)
	{
		ParameterList params;

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(const ParameterList& /*params*/, Runtime::Object* result, const Token& token)
	{
		try {
			std::string value;

			int c = getchar();
			if ( c ) {
				value = (char)c;
			}

			*result = Runtime::StringObject(value);
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
