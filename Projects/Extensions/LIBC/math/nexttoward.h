
#ifndef Slang_Extensions_LIBC_math_nexttoward_h
#define Slang_Extensions_LIBC_math_nexttoward_h


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


class NEXTTOWARD: public ExtensionMethod
{
public:
	NEXTTOWARD()
	: ExtensionMethod(0, "nexttoward", Designtime::DoubleType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("from", Common::TypeDeclaration(Designtime::DoubleType::TYPENAME)));
		params.push_back(Parameter::CreateDesigntime("to", Common::TypeDeclaration(Designtime::DoubleType::TYPENAME)));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_from = (*it++).value().toDouble();
		auto param_to   = (*it++).value().toDouble();

		*result = Runtime::DoubleType(nexttoward(param_from, param_to));

		return Runtime::ControlFlow::Normal;
	}
};


class NEXTTOWARDF: public ExtensionMethod
{
public:
	NEXTTOWARDF()
	: ExtensionMethod(0, "nexttowardf", Designtime::FloatType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("from", Common::TypeDeclaration(Designtime::FloatType::TYPENAME)));
		params.push_back(Parameter::CreateDesigntime("to", Common::TypeDeclaration(Designtime::FloatType::TYPENAME)));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_from = (*it++).value().toFloat();
		auto param_to   = (*it++).value().toFloat();

		*result = Runtime::FloatType(nexttowardf(param_from, param_to));

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
