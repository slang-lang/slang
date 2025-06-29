
#ifndef Slang_Extensions_LIBC_math_ldexp_h
#define Slang_Extensions_LIBC_math_ldexp_h


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


class LDEXP: public ExtensionMethod
{
public:
	LDEXP()
	: ExtensionMethod(0, "ldexp", Designtime::DoubleType::TYPENAME)
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

		*result = Runtime::DoubleType(ldexp(param_arg, param_exp));

		return Runtime::ControlFlow::Normal;
	}
};


class LDEXPF: public ExtensionMethod
{
public:
	LDEXPF()
	: ExtensionMethod(0, "ldexpf", Designtime::FloatType::TYPENAME)
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

		*result = Runtime::FloatType(ldexpf(param_arg, param_exp));

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
