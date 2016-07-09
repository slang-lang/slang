
// Header
#include "MysqlStoreResult.h"

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


MysqlStoreResult::MysqlStoreResult()
: Runtime::Method(0, "mysql_store_result", Designtime::IntegerObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, 0));

	setSignature(params);
}

Runtime::ControlFlow::E MysqlStoreResult::execute(const ParameterList& params, Runtime::Object* result, const Token& token)
{
	ParameterList list = mergeParameters(params);

	try {
		ParameterList::const_iterator it = list.begin();

		int param_handle = (*it++).value().toInt();

		MYSQL *myConn = mMysqlConnections[param_handle];

		MYSQL_RES *myResult = mysql_store_result(myConn);

		int my_result = 0;
		if ( myResult ) {
			my_result = ++mNumMysqlResults;
			mMysqlResults.insert(std::make_pair(my_result, myResult));
		}

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
