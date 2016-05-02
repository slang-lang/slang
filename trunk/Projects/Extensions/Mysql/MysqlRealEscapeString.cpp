
// Header
#include "MysqlRealEscapeString.h"

// Library includes
#include <vector>

// Project includes
#include <Core/BuildInObjects/IntegerObject.h>
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


MysqlRealEscapeString::MysqlRealEscapeString()
: Runtime::Method(0, "mysql_real_escape_string", Designtime::StringObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, VALUE_NONE));
	params.push_back(Parameter("from", Designtime::StringObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E MysqlRealEscapeString::execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token)
{
(void)params;
(void)token;

	try {
		// Parameter processing
		// {
		ParameterList::const_iterator it = params.begin();

		int param_handle = Tools::stringToInt((*it++).value());
		std::string param_from = (*it++).value();
		// }

		MYSQL *myConn = mMysqlConnections[param_handle];
		char* from = 0;
		char* to = 0;

		char * writable = new char[param_from.size() + 1];
		std::copy(param_from.begin(), param_from.end(), writable);
		writable[param_from.size()] = '\0'; // don't forget the terminating 0

		mysql_real_escape_string(myConn, writable, to, strlen(writable));

		// don't forget to free the string after finished using it
		delete[] writable;

		if ( to ) {
			*result = Runtime::StringObject(to);
		}
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
