
#ifndef ObjectiveScript_Extensions_Mysql_MysqlRealEscapeString_h
#define ObjectiveScript_Extensions_Mysql_MysqlRealEscapeString_h


// Library includes

// Project includes
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlRealEscapeString : public Runtime::Method
{
public:
	MysqlRealEscapeString();

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token);
};


}
}
}


#endif
