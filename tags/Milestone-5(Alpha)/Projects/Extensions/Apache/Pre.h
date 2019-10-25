
#ifndef ObjectiveScript_Extensions_Apache_Pre_h
#define ObjectiveScript_Extensions_Apache_Pre_h


// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Common/Exceptions.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


#define APACHEEXT_VARPREFIX '$'


namespace ObjectiveScript {
namespace Extensions {
namespace Apache {


class Pre : public ExtensionMethod
{
public:
	Pre()
	: ExtensionMethod(0, "pre", Designtime::VoidObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("text", Designtime::StringObject::TYPENAME));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* /*result*/, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			std::string param_text = (*it++).value().toStdString();
			size_t start = 0;

			while ( (start = param_text.find_first_of(APACHEEXT_VARPREFIX, start)) != std::string::npos ) {
				size_t end = param_text.find_first_of(APACHEEXT_VARPREFIX, start + 1);

				if ( end == std::string::npos ) {
					break;
				}

				std::string var = param_text.substr(start + 1, end - start - 1);

				Symbol* symbol = this->resolve(var, false);
				if ( !symbol ) {
					continue;	// skip not-existing symbols
				}
				if ( symbol->getSymbolType() != Symbol::IType::ObjectSymbol ) {
					continue;	// skip symbols with wrong type
				}

				Runtime::Object* tmp = dynamic_cast<Runtime::Object*>(symbol);

				param_text.replace(start, end - start + 1, tmp->getValue().toStdString());
			}

			std::cout << param_text << std::endl;
		}
		catch ( std::exception& e ) {
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
