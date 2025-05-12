
// Header
#include "ExceptionData.h"

// Library includes

// Project includes
#include <Core/Object.h>

// Namespace declarations


namespace Slang {
namespace Runtime {


ExceptionData::ExceptionData()
: mData(0)
{
}

ExceptionData::ExceptionData(Object* data, Common::Position position, std::string stackTrace)
: mData(data),
  mPosition(std::move(position)),
  mStackTrace(std::move(stackTrace))
{
}

Object* ExceptionData::getData() const
{
	return mData;
}

const Common::Position& ExceptionData::getPosition() const
{
	return mPosition;
}

const std::string& ExceptionData::getStackTrace() const
{
	return mStackTrace;
}


}
}
