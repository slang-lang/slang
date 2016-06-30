
#ifndef ObjectiveScript_Core_Runtime_TypeCast_h
#define ObjectiveScript_Core_Runtime_TypeCast_h


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class Repository;

namespace Runtime {

// Forward declarations
class Object;

void typecast(Object *base, const std::string& targetType, Repository *repository);


}
}


#endif
