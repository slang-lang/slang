
#ifndef Slang_Extensions_LIBC_math_log2_h
#define Slang_Extensions_LIBC_math_log2_h


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
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace math {


class LOG2: public ExtensionMethod
{
public:
	LOG2()
	: ExtensionMethod(0, "log2", Designtime::DoubleType::TYPENAME)
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

		*result = Runtime::DoubleType(log2(param_n));

		return Runtime::ControlFlow::Normal;
	}
};


class LOG2F: public ExtensionMethod
{
public:
	LOG2F()
	: ExtensionMethod(0, "log2f", Designtime::FloatType::TYPENAME)
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

		*result = Runtime::FloatType(log2f(param_value));

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
