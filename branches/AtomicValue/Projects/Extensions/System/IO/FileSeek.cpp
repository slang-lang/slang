
// Header
#include "FileSeek.h"

// Library includes
#ifdef __APPLE__
#	include <unistd.h>
#elif defined _WIN32
#	include <io.h>
#	pragma warning(disable:4996)
#else
#	include <unistd.h>
#endif

// Project includes
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Repository.h>
#include <Core/Tools.h>
#include <Core/Utils/Exceptions.h>
#include <Tools/Strings.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace IO {


FileSeek::FileSeek()
: Runtime::Method(0, "fseek", Designtime::IntegerObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, VALUE_NONE));
	params.push_back(Parameter("offset", Designtime::IntegerObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E FileSeek::execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token)
{
	try {
		ParameterList::const_iterator it = params.begin();

		std::string param_handle = params.front().value().toStdString();
		std::string param_offset = params.back().value().toStdString();

		int handle = Tools::stringToInt(param_handle);
		int offset = Tools::stringToInt(param_offset);

		long size = lseek(handle, offset, SEEK_SET);
		if ( size == -1 ) {    // error while reading
			return Runtime::ControlFlow::Throw;
		}

		*result = Runtime::IntegerObject((int)size);
	}
	catch ( std::exception& e ) {
		Runtime::Object *data = mRepository->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
		*data = Runtime::StringObject(std::string(e.what()));

		mExceptionData = Runtime::ExceptionData(data, token->position());
		return Runtime::ControlFlow::Throw;
	}

	return Runtime::ControlFlow::Normal;
}


}
}
}
