
#ifndef ObjectiveScript_Extensions_Mysql_MysqlPing_h
#define ObjectiveScript_Extensions_Mysql_MysqlPing_h


// Library include

// Project includes
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlPing: public Runtime::Method
{
public:
	MysqlPing();

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token);
};


}
}
}


#endif
