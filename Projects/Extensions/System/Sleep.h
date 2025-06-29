
#ifndef Slang_Extensions_System_Sleep_h
#define Slang_Extensions_System_Sleep_h


// Library includes
#ifdef _WIN32
#	include <cstdlib>
#else
	#include <chrono>
	#include <thread>
#endif

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Runtime/Utils.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {


class Sleep : public ExtensionMethod
{
public:
	Sleep()
	: ExtensionMethod(0, "sleep", Designtime::VoidType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("millis", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* /*result*/ )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		long param_millis = (*it++).value().toInt();

#ifdef _WIN32
		_sleep(param_millis);
#else
		std::this_thread::sleep_for(std::chrono::milliseconds(param_millis));
#endif

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}


#endif
