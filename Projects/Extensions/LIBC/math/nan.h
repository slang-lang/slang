
#ifndef Slang_Extensions_LIBC_math_nan_h
#define Slang_Extensions_LIBC_math_nan_h


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


class MathNAN: public ExtensionMethod
{
public:
	MathNAN()
	: ExtensionMethod(0, "nan", Designtime::DoubleType::TYPENAME)
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

		auto param_arg = (*it++).value().toStdString();

		*result = Runtime::DoubleType(nan(param_arg.c_str()));

		return Runtime::ControlFlow::Normal;
	}
};


class MathNANF: public ExtensionMethod
{
public:
	MathNANF()
	: ExtensionMethod(0, "nanf", Designtime::FloatType::TYPENAME)
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

		auto param_arg = (*it++).value().toStdString();

		*result = Runtime::FloatType(nanf(param_arg.c_str()));

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
