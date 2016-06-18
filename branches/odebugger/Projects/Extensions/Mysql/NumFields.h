
#ifndef ObjectiveScript_Extensions_MySQL_NumFields_h
#define ObjectiveScript_Extensions_MySQL_NumFields_h


// Library includes

// Project includes
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlNumFields : public Runtime::Method
{
public:
	MysqlNumFields();

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token);
};


}
}
}


#endif
