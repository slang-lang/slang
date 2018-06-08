
#ifndef ObjectiveScript_Extensions_System_IO_FileWrite_h
#define ObjectiveScript_Extensions_System_IO_FileWrite_h


// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/BoolObject.h>
#include <Core/Designtime/BuildInTypes/DoubleObject.h>
#include <Core/Designtime/BuildInTypes/FloatObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/DoubleObject.h>
#include <Core/BuildInObjects/FloatObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include <Tools/Strings.h>
#include "Defines.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {
namespace IO {


class FileWriteBool : public ExtensionMethod
{
public:
	FileWriteBool()
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

			std::string param_handle = (*it++).value().toStdString();

			int handle = Utils::Tools::stringToInt(param_handle);

			if ( mFileHandles.find(handle) == mFileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			bool value = (*it++).value().toBool();

			long size = fwrite(&value, sizeof(bool), 1, mFileHandles[handle]);
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


class FileWriteDouble : public ExtensionMethod
{
public:
	FileWriteDouble()
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

			std::string param_handle = (*it++).value().toStdString();

			int handle = Utils::Tools::stringToInt(param_handle);

			if ( mFileHandles.find(handle) == mFileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			double value = (*it++).value().toDouble();

			long size = fwrite(&value, sizeof(double), 1, mFileHandles[handle]);
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


class FileWriteFloat : public ExtensionMethod
{
public:
	FileWriteFloat()
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

			std::string param_handle = (*it++).value().toStdString();

			int handle = Utils::Tools::stringToInt(param_handle);

			if ( mFileHandles.find(handle) == mFileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			float value = (*it++).value().toFloat();

			long size = fwrite(&value, sizeof(float), 1, mFileHandles[handle]);
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


class FileWriteInt : public ExtensionMethod
{
public:
	FileWriteInt()
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

			std::string param_handle = (*it++).value().toStdString();

			int handle = Utils::Tools::stringToInt(param_handle);

			if ( mFileHandles.find(handle) == mFileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			int value = (*it++).value().toInt();

			long size = fwrite(&value, sizeof(int), 1, mFileHandles[handle]);
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


class FileWriteString : public ExtensionMethod
{
public:
	FileWriteString()
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

			std::string param_handle = (*it++).value().toStdString();

			int handle = Utils::Tools::stringToInt(param_handle);

			if ( mFileHandles.find(handle) == mFileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			std::string value = params.back().value().toStdString();

			long size = fwrite(&value, sizeof(char), strlen(value.c_str()), mFileHandles[handle]);
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


}
}
}
}


#endif
