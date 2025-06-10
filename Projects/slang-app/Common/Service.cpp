
// Header
#include "Service.h"
#include <iostream>

// Library includes

// Project includes
#include <Core/Object.h>
#include <Core/Parameter.h>
#include <Core/Runtime/Script.h>
#include <Core/VirtualMachine/Controller.h>
#include <Core/VirtualMachine/VirtualMachine.h>

// Namespace declarations


Service::Service( std::string path, std::string scriptFilename, Slang::VirtualMachine* vm )
: mPath( std::move( path ) )
, mScriptFilename( std::move( scriptFilename ) )
, mVirtualMachine( vm )
{
    initialize();
}

bool Service::handleRequest( const FCGX_Request& request )
{
    std::string output;
    output = "Hello from ";
    output += mPath;
    output += "\r\n";

    FCGX_FPrintF( request.out, "Content-Type: text/plain\r\n\r\n" );
    FCGX_FPrintF( request.out, output.c_str() );

    if ( mScript ) {
        Slang::Runtime::Object result;
        mVirtualMachine->run( mScript, Slang::ParameterList(), &result );

        // if ( result.getValue().type() == Slang::Runtime::AtomicValue::Type::INT ) {
        //     return result.getValue().toInt();
        // }
    }

    return true;
}

void Service::initialize()
{
    if ( mScriptFilename.empty() ) {
        // nothing to do here
        return;
    }

    mScript = mVirtualMachine->createScriptFromFile( mScriptFilename );
	assert( mScript );
}
