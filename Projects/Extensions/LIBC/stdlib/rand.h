
#ifndef Slang_Extensions_LIBC_stdlib_rand_h
#define Slang_Extensions_LIBC_stdlib_rand_h


// Library includes
#include <math.h>

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include "stdlib.h"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace stdlib {


class RAND: public ExtensionMethod
{
public:
    RAND()
    : ExtensionMethod(0, "rand", Designtime::Int32Type::TYPENAME)
    {
        ParameterList params;

        setSignature(params);
    }

public:
    Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& /*params*/, Runtime::Object* result, const Token& token)
    {
        try {
            *result = Runtime::Int32Type(rand());
        }
        catch ( std::exception& e ) {
            Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringType::TYPENAME, ANONYMOUS_OBJECT);
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
