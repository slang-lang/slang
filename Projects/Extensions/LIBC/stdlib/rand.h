
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
    Runtime::ControlFlow::E execute( const ParameterList& /*params*/, Runtime::Object* result )
    {
        *result = Runtime::Int32Type(rand());

        return Runtime::ControlFlow::Normal;
    }
};


}
}
}
}


#endif
