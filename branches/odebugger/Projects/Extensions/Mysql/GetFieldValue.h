
#ifndef ObjectiveScript_Extensions_MySQL_GetFieldValue_h
#define ObjectiveScript_Extensions_MySQL_GetFieldValue_h


// Library includes

// Project includes
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlGetFieldValue : public Runtime::Method
{
public:
	MysqlGetFieldValue();

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token);
};


}
}
}


#endif
