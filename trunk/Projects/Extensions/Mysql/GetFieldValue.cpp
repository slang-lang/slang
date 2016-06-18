
// Header
#include "GetFieldValue.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Repository.h>
#include <Core/Tools.h>
#include <Core/Utils/Exceptions.h>
#include "Types.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


MysqlGetFieldValue::MysqlGetFieldValue()
: Runtime::Method(0, "mysql_get_field_value", Designtime::StringObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, 0));
	params.push_back(Parameter("field_id", Designtime::IntegerObject::TYPENAME, 0));

	setSignature(params);
}

Runtime::ControlFlow::E MysqlGetFieldValue::execute(const ParameterList& params, Runtime::Object* result, const Token& token)
{
	try {
		// Parameter processing
		// {
		ParameterList::const_iterator it = params.begin();

		int param_handle = (*it++).value().toInt();
		int param_field_id = (*it++).value().toInt();
		// }

		MYSQL_RES *myResult = mMysqlResults[param_handle];

		if ( !myResult ) {
			throw Utils::Exceptions::Exception("no valid result handle: " + Tools::toString(param_handle));
		}

		MYSQL_ROW row = myResult->current_row;
		if ( !row ) {
			throw Utils::Exceptions::Exception("no valid row");
		}

		std::string my_result(row[param_field_id]);

		*result = Runtime::StringObject(my_result);
	}
	catch ( std::exception &e ) {
		Runtime::Object *data = mRepository->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
		*data = Runtime::StringObject(std::string(e.what()));

		mExceptionData = Runtime::ExceptionData(data, token.position());
		return Runtime::ControlFlow::Throw;
	}

	return Runtime::ControlFlow::Normal;
}

}
}
}
