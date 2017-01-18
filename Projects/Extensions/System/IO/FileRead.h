
#ifndef ObjectiveScript_Extensions_System_IO_FileRead_h
#define ObjectiveScript_Extensions_System_IO_FileRead_h


// Library includes
#include <fcntl.h>
#ifdef __APPLE__
#	include <unistd.h>
#elif defined _WIN32
#	include <io.h>
#	pragma warning(disable:4996)
#else
#	include <unistd.h>
#endif

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
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include <Tools/Strings.h>

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
		Runtime::ControlFlow::E controlFlow = Runtime::ControlFlow::Normal;

		int fileHandle = params.front().value().toInt();

		try {
			bool value = false;

			long size = read(fileHandle, &value, sizeof(bool));
			if ( size == -1 ) {    // error while reading
				return Runtime::ControlFlow::Throw;
			}

			*result = Runtime::BoolObject(value);
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().stack()->exception() = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return controlFlow;
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
		Runtime::ControlFlow::E controlFlow = Runtime::ControlFlow::Normal;

		int fileHandle = params.front().value().toInt();

		try {
			double value = 0.0;

			long size = read(fileHandle, &value, sizeof(double));
			if ( size == -1 ) {    // error while reading
				return Runtime::ControlFlow::Throw;
			}

			*result = Runtime::DoubleObject(value);
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().stack()->exception() = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return controlFlow;
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
		Runtime::ControlFlow::E controlFlow = Runtime::ControlFlow::Normal;

		int fileHandle = params.front().value().toInt();

		try {
			float value = 0.f;

			long size = read(fileHandle, &value, sizeof(float));
			if ( size == -1 ) {    // error while reading
				return Runtime::ControlFlow::Throw;
			}

			*result = Runtime::FloatObject(value);
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().stack()->exception() = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return controlFlow;
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
		Runtime::ControlFlow::E controlFlow = Runtime::ControlFlow::Normal;

		int fileHandle = params.front().value().toInt();

		try {
			int value = 0;

			long size = read(fileHandle, &value, sizeof(int));
			if ( size == -1 ) {    // error while reading
				return Runtime::ControlFlow::Throw;
			}

			*result = Runtime::IntegerObject(value);
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().stack()->exception() = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return controlFlow;
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
		Runtime::ControlFlow::E controlFlow = Runtime::ControlFlow::Normal;

		int fileHandle = params.front().value().toInt();
		int fileCount = params.back().value().toInt();

		try {
			int count = fileCount;
			std::string value;

			while ( count > 0 ) {
				char charValue;

				long size = read(fileHandle, &charValue, 1);
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

		return controlFlow;
	}

};


}
}
}
}


#endif
