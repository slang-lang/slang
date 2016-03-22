
// Header
#include "FileOpen.h"

// Library includes
#include <fcntl.h>

// Project includes
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/Tools.h>
#include <Core/Utils/Exceptions.h>
#include <Tools/Strings.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace IO {


FileOpen::FileOpen()
: Runtime::Method(0, "fopen", Designtime::IntegerObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("filename", Designtime::StringObject::TYPENAME, VALUE_NONE));
	params.push_back(Parameter("handle", Designtime::StringObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E FileOpen::execute(const ParameterList& params, Runtime::Object* result)
{
	if ( params.size() != 2 ) {
		throw Utils::Exceptions::ParameterCountMissmatch("2 parameter expected, but " + ::Utils::Tools::toString(params.size()) + " parameter(s) found");
	}

	Runtime::ControlFlow::E controlFlow = Runtime::ControlFlow::Normal;

	std::string filename = params.front().pointer()->getValue();
	std::string accessmode = params.back().pointer()->getValue();

	int handle = 0;
	int mode = parseAccessMode(accessmode);

	try {
		handle = open(filename.c_str(), mode);

		*result = Runtime::IntegerObject(handle);
	}
	catch ( ... ) {
		controlFlow =  Runtime::ControlFlow::Throw;
	}

	return controlFlow;
}

int FileOpen::parseAccessMode(std::string accessmode) const
{
	int mode = 0;

	while ( accessmode.size() > 0 ) {
		switch ( accessmode[0] ) {
			case 'a': mode |= O_APPEND; break;
			case 'r': mode |= O_RDONLY; break;
			case 'w': mode |= O_WRONLY; break;
		}

		accessmode = accessmode.substr(1, accessmode.size());
	}

	return mode;
}


}
}
}
