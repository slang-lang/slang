
// Header
#include "Close.h"

// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/BoolObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Tools.h>
#include <Core/Utils/Exceptions.h>
#include <Tools/Strings.h>
#include "Types.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


MysqlClose::MysqlClose()
: Runtime::Method(0, "mysql_close", Designtime::IntegerObject::TYPENAME)
{
	ParameterList params;

	setSignature(params);
}

Runtime::ControlFlow::E MysqlClose::execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token)
{
(void)params;
(void)result;
(void)token;

	if ( !MySQLConnection ) {
		// close without open connection?!
		return Runtime::ControlFlow::Normal;
	}

	mysql_close(MySQLConnection);

	return Runtime::ControlFlow::Normal;
}

}
}
}
