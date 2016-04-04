
// Header
#include "Close.h"

// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/Tools.h>
#include <Core/Utils/Exceptions.h>
#include <Tools/Strings.h>
#include "Types.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


MysqlClose::MysqlClose()
: Runtime::Method(0, "mysql_close", Designtime::VoidObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E MysqlClose::execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token)
{
(void)result;
(void)token;

	try {
		int handle = Tools::stringToInt(params.begin()->value());
		MYSQL *myConn = mMysqlConnections[handle];

		mysql_close(myConn);

		return Runtime::ControlFlow::Normal;
	}
	catch ( std::exception &e ) {
		return Runtime::ControlFlow::Throw;
	}

	return Runtime::ControlFlow::Normal;
}

}
}
}
