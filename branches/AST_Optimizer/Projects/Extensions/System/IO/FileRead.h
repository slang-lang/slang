
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

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			std::string param_handle = (*it++).value().toStdString();

			int handle = Utils::Tools::stringToInt(param_handle);

			if ( mFileHandles.find(handle) == mFileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			bool value = false;

			long size = fread(&value, 1, sizeof(bool), mFileHandles[handle]);
			if ( size == -1 ) {    // error while reading
				throw Runtime::Exceptions::RuntimeException("error while reading file");
			}

			*result = Runtime::BoolObject(value);
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().stack()->exception() = Runtime::ExceptionData(data, token.position());
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

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			std::string param_handle = (*it++).value().toStdString();

			int handle = Utils::Tools::stringToInt(param_handle);

			if ( mFileHandles.find(handle) == mFileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			double value = 0.0;

			long size = fread(&value, 1, sizeof(double), mFileHandles[handle]);
			if ( size == -1 ) {    // error while reading
				throw Runtime::Exceptions::RuntimeException("error while reading file");
			}

			*result = Runtime::DoubleObject(value);
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().stack()->exception() = Runtime::ExceptionData(data, token.position());
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

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			std::string param_handle = (*it++).value().toStdString();

			int handle = Utils::Tools::stringToInt(param_handle);

			if ( mFileHandles.find(handle) == mFileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			float value = 0.f;

			long size = fread(&value, 1, sizeof(float), mFileHandles[handle]);
			if ( size == -1 ) {    // error while reading
				throw Runtime::Exceptions::RuntimeException("error while reading file");
			}

			*result = Runtime::FloatObject(value);
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().stack()->exception() = Runtime::ExceptionData(data, token.position());
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

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			std::string param_handle = (*it++).value().toStdString();

			int handle = Utils::Tools::stringToInt(param_handle);

			if ( mFileHandles.find(handle) == mFileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			int value = 0;

			long size = fread(&value, 1, sizeof(int), mFileHandles[handle]);
			if ( size == -1 ) {    // error while reading
				throw Runtime::Exceptions::RuntimeException("error while reading file");
			}

			*result = Runtime::IntegerObject(value);
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().stack()->exception() = Runtime::ExceptionData(data, token.position());
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
		params.push_back(Parameter::CreateDesigntime("count", Designtime::IntegerObject::TYPENAME, 1, true));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			std::string param_handle = (*it++).value().toStdString();

			int handle = Utils::Tools::stringToInt(param_handle);
			int fileCount = params.back().value().toInt();

			if ( mFileHandles.find(handle) == mFileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			int count = fileCount;
			std::string value;

			while ( count > 0 ) {
				char charValue;

				long size = fread(&charValue, 1, sizeof(char), mFileHandles[handle]);
				if ( size == -1 ) {    // error while reading
					return Runtime::ControlFlow::Throw;
				}
				if ( size == 0 ) {	// EOF reached
					break;
				}

				value += charValue;
				count--;
			}

			*result = Runtime::StringObject(value);
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().stack()->exception() = Runtime::ExceptionData(data, token.position());
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