
#ifndef Slang_Extensions_LIBC_fenv_fetestexcept_h
#define Slang_Extensions_LIBC_fenv_fetestexcept_h


// Library includes
#include <cfenv>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace fenv {


class FETESTEXCEPT: public ExtensionMethod
{
public:
    FETESTEXCEPT()
    : ExtensionMethod(0, "fetestexcept", Designtime::Int32Type::TYPENAME)
    {
        ParameterList params;
        params.push_back(Parameter::CreateDesigntime("excepts", Common::TypeDeclaration(Designtime::Int32Type::TYPENAME)));

        setSignature(params);
    }

    Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
    {
        ParameterList list = mergeParameters(params);

        try {
            ParameterList::const_iterator it = list.begin();

            auto param_excepts = (*it++).value().toInt();

            *result = Runtime::Int32Type(fetestexcept(param_excepts));
        }
        catch ( std::exception& e ) {
            Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringType::TYPENAME);
            *data = Runtime::StringType(std::string(e.what()));

            Controller::Instance().thread(threadId)->exception() = Runtime::ExceptionData(data, token.position());
            return Runtime::ControlFlow::Throw;
        }

        return Runtime::ControlFlow::Normal;
    }
};


}
}
}
}


#endif
