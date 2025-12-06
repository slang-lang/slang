
// Header
#include "Application.h"

// Library includes
// #include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#ifdef _WIN32
#    include <direct.h>
#    define GetCurrentDir _getcwd
#else
#    include <dirent.h>
#    include <unistd.h>
#    define GetCurrentDir getcwd
#endif
#include <fcgiapp.h>

// Project includes
#include <Common/Consts.h>
#include <Common/Service.h>
#include <Core/Common/Exceptions.h>
#include <Core/Common/Parameter.h>
#include <Core/Common/Types.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Consts.h>
#include <Core/Defines.h>
#include <Core/Version.h>
#include <LIBC/Extension.h>
#include <Logger/Logger.h>
#include <System/SystemExtension.h>
#include <Tools/Strings.h>
#include <Utils.h>

// Namespace declarations


namespace {

    void handle_not_found( FCGX_Stream *out );
    void readJsonFile( const std::string& filename, Json::Value& result );

    Slang::StringSet mLibraryFolders;
    Slang::ParameterList mParameters;
    bool mPrintDebugInfo{ false };

}


namespace Slang {


Application::Application()
{
}

Application::~Application()
{
    deinit();
}

void Application::deinit()
{
    for ( auto& service : mSettings.Services ) {
        delete service;
    }

    delete mSettings.DefaultService;
}

int Application::exec()
{
    FCGX_Request request;
    FCGX_Init();
    FCGX_InitRequest( &request, 0, 0 );

    while( FCGX_Accept_r( &request ) == 0 ) {
        pid_t pid = fork();

        if ( pid == 0 ) {
            bool requestHandled{false};

            char* path = FCGX_GetParam( "PATH_INFO", request.envp );
            if ( path != NULL ) {
                auto servicePath = std::string( path );

                OSdebug( "Looking up service '" + servicePath + "'" );

                for ( auto* service : mSettings.Services ) {
                    if ( service->getPath() == servicePath ) {
                        requestHandled = service->handleRequest( request );
                        break;
                    }
                }

                if ( !requestHandled ) {
                    OSwarn( "Service '" << servicePath << "' not found" );

                    handle_not_found( request.out );
                }
            }
            else {
                if ( mSettings.DefaultService ) {
                    mSettings.DefaultService->handleRequest( request );
                }
                else {
                    OSwarn( "No default service configured" );

                    handle_not_found( request.out );
                }
            }

            FCGX_Finish_r( &request );
            exit( 0 );
        }
        else {
            waitpid( pid, NULL, 0 );
        }
    }

    return 0;
}

void Application::init( int argc, const char* argv[] )
{
    OSdebug( "Initializing application" );

    {   // set library home path
        const char* homepath = getenv( Slang::SLANG_LIBRARY );
        if ( homepath ) {
            auto path = std::string( homepath );

            // only read first entry
            if ( !path.empty() ) {
                std::string left;
                std::string right;

                Utils::Tools::splitBy( path, PATH_SEPARATOR, left, right );

                mSettings.LibraryFolder = left;
            }
        }
        else {
            // use fallback directory
            mSettings.LibraryFolder = SHARED_LIBRARY_DIRECTORY;
        }
    }

    {   // set current folder
        char currentPath[ FILENAME_MAX ];
        if ( !GetCurrentDir( currentPath, sizeof( currentPath ) ) )  {
            throw Slang::Common::Exceptions::Exception( "invalid current directory!" );
        }

        mSettings.CurrentFolder = std::string( currentPath );

        // require a trailing slash
        if ( mSettings.CurrentFolder[ sizeof( mSettings.CurrentFolder ) - 1 ] != '/' ) {
            mSettings.CurrentFolder += '/';
        }
    }

    // require a trailing slash
    if ( mSettings.LibraryFolder[ sizeof( mSettings.LibraryFolder ) - 1 ] != '/' ) {
        mSettings.LibraryFolder += '/';
    }

    processParameters( argc, argv );

    // add extensions
    #ifdef USE_SYSTEM_EXTENSION
    mVirtualMachine.addExtension( new Slang::Extensions::System::SystemExtension() );
    mVirtualMachine.addExtension( new Slang::Extensions::LIBC::Extension() );
    #endif

    mVirtualMachine.addLibraryFolder( mSettings.CurrentFolder );
    mVirtualMachine.addLibraryFolder( mSettings.LibraryFolder );

	for ( const auto& library : mLibraryFolders ) {
		mVirtualMachine.addLibraryFolder( library );
	}

    mVirtualMachine.init();

    if ( mPrintDebugInfo ) {
        mVirtualMachine.printLibraryFolders();
        mVirtualMachine.printExtensions();
    }

    mScript = mVirtualMachine.createScriptFromFile( mSettings.Script );

    Runtime::Object result;
    mVirtualMachine.run( mScript, mParameters, &result );

    loadConfig();
}

void Application::loadConfig()
{
    OSdebug( "Loading configuration" );

    readJsonFile( mSettings.CurrentFolder + CONFIG_SERVER, mSettings.Config );

    loadServices();
}

void Application::loadServices()
{
    // load service paths from config
    auto services = mSettings.Config[ "services" ];
    for ( const auto& serviceName : services.getMemberNames() ) {
        auto service = services[ serviceName ];

        OSdebug( "Loading service '" + serviceName + "' with service path '" + service.asString() + "'" );

        mSettings.Services.push_back(
            new Service( serviceName, service.asString(), mScript )
        );
    }

    if ( mSettings.Config.isMember( "default" ) ) {
        mSettings.DefaultService = new Service(
            "default", mSettings.Config[ "default" ].asString(), mScript
        );
    }
}

void Application::printUsage()
{
    std::cout << "Usage: slang-app [ args... ]" << std::endl;
    std::cout << std::endl;
    std::cout << "--debug                    Show debug information" << std::endl;
    std::cout << "-f | --file <file>         Parse and execute <file>" << std::endl;
    std::cout << "-h | --help                This help" << std::endl;
    std::cout << "-l | --library <library>   Library root path" << std::endl;
    std::cout << "-v | --verbose             Verbose output" << std::endl;
    std::cout << "--version                  Version information" << std::endl;
    std::cout << std::endl;
}

void Application::printVersion()
{
    std::cout << PRODUCT_NAME << " Application Server " << PRODUCT_VERSION << " (cli) " << std::endl;
    std::cout << COPYRIGHT << std::endl;
    std::cout << std::endl;
}

void Application::processParameters( int argc, const char* argv[] )
{
    StringList params;
    std::string paramStr;

    bool scriptParams = false;

    for ( int i = 1; i < argc; i++ ) {
        if ( !scriptParams ) {
            if ( Utils::Tools::StringCompare( argv[i], "--debug" ) ) {
                mPrintDebugInfo = true;
            }
            else if ( Utils::Tools::StringCompare( argv[i], "-f" ) || Utils::Tools::StringCompare( argv[i], "--file" ) ) {
                if ( argc <= ++i ) {
                    std::cout << "invalid number of parameters provided!" << std::endl;

                    exit( -1 );
                }

                mSettings.Script = argv[i];
                params.push_back( mSettings.Script );
                paramStr += mSettings.Script;

                // all parameters that follow are designated for our script
                scriptParams = true;
            }
            else if ( Utils::Tools::StringCompare( argv[i], "-h" ) || Utils::Tools::StringCompare( argv[i], "--help" ) ) {
                printUsage();
                exit( 0 );
            }
            else if ( Utils::Tools::StringCompare( argv[i], "-l" ) || Utils::Tools::StringCompare( argv[i], "--library" ) ) {
                if ( argc <= ++i ) {
                    std::cout << "invalid number of parameters provided!" << std::endl;

                    exit( -1 );
                }

                mLibraryFolders.insert( argv[i] );
            }
            else if ( Utils::Tools::StringCompare( argv[i], "-v" ) || Utils::Tools::StringCompare( argv[i], "--verbose" ) ) {
                mSettings.Verbose = true;
            }
            else if ( Utils::Tools::StringCompare( argv[i], "--version" ) ) {
                printVersion();
                exit( 0 );
            }
            else if ( mSettings.Script.empty() ){
                mSettings.Script = argv[i];
                params.push_back( mSettings.Script );
                paramStr += mSettings.Script;

                // all parameters that follow are designated for our script
                scriptParams = true;
            }
        }
        else {
            params.emplace_back( argv[i] );
            paramStr += "\n";
            paramStr += argv[i];
        }
    }

    mParameters.push_back( Parameter::CreateRuntime( Runtime::Int32Type::TYPENAME, static_cast<int32_t>( params.size() ) ) );
    mParameters.push_back( Parameter::CreateRuntime( Runtime::StringType::TYPENAME, paramStr ) );
}


}


namespace {

    void handle_not_found( FCGX_Stream *out )
    {
        FCGX_FPrintF( out, "Status: 404 Not Found\r\n" );
        FCGX_FPrintF( out, "Content-Type: text/plain\r\n\r\n" );
        FCGX_FPrintF( out, "404 - Endpoint not found\n" );
    }

    void readJsonFile( const std::string& filename, Json::Value& result )
    {
        std::fstream stream;
        stream.open( filename.c_str(), std::ios::in );    // open for reading
        std::string data( ( std::istreambuf_iterator<char>( stream ) ), std::istreambuf_iterator<char>() );    // read stream
        stream.close();

        Json::Reader reader;
        reader.parse( data, result );
    }

}
