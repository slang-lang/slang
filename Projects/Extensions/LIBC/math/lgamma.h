
#ifndef Slang_Extensions_LIBC_math_lgamma_h
#define Slang_Extensions_LIBC_math_lgamma_h


// Library includes
#include <math.h>

// Project includes
#include <Core/Designtime/BuildInTypes/DoubleType.h>
#include <Core/Designtime/BuildInTypes/FloatType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/DoubleType.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace math {


class LGAMMA: public ExtensionMethod
{
public:
	LGAMMA()
	: ExtensionMethod(0, "lgamma", Designtime::DoubleType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("arg", Designtime::DoubleType::TYPENAME));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_arg = (*it++).value().toDouble();

		*result = Runtime::DoubleType(lgamma(param_arg));

		return Runtime::ControlFlow::Normal;
	}
};


class LGAMMAF: public ExtensionMethod
{
public:
	LGAMMAF()
	: ExtensionMethod(0, "lgammaf", Designtime::FloatType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("arg", Designtime::FloatType::TYPENAME));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_arg = (*it++).value().toFloat();

		*result = Runtime::DoubleType(lgammaf(param_arg));

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
