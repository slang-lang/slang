
// Header
#include "FileClose.h"

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

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace IO {


FileClose::FileClose()
: Runtime::Method(0, "fclose", Designtime::IntegerObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E FileClose::execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token)
{
	try {
		ParameterList::const_iterator it = params.begin();

		std::string param_handle = (*it++).pointer()->getValue();

		int handle = Tools::stringToInt(param_handle);

		int fileResult = close(handle);
		if ( fileResult == -1 ) {
			return Runtime::ControlFlow::Throw;
		}

		*result = Runtime::IntegerObject(fileResult);
	}
	catch ( std::exception& e ) {
		Runtime::Object *data = mRepository->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
		*data = Runtime::StringObject(e.what());

		mExceptionData = Runtime::ExceptionData(data, token->position());
		return Runtime::ControlFlow::Throw;
	}

	return Runtime::ControlFlow::Normal;
}


}
}
}
