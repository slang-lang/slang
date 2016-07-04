
#ifndef ObjectiveScript_Extensions_MySQL_MysqlInit_h
#define ObjectiveScript_Extensions_MySQL_MysqlInit_h


// Library include

// Project includes
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlInit: public Runtime::Method
{
public:
	MysqlInit();

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token);
};


}
}
}


#endif
