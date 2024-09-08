
#ifndef Slang_Extensions_LIBC_cstring_strrchr_h
#define Slang_Extensions_LIBC_cstring_strrchr_h


// Library includes
#include <cassert>
#include <cstring>

// Project includes
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Runtime/BuildInTypes/IntegerObject.h>
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


class STRRCHR : public ExtensionMethod
{
public:
	STRRCHR()
	: ExtensionMethod( 0, "strrchr", Designtime::IntegerObject::TYPENAME )
	{
		ParameterList params;
		params.push_back( Parameter::CreateDesigntime( "str", Designtime::StringObject::TYPENAME ) );
		params.push_back( Parameter::CreateDesigntime( "ch", Designtime::IntegerObject::TYPENAME ) );

		setSignature( params );
	}

	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_str = (*it++).value().toStdString();
			auto param_ch  = (*it++).value().toInt();

			*result = Runtime::StringObject( std::string( strrchr( param_str.c_str(), param_ch ) ) );
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
