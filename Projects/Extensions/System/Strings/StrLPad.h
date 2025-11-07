
#ifndef Slang_Extensions_System_Strings_StrLPad_h
#define Slang_Extensions_System_Strings_StrLPad_h


// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Runtime/Exceptions.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Strings {


class StrLPad : public ExtensionMethod
{
public:
	StrLPad()
	: ExtensionMethod(nullptr, "strlpad", Designtime::StringType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("value", Designtime::StringType::TYPENAME, 0));
		params.push_back(Parameter::CreateDesigntime("length", Designtime::Int32Type::TYPENAME, 0));
		params.push_back(Parameter::CreateDesigntime("pattern", Designtime::StringType::TYPENAME, 0));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_value   = (*it++).value().toStdString();
		auto param_length  = static_cast<size_t>( (*it++).value().toInt() );
		auto param_pattern = (*it++).value().toStdString();

		if ( param_length < 0 ) {
			throw Runtime::Exceptions::SizeException("invalid length");
		}
		if ( param_pattern.size() != 1 ) {
			throw Runtime::Exceptions::SizeException("invalid pattern size");
		}

		if ( param_length > param_value.size() ) {
			param_value.insert(param_value.begin(), param_length - param_value.size(), param_pattern[0]);
		}

		*result = Runtime::StringType(param_value);

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
