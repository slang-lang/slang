
#ifndef Slang_Extensions_LIBC_stdio_fopen_h
#define Slang_Extensions_LIBC_stdio_fopen_h


// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include "stdio.hpp"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace stdio {


class FOPEN : public ExtensionMethod
{
public:
	FOPEN()
	: ExtensionMethod(0, "fopen", Designtime::Int32Type::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("filename", Designtime::StringType::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("accessmode", Designtime::StringType::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		std::string param_filename = (*it++).value().toStdString();
		std::string param_accessmode = (*it++).value().toStdString();

		int result_handle = 0;

		FILE* fileHandle = fopen(param_filename.c_str(), param_accessmode.c_str());
		if ( fileHandle ) {
			result_handle = stdio_t::FileHandles.size();

			stdio_t::FileHandles.insert(std::make_pair(result_handle, fileHandle));
		}

		*result = Runtime::Int32Type(result_handle);
		return Runtime::ControlFlow::Normal;
	}

private:
	int parseAccessMode(std::string accessmode) const
	{
		int mode = 0;

		while ( accessmode.size() > 0 ) {
			switch ( accessmode[0] ) {
				case 'a': mode |= O_APPEND; break;
				case 'c': mode |= O_CREAT; break;
				case 'r': mode |= O_RDONLY; break;
				case 't': mode |= O_TRUNC; break;
				case 'w': mode |= O_WRONLY; break;
				case 'x': mode |= O_EXCL; break;
				default: break;
			}

			accessmode = accessmode.substr(1, accessmode.size());
		}

		return mode;
	}
};


}
}
}
}


#endif
