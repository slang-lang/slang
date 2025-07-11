
#ifndef Slang_Extensions_LIBC_stdio_fwrite_h
#define Slang_Extensions_LIBC_stdio_fwrite_h


// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/BoolType.h>
#include <Core/Designtime/BuildInTypes/DoubleType.h>
#include <Core/Designtime/BuildInTypes/FloatType.h>
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/Exceptions.h>

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
	: ExtensionMethod(0, "fwriteb", Designtime::Int32Type::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME, 0));
		params.push_back(Parameter::CreateDesigntime("value", Designtime::BoolType::TYPENAME, false));

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

		bool param_value = (*it++).value().toBool();

		long size = fwrite(&param_value, sizeof(bool), 1, stdio_t::FileHandles[param_handle]);
		if ( size == -1 ) {    // error while writing
			throw Runtime::Exceptions::RuntimeException("error while writing file");
		}

		*result = Runtime::Int32Type((int)size);

		return Runtime::ControlFlow::Normal;
	}
};


class FWRITED : public ExtensionMethod
{
public:
	FWRITED()
	: ExtensionMethod(0, "fwrited", Designtime::Int32Type::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME, 0));
		params.push_back(Parameter::CreateDesigntime("value", Designtime::DoubleType::TYPENAME, 0.0));

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

		double param_value = (*it++).value().toDouble();

		long size = fwrite(&param_value, sizeof(double), 1, stdio_t::FileHandles[param_handle]);
		if ( size == -1 ) {    // error while writing
			throw Runtime::Exceptions::RuntimeException("error while writing file");
		}

		*result = Runtime::Int32Type((int)size);

		return Runtime::ControlFlow::Normal;
	}
};


class FWRITEF : public ExtensionMethod
{
public:
	FWRITEF()
	: ExtensionMethod(0, "fwritef", Designtime::Int32Type::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME, 0));
		params.push_back(Parameter::CreateDesigntime("value", Designtime::FloatType::TYPENAME, 0.f));

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

		float param_value = (*it++).value().toFloat();

		long size = fwrite(&param_value, sizeof(float), 1, stdio_t::FileHandles[param_handle]);
		if ( size == -1 ) {    // error while writing
			throw Runtime::Exceptions::RuntimeException("error while writing file");
		}

		*result = Runtime::Int32Type((int)size);

		return Runtime::ControlFlow::Normal;
	}
};


class FWRITEI : public ExtensionMethod
{
public:
	FWRITEI()
	: ExtensionMethod(0, "fwritei", Designtime::Int32Type::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME, 0));
		params.push_back(Parameter::CreateDesigntime("value", Designtime::Int32Type::TYPENAME, 0));

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

		int param_value = (*it++).value().toInt();

		long size = fwrite(&param_value, sizeof(int), 1, stdio_t::FileHandles[param_handle]);
		if ( size == -1 ) {    // error while writing
			throw Runtime::Exceptions::RuntimeException("error while writing file");
		}

		*result = Runtime::Int32Type((int)size);

		return Runtime::ControlFlow::Normal;
	}
};


class FWRITES : public ExtensionMethod
{
public:
	FWRITES()
	: ExtensionMethod(0, "fwrites", Designtime::Int32Type::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME, 0));
		params.push_back(Parameter::CreateDesigntime("value", Designtime::StringType::TYPENAME, VALUE_NONE));

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

		std::string param_value = (*it++).value().toStdString();

		//long size = fwrite(&param_value, sizeof(char), strlen(param_value.c_str()), stdio_t::FileHandles[param_handle]);
		long size = fputs(param_value.c_str(), stdio_t::FileHandles[param_handle]);
		if ( size == -1 ) {    // error while writing
			throw Runtime::Exceptions::RuntimeException("error while writing file");
		}

		*result = Runtime::Int32Type(static_cast<int>(size));

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
