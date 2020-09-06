
#ifndef Slang_Extensions_System_Network_Write_h
#define Slang_Extensions_System_Network_Write_h


// Library includes

// Project includes
#include "Defines.h"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Network {


class WriteBool : public ExtensionMethod
{
public:
	WriteBool()
	: ExtensionMethod(0, "writeb", Designtime::IntegerObject::TYPENAME, Mutability::Modify)
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

			int param_handle = (*it++).value().toInt();

			bool value = (*it++).value().toBool();

			long size = write(param_handle, &value, sizeof(bool));
			if ( size == -1 ) {    // error while writing
				throw Runtime::Exceptions::RuntimeException("error while writing handle");
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


class WriteDouble : public ExtensionMethod
{
public:
	WriteDouble()
	: ExtensionMethod(0, "writed", Designtime::IntegerObject::TYPENAME, Mutability::Modify)
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

			int param_handle = (*it++).value().toInt();

			double value = (*it++).value().toDouble();

			long size = write(param_handle, &value, sizeof(double));
			if ( size == -1 ) {    // error while writing
				throw Runtime::Exceptions::RuntimeException("error while writing handle");
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


class WriteFloat : public ExtensionMethod
{
public:
	WriteFloat()
	: ExtensionMethod(0, "writef", Designtime::IntegerObject::TYPENAME, Mutability::Modify)
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

			int param_handle = (*it++).value().toInt();

			float value = (*it++).value().toFloat();

			long size = write(param_handle, &value, sizeof(float));
			if ( size == -1 ) {    // error while writing
				throw Runtime::Exceptions::RuntimeException("error while writing handle");
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


class WriteInt : public ExtensionMethod
{
public:
	WriteInt()
	: ExtensionMethod(0, "writei", Designtime::IntegerObject::TYPENAME, Mutability::Modify)
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

			int param_handle = (*it++).value().toInt();

			int value = (*it++).value().toInt();

			long size = write(param_handle, &value, sizeof(int));
			if ( size == -1 ) {    // error while writing
				throw Runtime::Exceptions::RuntimeException("error while writing handle");
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


class WriteString : public ExtensionMethod
{
public:
	WriteString()
	: ExtensionMethod(0, "writes", Designtime::IntegerObject::TYPENAME, Mutability::Modify)
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

			int param_handle = (*it++).value().toInt();

			std::string value = params.back().value().toStdString();
			unsigned long count = 0;
			long size = 0;

			while ( count < value.size() ) {
				size = write(param_handle, &value[count], sizeof(char));
				if ( size == -1 ) {    // error while writing
					throw Runtime::Exceptions::RuntimeException("error while writing handle");
				}

				count++;
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
