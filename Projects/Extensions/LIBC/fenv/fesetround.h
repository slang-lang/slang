
#ifndef Slang_Extensions_LIBC_fenv_fesetround_h
#define Slang_Extensions_LIBC_fenv_fesetround_h


// Library includes
#include <cfenv>

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>

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
    : ExtensionMethod(0, "fesetround", Designtime::Int32Type::TYPENAME)
    {
        ParameterList params;
        params.push_back(Parameter::CreateDesigntime("round", Common::TypeDeclaration(Designtime::Int32Type::TYPENAME)));

        setSignature(params);
    }

    Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
    {
        ParameterList list = mergeParameters(params);

        ParameterList::const_iterator it = list.begin();

        auto param_round = (*it++).value().toInt();

        *result = Runtime::Int32Type(fesetround(param_round));

        return Runtime::ControlFlow::Normal;
    }
};


}
}
}
}


#endif
