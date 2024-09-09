
#ifndef Slang_Extensions_LIBC_fenv_fesetround_h
#define Slang_Extensions_LIBC_fenv_fesetround_h


// Library includes
#include <cfenv>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/IntegerObject.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace fenv {


class FESETROUND: public ExtensionMethod
{
public:
    FESETROUND()
    : ExtensionMethod(0, "fesetround", Designtime::IntegerObject::TYPENAME)
    {
        ParameterList params;
        params.push_back(Parameter::CreateDesigntime("round", Common::TypeDeclaration(Designtime::IntegerObject::TYPENAME)));

        setSignature(params);
    }

    Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
    {
        ParameterList list = mergeParameters(params);

        try {
            ParameterList::const_iterator it = list.begin();

            auto param_round = (*it++).value().toInt();

            *result = Runtime::IntegerObject(fesetround(param_round));
        }
        catch ( std::exception& e ) {
            Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME);
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
}


#endif
