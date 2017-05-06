
#ifndef ObjectiveScript_Extensions_Mysql_MysqlFieldTell_h
#define ObjectiveScript_Extensions_Mysql_MysqlFieldTell_h

// Library includes

// Project includes
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Tools.h>
#include "Types.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlFieldTell : public ExtensionMethod
{
public:
	MysqlFieldTell()
	: ExtensionMethod(0, "mysql_field_tell", Designtime::IntegerObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::IntegerObject::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		try {
			// Parameter processing
			// {
			ParameterList::const_iterator it = params.begin();

			int param_handle = (*it++).value().toInt();
			// }

			MYSQL_RES *myResult = mMysqlResults[param_handle];
			if ( !myResult ) {
				throw Common::Exceptions::Exception("no valid mysql result handle: " + Utils::Tools::toString(param_handle));
			}

			int my_result = mysql_field_tell(myResult);

			*result = Runtime::IntegerObject(my_result);
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
