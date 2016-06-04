
// Header
#include "ExceptionData.h"

// Library includes

// Project includes
#include <Core/Object.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


ExceptionData::ExceptionData()
: mData(0)
{
}

ExceptionData::ExceptionData(Object *data, const Utils::Position& position)
: mData(data),
  mPosition(position)
{
}

Object* ExceptionData::getData() const
{
	return mData;
}

const Utils::Position& ExceptionData::getPosition() const
{
	return mPosition;
}


}
}
