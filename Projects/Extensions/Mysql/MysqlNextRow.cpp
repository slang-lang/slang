
// Header
#include "MysqlNextRow.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/BoolObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Repository.h>
#include <Core/Tools.h>
#include "Types.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


MysqlNextRow::MysqlNextRow()
: Runtime::Method(0, "mysql_next_row", Designtime::BoolObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, 0));

	setSignature(params);
}

Runtime::ControlFlow::E MysqlNextRow::execute(const ParameterList& params, Runtime::Object* result, const Token& token)
{
	ParameterList list = mergeParameters(params);

	try {
		ParameterList::const_iterator it = list.begin();

		int param_handle = (*it++).value().toInt();

		MYSQL_RES *myResult = mMysqlResults[param_handle];
		MYSQL_ROW myRow = mysql_fetch_row(myResult);

		bool my_result = myRow ? true : false;

		*result = Runtime::BoolObject(my_result);
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
