
#ifndef ObjectiveScript_Extensions_Mysql_MysqlRealConnect_h
#define ObjectiveScript_Extensions_Mysql_MysqlRealConnect_h


// Library include

// Project includes
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlRealConnect: public Runtime::Method
{
public:
	MysqlRealConnect();

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token);
};


}
}
}


#endif
