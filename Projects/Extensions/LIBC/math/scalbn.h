
#ifndef Slang_Extensions_LIBC_math_scalbn_h
#define Slang_Extensions_LIBC_math_scalbn_h


// Library includes
#include <math.h>

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


class SCALBN: public ExtensionMethod
{
public:
	SCALBN()
	: ExtensionMethod(0, "scalbn", Designtime::DoubleType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("arg", Designtime::DoubleType::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("exp", Designtime::DoubleType::TYPENAME));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_arg = (*it++).value().toDouble();
		auto param_exp = (*it++).value().toDouble();

		*result = Runtime::DoubleType(scalbn(param_arg, param_exp));

		return Runtime::ControlFlow::Normal;
	}
};


class SCALBNF: public ExtensionMethod
{
public:
	SCALBNF()
	: ExtensionMethod(0, "scalbnf", Designtime::FloatType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("arg", Designtime::FloatType::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("exp", Designtime::FloatType::TYPENAME));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_arg = (*it++).value().toFloat();
		auto param_exp = (*it++).value().toFloat();

		*result = Runtime::FloatType(scalbnf(param_arg, param_exp));

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
