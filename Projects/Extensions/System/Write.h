
#ifndef Slang_Extensions_System_Write_h
#define Slang_Extensions_System_Write_h


// Library includes
#include <iostream>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Designtime/BuildInTypes/VoidType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/Utils.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {


class Write : public ExtensionMethod
{
public:
	Write()
	: ExtensionMethod(0, "write", Designtime::VoidType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("text", Designtime::StringType::TYPENAME));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* /*result*/ )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		std::string param_text = (*it++).value().toStdString();

		std::cout << param_text;

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}


#endif
