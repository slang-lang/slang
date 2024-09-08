
#ifndef Slang_Extensions_LIBC_cstring_strncat_h
#define Slang_Extensions_LIBC_cstring_strncat_h


// Library includes
#include <cassert>

// Project includes
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace cstring {


class STRNCAT : public ExtensionMethod
{
public:
	STRNCAT()
	: ExtensionMethod( 0, "strncat", Designtime::StringObject::TYPENAME )
	{
		ParameterList params;
		params.push_back( Parameter::CreateDesigntime( "destination", Designtime::StringObject::TYPENAME ) );
		params.push_back( Parameter::CreateDesigntime( "source", Designtime::StringObject::TYPENAME ) );
		params.push_back( Parameter::CreateDesigntime( "num", Designtime::IntegerObject::TYPENAME ) );

		setSignature( params );
	}

	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_destination = (*it++).value().toStdString();
			auto param_source      = (*it++).value().toStdString();
            auto param_num         = (*it++).value().toInt();

			*result = Runtime::StringObject( param_destination + param_source.substr( param_num ) );
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance( Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT );
			*data = Runtime::StringObject( std::string( e.what() ) );

			Controller::Instance().thread(threadId)->exception() = Runtime::ExceptionData( data, token.position() );
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
