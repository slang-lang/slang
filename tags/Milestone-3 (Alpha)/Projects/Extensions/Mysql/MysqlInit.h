
#ifndef ObjectiveScript_Extensions_Mysql_MysqlInit_h
#define ObjectiveScript_Extensions_Mysql_MysqlInit_h


// Library include

// Project includes
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Tools.h>
#include "Types.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlInit: public ExtensionMethod
{
public:
	MysqlInit()
	: ExtensionMethod(0, "mysql_init", Designtime::IntegerObject::TYPENAME)
	{
		ParameterList params;

		setSignature(params);
	}


	Runtime::ControlFlow::E execute(const ParameterList& /*params*/, Runtime::Object* result, const Token& token)
	{
		try {
			MYSQL *myHandle = mysql_init(0);

			int my_result = 0;
			if ( myHandle ) {
				my_result = ++mNumMysqlConnections;
				mMysqlConnections.insert(std::make_pair(my_result, myHandle));
			}

			*result = Runtime::IntegerObject(my_result);
		}
		catch ( std::exception &e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
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