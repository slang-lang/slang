
#ifndef Slang_Extensions_LIBC_math_ldexp_h
#define Slang_Extensions_LIBC_math_ldexp_h


// Library includes
#include <math.h>

// Project includes
#include <Core/Designtime/BuildInTypes/DoubleObject.h>
#include <Core/Designtime/BuildInTypes/FloatObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/DoubleObject.h>
#include <Core/Runtime/BuildInTypes/FloatObject.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace ExtensionLIBC {
namespace math {


class LDEXP: public ExtensionMethod
{
public:
	LDEXP()
	: ExtensionMethod(0, "ldexp", Designtime::DoubleObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("arg", Designtime::DoubleObject::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("exp", Designtime::DoubleObject::TYPENAME));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_arg = (*it++).value().toDouble();
			auto param_exp = (*it++).value().toDouble();

			*result = Runtime::DoubleObject(ldexp(param_arg, param_exp));
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().thread(threadId)->exception() = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};


class LDEXPF: public ExtensionMethod
{
public:
	LDEXPF()
	: ExtensionMethod(0, "ldexpf", Designtime::FloatObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("arg", Designtime::FloatObject::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("exp", Designtime::FloatObject::TYPENAME));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_arg = (*it++).value().toFloat();
			auto param_exp = (*it++).value().toFloat();

			*result = Runtime::FloatObject(ldexpf(param_arg, param_exp));
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().thread(threadId)->exception() = Runtime::ExceptionData(data, token.position());
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