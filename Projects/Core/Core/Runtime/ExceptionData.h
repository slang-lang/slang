
#ifndef ObjectiveScript_Runtime_ExceptionData_h
#define ObjectiveScript_Runtime_ExceptionData_h


// Library includes

// Project includes
#include <Core/Common/Position.h>

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
	ExceptionData(Object *data, const Common::Position& position);

public:
	Object* getData() const;
	const Common::Position& getPosition() const;

private:
	Object *mData;
	Common::Position mPosition;
};


}
}


#endif
