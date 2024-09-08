
#ifndef Slang_Extensions_LIBC_stdio_fwrite_h
#define Slang_Extensions_LIBC_stdio_fwrite_h


// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/BoolObject.h>
#include <Core/Designtime/BuildInTypes/DoubleObject.h>
#include <Core/Designtime/BuildInTypes/FloatObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/BoolObject.h>
#include <Core/Runtime/BuildInTypes/DoubleObject.h>
#include <Core/Runtime/BuildInTypes/FloatObject.h>
#include <Core/Runtime/BuildInTypes/IntegerObject.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include "stdio.hpp"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace stdio {


class FWRITEB : public ExtensionMethod
{
public:
	FWRITEB()
	: ExtensionMethod(0, "fwriteb", Designtime::IntegerObject::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::IntegerObject::TYPENAME, 0));
		params.push_back(Parameter::CreateDesigntime("value", Designtime::BoolObject::TYPENAME, false));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList &params, Runtime::Object *result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_handle = (*it++).value().toInt();

			if ( stdio_t::FileHandles.find(param_handle) == stdio_t::FileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			bool param_value = (*it++).value().toBool();

			long size = fwrite(&param_value, sizeof(bool), 1, stdio_t::FileHandles[param_handle]);
			if ( size == -1 ) {    // error while writing
				throw Runtime::Exceptions::RuntimeException("error while writing file");
			}

			*result = Runtime::IntegerObject((int)size);
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


class FWRITED : public ExtensionMethod
{
public:
	FWRITED()
	: ExtensionMethod(0, "fwrited", Designtime::IntegerObject::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::IntegerObject::TYPENAME, 0));
		params.push_back(Parameter::CreateDesigntime("value", Designtime::DoubleObject::TYPENAME, 0.0));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList &params, Runtime::Object *result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_handle = (*it++).value().toInt();

			if ( stdio_t::FileHandles.find(param_handle) == stdio_t::FileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			double param_value = (*it++).value().toDouble();

			long size = fwrite(&param_value, sizeof(double), 1, stdio_t::FileHandles[param_handle]);
			if ( size == -1 ) {    // error while writing
				throw Runtime::Exceptions::RuntimeException("error while writing file");
			}

			*result = Runtime::IntegerObject((int)size);
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


class FWRITEF : public ExtensionMethod
{
public:
	FWRITEF()
	: ExtensionMethod(0, "fwritef", Designtime::IntegerObject::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::IntegerObject::TYPENAME, 0));
		params.push_back(Parameter::CreateDesigntime("value", Designtime::FloatObject::TYPENAME, 0.f));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList &params, Runtime::Object *result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_handle = (*it++).value().toInt();

			if ( stdio_t::FileHandles.find(param_handle) == stdio_t::FileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			float param_value = (*it++).value().toFloat();

			long size = fwrite(&param_value, sizeof(float), 1, stdio_t::FileHandles[param_handle]);
			if ( size == -1 ) {    // error while writing
				throw Runtime::Exceptions::RuntimeException("error while writing file");
			}

			*result = Runtime::IntegerObject((int)size);
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


class FWRITEI : public ExtensionMethod
{
public:
	FWRITEI()
	: ExtensionMethod(0, "fwritei", Designtime::IntegerObject::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::IntegerObject::TYPENAME, 0));
		params.push_back(Parameter::CreateDesigntime("value", Designtime::IntegerObject::TYPENAME, 0));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList &params, Runtime::Object *result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_handle = (*it++).value().toInt();

			if ( stdio_t::FileHandles.find(param_handle) == stdio_t::FileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			int param_value = (*it++).value().toInt();

			long size = fwrite(&param_value, sizeof(int), 1, stdio_t::FileHandles[param_handle]);
			if ( size == -1 ) {    // error while writing
				throw Runtime::Exceptions::RuntimeException("error while writing file");
			}

			*result = Runtime::IntegerObject((int)size);
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


class FWRITES : public ExtensionMethod
{
public:
	FWRITES()
	: ExtensionMethod(0, "fwrites", Designtime::IntegerObject::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::IntegerObject::TYPENAME, 0));
		params.push_back(Parameter::CreateDesigntime("value", Designtime::StringObject::TYPENAME, VALUE_NONE));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList &params, Runtime::Object *result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_handle = (*it++).value().toInt();

			if ( stdio_t::FileHandles.find(param_handle) == stdio_t::FileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			std::string param_value = (*it++).value().toStdString();

			//long size = fwrite(&param_value, sizeof(char), strlen(param_value.c_str()), stdio_t::FileHandles[param_handle]);
			long size = fputs(param_value.c_str(), stdio_t::FileHandles[param_handle]);
			if ( size == -1 ) {    // error while writing
				throw Runtime::Exceptions::RuntimeException("error while writing file");
			}

			*result = Runtime::IntegerObject(static_cast<int>(size));
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
