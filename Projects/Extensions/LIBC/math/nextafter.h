
#ifndef Slang_Extensions_LIBC_math_nextafter_h
#define Slang_Extensions_LIBC_math_nextafter_h


// Library includes
#include <cmath>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/DoubleType.h>
#include <Core/Designtime/BuildInTypes/FloatObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/DoubleType.h>
#include <Core/Runtime/BuildInTypes/FloatObject.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace math {


class NEXTAFTER: public ExtensionMethod
{
public:
	NEXTAFTER()
	: ExtensionMethod(0, "nextafter", Designtime::DoubleType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("from", Common::TypeDeclaration(Designtime::DoubleType::TYPENAME)));
		params.push_back(Parameter::CreateDesigntime("to", Common::TypeDeclaration(Designtime::DoubleType::TYPENAME)));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_from = (*it++).value().toDouble();
			auto param_to   = (*it++).value().toDouble();

			*result = Runtime::DoubleType(nextafter(param_from, param_to));
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


class NEXTAFTERF: public ExtensionMethod
{
public:
	NEXTAFTERF()
	: ExtensionMethod(0, "nextafterf", Designtime::FloatObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("from", Common::TypeDeclaration(Designtime::FloatObject::TYPENAME)));
		params.push_back(Parameter::CreateDesigntime("to", Common::TypeDeclaration(Designtime::FloatObject::TYPENAME)));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_from = (*it++).value().toFloat();
			auto param_to   = (*it++).value().toFloat();

			*result = Runtime::FloatObject(nextafterf(param_from, param_to));
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
