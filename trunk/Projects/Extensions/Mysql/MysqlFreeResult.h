
#ifndef ObjectiveScript_Extensions_Mysql_MysqlFreeResult_h
#define ObjectiveScript_Extensions_Mysql_MysqlFreeResult_h


// Library include

// Project includes
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlFreeResult: public Runtime::Method
{
public:
	MysqlFreeResult();

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token);
};


}
}
}


#endif
