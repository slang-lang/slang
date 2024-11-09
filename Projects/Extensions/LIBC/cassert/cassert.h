
#ifndef Slang_Extensions_LIBC_cassert_cassert_any_h
#define Slang_Extensions_LIBC_cassert_cassert_any_h


// Library includes
#include <cassert>

// Project includes
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Designtime/BuildInTypes/VoidType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace cassert {


class CASSERT : public ExtensionMethod
{
public:
    CASSERT()
    : ExtensionMethod(0, "assert", Designtime::VoidType::TYPENAME)
    {
        ParameterList params;
        params.push_back(Parameter::CreateDesigntime("condition", Common::TypeDeclaration(_any)));
        params.push_back(Parameter::CreateDesigntime("message", Designtime::StringType::TYPENAME, Runtime::AtomicValue(std::string(VALUE_NONE)), true));

        setExceptions(CheckedExceptions::Throw);
        setSignature(params);
    }

    Runtime::ControlFlow::E execute(Common::ThreadId /*threadId*/, const ParameterList& params, Runtime::Object* /*result*/, const Token& token)
    {
        ParameterList list = mergeParameters(params);

        ParameterList::const_iterator it = list.begin();

        auto param_reference = (*it).reference();
        auto param_condition = (*it++).value();
        auto param_message   = (*it++).value().toStdString();

        bool success = false;

        if ( param_reference.isValid() ) {
            Runtime::Object* condition = Controller::Instance().memory()->get(param_reference);

            success = isTrue(condition);
        }
        else {
            Runtime::Object tmp;
            tmp.setValue(param_condition);

            success = isTrue(tmp);
        }

        if ( param_message.empty() ) {
            param_message = "false";
        }

        if ( !success ) {
            throw Runtime::Exceptions::AssertionFailed(param_message, token.position());
        }

        return Runtime::ControlFlow::Normal;
    }
};


}
}
}
}


#endif
