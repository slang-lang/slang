
#ifndef Slang_Extensions_System_Strings_StrLen_h
#define Slang_Extensions_System_Strings_StrLen_h


// Library includes
#include <cstdlib>
#include <sstream>

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Runtime/Utils.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {


class Ascii : public ExtensionMethod
{
public:
	Ascii()
	: ExtensionMethod(0, "ascii", Designtime::StringType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("value", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		std::ostringstream character;
		character << (char)(*it++).value().toInt();

		*result = Runtime::StringType(character.str());

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}


#endif
