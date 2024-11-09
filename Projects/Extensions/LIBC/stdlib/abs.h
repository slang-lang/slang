
#ifndef Slang_Extensions_LIBC_stdlib_abs_hpp
#define Slang_Extensions_LIBC_stdlib_abs_hpp


// Library includes
#include <cstdlib>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/DoubleType.h>
#include <Core/Designtime/BuildInTypes/FloatType.h>
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/DoubleType.h>
#include <Core/Runtime/BuildInTypes/FloatType.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace stdlib {


class ABSDouble: public ExtensionMethod
{
public:
    ABSDouble()
    : ExtensionMethod(0, "abs", Designtime::DoubleType::TYPENAME)
    {
        ParameterList params;
        params.push_back(Parameter::CreateDesigntime("arg", Common::TypeDeclaration(Designtime::DoubleType::TYPENAME)));

        setSignature(params);
    }

public:
    Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
    {
        ParameterList list = mergeParameters(params);

        try {
            ParameterList::const_iterator it = list.begin();

            auto param_arg = (*it++).value().toDouble();

            *result = Runtime::DoubleType(std::abs(param_arg));
        }
        catch ( std::exception& e ) {
            Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringType::TYPENAME);
            *data = Runtime::StringType(std::string(e.what()));

            Controller::Instance().thread(threadId)->exception(data, token.position());
            return Runtime::ControlFlow::Throw;
        }

        return Runtime::ControlFlow::Normal;
    }
};


class ABSFloat: public ExtensionMethod
{
public:
    ABSFloat()
    : ExtensionMethod(0, "abs", Designtime::FloatType::TYPENAME)
    {
        ParameterList params;
        params.push_back(Parameter::CreateDesigntime("arg", Common::TypeDeclaration(Designtime::FloatType::TYPENAME)));

        setSignature(params);
    }

public:
    Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
    {
        ParameterList list = mergeParameters(params);

        try {
            ParameterList::const_iterator it = list.begin();

            auto param_arg = (*it++).value().toFloat();

            *result = Runtime::FloatType(std::abs(param_arg));
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


class ABSInt: public ExtensionMethod
{
public:
    ABSInt()
    : ExtensionMethod(0, "abs", Designtime::Int32Type::TYPENAME)
    {
        ParameterList params;
        params.push_back(Parameter::CreateDesigntime("arg", Common::TypeDeclaration(Designtime::Int32Type::TYPENAME)));

        setSignature(params);
    }

public:
    Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
    {
        ParameterList list = mergeParameters(params);

        try {
            ParameterList::const_iterator it = list.begin();

            auto param_arg = (*it++).value().toInt();

            result->assign(Runtime::Int32Type(std::abs(param_arg)));
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
