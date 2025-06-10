
#ifndef Slang_Extensions_LIBC_cstring_strncmp_h
#define Slang_Extensions_LIBC_cstring_strncmp_h


// Library includes
#include <cassert>
#include <cstring>

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
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
namespace cstring {


class STRNCMP : public ExtensionMethod
{
public:
	STRNCMP()
	: ExtensionMethod( 0, "strncmp", Designtime::Int32Type::TYPENAME )
	{
		ParameterList params;
		params.push_back( Parameter::CreateDesigntime( "str1", Designtime::StringType::TYPENAME ) );
		params.push_back( Parameter::CreateDesigntime( "str2", Designtime::StringType::TYPENAME ) );
		params.push_back( Parameter::CreateDesigntime( "num", Designtime::Int32Type::TYPENAME ) );

		setSignature( params );
	}

	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_str1 = (*it++).value().toStdString();
			auto param_str2 = (*it++).value().toStdString();
			auto param_num  = (*it++).value().toInt();

			*result = Runtime::Int32Type( strncmp( param_str1.c_str(), param_str2.c_str(), param_num ) );
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
