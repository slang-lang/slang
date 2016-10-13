
#ifndef ObjectiveScript_Extensions_Apache_Pre_h
#define ObjectiveScript_Extensions_Apache_Pre_h


// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Common/Exceptions.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Repository.h>
#include <Tools/Strings.h>

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
		params.push_back(Parameter("text", Designtime::StringObject::TYPENAME, VALUE_NONE, true));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* /*result*/, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			std::string param_text = (*it++).value().toStdString();

			size_t start = 0;
			size_t end = 0;

			while ( (start = param_text.find_first_of(APACHEEXT_VARPREFIX, start)) != std::string::npos ) {
				end = param_text.find_first_of(APACHEEXT_VARPREFIX, start + 1);

				if ( end == std::string::npos ) {
					break;
				}

				std::string var = param_text.substr(start + 1, end - start - 1);

				Symbol* symbol = this->resolve(var, false);
				if ( !symbol ) {
					throw Common::Exceptions::UnknownIdentifer("unknown identifier '" + var + "'", token.position());
				}
				if ( symbol->getSymbolType() != Symbol::IType::ObjectSymbol ) {
					throw Common::Exceptions::Exception("invalid symbol type found", token.position());
				}

				Runtime::Object* tmp = static_cast<Runtime::Object*>(symbol);

				param_text.replace(start, end - start + 1, tmp->getValue().toStdString());
			}

			std::cout << param_text << std::endl;
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Repository::Instance().createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
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
