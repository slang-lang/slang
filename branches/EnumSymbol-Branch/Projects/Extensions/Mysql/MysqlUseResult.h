
#ifndef ObjectiveScript_Extensions_Mysql_MysqlUseResult_h
#define ObjectiveScript_Extensions_Mysql_MysqlUseResult_h


// Library include

// Project includes
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlUseResult: public Runtime::Method
{
public:
	MysqlUseResult();

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token);
};


}
}
}


#endif
