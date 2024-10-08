
#ifndef Slang_Extensions_LIBC_math_ceil_h
#define Slang_Extensions_LIBC_math_ceil_h


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
namespace LIBC {
namespace math {


class CEIL: public ExtensionMethod
{
public:
	CEIL()
	: ExtensionMethod(0, "ceil", Designtime::DoubleObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("arg", Designtime::DoubleObject::TYPENAME));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_arg = (*it++).value().toDouble();

			*result = Runtime::DoubleObject(ceil(param_arg));
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


class CEILF: public ExtensionMethod
{
public:
	CEILF()
	: ExtensionMethod(0, "ceilf", Designtime::FloatObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("arg", Designtime::FloatObject::TYPENAME));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_arg = (*it++).value().toDouble();

			*result = Runtime::FloatObject(ceilf(param_arg));
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
