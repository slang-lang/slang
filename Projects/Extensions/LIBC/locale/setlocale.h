
#ifndef Slang_Extensions_LIBC_locale_setlocale_h
#define Slang_Extensions_LIBC_locale_setlocale_h


// Library includes
#include <cassert>

// Project includes
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace locale {


class SETLOCALE : public ExtensionMethod
{
public:
	SETLOCALE()
	: ExtensionMethod( 0, "setlocale", Designtime::StringType::TYPENAME )
	{
		ParameterList params;
		params.push_back( Parameter::CreateDesigntime( "category", Designtime::Int32Type::TYPENAME ) );
		params.push_back( Parameter::CreateDesigntime( "locale", Designtime::StringType::TYPENAME ) );

		setSignature( params );
	}

	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_category = (*it++).value().toInt();
			auto param_locale   = (*it++).value().toStdString();

			*result = Runtime::StringType( std::string( setlocale( param_category, param_locale.c_str() ) ) );
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance( Runtime::StringType::TYPENAME, ANONYMOUS_OBJECT );
			*data = Runtime::StringType( std::string( e.what() ) );

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
