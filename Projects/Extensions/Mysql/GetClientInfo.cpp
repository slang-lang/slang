
// Header
#include "GetClientInfo.h"

// Library includes
#include <mysql.h>

// Project includes
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Tools.h>
#include <Core/Utils/Exceptions.h>
#include <Tools/Strings.h>

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

Runtime::ControlFlow::E MysqlGetClientInfo::execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token)
{
	(void)params;
	(void)token;

/*
	if ( params.size() > 0 ) {
		throw Utils::Exceptions::ParameterCountMissmatch("0 parameters expected, but " + ::Utils::Tools::toString(params.size()) + " parameter(s) found", token->position());
	}
*/

	*result = Runtime::StringObject(mysql_get_client_info());

	return Runtime::ControlFlow::Normal;
}


}
}
}
