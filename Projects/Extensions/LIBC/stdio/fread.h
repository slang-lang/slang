
#ifndef Slang_Extensions_LIBC_stdio_fread_h
#define Slang_Extensions_LIBC_stdio_fread_h


// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/BoolObject.h>
#include <Core/Designtime/BuildInTypes/DoubleObject.h>
#include <Core/Designtime/BuildInTypes/FloatObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Common/Exceptions.h>
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
namespace ExtensionLIBC {
namespace stdio {


class FREADB : public ExtensionMethod
{
public:
	FREADB()
	: ExtensionMethod(0, "freadb", Designtime::BoolObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::IntegerObject::TYPENAME));

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

			bool value = false;

			long size = fread(&value, 1, sizeof(bool), stdio_t::FileHandles[param_handle]);
			if ( size == -1 ) {    // error while reading
				throw Runtime::Exceptions::RuntimeException("error while reading file");
			}

			*result = Runtime::BoolObject(value);
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


class FREADD : public ExtensionMethod
{
public:
	FREADD()
	: ExtensionMethod(0, "freadd", Designtime::DoubleObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::IntegerObject::TYPENAME));

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

			double value = 0.0;

			long size = fread(&value, 1, sizeof(double), stdio_t::FileHandles[param_handle]);
			if ( size == -1 ) {    // error while reading
				throw Runtime::Exceptions::RuntimeException("error while reading file");
			}

			*result = Runtime::DoubleObject(value);
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


class FREADF : public ExtensionMethod
{
public:
	FREADF()
	: ExtensionMethod(0, "freadf", Designtime::FloatObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::IntegerObject::TYPENAME));

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

			float value = 0.f;

			long size = fread(&value, 1, sizeof(float), stdio_t::FileHandles[param_handle]);
			if ( size == -1 ) {    // error while reading
				throw Runtime::Exceptions::RuntimeException("error while reading file");
			}

			*result = Runtime::FloatObject(value);
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


class FREADI : public ExtensionMethod
{
public:
	FREADI()
	: ExtensionMethod(0, "freadi", Designtime::IntegerObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::IntegerObject::TYPENAME));

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

			int value = 0;

			long size = fread(&value, 1, sizeof(int), stdio_t::FileHandles[param_handle]);
			if ( size == -1 ) {    // error while reading
				throw Runtime::Exceptions::RuntimeException("error while reading file");
			}

			*result = Runtime::IntegerObject(value);
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


class FREADS : public ExtensionMethod
{
public:
	FREADS()
	: ExtensionMethod(0, "freads", Designtime::StringObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::IntegerObject::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("length", Designtime::IntegerObject::TYPENAME, 1, true));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList &params, Runtime::Object *result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_handle = (*it++).value().toInt();
			auto param_length = (*it++).value().toInt();

			if ( stdio_t::FileHandles.find(param_handle) == stdio_t::FileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			std::string value;

			while ( param_length > 0 || param_length == -1 ) {
				char charValue;

				long size = fread(&charValue, 1, sizeof(char), stdio_t::FileHandles[param_handle]);
				if ( size == -1 ) {    // error while reading
					return Runtime::ControlFlow::Throw;
				}
				if ( size == 0 ) {	// EOF reached
					break;
				}

				value += charValue;

				if ( param_length > 0 ) {
					param_length--;
				}
			}

			*result = Runtime::StringObject(value);
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