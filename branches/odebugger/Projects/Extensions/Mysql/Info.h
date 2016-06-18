
#ifndef ObjectiveScript_Extensions_MySQL_Info_h
#define ObjectiveScript_Extensions_MySQL_Info_h


// Library includes

// Project includes
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlInfo : public Runtime::Method
{
public:
	MysqlInfo();

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token);
};


}
}
}


#endif
