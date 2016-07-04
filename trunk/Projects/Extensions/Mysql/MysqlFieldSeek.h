
#ifndef ObjectiveScript_Extensions_Mysql_MysqlFieldSeek_h
#define ObjectiveScript_Extensions_Mysql_MysqlFieldSeek_h

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


class MysqlFieldSeek : public Runtime::Method
{
public:
	MysqlFieldSeek()
	: Runtime::Method(0, "mysql_field_seek", Designtime::IntegerObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, 0));
		params.push_back(Parameter("offset", Designtime::IntegerObject::TYPENAME, 0));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		try {
			// Parameter processing
			// {
			ParameterList::const_iterator it = params.begin();

			int param_handle = (*it++).value().toInt();
			int param_offset = (*it++).value().toInt();
			// }

			MYSQL_RES *myResult = mMysqlResults[param_handle];

			int my_result = mysql_field_seek(myResult, param_offset);

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
};


}
}
}


#endif
