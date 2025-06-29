
#ifndef Slang_Extensions_LIBC_math_remainder_h
#define Slang_Extensions_LIBC_math_remainder_h


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


class REMAINDER: public ExtensionMethod
{
public:
	REMAINDER()
	: ExtensionMethod(0, "remainder", Designtime::DoubleType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("x", Common::TypeDeclaration(Designtime::DoubleType::TYPENAME)));
		params.push_back(Parameter::CreateDesigntime("y", Common::TypeDeclaration(Designtime::DoubleType::TYPENAME)));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_x = (*it++).value().toDouble();
		auto param_y = (*it++).value().toDouble();

		*result = Runtime::DoubleType(remainder(param_x, param_y));

		return Runtime::ControlFlow::Normal;
	}
};


class REMAINDERF: public ExtensionMethod
{
public:
	REMAINDERF()
	: ExtensionMethod(0, "remainderf", Designtime::FloatType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("x", Common::TypeDeclaration(Designtime::FloatType::TYPENAME)));
		params.push_back(Parameter::CreateDesigntime("y", Common::TypeDeclaration(Designtime::FloatType::TYPENAME)));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_x = (*it++).value().toFloat();
		auto param_y = (*it++).value().toFloat();

		*result = Runtime::FloatType(remainderf(param_x, param_y));

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
