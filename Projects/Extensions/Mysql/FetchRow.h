
#ifndef ObjectiveScript_Extensions_MySQL_FetchRow_h
#define ObjectiveScript_Extensions_MySQL_FetchRow_h


// Library includes

// Project includes
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlFetchRow : public Runtime::Method
{
public:
	MysqlFetchRow();

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token);
};


}
}
}


#endif
