
#ifndef ObjectiveScript_Extensions_Mysql_MysqlClose_h
#define ObjectiveScript_Extensions_Mysql_MysqlClose_h


// Library include

// Project includes
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlClose: public Runtime::Method
{
public:
	MysqlClose();

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token);
};


}
}
}


#endif
