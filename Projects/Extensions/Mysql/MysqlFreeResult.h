
#ifndef ObjectiveScript_Extensions_Mysql_MysqlFreeResult_h
#define ObjectiveScript_Extensions_Mysql_MysqlFreeResult_h


// Library include

// Project includes
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Tools.h>
#include "Types.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlFreeResult: public ExtensionMethod
{
public:
	MysqlFreeResult()
	: ExtensionMethod(0, "mysql_free_result", Designtime::VoidObject::TYPENAME)
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
				throw Common::Exceptions::Exception("no valid mysql result handle: " + Tools::toString(param_handle));
			}

			mysql_free_result(myResult);
		}
		catch ( std::exception &e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().stack()->exception() = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}


#endif
