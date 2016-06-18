
#ifndef ObjectiveScript_Extensions_MySQL_Query_h
#define ObjectiveScript_Extensions_MySQL_Query_h


// Library include

// Project includes
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlQuery: public Runtime::Method
{
public:
	MysqlQuery();

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token);
};


}
}
}


#endif
