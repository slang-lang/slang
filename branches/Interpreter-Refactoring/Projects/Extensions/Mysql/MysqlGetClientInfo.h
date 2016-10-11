
#ifndef ObjectiveScript_Extensions_Mysql_MysqlGetClientInfo_h
#define ObjectiveScript_Extensions_Mysql_MysqlGetClientInfo_h


// Library includes
#include <mysql.h>

// Project includes
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Tools.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlGetClientInfo : public ExtensionMethod
{
public:
	MysqlGetClientInfo()
	: ExtensionMethod(0, "mysql_get_client_info", Designtime::StringObject::TYPENAME)
	{
		ParameterList params;

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(const ParameterList& /*params*/, Runtime::Object* result, const Token& token)
	{
		try {
			std::string my_result = mysql_get_client_info();

			*result = Runtime::StringObject(my_result);
		}
		catch ( std::exception &e ) {
			Runtime::Object *data = Repository::GetInstance().createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			mExceptionData = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}


#endif
