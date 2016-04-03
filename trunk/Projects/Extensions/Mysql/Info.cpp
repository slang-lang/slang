
// Header
#include "Info.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Tools.h>
#include <Core/Utils/Exceptions.h>
#include <Tools/Strings.h>
#include "Types.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


MysqlInfo::MysqlInfo()
: Runtime::Method(0, "mysql_info", Designtime::StringObject::TYPENAME)
{
	ParameterList params;

	setSignature(params);
}

Runtime::ControlFlow::E MysqlInfo::execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token)
{
(void)params;
(void)token;

	*result = Runtime::StringObject(mysql_info(MySQLConnection));

	return Runtime::ControlFlow::Normal;
}

}
}
}
