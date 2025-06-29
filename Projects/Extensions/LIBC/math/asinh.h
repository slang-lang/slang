
#ifndef Slang_Extensions_LIBC_math_asinh_h
#define Slang_Extensions_LIBC_math_asinh_h


// Library includes
#include <cmath>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/DoubleType.h>
#include <Core/Designtime/BuildInTypes/FloatType.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/DoubleType.h>
#include <Core/Runtime/BuildInTypes/FloatType.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Runtime/Utils.h>
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace math {


class ASINH: public ExtensionMethod
{
public:
	ASINH()
	: ExtensionMethod(0, "asinh", Designtime::DoubleType::TYPENAME)
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

		*result = Runtime::DoubleType(asinh(param_arg));

		return Runtime::ControlFlow::Normal;
	}
};


class ASINHF: public ExtensionMethod
{
public:
	ASINHF()
	: ExtensionMethod(0, "asinhf", Designtime::FloatType::TYPENAME)
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

		*result = Runtime::FloatType(asinhf(param_arg));

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
