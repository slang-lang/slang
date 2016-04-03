
// Header
#include "Query.h"

// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Tools.h>
#include <Core/Utils/Exceptions.h>
#include <Tools/Strings.h>
#include "Types.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


MysqlQuery::MysqlQuery()
: Runtime::Method(0, "mysql_query", Designtime::IntegerObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("query", Designtime::StringObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E MysqlQuery::execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token)
{
(void)token;

	try {
		ParameterList::const_iterator it = params.begin();

		std::string query = (*it++).value();

		*result = Runtime::IntegerObject(mysql_query(MySQLConnection, query.c_str()));

		return Runtime::ControlFlow::Normal;
	}
	catch ( ... ) {
		return Runtime::ControlFlow::Throw;
	}

	// something weird happened...
	return Runtime::ControlFlow::Throw;
}

}
}
}
