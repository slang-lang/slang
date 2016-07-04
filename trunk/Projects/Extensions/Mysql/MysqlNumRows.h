
#ifndef ObjectiveScript_Extensions_Mysql_MysqlNumRows_h
#define ObjectiveScript_Extensions_Mysql_MysqlNumRows_h


// Library includes

// Project includes
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlNumRows : public Runtime::Method
{
public:
	MysqlNumRows();

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token);
};


}
}
}


#endif
