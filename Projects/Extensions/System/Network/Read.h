
#ifndef Slang_Extensions_System_Network_Read_h
#define Slang_Extensions_System_Network_Read_h


// Library includes

// Project includes
#include "Defines.h"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Network {


class ReadBool : public ExtensionMethod
{
public:
	ReadBool()
	: ExtensionMethod(0, "readb", Designtime::BoolType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList &params, Runtime::Object *result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		int param_handle = (*it++).value().toInt();

		bool value = false;

		long size = read(param_handle, &value, sizeof(bool));
		if ( size == -1 ) {    // error while reading
			throw Runtime::Exceptions::RuntimeException("error while reading handle");
		}

		*result = Runtime::BoolType(value);

		return Runtime::ControlFlow::Normal;
	}
};


class ReadDouble : public ExtensionMethod
{
public:
	ReadDouble()
	: ExtensionMethod(0, "readd", Designtime::DoubleType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList &params, Runtime::Object *result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		int param_handle = (*it++).value().toInt();

		double value = 0.0;

		long size = read(param_handle, &value, sizeof(double));
		if ( size == -1 ) {    // error while reading
			throw Runtime::Exceptions::RuntimeException("error while reading handle");
		}

		*result = Runtime::DoubleType(value);

		return Runtime::ControlFlow::Normal;
	}
};


class ReadFloat : public ExtensionMethod
{
public:
	ReadFloat()
	: ExtensionMethod(0, "readf", Designtime::FloatType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList &params, Runtime::Object *result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		int param_handle = (*it++).value().toInt();

		float value = 0.f;

		long size = read(param_handle, &value, sizeof(float));
		if ( size == -1 ) {    // error while reading
			throw Runtime::Exceptions::RuntimeException("error while reading handle");
		}

		*result = Runtime::FloatType(value);

		return Runtime::ControlFlow::Normal;
	}
};


class ReadInt : public ExtensionMethod
{
public:
	ReadInt()
	: ExtensionMethod(0, "readi", Designtime::Int32Type::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList &params, Runtime::Object *result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		int param_handle = (*it++).value().toInt();

		int value = 0;

		long size = read(param_handle, &value, sizeof(int));
		if ( size == -1 ) {    // error while reading
			throw Runtime::Exceptions::RuntimeException("error while reading handle");
		}

		*result = Runtime::Int32Type(value);

		return Runtime::ControlFlow::Normal;
	}
};


class ReadString : public ExtensionMethod
{
public:
	ReadString()
	: ExtensionMethod(0, "reads", Designtime::StringType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("length", Designtime::Int32Type::TYPENAME, 1, true));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList &params, Runtime::Object *result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		int param_handle = (*it++).value().toInt();
		int param_length = (*it++).value().toInt();

		std::string value;

		while ( param_length > 0 || param_length == -1 ) {
			char charValue;

			long size = read(param_handle, &charValue, sizeof(char));
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

		*result = Runtime::StringType(value);

		return Runtime::ControlFlow::Normal;
	}

};


}
}
}
}


#endif
