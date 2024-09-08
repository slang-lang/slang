
#ifndef Slang_Extensions_LIBC_math_fma_h
#define Slang_Extensions_LIBC_math_fma_h


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
namespace LIBC {
namespace math {


class FMA: public ExtensionMethod
{
public:
	FMA()
	: ExtensionMethod(0, "fma", Designtime::DoubleObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("x", Common::TypeDeclaration(Designtime::DoubleObject::TYPENAME)));
		params.push_back(Parameter::CreateDesigntime("y", Common::TypeDeclaration(Designtime::DoubleObject::TYPENAME)));
		params.push_back(Parameter::CreateDesigntime("z", Common::TypeDeclaration(Designtime::DoubleObject::TYPENAME)));

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
			auto param_z = (*it++).value().toDouble();

			*result = Runtime::DoubleObject(fma(param_x, param_y, param_z));
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


class FMAF: public ExtensionMethod
{
public:
	FMAF()
	: ExtensionMethod(0, "fmaf", Designtime::FloatObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("x", Common::TypeDeclaration(Designtime::FloatObject::TYPENAME)));
		params.push_back(Parameter::CreateDesigntime("y", Common::TypeDeclaration(Designtime::FloatObject::TYPENAME)));
		params.push_back(Parameter::CreateDesigntime("z", Common::TypeDeclaration(Designtime::FloatObject::TYPENAME)));

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
			auto param_z = (*it++).value().toFloat();

			*result = Runtime::FloatObject(fmaf(param_x, param_y, param_z));
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
