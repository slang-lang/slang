
#ifndef ObjectiveScript_Runtime_ExceptionData_h
#define ObjectiveScript_Runtime_ExceptionData_h


// Library includes

// Project includes
#include <Core/Utils/Position.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {

// Forward declarations
class Object;

class ExceptionData
{
public:
	ExceptionData();
	ExceptionData(Object *data, const Utils::Position& position);

public:
	Object* getData() const;
	const Utils::Position& getPosition() const;

private:
	Object *mData;
	Utils::Position mPosition;
};


}
}


#endif
