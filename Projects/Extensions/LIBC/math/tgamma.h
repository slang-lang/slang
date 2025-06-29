
#ifndef Slang_Extensions_LIBC_math_tgamma_h
#define Slang_Extensions_LIBC_math_tgamma_h


// Library includes
#include <math.h>

// Project includes
#include <Core/Designtime/BuildInTypes/DoubleType.h>
#include <Core/Designtime/BuildInTypes/FloatType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/DoubleType.h>
#include <Core/Runtime/BuildInTypes/FloatType.h>
#include <Core/Runtime/Utils.h>
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace math {


class TGAMMA: public ExtensionMethod
{
public:
	TGAMMA()
	: ExtensionMethod(0, "tgamma", Designtime::DoubleType::TYPENAME)
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

		*result = Runtime::DoubleType(tgamma(param_arg));

		return Runtime::ControlFlow::Normal;
	}
};


class TGAMMAF: public ExtensionMethod
{
public:
	TGAMMAF()
	: ExtensionMethod(0, "tgammaf", Designtime::FloatType::TYPENAME)
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

		*result = Runtime::DoubleType(tgammaf(param_arg));

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
