
// Header
#include "Connect.h"

// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/BoolObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Tools.h>
#include <Core/Utils/Exceptions.h>
#include <Tools/Strings.h>
#include "Types.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


MysqlRealConnect::MysqlRealConnect()
: Runtime::Method(0, "mysql_real_connect", Designtime::IntegerObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("host", Designtime::StringObject::TYPENAME, VALUE_NONE));
	params.push_back(Parameter("port", Designtime::IntegerObject::TYPENAME, VALUE_NONE));
	params.push_back(Parameter("user", Designtime::StringObject::TYPENAME, VALUE_NONE));
	params.push_back(Parameter("passwd", Designtime::StringObject::TYPENAME, VALUE_NONE));
	params.push_back(Parameter("db", Designtime::StringObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E MysqlRealConnect::execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token)
{
(void)result;
(void)token;

	if ( !MySQLConnection ) {
		MySQLConnection = mysql_init(MySQLConnection);
	}

	ParameterList::const_iterator it = params.begin();

	std::string host = (*it++).value();
	int port = Tools::stringToInt((*it++).value());
	std::string user = (*it++).value();
	std::string passwd = (*it++).value();
	std::string db = (*it++).value();
	std::string socket;
	long clientflag = 0;

	MySQLConnection = mysql_real_connect(MySQLConnection, host.c_str(), user.c_str(), passwd.c_str(), db.c_str(), port, socket.c_str(), clientflag);

	return Runtime::ControlFlow::Normal;
}

}
}
}
