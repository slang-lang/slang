
#ifndef ObjectiveScript_Extensions_MySQL_NextResult_h
#define ObjectiveScript_Extensions_MySQL_NextResult_h


// Library includes

// Project includes
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlNextResult : public Runtime::Method
{
public:
	MysqlNextResult();

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token);
};


}
}
}


#endif
