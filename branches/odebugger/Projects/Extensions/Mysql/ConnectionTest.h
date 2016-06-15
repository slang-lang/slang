
#ifndef OBJECTIVESCRIPT_CONNECTIONTEST_H
#define OBJECTIVESCRIPT_CONNECTIONTEST_H


// Library includes

// Project includes
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class ConnectionTest : public Runtime::Method
{
public:
	ConnectionTest();

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token);
};


}
}
}


#endif
