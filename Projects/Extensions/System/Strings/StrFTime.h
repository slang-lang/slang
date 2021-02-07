
#ifndef Slang_Extensions_System_StrFTime_h
#define Slang_Extensions_System_StrFTime_h


// Library includes
#include <ctime>
#include <iomanip>
#include <iostream>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/IntegerObject.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Tools.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Strings {


class StrFTime : public ExtensionMethod
{
public:
	StrFTime()
	: ExtensionMethod( 0, "strftime", Designtime::IntegerObject::TYPENAME )
	{
		ParameterList params;
		params.push_back( Parameter::CreateDesigntime( "format", Designtime::StringObject::TYPENAME, 0 ) );
       		params.push_back( Parameter::CreateDesigntime( "time", Designtime::IntegerObject::TYPENAME, 0, true ) );

		setSignature( params );
	}

public:
	Runtime::ControlFlow::E execute( Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token )
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			std::string param_format = (*it++).value().toStdString();
			int32_t param_time = (*it++).value().toInt();

			std::time_t time;
			if ( param_time ) {
				time = param_time;
			}
			else {
				time = std::time(nullptr);
			}

			std::tm tm = *std::localtime(&time);

			std::stringstream ssr;
			ssr << std::put_time( &tm, param_format.c_str() );

			*result = Runtime::StringObject( ssr.str() );
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
