
// Header
#include "GetFieldName.h"

// Library includes

// Project includes
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


MysqlGetFieldName::MysqlGetFieldName()
: Runtime::Method(0, "mysql_get_field_name", Designtime::StringObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, VALUE_NONE));
	params.push_back(Parameter("field_id", Designtime::IntegerObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E MysqlGetFieldName::execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token)
{
(void)token;

	try {
		// Parameter processing
		// {
		ParameterList::const_iterator it = params.begin();

		int param_handle = Tools::stringToInt((*it++).value());
		int param_field_id = Tools::stringToInt((*it++).value());
		// }

		MYSQL_RES *myResult = mMysqlResults[param_handle];

		std::string my_result(myResult->fields[param_field_id].name);

		*result = Runtime::StringObject(my_result);
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
