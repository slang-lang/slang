
#ifndef ObjectiveScript_Extensions_Mysql_MysqlGetFieldValue_h
#define ObjectiveScript_Extensions_Mysql_MysqlGetFieldValue_h


// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Tools.h>
#include "Types.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlGetFieldValueByIndex : public ExtensionMethod
{
public:
	MysqlGetFieldValueByIndex()
	: ExtensionMethod(0, "mysql_get_field_value", Designtime::StringObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::IntegerObject::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("field_index", Designtime::IntegerObject::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			int param_handle = (*it++).value().toInt();
			int param_field_id = (*it++).value().toInt();

			MYSQL_RES *myResult = mMysqlResults[param_handle];
			if ( !myResult ) {
				throw Common::Exceptions::Exception("no valid result handle: " + std::to_string(param_handle));
			}

			MYSQL_ROW row = myResult->current_row;
			if ( !row ) {
				throw Common::Exceptions::Exception("no valid row");
			}

			std::string my_result;
			if ( row[param_field_id] ) {
				my_result = std::string(row[param_field_id]);
			}

			*result = Runtime::StringObject(my_result);
		}
		catch ( std::exception &e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().thread(threadId)->exception() = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};


class MysqlGetFieldValueByName : public ExtensionMethod
{
public:
	MysqlGetFieldValueByName()
	: ExtensionMethod(0, "mysql_get_field_value", Designtime::StringObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::IntegerObject::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("field_name", Designtime::StringObject::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			int param_handle = (*it++).value().toInt();
			std::string param_field_name = (*it++).value().toStdString();

			MYSQL_RES *myResult = mMysqlResults[param_handle];
			if ( !myResult ) {
				throw Common::Exceptions::Exception("no valid result handle: " + std::to_string(param_handle));
			}

			bool foundField = false;
			std::string my_result;

			for ( unsigned int idx = 0; idx < myResult->field_count; ++idx ) {
				if ( !myResult->fields[idx].name ) {
					throw Common::Exceptions::Exception("invalid field name detected at field index: " + std::to_string(idx));
				}

				if ( std::string(myResult->fields[idx].name) == param_field_name ) {
					foundField = true;
					if ( myResult->current_row[idx] ) {
						my_result = std::string(myResult->current_row[idx]);
					}
				}
			}

			if ( !foundField ) {
				throw Common::Exceptions::Exception("invalid field name '" + param_field_name + "' provided!");
			}

			*result = Runtime::StringObject(my_result);
		}
		catch ( std::exception &e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().thread(threadId)->exception() = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}


#endif
