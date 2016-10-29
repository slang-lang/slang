
#ifndef ObjectiveScript_Extensions_System_Math_Sqrt_h
#define ObjectiveScript_Extensions_System_Math_Sqrt_h


// Library includes
#include <math.h>

// Project includes
#include <Core/BuildInObjects/DoubleObject.h>
#include <Core/BuildInObjects/FloatObject.h>
#include <Core/Designtime/BuildInTypes/DoubleObject.h>
#include <Core/Designtime/BuildInTypes/FloatObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Tools.h>
#include <Tools/Strings.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {
namespace Math {


class SqrtDouble: public ExtensionMethod
{
public:
	SqrtDouble()
	: ExtensionMethod(0, "sqrt", Designtime::DoubleObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter("value", Designtime::DoubleObject::TYPENAME, VALUE_NONE));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			double param_value = (*it++).value().toDouble();

			*result = Runtime::DoubleObject(sqrt(param_value));
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			mExceptionData = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};


class SqrtFloat: public ExtensionMethod
{
public:
	SqrtFloat()
	: ExtensionMethod(0, "sqrt", Designtime::FloatObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter("value", Designtime::FloatObject::TYPENAME, VALUE_NONE));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			double param_value = (*it++).value().toDouble();

			*result = Runtime::DoubleObject(sqrt(param_value));
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			mExceptionData = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
