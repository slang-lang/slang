
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
    char* pathInfo      = FCGX_GetParam( "PATH_INFO", request.envp );
    char* queryString   = FCGX_GetParam( "QUERY_STRING", request.envp );
    char* requestMethod = FCGX_GetParam( "REQUEST_METHOD", request.envp );
    char* requestUri    = FCGX_GetParam( "REQUEST_URI", request.envp );
    char* scriptName    = FCGX_GetParam( "SCRIPT_NAME", request.envp );

    setenv( "QUERY_STRING", queryString, 1 );
    setenv( "REQUEST_METHOD", requestMethod, 1 );
    setenv( "REQUEST_URI", requestUri, 1 );
    setenv( "SCRIPT_NAME", scriptName, 1 );

    OSinfo( "REQUEST_METHOD: " << ( requestMethod ? requestMethod : "" ) );
    OSinfo( "SCRIPT_NAME: " << ( scriptName ? scriptName : "" ) );
    OSinfo( "PATH_INFO: " << ( pathInfo ? pathInfo : "" ) );
    OSinfo( "QUERY_STRING: " << ( queryString ? queryString : "" ) );
    // OSinfo( "REQUEST_URI: " << ( requestUri ? requestUri : "" ) );

    FCGX_FPrintF( request.out, "Content-Type: text/plain\r\n\r\n" );

    std::stringstream stream;
    auto* old = std::cout.rdbuf( stream.rdbuf() );

    if ( mScript ) {
        try {
            Slang::Runtime::Object result;
            mScript->execute( Slang::Controller::Instance().threads()->createThread()->getId(), mEntryPoint, Slang::ParameterList(), &result );
        }
        catch ( const std::exception& e ) {
            OSerror( "Exception: " << e.what() );
        }
    }

    std::cout.rdbuf( old );
    auto output = stream.str();

    std::cout << output << std::endl;

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
