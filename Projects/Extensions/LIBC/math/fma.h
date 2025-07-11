
#ifndef Slang_Extensions_LIBC_math_fma_h
#define Slang_Extensions_LIBC_math_fma_h


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


class FMA: public ExtensionMethod
{
public:
	FMA()
	: ExtensionMethod(0, "fma", Designtime::DoubleType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("x", Common::TypeDeclaration(Designtime::DoubleType::TYPENAME)));
		params.push_back(Parameter::CreateDesigntime("y", Common::TypeDeclaration(Designtime::DoubleType::TYPENAME)));
		params.push_back(Parameter::CreateDesigntime("z", Common::TypeDeclaration(Designtime::DoubleType::TYPENAME)));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_x = (*it++).value().toDouble();
		auto param_y = (*it++).value().toDouble();
		auto param_z = (*it++).value().toDouble();

		*result = Runtime::DoubleType(fma(param_x, param_y, param_z));

		return Runtime::ControlFlow::Normal;
	}
};


class FMAF: public ExtensionMethod
{
public:
	FMAF()
	: ExtensionMethod(0, "fmaf", Designtime::FloatType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("x", Common::TypeDeclaration(Designtime::FloatType::TYPENAME)));
		params.push_back(Parameter::CreateDesigntime("y", Common::TypeDeclaration(Designtime::FloatType::TYPENAME)));
		params.push_back(Parameter::CreateDesigntime("z", Common::TypeDeclaration(Designtime::FloatType::TYPENAME)));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_x = (*it++).value().toFloat();
		auto param_y = (*it++).value().toFloat();
		auto param_z = (*it++).value().toFloat();

		*result = Runtime::FloatType(fmaf(param_x, param_y, param_z));

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
