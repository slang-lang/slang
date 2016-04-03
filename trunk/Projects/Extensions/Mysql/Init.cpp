
// Header
#include "Init.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Tools.h>
#include <Core/Utils/Exceptions.h>
#include <Tools/Strings.h>
#include "Types.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


MysqlInit::MysqlInit()
: Runtime::Method(0, "mysql_init", Designtime::IntegerObject::TYPENAME)
{
	ParameterList params;

	setSignature(params);
}

Runtime::ControlFlow::E MysqlInit::execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token)
{
(void)params;
(void)token;

	try {
		MYSQL *handle = mysql_init(0);

		mNumMysqlConnections++;
		mMysqlConnections.insert(std::make_pair(mNumMysqlConnections, handle));

		*result = Runtime::IntegerObject(mNumMysqlConnections);

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
