
#ifndef ObjectiveScript_Extensions_Mysql_MysqlError_h
#define ObjectiveScript_Extensions_Mysql_MysqlError_h


// Library includes

// Project includes
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Tools.h>
#include "Types.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlError : public Runtime::Method
{
public:
	MysqlError()
	: Runtime::Method(0, "mysql_error", Designtime::StringObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, VALUE_NONE));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			int param_handle = (*it++).value().toInt();

			MYSQL *myConn = mMysqlConnections[param_handle];
			if ( !myConn ) {
				throw Common::Exceptions::Exception("no valid mysql connection handle: " + Tools::toString(param_handle));
			}

			std::string my_result = mysql_error(myConn);

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
