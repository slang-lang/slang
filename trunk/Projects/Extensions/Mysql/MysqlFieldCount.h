
#ifndef ObjectiveScript_Extensions_MySQL_MysqlFieldCount_h
#define ObjectiveScript_Extensions_MySQL_MysqlFieldCount_h


// Library includes

// Project includes
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlFieldCount : public Runtime::Method
{
public:
	MysqlFieldCount();

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token);
};


}
}
}


#endif
