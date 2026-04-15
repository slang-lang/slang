
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


namespace {

    static inline void setenv_s( const char* param, const FCGX_Request& request );

}


Service::Service( std::string path, std::string entryPoint, Slang::Script* script, Slang::Controller* controller )
: mController( controller )
, mEntryPoint( std::move( entryPoint ) )
, mPath( std::move( path ) )
, mScript( script )
{
    initialize();
}

bool Service::handleRequest( const FCGX_Request& request )
{
    prepareEnvironment( request );

    std::stringstream stream;
    auto* old = std::cout.rdbuf( stream.rdbuf() );

    if ( mScript ) {
        try {
            Slang::Runtime::Object result;
            mScript->execute( mController->threads()->createThread()->getId(), mEntryPoint, Slang::ParameterList(), &result );
        }
        catch ( std::exception &e ) {	// catch every std::exception and all derived exception types
            OSerror( e.what() );
        }
        catch ( ... ) {	// catch everything
            OSerror( "uncaught exception detected!" );
        }
    }

    std::cout.rdbuf( old );
    auto output = stream.str();

    std::cout << output << std::endl;

    FCGX_PutStr( output.c_str(), output.size(), request.out );

    return true;
}

void Service::initialize()
{
    if ( mEntryPoint.empty() ) {
        OSwarn( "Service entry point is empty." );
    }
    if ( !mScript ) {
        OSwarn( "Service script is null." );
    }
}

void Service::prepareEnvironment( const FCGX_Request& request )
{
    char* pathInfo      = FCGX_GetParam( "PATH_INFO", request.envp );
    char* queryString   = FCGX_GetParam( "QUERY_STRING", request.envp );
    char* requestMethod = FCGX_GetParam( "REQUEST_METHOD", request.envp );
    char* requestUri    = FCGX_GetParam( "REQUEST_URI", request.envp );
    char* scriptName    = FCGX_GetParam( "SCRIPT_NAME", request.envp );

    setenv_s( "HTTP_ACCEPT",           request );
    setenv_s( "HTTP_COOKIE",           request );
    setenv_s( "HTTP_FORWARDED",        request );
    setenv_s( "HTTP_HOST",             request );
    setenv_s( "HTTP_PROXY_CONNECTION", request );
    setenv_s( "HTTP_REFERER",          request );
    setenv_s( "HTTP_USER_AGENT",       request );

    setenv_s( "REQUEST_SCHEME",        request );
    setenv( "REQUEST_METHOD",          requestMethod, 1 );
    setenv( "REQUEST_URI",             requestUri, 1 );
    setenv_s( "DOCUMENT_URI",          request );
    setenv_s( "REQUEST_FILENAME",      request );
    setenv_s( "SCRIPT_FILENAME",       request );
    setenv_s( "LAST_MODIFIED",         request );
    setenv_s( "SCRIPT_USER",           request );
    setenv_s( "SCRIPT_GROUP",          request );
    setenv_s( "PATH_INFO",             request );
    setenv( "QUERY_STRING",            queryString, 1 );
    setenv_s( "IS_SUBREQ",             request );
    setenv_s( "THE_REQUEST",           request );
    setenv_s( "REMOTE_ADDR",           request );
    setenv_s( "REMOTE_PORT",           request );
    setenv_s( "REMOTE_HOST",           request );
    setenv_s( "REMOTE_USER",           request );
    setenv_s( "REMOTE_IDENT",          request );
    setenv_s( "SERVER_NAME",           request );
    setenv_s( "SERVER_PORT",           request );
    setenv_s( "SERVER_ADMIN",          request );
    setenv_s( "SERVER_PROTOCOL",       request );
    setenv_s( "DOCUMENT_ROOT",         request );
    setenv_s( "AUTH_TYPE",             request );
    setenv_s( "CONTENT_TYPE",          request );
    setenv_s( "HANDLER",               request );
    setenv_s( "HTTP2",                 request );
    setenv_s( "HTTPS",                 request );
    setenv_s( "IPV6",                  request );
    setenv_s( "REQUEST_STATUS",        request );
    setenv_s( "REQUEST_LOG_ID",        request );
    setenv_s( "CONN_LOG_ID",           request );
    setenv_s( "CONN_REMOTE_ADDR",      request );
    setenv_s( "CONTEXT_PREFIX",        request );
    setenv_s( "CONTEXT_DOCUMENT_ROOT", request );

    // OSinfo( "METHOD: "       << ( requestMethod ? requestMethod : "" ) );
    // OSinfo( "SCRIPT_NAME: "  << ( scriptName ? scriptName : "" ) );
    // OSinfo( "PATH_INFO: "    << ( pathInfo ? pathInfo : "" ) );
    // OSinfo( "QUERY_STRING: " << ( queryString ? queryString : "" ) );
    // // OSinfo( "REQUEST_URI: "  << ( requestUri ? requestUri : "" ) );

    OSinfo( ( requestMethod ? requestMethod : "" ) << " " << ( scriptName ? scriptName : "" ) << " " << ( pathInfo ? pathInfo : "" ) << " " << ( queryString ? queryString : "" ) );
}


namespace {

    static inline void setenv_s( const char* param, const FCGX_Request& request )
    {
        auto* val = FCGX_GetParam( param, request.envp );

        setenv( param, val ? val : "", static_cast<bool>( val ) );
    }

}