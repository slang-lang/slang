
#ifndef ObjectiveScript_Extensions_System_Math_Round_h
#define ObjectiveScript_Extensions_System_Math_Round_h


// Library includes
#include <math.h>

// Project includes
#include <Core/BuildInObjects/DoubleObject.h>
#include <Core/BuildInObjects/FloatObject.h>
#include <Core/Designtime/BuildInTypes/DoubleObject.h>
#include <Core/Designtime/BuildInTypes/FloatObject.h>
#include <Core/Method.h>
#include <Core/Repository.h>
#include <Core/Tools.h>
#include <Core/Common/Exceptions.h>
#include <Tools/Strings.h>
#include "Math.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {
namespace Math {


class RoundDouble: public Runtime::Method
{
public:
	RoundDouble()
	: Runtime::Method(0, "round", Designtime::DoubleObject::TYPENAME)
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

#ifdef _WIN32
			*result = Runtime::DoubleObject(floor(param_value + 0.5));
#else
			*result = Runtime::DoubleObject(round(param_value));
#endif
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = mRepository->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			mExceptionData = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};


class RoundFloat: public Runtime::Method
{
public:
	RoundFloat()
	: Runtime::Method(0, "round", Designtime::FloatObject::TYPENAME)
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

#ifdef _WIN32
			*result = Runtime::FloatObject(floor(param_value + 0.5f));
#else
			*result = Runtime::FloatObject(round(param_value));
#endif
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = mRepository->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
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
