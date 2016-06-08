
// Header
#include "Info.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Repository.h>
#include <Core/Tools.h>
#include "Types.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


MysqlInfo::MysqlInfo()
: Runtime::Method(0, "mysql_info", Designtime::StringObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E MysqlInfo::execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token)
{
(void)token;

	try {
		// Parameter processing
		// {
		ParameterList::const_iterator it = params.begin();

		int param_handle = (*it++).value().toInt();
		// }

		MYSQL *myConn = mMysqlConnections[param_handle];

		std::string my_result;
		if ( myConn ) {
			const char* my_info = mysql_info(myConn);

			if ( my_info ) {
				my_result = std::string(my_info);
			}
		}

		*result = Runtime::StringObject(my_result);
	}
	catch ( std::exception &e ) {
		Runtime::Object *data = mRepository->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
		*data = Runtime::StringObject(std::string(e.what()));

		mExceptionData = Runtime::ExceptionData(data, token->position());
		return Runtime::ControlFlow::Throw;
	}

	return Runtime::ControlFlow::Normal;
}

}
}
}
