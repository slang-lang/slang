
// Header
#include "Service.h"
#include <iostream>
#include <sstream>

// Library includes

// Project includes
#include <Core/Object.h>
#include <Core/Runtime/Parameter.h>
#include <Core/Runtime/Script.h>
#include <Core/VirtualMachine/Controller.h>
#include <Core/VirtualMachine/VirtualMachine.h>
#include <Logger/Logger.h>
#include <Utils.h>

// Namespace declarations


Service::Service( std::string path, std::string entryPoint, Slang::Script* script )
: mEntryPoint( std::move( entryPoint ) )
, mPath( std::move( path ) )
, mScript( script )
{
    initialize();
}

bool Service::handleRequest( const FCGX_Request& request )
{
    FCGX_FPrintF( request.out, "Content-Type: text/plain\r\n\r\n" );

    std::stringstream stream;
    auto* old = std::cout.rdbuf( stream.rdbuf() );

    if ( mScript ) {
        Slang::Runtime::Object result;
        mScript->execute( Slang::Controller::Instance().threads()->createThread()->getId(), mEntryPoint, Slang::ParameterList(), &result );
    }

    std::cout.rdbuf( old );
    auto output = stream.str();

    OSinfo( "Output: \r\n" + output );

    FCGX_FPrintF( request.out, output.c_str() );

    return true;
}

void Service::initialize()
{
    if ( mEntryPoint.empty() ) {
        // nothing to do here
        return;
    }

    // CHECKME: verify that the entry point exists in the script
    //mScript->
}
