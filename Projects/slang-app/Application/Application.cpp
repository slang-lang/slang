
// Header
#include "Application.h"

// Library includes
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <sys/wait.h>
#ifdef _WIN32
#    include <direct.h>
#    define GetCurrentDir _getcwd
#else
#    include <unistd.h>
#    define GetCurrentDir getcwd
#endif
#include <fcgiapp.h>

// Project includes
#include <Common/Consts.h>
#include <Common/Service.h>
#include <Core/Common/Exceptions.h>
#include <Core/Common/Types.h>
#include <Core/Runtime/Parameter.h>
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

} // namespace


namespace Slang {


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
        const pid_t pid = fork();

        if ( pid == 0 ) {
            bool requestHandled{ false };

            const std::string servicePath{ FCGX_GetParam( "PATH_INFO", request.envp ) };

            if ( servicePath.empty() ) {
                if ( mSettings.DefaultService ) {
                    requestHandled = mSettings.DefaultService->handleRequest( request );
                }
            }
            else {
                OSdebug( "Looking up service '" + servicePath + "'" );

                for ( auto* service : mSettings.Services ) {
                    if ( service->getPath() == servicePath ) {
                        requestHandled = service->handleRequest( request );
                        break;
                    }
                }
            }

            if ( !requestHandled ) {
                OSwarn( "Service '" << servicePath << "' not found" );

                handle_not_found( request.out );
            }

            FCGX_Finish_r( &request );
            exit( 0 );
        }
        else {
            waitpid( pid, nullptr, 0 );
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
        if ( mSettings.CurrentFolder[ mSettings.CurrentFolder.size() - 1 ] != '/' ) {
            mSettings.CurrentFolder += '/';
        }
    }

    // require a trailing slash
    if ( mSettings.LibraryFolder[ mSettings.LibraryFolder.size() - 1 ] != '/' ) {
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
    std::cout << "Usage: slang-app [ args... ]" << '\n';
    std::cout << '\n';
    std::cout << "--debug                    Show debug information" << '\n';
    std::cout << "-f | --file <file>         Parse and execute <file>" << '\n';
    std::cout << "-h | --help                This help" << '\n';
    std::cout << "-l | --library <library>   Library root path" << '\n';
    std::cout << "-v | --verbose             Verbose output" << '\n';
    std::cout << "--version                  Version information" << '\n';
    std::cout << '\n';
}

void Application::printVersion()
{
    std::cout << PRODUCT_NAME << " Application Server " << PRODUCT_VERSION << " (cli) " << '\n';
    std::cout << COPYRIGHT << '\n';
    std::cout << '\n';
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
                    std::cout << "invalid number of parameters provided!" << '\n';

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
                    std::cout << "invalid number of parameters provided!" << '\n';

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


} // namespace Slang


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
        const std::string data( ( std::istreambuf_iterator<char>( stream ) ), std::istreambuf_iterator<char>() );    // read stream
        stream.close();

        Json::Reader reader;
        reader.parse( data, result );
    }

} // namespace
