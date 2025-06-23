
#ifndef Slang_Extensions_LIBC_math_log10_h
#define Slang_Extensions_LIBC_math_log10_h


// Library includes
#include <cmath>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/DoubleType.h>
#include <Core/Designtime/BuildInTypes/FloatType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/DoubleType.h>
#include <Core/Runtime/BuildInTypes/FloatType.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Runtime/Utils.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace math {


class LOG10: public ExtensionMethod
{
public:
	LOG10()
	: ExtensionMethod(0, "log10", Designtime::DoubleType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("n", Common::TypeDeclaration(Designtime::DoubleType::TYPENAME)));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_n = (*it++).value().toDouble();

		*result = Runtime::DoubleType(log10(param_n));

		return Runtime::ControlFlow::Normal;
	}
};


class LOG10F: public ExtensionMethod
{
public:
	LOG10F()
	: ExtensionMethod(0, "log10f", Designtime::FloatType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("value", Common::TypeDeclaration(Designtime::FloatType::TYPENAME)));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_value = (*it++).value().toFloat();

		*result = Runtime::FloatType(log10f(param_value));

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
