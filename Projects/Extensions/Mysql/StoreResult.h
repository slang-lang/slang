
#ifndef ObjectiveScript_Extensions_MySQL_StoreResult_h
#define ObjectiveScript_Extensions_MySQL_StoreResult_h


// Library include

// Project includes
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlStoreResult: public Runtime::Method
{
public:
	MysqlStoreResult();

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token);
};


}
}
}


#endif
