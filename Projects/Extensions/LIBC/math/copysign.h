
#ifndef Slang_Extensions_LIBC_math_copysign_h
#define Slang_Extensions_LIBC_math_copysign_h


// Library includes
#include <cmath>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/DoubleObject.h>
#include <Core/Designtime/BuildInTypes/FloatObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/DoubleObject.h>
#include <Core/Runtime/BuildInTypes/FloatObject.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace ExtensionLIBC {
namespace math {


class COPYSIGN: public ExtensionMethod
{
public:
	COPYSIGN()
	: ExtensionMethod(0, "copysign", Designtime::DoubleObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("x", Common::TypeDeclaration(Designtime::DoubleObject::TYPENAME)));
		params.push_back(Parameter::CreateDesigntime("y", Common::TypeDeclaration(Designtime::DoubleObject::TYPENAME)));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_x = (*it++).value().toDouble();
			auto param_y = (*it++).value().toDouble();

			*result = Runtime::DoubleObject(copysign(param_x, param_y));
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().thread(threadId)->exception(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};


class COPYSIGNF: public ExtensionMethod
{
public:
	COPYSIGNF()
	: ExtensionMethod(0, "copysignf", Designtime::FloatObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("x", Common::TypeDeclaration(Designtime::FloatObject::TYPENAME)));
		params.push_back(Parameter::CreateDesigntime("y", Common::TypeDeclaration(Designtime::FloatObject::TYPENAME)));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_x = (*it++).value().toFloat();
			auto param_y = (*it++).value().toFloat();

			*result = Runtime::FloatObject(copysignf(param_x, param_y));
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().thread(threadId)->exception(data, token.position());
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