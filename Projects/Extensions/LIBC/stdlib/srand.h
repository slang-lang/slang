
#ifndef Slang_Extensions_LIBC_stdlib_srand_h
#define Slang_Extensions_LIBC_stdlib_srand_h


// Library includes
#include <math.h>

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/VoidType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/Utils.h>
#include "Defines.h"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace stdlib {


class SRAND: public ExtensionMethod
{
public:
    SRAND()
    : ExtensionMethod(0, "srand", Designtime::VoidType::TYPENAME)
    {
        ParameterList params;
        params.push_back(Parameter::CreateDesigntime("seed", Designtime::Int32Type::TYPENAME));

        setSignature(params);
    }

public:
    Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* /*result*/ )
    {
        ParameterList list = mergeParameters(params);

        ParameterList::const_iterator it = list.begin();

        auto param_seed = (it++)->value().toInt();

        srand(param_seed);

        return Runtime::ControlFlow::Normal;
    }
};


}
}
}
}


#endif
