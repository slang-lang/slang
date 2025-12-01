
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
#include <Core/Common/Types.h>
#include <Core/VirtualMachine/Controller.h>
#include <Core/VirtualMachine/VirtualMachine.h>
#include <Core/Consts.h>
#include <Core/Defines.h>
#include <Core/Version.h>
#include <LIBC/Extension.h>
#include <Logger/StdOutLogger.h>
#include <System/SystemExtension.h>
#include <Tools/Files.h>
#include <Tools/Strings.h>
#include <Utils.h>

// Namespace declarations


namespace {

    // bool contains( const StringList& list, const std::string& value );
    // void execute( const std::string& command, bool debug = false );
    // size_t findCaseInsensitive( std::string data, std::string toSearch, size_t pos = 0 );
    bool isLocalLibrary();
    void readJsonFile( const std::string& filename, Json::Value& result );
    // void storeConfig();
    // void writeJsonFile( const std::string& filename, Json::Value& result );

    // void handle_hello( FCGX_Stream *out );
    // void handle_data( FCGX_Stream *out );
    void handle_not_found( FCGX_Stream *out );


    Utils::Common::StdOutLogger mLogger;
    Slang::StringList mParameters;
    Settings mSettings;

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
    OSdebug( "exec()" );

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

                // Dispatch based on path
                for ( auto* service : mSettings.Services ) {
                    OSdebug( "Service path: '" + service->getPath() + "'" );
                    OSdebug( "Request path: '" + servicePath + "'" );

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

    processParameters( argc, argv );

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
    // override library folder if our current folder is a library
    if ( isLocalLibrary() ) {
        mSettings.LibraryFolder = mSettings.CurrentFolder;
    }

    mVirtualMachine = new VirtualMachine();

    // add extensions
    #ifdef USE_SYSTEM_EXTENSION
    mVirtualMachine->addExtension( new Slang::Extensions::System::SystemExtension() );
    mVirtualMachine->addExtension( new Slang::Extensions::LIBC::Extension() );
    #endif

    mVirtualMachine->addLibraryFolder( mSettings.CurrentFolder );
    mVirtualMachine->init();

    //mVirtualMachine->printLibraryFolders();
    //mVirtualMachine->printExtensions();

    loadConfig();
}

void Application::loadConfig()
{
    OSdebug( "Loading configuration" );

    readJsonFile( mSettings.LibraryFolder + CONFIG_SERVER, mSettings.Config );

    // TODO: Implement configuration loading

    loadServices();
}

void Application::loadServices()
{
    if ( !mSettings.Config.isMember( "script" ) ) {
        mSettings.Config[ "script" ] = Json::Value();
    }
    if ( !mSettings.Config.isMember( "services" ) ) {
        mSettings.Config[ "services" ] = Json::Value();
    }

    mSettings.Script = mSettings.Config[ "script" ].asString();
    OSdebug( "Loading script '" + mSettings.Script + "'" );

    mScript = mVirtualMachine->createScriptFromFile( mSettings.Script );

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
    std::cout << "help                       Print command usage info" << std::endl;
    std::cout << "--verbose                  Verbose output" << std::endl;
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
    if ( argc > 1 ) {
        std::string arg1 = argv[ 1 ];

        if ( Utils::Tools::StringCompare( arg1, "help" ) ) {
            printUsage();
            exit( 0 );
        }
        else if ( Utils::Tools::StringCompare( arg1, "--version" ) ) {
            printVersion();
            exit( 0 );
        }
    }

    for ( int i = 2; i < argc; ++i ) {
        if ( Utils::Tools::StringCompare( argv[ i ], "--verbose" ) ) {
            mSettings.Verbose = true;
        }
        else {
            mParameters.emplace_back( argv[ i ] );
        }
    }
}


}


namespace {

// bool contains( const StringList& list, const std::string& value )
// {
//     for ( const auto& it : list ) {
//         if ( it == value ) {
//             return true;
//         }
//     }

//     return false;
// }

// void execute( const std::string& command, bool debug )
// {
//     if ( debug ) {
//         std::cout << command << std::endl;
//     }

//     auto result = system( command.c_str() );
//     ( void )result;
// }

// /*
//  * Find Case Insensitive Sub String in a given substring
//  */
// size_t findCaseInsensitive( std::string data, std::string toSearch, size_t pos )
// {
//     // Convert complete given String to lower case
//     std::transform( data.begin(), data.end(), data.begin(), ::tolower );
//     // Convert complete given Sub String to lower case
//     std::transform( toSearch.begin(), toSearch.end(), toSearch.begin(), ::tolower );
//     // Find sub string in given string
//     return data.find( toSearch, pos );
// }

bool isLocalLibrary()
{
    return Utils::Tools::Files::exists( mSettings.CurrentFolder + CONFIG_SERVER );
}

void readJsonFile( const std::string& filename, Json::Value& result )
{
    // load contents of filename into Json::Value

    std::fstream stream;
    stream.open( filename.c_str(), std::ios::in );    // open for reading
    std::string data( ( std::istreambuf_iterator<char>( stream ) ), std::istreambuf_iterator<char>() );    // read stream
    stream.close();

    Json::Reader reader;
    reader.parse( data, result );
}

// void storeConfig()
// {
//     // write json config to file
//     writeJsonFile( mSettings.LibraryFolder + CONFIG_SERVER, mSettings.Config );
// }

// void writeJsonFile( const std::string& filename, Json::Value& result )
// {
//     // write contents of Json::Value into filename

//     Json::StyledWriter writer;
//     std::string data = writer.write( result );

//     std::fstream stream;
//     stream.open( filename.c_str(), std::ios::out );    // open file for writing
//     stream.write( data.c_str(), data.size() );
//     stream.close();
// }

// void handle_hello( FCGX_Stream *out )
// {
//     FCGX_FPrintF(out, "Content-Type: text/plain\r\n\r\n");
//     FCGX_FPrintF(out, "Hello from /hello endpoint!\n");
// }

// void handle_data( FCGX_Stream *out )
// {
//     FCGX_FPrintF(out, "Content-Type: application/json\r\n\r\n");
//     FCGX_FPrintF(out, "{\"status\": \"ok\", \"data\": 42}\n");
// }

void handle_not_found( FCGX_Stream *out )
{
    FCGX_FPrintF(out, "Status: 404 Not Found\r\n");
    FCGX_FPrintF(out, "Content-Type: text/plain\r\n\r\n");
    FCGX_FPrintF(out, "404 - Endpoint not found\n");
}

}
