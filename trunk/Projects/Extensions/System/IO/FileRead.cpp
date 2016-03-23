
// Header
#include "FileRead.h"

// Library includes
#include <fcntl.h>
#ifdef __APPLE__
#	include <unistd.h>
#elif defined _WIN32
#	include <io.h>
#	pragma warning(disable:4996)
#endif

// Project includes
#include <Core/Designtime/BuildInTypes/BoolObject.h>
#include <Core/Designtime/BuildInTypes/DoubleObject.h>
#include <Core/Designtime/BuildInTypes/FloatObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/BuildInObjects/BoolObject.h>
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


FileReadBool::FileReadBool()
: Runtime::Method(0, "freadb", Designtime::BoolObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E FileReadBool::execute(const ParameterList& params, Runtime::Object* result)
{
	if ( params.size() != 1 ) {
		throw Utils::Exceptions::ParameterCountMissmatch("1 parameter expected, but " + ::Utils::Tools::toString(params.size()) + " parameter(s) found");
	}

	Runtime::ControlFlow::E controlFlow = Runtime::ControlFlow::Normal;

	std::string fileHandle = params.front().pointer()->getValue();

	try {
		int handle = Tools::stringToInt(fileHandle);
		bool value = false;

		long size = read(handle, &value, sizeof(bool));
		if ( size == -1 ) {    // error while reading
			throw;
		}

		*result = Runtime::BoolObject(value);
	}
	catch ( ... ) {
		controlFlow =  Runtime::ControlFlow::Throw;
	}

	return controlFlow;
}


FileReadDouble::FileReadDouble()
: Runtime::Method(0, "freadd", Designtime::DoubleObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E FileReadDouble::execute(const ParameterList& params, Runtime::Object* result)
{
	if ( params.size() != 1 ) {
		throw Utils::Exceptions::ParameterCountMissmatch("1 parameter expected, but " + ::Utils::Tools::toString(params.size()) + " parameter(s) found");
	}

	Runtime::ControlFlow::E controlFlow = Runtime::ControlFlow::Normal;

	std::string fileHandle = params.front().pointer()->getValue();

	try {
		int handle = Tools::stringToInt(fileHandle);
		double value = 0.0;

		long size = read(handle, &value, sizeof(double));
		if ( size == -1 ) {    // error while reading
			throw;
		}

		*result = Runtime::DoubleObject(value);
	}
	catch ( ... ) {
		controlFlow =  Runtime::ControlFlow::Throw;
	}

	return controlFlow;
}

FileReadFloat::FileReadFloat()
: Runtime::Method(0, "freadf", Designtime::FloatObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E FileReadFloat::execute(const ParameterList& params, Runtime::Object* result)
{
	if ( params.size() != 1 ) {
		throw Utils::Exceptions::ParameterCountMissmatch("1 parameter expected, but " + ::Utils::Tools::toString(params.size()) + " parameter(s) found");
	}

	Runtime::ControlFlow::E controlFlow = Runtime::ControlFlow::Normal;

	std::string fileHandle = params.front().pointer()->getValue();

	try {
		int handle = Tools::stringToInt(fileHandle);
		float value = 0.f;

		long size = read(handle, &value, sizeof(float));
		if ( size == -1 ) {	// error while reading
			throw;
		}

		*result = Runtime::FloatObject(value);
	}
	catch ( ... ) {
		controlFlow =  Runtime::ControlFlow::Throw;
	}

	return controlFlow;
}

FileReadInt::FileReadInt()
: Runtime::Method(0, "freadi", Designtime::IntegerObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E FileReadInt::execute(const ParameterList& params, Runtime::Object* result)
{
	if ( params.size() != 1 ) {
		throw Utils::Exceptions::ParameterCountMissmatch("1 parameter expected, but " + ::Utils::Tools::toString(params.size()) + " parameter(s) found");
	}

	Runtime::ControlFlow::E controlFlow = Runtime::ControlFlow::Normal;

	std::string fileHandle = params.front().pointer()->getValue();

	try {
		int handle = Tools::stringToInt(fileHandle);
		int value = 0;

		long size = read(handle, &value, sizeof(int));
		if ( size == -1 ) {	// error while reading
			throw;
		}

		*result = Runtime::IntegerObject(value);
	}
	catch ( ... ) {
		controlFlow = Runtime::ControlFlow::Throw;
	}

	return controlFlow;
}

FileReadString::FileReadString()
: Runtime::Method(0, "freads", Designtime::StringObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, VALUE_NONE));
	params.push_back(Parameter("count", Designtime::IntegerObject::TYPENAME, "1", true));

	setSignature(params);
}

Runtime::ControlFlow::E FileReadString::execute(const ParameterList& params, Runtime::Object* result)
{
	if ( params.size() != 2 ) {
		throw Utils::Exceptions::ParameterCountMissmatch("2 parameters expected, but " + ::Utils::Tools::toString(params.size()) + " parameter(s) found");
	}

	Runtime::ControlFlow::E controlFlow = Runtime::ControlFlow::Normal;

	std::string fileHandle = params.front().pointer()->getValue();
	std::string fileCount = params.back().pointer()->getValue();

	try {
		int handle = Tools::stringToInt(fileHandle);
		int count = Tools::stringToInt(fileCount);
		std::string value;

		while ( count > 0 ) {
			char charValue;

			long size = read(handle, &charValue, 1);
			if ( size == -1 ) {	// error while reading
				throw;
			}
			if ( size == 0 ) {	// EOF reached
				break;
			}

			value += charValue;
			count--;
		}

		*result = Runtime::StringObject(value);
	}
	catch ( ... ) {
		controlFlow =  Runtime::ControlFlow::Throw;
	}

	return controlFlow;
}


}
}
}
