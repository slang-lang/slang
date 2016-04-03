
// Header
#include "AffectedRows.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Repository.h>
#include <Core/Tools.h>
#include <Core/Utils/Exceptions.h>
#include <Tools/Strings.h>
#include "Types.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


MysqlAffectedRows::MysqlAffectedRows()
: Runtime::Method(0, "mysql_affected_rows", Designtime::IntegerObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E MysqlAffectedRows::execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token)
{
(void)params;
(void)token;

	try {
		int handle = Tools::stringToInt(params.begin()->value());
		MYSQL *myConn = mMysqlConnections[handle];

		*result = Runtime::IntegerObject(mysql_affected_rows(myConn));

		return Runtime::ControlFlow::Normal;
	}
	catch ( std::exception &e ) {
		Runtime::Object *data = mRepository->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
		*data = Runtime::StringObject(e.what());

		mExceptionData = Runtime::ExceptionData(data, token->position());
		return Runtime::ControlFlow::Throw;
	}

	return Runtime::ControlFlow::Throw;
}

}
}
}
