
#ifndef Slang_Extensions_LIBC_math_round_h
#define Slang_Extensions_LIBC_math_round_h


// Library includes
#include <math.h>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/DoubleType.h>
#include <Core/Designtime/BuildInTypes/FloatType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/DoubleType.h>
#include <Core/Runtime/BuildInTypes/FloatType.h>
#include <Core/Runtime/Utils.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace math {


class ROUND: public ExtensionMethod
{
public:
	ROUND()
	: ExtensionMethod(0, "round", Designtime::DoubleType::TYPENAME)
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
		*result = Runtime::DoubleType(floor(param_arg + 0.5));
#else
		*result = Runtime::DoubleType(round(param_arg));
#endif

		return Runtime::ControlFlow::Normal;
	}
};


class ROUNDF: public ExtensionMethod
{
public:
	ROUNDF()
	: ExtensionMethod(0, "round", Designtime::FloatType::TYPENAME)
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
		*result = Runtime::FloatType(floorf(param_arg + 0.5f));
#else
		*result = Runtime::FloatType(roundf(param_arg));
#endif

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
