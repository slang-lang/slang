
// Header
#include "Query.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Repository.h>
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
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, VALUE_NONE));
	params.push_back(Parameter("query", Designtime::StringObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E MysqlQuery::execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token)
{
(void)token;

	try {
		// Parameter processing
		// {
		ParameterList::const_iterator it = params.begin();

		int param_handle = Tools::stringToInt((*it++).value());
		std::string query = (*it++).value();
		// }

		MYSQL *myConn = mMysqlConnections[param_handle];
		if ( !myConn ) {
			throw Utils::Exceptions::Exception("no database connection found for connection handle " + Tools::toString(param_handle));
		}

		int my_result = mysql_query(myConn, query.c_str());

		*result = Runtime::IntegerObject(my_result);
	}
	catch ( std::exception &e ) {
		Runtime::Object *data = mRepository->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
		*data = Runtime::StringObject(e.what());

		mExceptionData = Runtime::ExceptionData(data, token->position());
		return Runtime::ControlFlow::Throw;
	}

	return Runtime::ControlFlow::Normal;
}

}
}
}
