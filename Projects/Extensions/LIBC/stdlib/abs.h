
#ifndef Slang_Extensions_LIBC_stdlib_abs_hpp
#define Slang_Extensions_LIBC_stdlib_abs_hpp


// Library includes
#include <cstdlib>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/DoubleType.h>
#include <Core/Designtime/BuildInTypes/FloatObject.h>
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/DoubleType.h>
#include <Core/Runtime/BuildInTypes/FloatObject.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
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
            Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME);
            *data = Runtime::StringObject(std::string(e.what()));

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
    : ExtensionMethod(0, "abs", Designtime::FloatObject::TYPENAME)
    {
        ParameterList params;
        params.push_back(Parameter::CreateDesigntime("arg", Common::TypeDeclaration(Designtime::FloatObject::TYPENAME)));

        setSignature(params);
    }

public:
    Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
    {
        ParameterList list = mergeParameters(params);

        try {
            ParameterList::const_iterator it = list.begin();

            auto param_arg = (*it++).value().toFloat();

            *result = Runtime::FloatObject(std::abs(param_arg));
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
