
#ifndef ObjectiveScript_Extensions_Mysql_MysqlClose_h
#define ObjectiveScript_Extensions_Mysql_MysqlClose_h


// Library include

// Project includes
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include "Types.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlClose: public ExtensionMethod
{
public:
	MysqlClose()
	: ExtensionMethod(0, "mysql_close", Designtime::IntegerObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::IntegerObject::TYPENAME));

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
				throw Common::Exceptions::Exception("no valid mysql connection handle: " + Utils::Tools::toString(param_handle));
			}

			mysql_close(myConn);

			*result = Runtime::IntegerObject(0);
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