
// Header
#include "NextResult.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Repository.h>
#include <Core/Tools.h>
#include "Types.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


MysqlNextResult::MysqlNextResult()
: Runtime::Method(0, "mysql_next_result", Designtime::IntegerObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, 0));

	setSignature(params);
}

Runtime::ControlFlow::E MysqlNextResult::execute(const ParameterList& params, Runtime::Object* result, const Token& token)
{
	try {
		// Parameter processing
		// {
		ParameterList::const_iterator it = params.begin();

		int param_handle = (*it++).value().toInt();
		// }

		MYSQL *myConn = mMysqlConnections[param_handle];

		int my_result = mysql_next_result(myConn);

		*result = Runtime::IntegerObject(my_result);
	}
	catch ( std::exception &e ) {
		Runtime::Object *data = mRepository->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
		*data = Runtime::StringObject(std::string(e.what()));

		mExceptionData = Runtime::ExceptionData(data, token.position());
		return Runtime::ControlFlow::Throw;
	}

	return Runtime::ControlFlow::Normal;
}

}
}
}
