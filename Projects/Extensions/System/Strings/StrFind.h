
#ifndef Slang_Extensions_System_Strings_StrFind_h
#define Slang_Extensions_System_Strings_StrFind_h


// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Tools/Strings.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Strings {


class StrFind : public ExtensionMethod
{
public:
	StrFind()
	: ExtensionMethod( nullptr, "strfind", Designtime::Int32Type::TYPENAME )
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("source", Designtime::StringType::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("target", Designtime::StringType::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("position", Designtime::Int32Type::TYPENAME, 0, true));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_source   = (*it++).value().toStdString();
		auto param_target   = (*it++).value().toStdString();
		auto param_position = (*it).value().toInt();

		*result = Runtime::Int32Type( static_cast<int32_t>( param_source.find( param_target, param_position ) ) );

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
