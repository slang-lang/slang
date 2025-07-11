
#ifndef Slang_Extensions_LIBC_math_log1p_h
#define Slang_Extensions_LIBC_math_log1p_h


// Library includes
#include <cmath>

// Project includes
#include <Core/Designtime/BuildInTypes/DoubleType.h>
#include <Core/Designtime/BuildInTypes/FloatType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/DoubleType.h>
#include <Core/Runtime/BuildInTypes/FloatType.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace math {


class LOG1P: public ExtensionMethod
{
public:
	LOG1P()
	: ExtensionMethod(0, "log1p", Designtime::DoubleType::TYPENAME)
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

		*result = Runtime::DoubleType(log1p(param_n));

		return Runtime::ControlFlow::Normal;
	}
};


class LOG1PF: public ExtensionMethod
{
public:
	LOG1PF()
	: ExtensionMethod(0, "log1pf", Designtime::FloatType::TYPENAME)
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

		*result = Runtime::FloatType(log1pf(param_value));

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
