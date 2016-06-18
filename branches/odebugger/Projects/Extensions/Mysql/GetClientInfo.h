
#ifndef ObjectiveScript_Extensions_MySQL_GetClientInfo_h
#define ObjectiveScript_Extensions_MySQL_GetClientInfo_h


// Library includes

// Project includes
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlGetClientInfo : public Runtime::Method
{
public:
	MysqlGetClientInfo();

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token);
};


}
}
}


#endif
