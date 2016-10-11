
#ifndef ObjectiveScript_Extensions_System_Math_Abs_h
#define ObjectiveScript_Extensions_System_Math_Abs_h


// Library includes
#include <cmath>

// Project includes
#include <Core/BuildInObjects/DoubleObject.h>
#include <Core/BuildInObjects/FloatObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/DoubleObject.h>
#include <Core/Designtime/BuildInTypes/FloatObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Repository.h>
#include <Tools/Strings.h>
#include "Math.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {
namespace Math {


class AbsDouble: public ExtensionMethod
{
public:
	AbsDouble()
	: ExtensionMethod(0, "abs", Designtime::DoubleObject::TYPENAME)
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

			*result = Runtime::DoubleObject(std::abs(param_value));
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Repository::GetInstance().createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			mExceptionData = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};


class AbsFloat: public ExtensionMethod
{
public:
	AbsFloat()
	: ExtensionMethod(0, "abs", Designtime::FloatObject::TYPENAME)
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

			float param_value = (*it++).value().toFloat();

			*result = Runtime::FloatObject(std::abs(param_value));
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Repository::GetInstance().createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			mExceptionData = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};


class AbsInt: public ExtensionMethod
{
public:
	AbsInt()
	: ExtensionMethod(0, "abs", Designtime::IntegerObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter("value", Designtime::IntegerObject::TYPENAME, VALUE_NONE));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			int param_value = (*it++).value().toInt();

			*result = Runtime::IntegerObject(std::abs(param_value));
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Repository::GetInstance().createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
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
