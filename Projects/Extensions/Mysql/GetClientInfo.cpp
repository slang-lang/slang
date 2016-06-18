
// Header
#include "GetClientInfo.h"

// Library includes
#include <mysql.h>

// Project includes
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Repository.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


MysqlGetClientInfo::MysqlGetClientInfo()
: Runtime::Method(0, "mysql_get_client_info", Designtime::StringObject::TYPENAME)
{
	ParameterList params;

	setSignature(params);
}

Runtime::ControlFlow::E MysqlGetClientInfo::execute(const ParameterList& params, Runtime::Object* result, const Token& token)
{
(void)params;
	try {
		std::string my_result = mysql_get_client_info();

		*result = Runtime::StringObject(my_result);
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
