
// Header
#include "StoreResult.h"

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


MysqlStoreResult::MysqlStoreResult()
: Runtime::Method(0, "mysql_store_result", Designtime::IntegerObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E MysqlStoreResult::execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token)
{
(void)token;

	try {
		int handle = Tools::stringToInt(params.begin()->value());
		MYSQL *myConn = mMysqlConnections[handle];

		MYSQL_RES *my_result = mysql_store_result(myConn);

		mNumMysqlResults++;
		mMysqlResults.insert(std::make_pair(mNumMysqlResults, my_result));

		*result = Runtime::IntegerObject(mNumMysqlResults);

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
