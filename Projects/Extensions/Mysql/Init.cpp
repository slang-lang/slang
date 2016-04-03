
// Header
#include "Init.h"

// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Tools.h>
#include <Core/Utils/Exceptions.h>
#include <Tools/Strings.h>
#include "Types.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


MysqlInit::MysqlInit()
: Runtime::Method(0, "mysql_init", Designtime::VoidObject::TYPENAME)
{
	ParameterList params;

	setSignature(params);
}

Runtime::ControlFlow::E MysqlInit::execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token)
{
(void)params;
(void)result;
(void)token;

	MySQLConnection = mysql_init(MySQLConnection);

	return Runtime::ControlFlow::Normal;
}

}
}
}
