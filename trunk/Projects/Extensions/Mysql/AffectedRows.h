
#ifndef ObjectiveScript_Extensions_MySQL_AffectedRows_h
#define ObjectiveScript_Extensions_MySQL_AffectedRows_h


// Library includes

// Project includes
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlAffectedRows : public Runtime::Method
{
public:
	MysqlAffectedRows();

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token);
};


}
}
}


#endif
