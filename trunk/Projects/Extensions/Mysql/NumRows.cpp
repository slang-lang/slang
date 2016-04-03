
// Header
#include "NumRows.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Repository.h>
#include <Core/Tools.h>
#include <Core/Utils/Exceptions.h>
#include <Tools/Strings.h>
#include "Types.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


MysqlNumRows::MysqlNumRows()
: Runtime::Method(0, "mysql_num_rows", Designtime::IntegerObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("handle", Designtime::IntegerObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E MysqlNumRows::execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token)
{
(void)params;
(void)token;

	try {
		if ( !MySQLResult ) {
			throw Utils::Exceptions::Exception("no result selected");
		}

		*result = Runtime::IntegerObject(mysql_num_rows(MySQLResult));

		return Runtime::ControlFlow::Normal;
	}
	catch ( std::exception &e ) {
		Runtime::Object *data = mRepository->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
		*data = Runtime::StringObject(e.what());

		mExceptionData = Runtime::ExceptionData(data, token->position());
		return Runtime::ControlFlow::Throw;
	}

	return Runtime::ControlFlow::Throw;
}

}
}
}
