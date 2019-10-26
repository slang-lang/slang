
#ifndef ObjectiveScript_Extensions_System_IO_FileRead_h
#define ObjectiveScript_Extensions_System_IO_FileRead_h


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
#include "Defines.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {
namespace IO {


class FileReadBool : public ExtensionMethod
{
public:
	FileReadBool()
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

			int param_handle = (*it++).value().toInt();

			if ( mFileHandles.find(param_handle) == mFileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			bool value = false;

			long size = fread(&value, 1, sizeof(bool), mFileHandles[param_handle]);
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


class FileReadDouble : public ExtensionMethod
{
public:
	FileReadDouble()
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

			int param_handle = (*it++).value().toInt();

			if ( mFileHandles.find(param_handle) == mFileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			double value = 0.0;

			long size = fread(&value, 1, sizeof(double), mFileHandles[param_handle]);
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


class FileReadFloat : public ExtensionMethod
{
public:
	FileReadFloat()
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

			int param_handle = (*it++).value().toInt();

			if ( mFileHandles.find(param_handle) == mFileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			float value = 0.f;

			long size = fread(&value, 1, sizeof(float), mFileHandles[param_handle]);
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


class FileReadInt : public ExtensionMethod
{
public:
	FileReadInt()
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

			int param_handle = (*it++).value().toInt();

			if ( mFileHandles.find(param_handle) == mFileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			int value = 0;

			long size = fread(&value, 1, sizeof(int), mFileHandles[param_handle]);
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


class FileReadString : public ExtensionMethod
{
public:
	FileReadString()
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

			int param_handle = (*it++).value().toInt();
			int param_length = (*it++).value().toInt();

			if ( mFileHandles.find(param_handle) == mFileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			std::string value;

			while ( param_length > 0 || param_length == -1 ) {
				char charValue;

				long size = fread(&charValue, 1, sizeof(char), mFileHandles[param_handle]);
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
