
// Header
#include "Error.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Tools.h>
#include <Core/Utils/Exceptions.h>
#include <Tools/Strings.h>
#include "Types.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


MysqlError::MysqlError()
: Runtime::Method(0, "mysql_error", Designtime::StringObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E MysqlError::execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token)
{
(void)params;
(void)token;

	try {
		int handle = Tools::stringToInt(params.begin()->value());

		*result = Runtime::StringObject(mysql_error(mMysqlConnections[handle]));

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
