
// Header
#include "FileWrite.h"

// Library includes
#include <fcntl.h>
#ifdef __APPLE__
#	include <unistd.h>
#elif defined _WIN32
#	include <io.h>
#	pragma warning(disable:4996)
#else
#	include <string.h>
#	include <unistd.h>
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
#include <Core/Common/Exceptions.h>
#include <Tools/Strings.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace IO {


FileWriteBool::FileWriteBool()
: Runtime::Method(0, "fwriteb", Designtime::IntegerObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, 0));
	params.push_back(Parameter("value", Designtime::BoolObject::TYPENAME, false));

	setSignature(params);
}

Runtime::ControlFlow::E FileWriteBool::execute(const ParameterList& params, Runtime::Object* result, const Token& /*token*/)
{
	Runtime::ControlFlow::E controlFlow = Runtime::ControlFlow::Normal;

	ParameterList::const_iterator it = params.begin();

	int fileHandle = (*it++).value().toInt();
	bool value = (*it++).value().toBool();

	try {
		long size = write(fileHandle, &value, sizeof(bool));
		if ( size == -1 ) {    // error while reading
			return Runtime::ControlFlow::Throw;
		}

		*result = Runtime::IntegerObject((int)size);
	}
	catch ( ... ) {
		controlFlow =  Runtime::ControlFlow::Throw;
	}

	return controlFlow;
}


FileWriteDouble::FileWriteDouble()
: Runtime::Method(0, "fwrited", Designtime::IntegerObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, 0));
	params.push_back(Parameter("value", Designtime::DoubleObject::TYPENAME, 0.0));

	setSignature(params);
}

Runtime::ControlFlow::E FileWriteDouble::execute(const ParameterList& params, Runtime::Object* result, const Token& /*token*/)
{
	Runtime::ControlFlow::E controlFlow = Runtime::ControlFlow::Normal;

	int fileHandle = params.front().value().toInt();
	double value = params.back().value().toDouble();

	try {
		long size = write(fileHandle, &value, sizeof(double));
		if ( size == -1 ) {    // error while reading
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
: Runtime::Method(0, "fwritef", Designtime::IntegerObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, 0));
	params.push_back(Parameter("value", Designtime::FloatObject::TYPENAME, 0.f));

	setSignature(params);
}

Runtime::ControlFlow::E FileWriteFloat::execute(const ParameterList& params, Runtime::Object* result, const Token& /*token*/)
{
	Runtime::ControlFlow::E controlFlow = Runtime::ControlFlow::Normal;

	int fileHandle = params.front().value().toInt();
	float value = params.back().value().toFloat();

	try {
		long size = write(fileHandle, &value, sizeof(float));
		if ( size == -1 ) {    // error while reading
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
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, 0));
	params.push_back(Parameter("value", Designtime::IntegerObject::TYPENAME, 0));

	setSignature(params);
}

Runtime::ControlFlow::E FileWriteInt::execute(const ParameterList& params, Runtime::Object* result, const Token& /*token*/)
{
	Runtime::ControlFlow::E controlFlow = Runtime::ControlFlow::Normal;

	int fileHandle = params.front().value().toInt();
	int value = params.back().value().toInt();

	try {
		long size = write(fileHandle, &value, sizeof(int));
		if ( size == -1 ) {    // error while reading
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
: Runtime::Method(0, "fwrites", Designtime::IntegerObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, 0));
	params.push_back(Parameter("value", Designtime::StringObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E FileWriteString::execute(const ParameterList& params, Runtime::Object* result, const Token& /*token*/)
{
	Runtime::ControlFlow::E controlFlow = Runtime::ControlFlow::Normal;

	int fileHandle = params.front().value().toInt();
	std::string value = params.back().value().toStdString();

	try {
		long size = write(fileHandle, (void*)value.c_str(), strlen(value.c_str()));
		if ( size == -1 ) {    // error while reading
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
