
#ifndef ObjectiveScript_Extensions_Mysql_MysqlFreeResult_h
#define ObjectiveScript_Extensions_Mysql_MysqlFreeResult_h


// Library include

// Project includes
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Repository.h>
#include <Core/Tools.h>
#include "Types.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlFreeResult: public Runtime::Method
{
public:
	MysqlFreeResult()
	: Runtime::Method(0, "mysql_free_result", Designtime::VoidObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, 0));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* /*result*/, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			int param_handle = (*it++).value().toInt();

			MYSQL_RES *myResult = mMysqlResults[param_handle];
			if ( !myResult ) {
				throw Utils::Exceptions::Exception("no valid mysql result!");
			}

			mysql_free_result(myResult);
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
