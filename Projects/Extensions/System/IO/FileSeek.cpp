
// Header
#include "FileSeek.h"

// Library includes
#ifdef __APPLE__
#	include <unistd.h>
#elif defined _WIN32
#	include <io.h>
#endif

// Project includes
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
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
	//params.push_back(Parameter("whence", Designtime::IntegerObject::TYPENAME, "0", true));

	setSignature(params);
}

Runtime::ControlFlow::E FileSeek::execute(const ParameterList& params, Runtime::Object* result)
{
	if ( params.size() != 2 ) {
		throw Utils::Exceptions::ParameterCountMissmatch("2 parameters expected, but " + ::Utils::Tools::toString(params.size()) + " parameter(s) found");
	}

	Runtime::ControlFlow::E controlFlow = Runtime::ControlFlow::Normal;

	std::string fileHandle = params.front().pointer()->getValue();
	std::string fileOffset = params.back().pointer()->getValue();

	try {
		int handle = Tools::stringToInt(fileHandle);
		int offset = Tools::stringToInt(fileOffset);

		long size = lseek(handle, offset, SEEK_SET);

		*result = Runtime::IntegerObject(size);
	}
	catch ( ... ) {
		controlFlow =  Runtime::ControlFlow::Throw;
	}

	return controlFlow;
}


}
}
}
