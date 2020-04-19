
#ifndef ObjectiveScript_Runtime_ExceptionData_h
#define ObjectiveScript_Runtime_ExceptionData_h


// Library includes

// Project includes
#include <Core/Common/Position.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Runtime {

// Forward declarations
class Object;

class ExceptionData
{
public:
	ExceptionData();
	ExceptionData(Object* data, const Common::Position& position = Common::Position(), const std::string& stackTrace = "");

public:
	Object* getData() const;
	const Common::Position& getPosition() const;
	const std::string& getStackTrace() const;

private:
	Object *mData;
	Common::Position mPosition;
	std::string mStackTrace;
};


}
}


#endif
