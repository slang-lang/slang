
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
#include <Core/Tools.h>
#include <Core/VirtualMachine/Repository.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace IO {


FileSeek::FileSeek()
: ExtensionMethod(0, "fseek", Designtime::IntegerObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, VALUE_NONE));
	params.push_back(Parameter("offset", Designtime::IntegerObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E FileSeek::execute(const ParameterList& params, Runtime::Object* result, const Token& token)
{
	ParameterList list = mergeParameters(params);

	try {
		ParameterList::const_iterator it = list.begin();

		int param_handle = (*it++).value().toInt();
		int param_offset = (*it++).value().toInt();

		long size = lseek(param_handle, param_offset, SEEK_SET);
		if ( size == -1 ) {    // error while reading
			return Runtime::ControlFlow::Throw;
		}

		*result = Runtime::IntegerObject((int)size);
	}
	catch ( std::exception& e ) {
		Runtime::Object *data = Repository::GetInstance().createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
		*data = Runtime::StringObject(std::string(e.what()));

		mExceptionData = Runtime::ExceptionData(data, token.position());
		return Runtime::ControlFlow::Throw;
	}

	return Runtime::ControlFlow::Normal;
}


}
}
}
