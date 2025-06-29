
#ifndef Slang_Extensions_LIBC_fenv_fegetround_h
#define Slang_Extensions_LIBC_fenv_fegetround_h


// Library includes
#include <cfenv>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Runtime/Utils.h>
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace fenv {


class FEGETROUND: public ExtensionMethod
{
public:
    FEGETROUND()
    : ExtensionMethod(0, "fegetround", Designtime::Int32Type::TYPENAME)
    {
        ParameterList params;

        setSignature(params);
    }

    Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
    {
        ParameterList list = mergeParameters(params);

        *result = Runtime::Int32Type(fegetround());

        return Runtime::ControlFlow::Normal;
    }
};


}
}
}
}


#endif
