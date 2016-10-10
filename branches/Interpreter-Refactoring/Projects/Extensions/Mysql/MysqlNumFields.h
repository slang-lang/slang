
#ifndef ObjectiveScript_Extensions_Mysql_MysqlNumFields_h
#define ObjectiveScript_Extensions_Mysql_MysqlNumFields_h


// Library includes

// Project includes
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Tools.h>
#include "Types.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlNumFields : public Runtime::Method
{
public:
	MysqlNumFields()
	: Runtime::Method(0, "mysql_num_fields", Designtime::IntegerObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, 0));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			int param_handle = (*it++).value().toInt();

			MYSQL_RES *myResult = mMysqlResults[param_handle];
			if ( !myResult ) {
				throw Common::Exceptions::Exception("no valid mysql result handle: " + Tools::toString(param_handle));
			}

			int my_result = mysql_num_fields(myResult);

			*result = Runtime::IntegerObject(my_result);
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
