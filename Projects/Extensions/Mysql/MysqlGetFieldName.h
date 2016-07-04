
#ifndef ObjectiveScript_Extensions_Mysql_MysqlGetFieldName_h
#define ObjectiveScript_Extensions_Mysql_MysqlGetFieldName_h


// Library includes

// Project includes
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlGetFieldName : public Runtime::Method
{
public:
	MysqlGetFieldName();

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token);
};


}
}
}


#endif
