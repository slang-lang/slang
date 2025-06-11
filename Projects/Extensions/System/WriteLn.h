
#ifndef Slang_Extensions_System_WriteLn_h
#define Slang_Extensions_System_WriteLn_h


// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Designtime/BuildInTypes/VoidType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Tools.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {


class WriteLn : public ExtensionMethod
{
public:
	WriteLn()
	: ExtensionMethod(0, "writeln", Designtime::VoidType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("text", Designtime::StringType::TYPENAME, Runtime::AtomicValue(std::string(VALUE_NONE)), true));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* /*result*/ )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		std::string param_text = (*it++).value().toStdString();

		std::cout << param_text << std::endl;

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}


#endif
