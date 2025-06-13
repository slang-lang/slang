
#ifndef Slang_Extensions_LIBC_stdio_fread_h
#define Slang_Extensions_LIBC_stdio_fread_h


// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/BoolType.h>
#include <Core/Designtime/BuildInTypes/DoubleType.h>
#include <Core/Designtime/BuildInTypes/FloatType.h>
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Common/Exceptions.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/BoolType.h>
#include <Core/Runtime/BuildInTypes/DoubleType.h>
#include <Core/Runtime/BuildInTypes/FloatType.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Runtime/Utils.h>
#include <Core/VirtualMachine/Controller.h>
#include "stdio.hpp"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace stdio {


class FREADB : public ExtensionMethod
{
public:
	FREADB()
	: ExtensionMethod(0, "freadb", Designtime::BoolType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList &params, Runtime::Object *result )
	{
		ParameterList list = mergeParameters(params);

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

		*result = Runtime::BoolType(value);

		return Runtime::ControlFlow::Normal;
	}
};


class FREADD : public ExtensionMethod
{
public:
	FREADD()
	: ExtensionMethod(0, "freadd", Designtime::DoubleType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList &params, Runtime::Object *result )
	{
		ParameterList list = mergeParameters(params);

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

		*result = Runtime::DoubleType(value);

		return Runtime::ControlFlow::Normal;
	}
};


class FREADF : public ExtensionMethod
{
public:
	FREADF()
	: ExtensionMethod(0, "freadf", Designtime::FloatType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList &params, Runtime::Object *result )
	{
		ParameterList list = mergeParameters(params);

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

		*result = Runtime::FloatType(value);

		return Runtime::ControlFlow::Normal;
	}
};


class FREADI : public ExtensionMethod
{
public:
	FREADI()
	: ExtensionMethod(0, "freadi", Designtime::Int32Type::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList &params, Runtime::Object *result )
	{
		ParameterList list = mergeParameters(params);

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

		*result = Runtime::Int32Type(value);

		return Runtime::ControlFlow::Normal;
	}
};


class FREADS : public ExtensionMethod
{
public:
	FREADS()
	: ExtensionMethod(0, "freads", Designtime::StringType::TYPENAME)
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

		*result = Runtime::StringType(value);

		return Runtime::ControlFlow::Normal;
	}

};


}
}
}
}


#endif
