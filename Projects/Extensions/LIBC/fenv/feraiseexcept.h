
#ifndef Slang_Extensions_LIBC_fenv_feraiseexcept_h
#define Slang_Extensions_LIBC_fenv_feraiseexcept_h


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


class FERAISEEXCEPT: public ExtensionMethod
{
public:
    FERAISEEXCEPT()
    : ExtensionMethod(0, "feraiseexcept", Designtime::Int32Type::TYPENAME)
    {
        ParameterList params;
        params.push_back(Parameter::CreateDesigntime("excepts", Common::TypeDeclaration(Designtime::Int32Type::TYPENAME)));

        setSignature(params);
    }

    Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
    {
        ParameterList list = mergeParameters(params);

        ParameterList::const_iterator it = list.begin();

        auto param_excepts = (*it++).value().toInt();

        *result = Runtime::Int32Type(feraiseexcept(param_excepts));

        return Runtime::ControlFlow::Normal;
    }
};


}
}
}
}


#endif
