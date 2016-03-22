
// Header
#include "FileWrite.h"

// Library includes
#include <fcntl.h>
#include <unistd.h>

// Project includes
#include <Core/Designtime/BuildInTypes/DoubleObject.h>
#include <Core/Designtime/BuildInTypes/FloatObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/BuildInObjects/DoubleObject.h>
#include <Core/BuildInObjects/FloatObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Tools.h>
#include <Core/Utils/Exceptions.h>
#include <Tools/Strings.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace IO {


FileWriteDouble::FileWriteDouble()
: Runtime::Method(0, "fwrited", Designtime::DoubleObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, VALUE_NONE));
	params.push_back(Parameter("value", Designtime::DoubleObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E FileWriteDouble::execute(const ParameterList& params, Runtime::Object* result)
{
	if ( params.size() != 2 ) {
		throw Utils::Exceptions::ParameterCountMissmatch("2 parameters expected, but " + ::Utils::Tools::toString(params.size()) + " parameter(s) found");
	}

	Runtime::ControlFlow::E controlFlow = Runtime::ControlFlow::Normal;

	std::string fileHandle = params.front().pointer()->getValue();
	std::string value = params.back().pointer()->getValue();

	try {
		int handle = Tools::stringToInt(fileHandle);
		double doubleValue = Tools::stringToDouble(value);

		void* buffer = &doubleValue;

		ssize_t size = write(handle, buffer, sizeof(double));
		if ( size == -1 ) {
			return Runtime::ControlFlow::Throw;
		}

		*result = Runtime::IntegerObject((int)size);
	}
	catch ( ... ) {
		controlFlow =  Runtime::ControlFlow::Throw;
	}

	return controlFlow;
}

FileWriteFloat::FileWriteFloat()
: Runtime::Method(0, "fwritef", Designtime::FloatObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, VALUE_NONE));
	params.push_back(Parameter("value", Designtime::FloatObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E FileWriteFloat::execute(const ParameterList& params, Runtime::Object* result)
{
	if ( params.size() != 2 ) {
		throw Utils::Exceptions::ParameterCountMissmatch("2 parameters expected, but " + ::Utils::Tools::toString(params.size()) + " parameter(s) found");
	}

	Runtime::ControlFlow::E controlFlow = Runtime::ControlFlow::Normal;

	std::string fileHandle = params.front().pointer()->getValue();
	std::string value = params.back().pointer()->getValue();

	try {
		int handle = Tools::stringToInt(fileHandle);
		float floatValue = Tools::stringToDouble(value);

		void* buffer = &floatValue;

		ssize_t size = write(handle, buffer, sizeof(float));
		if ( size == -1 ) {
			return Runtime::ControlFlow::Throw;
		}

		*result = Runtime::IntegerObject((int)size);
	}
	catch ( ... ) {
		controlFlow =  Runtime::ControlFlow::Throw;
	}

	return controlFlow;
}

FileWriteInt::FileWriteInt()
: Runtime::Method(0, "fwritei", Designtime::IntegerObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, VALUE_NONE));
	params.push_back(Parameter("value", Designtime::IntegerObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E FileWriteInt::execute(const ParameterList& params, Runtime::Object* result)
{
	if ( params.size() != 2 ) {
		throw Utils::Exceptions::ParameterCountMissmatch("2 parameters expected, but " + ::Utils::Tools::toString(params.size()) + " parameter(s) found");
	}

	Runtime::ControlFlow::E controlFlow = Runtime::ControlFlow::Normal;

	std::string fileHandle = params.front().pointer()->getValue();
	std::string value = params.back().pointer()->getValue();

	try {
		int handle = Tools::stringToInt(fileHandle);
		int intValue = Tools::stringToDouble(value);

		void* buffer = &intValue;

		ssize_t size = write(handle, buffer, sizeof(int));
		if ( size == -1 ) {
			return Runtime::ControlFlow::Throw;
		}

		*result = Runtime::IntegerObject((int)size);
	}
	catch ( ... ) {
		controlFlow =  Runtime::ControlFlow::Throw;
	}

	return controlFlow;
}

FileWriteString::FileWriteString()
: Runtime::Method(0, "fwrites", Designtime::StringObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, VALUE_NONE));
	params.push_back(Parameter("value", Designtime::StringObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E FileWriteString::execute(const ParameterList& params, Runtime::Object* result)
{
	if ( params.size() != 2 ) {
		throw Utils::Exceptions::ParameterCountMissmatch("2 parameters expected, but " + ::Utils::Tools::toString(params.size()) + " parameter(s) found");
	}

	Runtime::ControlFlow::E controlFlow = Runtime::ControlFlow::Normal;

	std::string fileHandle = params.front().pointer()->getValue();
	std::string value = params.back().pointer()->getValue();

	try {
		int handle = Tools::stringToInt(fileHandle);

		void* buffer = 0;

		ssize_t size = write(handle, buffer, sizeof(value.c_str()));
		if ( size == -1 ) {
			return Runtime::ControlFlow::Throw;
		}

		*result = Runtime::IntegerObject((int)size);
	}
	catch ( ... ) {
		controlFlow =  Runtime::ControlFlow::Throw;
	}

	return controlFlow;
}


}
}
}
