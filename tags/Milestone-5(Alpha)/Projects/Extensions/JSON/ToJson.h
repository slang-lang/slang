
#ifndef ObjectiveScript_Extensions_System_ToJson_h
#define ObjectiveScript_Extensions_System_ToJson_h


// Library includes
#include <Json/Value.h>

// Project includes
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {


class ToJson : public ExtensionMethod
{
public:
	ToJson()
	: ExtensionMethod(0, "ToJsonString", Designtime::StringObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("source", Common::TypeDeclaration(VALUE_NONE)));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			Runtime::Object *param_object = Controller::Instance().memory()->get((*it++).reference());
			if ( !param_object ) {
				throw Runtime::Exceptions::AccessViolation("invalid reference set for 'object'", token.position());
			}

			::Json::Value value;

			toJson(param_object, value);

			*result = Runtime::StringObject(value.toString());
		}
		catch ( std::exception &e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().thread(threadId)->exception() = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}

private:
	void toJson(Runtime::Object* object, ::Json::Value& result) const {
		for ( Symbols::const_iterator it = object->beginSymbols(); it != object->endSymbols(); ++it ) {
			if ( it->first == IDENTIFIER_THIS || !it->second || it->second->getSymbolType() != Symbol::IType::ObjectSymbol ) {
				continue;
			}

			if ( it->first == IDENTIFIER_BASE ) {
				Runtime::Object* obj = dynamic_cast<Runtime::Object*>(it->second);
				if ( !obj || obj->QualifiedTypename() == _object ) {
					continue;
				}

				::Json::Value value;
				toJson(obj, value);

				result.addMember(it->first, value);
				continue;
			}

			Runtime::Object *obj = dynamic_cast<Runtime::Object*>(it->second);
			if ( !obj ) {
				continue;
			}

			result.addMember(it->first, obj->getValue().toStdString());
		}
	}
};


}
}

#endif
