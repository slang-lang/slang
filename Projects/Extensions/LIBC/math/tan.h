
#ifndef Slang_Extensions_LIBC_math_tan_h
#define Slang_Extensions_LIBC_math_tan_h


// Library includes
#include <cmath>

// Project includes
#include <Core/Designtime/BuildInTypes/DoubleType.h>
#include <Core/Designtime/BuildInTypes/FloatType.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/DoubleType.h>
#include <Core/Runtime/BuildInTypes/FloatType.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace math {


class TAN: public ExtensionMethod
{
public:
	TAN()
	: ExtensionMethod(0, "tan", Designtime::DoubleType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("arg", Common::TypeDeclaration(Designtime::StringType::TYPENAME)));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_arg = (*it++).value().toDouble();

		*result = Runtime::DoubleType(tan(param_arg));

		return Runtime::ControlFlow::Normal;
	}
};


class TANF: public ExtensionMethod
{
public:
	TANF()
	: ExtensionMethod(0, "tanf", Designtime::FloatType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("arg", Common::TypeDeclaration(Designtime::StringType::TYPENAME)));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_arg = (*it++).value().toFloat();

		*result = Runtime::FloatType(tanf(param_arg));

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
