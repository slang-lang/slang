
#ifndef ObjectiveScript_Extensions_MySQL_Init_h
#define ObjectiveScript_Extensions_MySQL_Init_h


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

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token);
};


}
}
}


#endif
