
#ifndef Slang_Extensions_LIBC_math_trunc_h
#define Slang_Extensions_LIBC_math_trunc_h


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


class TRUNC: public ExtensionMethod
{
public:
	TRUNC()
	: ExtensionMethod(0, "trunc", Designtime::DoubleType::TYPENAME)
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

#ifdef _WIN32
		*result = Runtime::DoubleType((param_arg > 0) ? floor(param_arg) : ceil(param_arg));
#else
		*result = Runtime::DoubleType(trunc(param_arg));
#endif

		return Runtime::ControlFlow::Normal;
	}
};


class TRUNCF: public ExtensionMethod
{
public:
	TRUNCF()
	: ExtensionMethod(0, "truncf", Designtime::FloatType::TYPENAME)
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

#ifdef _WIN32
		*result = Runtime::FloatType((param_arg > 0) ? floorf(param_arg) : ceilf(param_arg));
#else
		*result = Runtime::FloatType(truncf(param_arg));
#endif

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
