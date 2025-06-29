
// Header
#include "Application.h"

// Library includes
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sys/utsname.h>
#ifdef _WIN32
#    include <direct.h>
#    define GetCurrentDir _getcwd
#else
#    include <dirent.h>
#    include <unistd.h>
#    define GetCurrentDir getcwd
#endif
#include <curl/curl.h>

// Project includes
#include <Common/Consts.h>
#include <Common/Module.h>
#include <Common/Repository.h>
#include <Common/Restriction.h>
#include <Core/Common/Exceptions.h>
#include <Core/Common/Types.h>
#include <Core/Consts.h>
#include <Core/Defines.h>
#include <Core/Version.h>
#include <Logger/StdOutLogger.h>
#include <Tools/Files.h>
#include <Tools/Strings.h>
#include <Utils.h>

// Namespace declarations
using namespace Slang;


namespace {

    void checkOutdatedModules( Modules& outdatedModules );
    bool checkRestrictions( const Module& module );
    void cleanCache();
    void collectLocalModuleData();
    Module collectModuleData( const std::string& path, const std::string& filename );
    bool contains( const StringList& list, const std::string& value );
    void create( const StringList& params );
    void createLocalLibrary();
    bool download( const std::string& url, const std::string& target, bool allowCleanup = true );
    void execute( const std::string& command, bool debug = false );
    size_t findCaseInsensitive( std::string data, std::string toSearch, size_t pos = 0 );
    void info( const StringList& params );
    void install( const StringList& params );
    void installModule( const std::string& repo, const std::string& module );
    bool isLocalLibrary();
    void list();
    void loadConfig();
    void loadRestrictions();
    void prepareModuleInstallation( const std::string& repo, const Module& installModule );
    bool prepareRemoteRepository();
    void processRestrictions( const StringList& params );
    void purge( const StringList& params );
    size_t push( const StringList& params );
    void readJsonFile( const std::string& filename, Json::Value& result );
    void remove( const StringList& params );
    void removeRestriction( const std::string& module );
    void removeRestriction( const StringList& params );
    void search( const StringList& params );
    void storeConfig();
    void writeJsonFile( const std::string& filename, Json::Value& result );
    void update();
    size_t upload( const std::string& filename, const std::string& url, const std::string& contentType );
    void upgrade( const StringList& params );


    StringList mDownloadedFiles;
    Repository mLocalRepository( "local" );
    Utils::Common::StdOutLogger mLogger;
    Repository mMissingDependencies( "missing" );
    StringList mParameters;
    Repository mRemoteRepository;
    Settings mSettings;

}


namespace Slang {


Application::~Application()
{
    deinit();
}

void Application::deinit()
{
    // put de-initialization stuff here

    // clean up curl library
    curl_global_cleanup();
}

int Application::exec()
{
    switch ( mSettings.Action ) {
        case Create:             create( mParameters ); break;
        case CreateLocalLibrary: createLocalLibrary(); break;
        case Help:               printUsage( mParameters ); break;
        case Info:               info( mParameters ); break;
        case Install:            install( mParameters ); break;
        case List:               list(); break;
        case None:               /* nothing to do here*/ break;
        case Purge:              purge( mParameters ); break;
        case Push:               push( mParameters ); break;
        case Remove:             remove( mParameters ); break;
        case Restrict:           processRestrictions( mParameters ); break;
        case Search:             search( mParameters ); break;
        case Update:             update(); break;
        case Upgrade:            upgrade( mParameters ); break;
        case Version:            printVersion(); break;
    }

    cleanCache();

    return 0;
}

void Application::init( int argc, const char* argv[] )
{
    processParameters( argc, argv );

    struct utsname name{};

    if ( uname( &name ) == -1 ) {
        std::cerr << "!!! Cannot get system name" << std::endl;
        exit( ERROR_SYSTEM );
    }

    mSettings.Architecture = name.machine;

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
    // override library folder if our current folder is a library
    if ( isLocalLibrary() ) {
        mSettings.LibraryFolder = mSettings.CurrentFolder;
    }

    loadConfig();

    // initialize curl library
    curl_global_init( CURL_GLOBAL_ALL );
}

void Application::printUsage( const StringList& params )
{
    if ( !params.empty() ) {
        const auto& param = params.front();

        if ( param == "create" ) {
            std::cout << "Usage: slang-pkg create <module>" << std::endl;
            std::cout << std::endl;
            std::cout << "[Deprecated] Provide a single directory name to create a module from it. A module.json is required in this directory." << std::endl;
        }
        else if ( param == "help" ) {
            std::cout << "Usage: slang-pkg help [<command>]" << std::endl;
            std::cout << std::endl;
            std::cout << "Prints out the usage/info for a given command." << std::endl;
        }
        else if ( param == "info" ) {
            std::cout << "Usage: slang-pkg info <module> [<module> ...]" << std::endl;
            std::cout << std::endl;
            std::cout << "Retrieves information of given module[s]." << std::endl;
        }
        else if ( param == "install" ) {
            std::cout << "Usage: slang-pkg install <module> [<module> ...]" << std::endl;
            std::cout << std::endl;
            std::cout << "Downloads and installs given module[s] from remote repository into library folder." << std::endl;
        }
        else if ( param == "list" ) {
            std::cout << "Usage: slang-pkg list" << std::endl;
            std::cout << std::endl;
            std::cout << "Lists installed modules (including version number)." << std::endl;
        }
        else if ( param == "purge" ) {
            std::cout << "Usage: slang-pkg purge <module> [<module> ...]" << std::endl;
            std::cout << std::endl;
            std::cout << "Deletes installed module[s] and removes restrictions." << std::endl;
        }
        else if ( param == "push" ) {
            std::cout << "Usage: slang-pkg push <module> [<module> ...]" << std::endl;
            std::cout << std::endl;
            std::cout << "Creates a module and pushes it to the configured repository server." << std::endl;
        }
        else if ( param == "remove" ) {
            std::cout << "Usage: slang-pkg remove <module> [<module> ...]" << std::endl;
            std::cout << std::endl;
            std::cout << "Deletes installed module[s] without removing restrictions." << std::endl;
        }
        else if ( param == "restrict" ) {
            std::cout << "Usage: slang-pkg restrict <module> [ [<version_min>]:[<version_max>] ]" << std::endl;
            std::cout << std::endl;
            std::cout << "Adds or removes a restriction for a given module." << std::endl;
            std::cout << std::endl;
            std::cout << "Example to add a minimum version restriction without setting a maximum version:" << std::endl;
            std::cout << "    slang-pkg restrict System 0.1.0:" << std::endl;
        }
        else if ( param == "search" ) {
            std::cout << "Usage: slang-pkg search <text>" << std::endl;
            std::cout << std::endl;
            std::cout << "Searches the module cache for the given parameter." << std::endl;
        }
        else if ( param == "update" ) {
            std::cout << "Usage: slang-pkg update" << std::endl;
            std::cout << std::endl;
            std::cout << "Updates the module cache from the configured remote repository." << std::endl;
        }
        else if ( param == "upgrade" ) {
            std::cout << "Usage: slang-pkg upgrade <module> [<module> ...]" << std::endl;
            std::cout << std::endl;
            std::cout << "Upgrades outdated modules according to the currently set restrictions. Upgrades only the provided modules or, if no parameter is provided, upgrades all outdated modules." << std::endl;
        }
        else if ( param == "--locallibrary" ) {
            std::cout << "Usage: slang-pkg --locallibrary" << std::endl;
            std::cout << std::endl;
            std::cout << "Creates a library folder in the current folder which is used to install and update modules from a remote repository." << std::endl;
        }
        else if ( param == "--skip-dependencies" ) {
            std::cout << "Usage: slang-pkg --skip-dependencies <command>" << std::endl;
            std::cout << std::endl;
            std::cout << "Flag to indicate if dependencies should be ignored while installing or removing/purging modules." << std::endl;
        }
        else if ( param == "--verbose" ) {
            std::cout << "Usage: slang-pkg <command> --verbose" << std::endl;
            std::cout << std::endl;
            std::cout << "Activates verbose output of given command, if supported." << std::endl;
        }
        else if ( param == "--version" ) {
            std::cout << "Usage: slang-pkg --version" << std::endl;
            std::cout << std::endl;
            std::cout << "Prints the version number of slang-pkg." << std::endl;
        }
        else {
            std::cerr << "!!! Unknown command '" << param << "' provided" << std::endl;
        }

        std::cout << std::endl;
        return;
    }

    std::cout << "Usage: slang-pkg [ args... ]" << std::endl;
    std::cout << std::endl;
    std::cout << "create                     Create a new module from a given directory" << std::endl;
    std::cout << "help                       Print command usage info" << std::endl;
    std::cout << "info                       Print information about requested module" << std::endl;
    std::cout << "install                    Install new module" << std::endl;
    std::cout << "list                       List all installed modules" << std::endl;
    std::cout << "purge                      Remove an installed module and all of its configuration" << std::endl;
    std::cout << "push                       Push module(s) to repository server" << std::endl;
    std::cout << "remove                     Remove an installed module" << std::endl;
    std::cout << "restrict                   Add version restriction for module" << std::endl;
    std::cout << "search                     Search for a module" << std::endl;
    std::cout << "update                     Update repository indices" << std::endl;
    std::cout << "upgrade                    Upgrade outdated modules" << std::endl;
    std::cout << "--locallibrary             Use current directory as library" << std::endl;
    std::cout << "--skip-dependencies        Skip dependencies while installing or removing modules" << std::endl;
    std::cout << "--verbose                  Verbose output" << std::endl;
    std::cout << "--version                  Version information" << std::endl;
    std::cout << std::endl;
}

void Application::printVersion()
{
    std::cout << PRODUCT_NAME << " Dependency Manager " << PRODUCT_VERSION << " (cli) " << mSettings.Architecture << std::endl;
    std::cout << COPYRIGHT << std::endl;
    std::cout << std::endl;
}

void Application::processParameters( int argc, const char* argv[] )
{
    mSettings.Action = Help;

    if ( argc > 1 ) {
        std::string arg1 = argv[ 1 ];

        if ( Utils::Tools::StringCompare( arg1, "create" ) ) {
            mSettings.Action = Create;
        }
        else if ( Utils::Tools::StringCompare( arg1, "help" ) ) {
            mSettings.Action = Help;
        }
        else if ( Utils::Tools::StringCompare( arg1, "info" ) ) {
            mSettings.Action = Info;
        }
        else if ( Utils::Tools::StringCompare( arg1, "install" ) ) {
            mSettings.Action = Install;
        }
        else if ( Utils::Tools::StringCompare( arg1, "list" ) ) {
            mSettings.Action = List;
        }
        else if ( Utils::Tools::StringCompare( arg1, "purge" ) ) {
            mSettings.Action = Purge;
        }
        else if ( Utils::Tools::StringCompare( arg1, "push" ) ) {
            mSettings.Action = Push;
        }
        else if ( Utils::Tools::StringCompare( arg1, "remove" ) ) {
            mSettings.Action = Remove;
        }
        else if ( Utils::Tools::StringCompare( arg1, "restrict" ) ) {
            mSettings.Action = Restrict;
        }
        else if ( Utils::Tools::StringCompare( arg1, "search" ) ) {
            mSettings.Action = Search;
        }
        else if ( Utils::Tools::StringCompare( arg1, "update" ) ) {
            mSettings.Action = Update;
        }
        else if ( Utils::Tools::StringCompare( arg1, "upgrade" ) ) {
            mSettings.Action = Upgrade;
        }
        else if ( Utils::Tools::StringCompare( arg1, "--locallibrary" ) ) {
            mSettings.Action = CreateLocalLibrary;
        }
        else if ( Utils::Tools::StringCompare( arg1, "--version" ) ) {
            mSettings.Action = Version;
        }
    }

    for ( int i = 2; i < argc; ++i ) {
        if ( Utils::Tools::StringCompare( argv[ i ], "--skip-dependencies" ) ) {
            mSettings.SkipDependencies = true;
        }
        else if ( Utils::Tools::StringCompare( argv[ i ], "--verbose" ) ) {
            mSettings.Verbose = true;
        }
        else {
            mParameters.emplace_back( argv[ i ] );
        }
    }
}


}


namespace {

size_t write_data( void *ptr, size_t size, size_t nmemb, void *stream )
{
    size_t written = fwrite( ptr, size, nmemb, (FILE*)stream );
    return written;
}

void checkOutdatedModules( Modules& outdatedModules )
{
    // compare new index.json with local module information:
    // find all folders in local <repo> folder and compare their corresponding <repo>/<module>/module.json [ version ] field
    // with the version in the index.json file

    auto local  = mLocalRepository.getModules();
    auto remote = mRemoteRepository.getModules();

    for ( const auto& localModule : local ) {
        for ( const auto& remoteModule : remote ) {
            if ( localModule.mShortName == remoteModule.mShortName && localModule.mVersion < remoteModule.mVersion ) {
                outdatedModules.insert( remoteModule );
            }
        }
    }
}

bool checkRestrictions( const Module& module )
{
    for ( const auto& mLocalRestriction : mSettings.LocalRestrictions ) {
        if ( mLocalRestriction.mModule == module.mShortName ) {
            // check minimal version
            if ( mLocalRestriction.mMinVersion.isValid() && module.mVersion < mLocalRestriction.mMinVersion ) {
                return false;
            }
            // check maximum version
            if ( mLocalRestriction.mMaxVersion.isValid() && mLocalRestriction.mMaxVersion < module.mVersion ) {
                return false;
            }
        }
    }

    return true;
}

void cleanCache()
{
    // delete all downloaded files from cache

#ifdef SLANG_DEBUG
    std::cout << "Cleaning cache..." << std::endl;
#endif

    for ( StringList::const_iterator it = mDownloadedFiles.begin(); it != mDownloadedFiles.end(); ++it ) {
        execute( "rm " + ( *it ) );
    }
}

void collectLocalModuleData()
{
    // iterate over all directories in the modules directory and collect all "module.json" files

    auto* dir = opendir( mSettings.LibraryFolder.c_str() );
    if ( !dir ) {
        std::cerr << "!!! Error while accessing modules directory '" << mSettings.LibraryFolder << "'" << std::endl;
        exit( ERROR_MODULE_DIRECTORY );
    }

    struct dirent* dirEntry = readdir( dir );

    // add Slang version as virtually installed module to force correct dependencies
    // {
    Module slang;
    slang.mArchitecture = mSettings.Architecture;
    slang.mDescription  = "Virtual module to prevent installation of modules that are not compatible with your version of the Slang interpreter";
    slang.mLongName     = PRODUCT_DESCRIPTION;
    slang.mShortName    = PRODUCT_NAME;
    slang.mVersion      = PRODUCT_VERSION;

    mLocalRepository.addModule( slang );
    // }

    while ( dirEntry ) {
        if ( dirEntry->d_type == DT_DIR ) {
            std::string entry( dirEntry->d_name );

            if ( entry != "." && entry != ".." ) {
                auto filename = "module.json";
                auto path     = mSettings.LibraryFolder + entry + "/";

                if ( Utils::Tools::Files::exists( path + filename ) ) {
                    mLocalRepository.addModule(
                        collectModuleData( path, filename )
                    );
                }
            }
        }

        dirEntry = readdir( dir );
    }

    closedir( dir );
}

Module collectModuleData( const std::string& path, const std::string& filename )
{
#ifdef SLANG_DEBUG
    std::cout << "Collecting module data from \"" << path << "\"" << std::endl;
#endif

    Json::Value config;
    readJsonFile( path + "/" + filename, config );

    Module module;
    if ( !module.loadFromJson( config ) ) {
        std::cerr << "!!! Invalid module data in file '" << filename << "'" << std::endl;
        return module;
    }

    module.mTarget.Directory = path;

    return module;
}

bool contains( const StringList& list, const std::string& value )
{
    for ( const auto& it : list ) {
        if ( it == value ) {
            return true;
        }
    }

    return false;
}

/*
 * creates a module package ( "<module>.json", "<module>_<version>.tar.gz" )
 * does NOT upload the package to a repository
 */
void create( const StringList& params )
{
    // ( 1 ) collect module information from given "<directory>/module.json"
    // ( 2 ) create "<module>_<version>.json", "<module>_<version>.tar.gz"

    if ( params.empty() || params.size() != 1 ) {
        std::cerr << "!!! Invalid number of parameters" << std::endl;
        return;
    }

    // TODO: module name is not allowed to end with '/'
    const std::string& path     = params.front();
    const std::string& filename = "module.json";

    auto module = collectModuleData( path, filename );

    {   // create version specific module information ( "<module>_<version>.json" )
        std::cout << "Creating module information \"" << module.mShortName + FILE_VERSION_SEPARATOR + module.mVersion.toString() + ".json\"" << std::endl;

        execute( "cp " + path + "/" + filename + " " + module.mShortName + FILE_VERSION_SEPARATOR + module.mVersion.toString() + ".json" );
    }
    {   // create package ( "<module>_<version>.tar.gz" )
        std::cout << "Creating module package \"" << module.mShortName + FILE_VERSION_SEPARATOR + module.mVersion.toString() + ".tar.gz\"" << std::endl;

        execute( "tar --exclude-vcs -cjf " + module.mShortName + FILE_VERSION_SEPARATOR + module.mVersion.toString() + ".tar.gz " + path );
    }
}

void createLocalLibrary()
{
    std::cout << "Preparing current directory for slang-pkg..." << std::endl;

    // .slang folder for all repository configs etc.
    if ( !Utils::Tools::Files::exists( mSettings.CurrentFolder + CONFIG_FOLDER ) ) {
        // create folder for library config
        execute( "mkdir " + mSettings.CurrentFolder + CONFIG_FOLDER );
    }

    // .slang/apps/ folder to copy symlinks to
    if ( !Utils::Tools::Files::exists( mSettings.CurrentFolder + CONFIG_APPS ) ) {
        // create folder for library config
        execute( "mkdir " + mSettings.CurrentFolder + CONFIG_APPS );
    }

    // .slang/cache/modules" folder
    if ( !Utils::Tools::Files::exists( mSettings.CurrentFolder + CONFIG_CACHE_MODULES ) ) {
        execute( "mkdir -p " + mSettings.CurrentFolder + CONFIG_CACHE_MODULES );
    }

    // .slang/cache/repositories" folder
    if ( !Utils::Tools::Files::exists( mSettings.CurrentFolder + CONFIG_CACHE_REPOSITORIES ) ) {
        execute( "mkdir -p " + mSettings.CurrentFolder + CONFIG_CACHE_REPOSITORIES );
    }

    if ( !Utils::Tools::Files::exists( mSettings.CurrentFolder + CONFIG_FILE ) ) {
        Json::Value repository;
        repository[ "authentication" ] = "Bearer";    // user needs to fill in his preferred method of authentication (Basic|Bearer)
        repository[ "authorization" ]  = "<get-your-token-from-https://modules.slang-lang.org>";   // user needs to fill in his authorization token here
        repository[ "name" ]           = REMOTE_REPOSITORY_NAME;
        repository[ "url" ]            = REMOTE_REPOSITORY_URL;

        Json::Value config;
        config[ "repository" ]   = repository;
        config[ "restrictions" ] = Json::Value();

        // write json config to file
        writeJsonFile( mSettings.CurrentFolder + CONFIG_FILE, config );
    }
}

bool download( const std::string& url, const std::string& target, bool allowCleanup )
{
#ifdef SLANG_DEBUG
    std::cout << "Downloading \"" << url << "\" => \"" << target << "\"" << std::endl;
#endif

    CURL *curl_handle;
    FILE *pagefile;
    bool result = false;

    /* init the curl session */
    curl_handle = curl_easy_init();

    /* disable progress meter, set to 0L to enable and disable debug output */
    curl_easy_setopt( curl_handle, CURLOPT_NOPROGRESS, 1L );

    /* Switch on full protocol/debug output while testing */
    curl_easy_setopt( curl_handle, CURLOPT_VERBOSE, mSettings.Verbose );

    /* set URL to get here */
    curl_easy_setopt( curl_handle, CURLOPT_URL, url.c_str() );

    /* send all data to this function  */
    curl_easy_setopt( curl_handle, CURLOPT_WRITEFUNCTION, write_data );

    /* open the file */
    pagefile = fopen( target.c_str(), "wb" );
    if ( pagefile ) {
        /* write the page body to this file handle */
        curl_easy_setopt( curl_handle, CURLOPT_WRITEDATA, pagefile );

        /* get it! */
        curl_easy_perform( curl_handle );

        /* close the header file */
        fclose( pagefile );

        if ( allowCleanup ) {
            mDownloadedFiles.push_back( target );
        }

        result = true;
    }

    /* cleanup curl stuff */
    curl_easy_cleanup( curl_handle );

    return result;
}

void execute( const std::string& command, bool debug )
{
    if ( debug ) {
        std::cout << command << std::endl;
    }

    auto result = system( command.c_str() );
    ( void )result;
}

/*
 * Find Case Insensitive Sub String in a given substring
 */
size_t findCaseInsensitive( std::string data, std::string toSearch, size_t pos )
{
    // Convert complete given String to lower case
    std::transform( data.begin(), data.end(), data.begin(), ::tolower );
    // Convert complete given Sub String to lower case
    std::transform( toSearch.begin(), toSearch.end(), toSearch.begin(), ::tolower );
    // Find sub string in given string
    return data.find( toSearch, pos );
}

void info( const StringList& params )
{
    // ( 1 ) collect local module data
    // ( 2 ) update remote repository data
    // ( 3 ) print module information for requested module

    if ( params.empty() /*|| params.size() != 1*/ ) {
        std::cerr << "!!! Invalid number of parameters" << std::endl;
        return;
    }

    for ( auto paramIt = params.cbegin(); paramIt != params.cend(); ++paramIt ) {
        if ( paramIt != params.cbegin() ) {
            std::cout << std::endl;
        }

        collectLocalModuleData();
        if ( !prepareRemoteRepository() ) {
            update();
        }

        std::string moduleName;
        std::string moduleVersion;

        Utils::Tools::splitBy( ( *paramIt ), VERSION_SEPARATOR, moduleName, moduleVersion );

        if ( moduleVersion.empty() ) {
            Module tmpModule;

            if ( mRemoteRepository.getModule( moduleName, tmpModule ) ) {
                moduleVersion = tmpModule.mVersion.toString();
            }
        }

        bool found{ false };
        Module infoModule;

        {   // look up module in local repository
            auto localModules = mLocalRepository.getModules();

            for ( const auto& localIt : localModules ) {
                if ( localIt.mShortName == moduleName && localIt.mVersion == moduleVersion ) {
                    found = true;

                    infoModule = localIt;
                }
            }
        }

        if ( !found ) {    // lookup module in remote repository
            auto path         = mSettings.LibraryFolder + CONFIG_CACHE_MODULES;
            auto filename     = moduleName + ".json";
            auto moduleConfig = path + filename;
            auto url          = mRemoteRepository.getURL() + MODULES + moduleName + FILE_VERSION_SEPARATOR + moduleVersion + ".json";

            auto result = download( url, moduleConfig );
            if ( result ) {
                auto tmpModule = collectModuleData( path, filename );
                if ( tmpModule.isValid() ) {
                    found = true;

                    infoModule = tmpModule;
                }
            }
        }

        if ( found ) {    // print out module information if found
            std::cout << infoModule.mShortName << VERSION_SEPARATOR << infoModule.mVersion.toString() << " - " << infoModule.mLongName << std::endl;
            std::cout << infoModule.mDescription << std::endl;
            std::cout << std::endl;
            std::cout << "Dependencies:" << std::endl;

            if ( infoModule.mDependencies.empty() ) {
                std::cout << "<none>" << std::endl;
            }
            else {
                for ( const auto& dependency : infoModule.mDependencies ) {
                    std::cout << dependency.Module << "\t\t";
                    std::cout << "min: " << ( dependency.MinVersion.empty() ? "<not set>" : dependency.MinVersion );
                    std::cout << "\t\tmax: " << ( dependency.MaxVersion.empty() ? "<not set>" : dependency.MaxVersion );
                    std::cout << "\t\tsource: " << ( dependency.Source.empty() ? "<not set>" : dependency.Source );
                    std::cout << std::endl;
                }
            }
        }
        else {
            std::cerr << "!!! Requested module \"" << moduleName << "\" not found" << std::endl;
        }
    }
}

void install( const StringList& params )
{
    // ( 1 ) prepare dependencies
    // ( 2 ) install missing dependencies
    // ( 3 ) check if we don't violate any module restrictions
    // ( 4 ) install requested modules

    if ( params.empty() ) {
        std::cerr << "!!! Invalid number of parameters" << std::endl;
        return;
    }

    collectLocalModuleData();
    if ( !prepareRemoteRepository() ) {
        update();
    }

    std::cout << "Preparing dependencies..." << std::endl;

    bool forceVersion = false;

    for ( const auto& param : params ) {
        std::string moduleName;
        std::string source;
        std::string version;

        Utils::Tools::splitBy( param, VERSION_SEPARATOR, moduleName, version );

        if ( version.empty() ) {
            Module tmpModule;

            if ( mRemoteRepository.getModule( moduleName, tmpModule ) ) {
                source  = tmpModule.mSource;
                version = tmpModule.mVersion.toString();
            }
        }
        else {
            forceVersion = true;
        }

        prepareModuleInstallation( mRemoteRepository.getURL(), Module( moduleName, version, source ) );
    }

    bool allowInstall = true;

    // add all other requested modules to missing modules to prevent multiple installations of the same modules
    for ( const auto& param : params ) {
        std::string moduleName;
        std::string source;
        std::string version;

        Utils::Tools::splitBy( param, VERSION_SEPARATOR, moduleName, version );

        if ( version.empty() ) {
            Module tmpModule;

            if ( mRemoteRepository.getModule( moduleName, tmpModule ) ) {
                source = tmpModule.mSource;
                version = tmpModule.mVersion.toString();
            }
        }
        else {
            forceVersion = true;
        }

        Module missingModule( moduleName, version, source );

        if ( !checkRestrictions( missingModule ) ) {
            allowInstall = false;
            std::cout << "!!! Module " << missingModule.mShortName << "( " << missingModule.mVersion.toString() << " ) cannot be installed due to current module restrictions" << std::endl;
        }

        mMissingDependencies.addModule( missingModule );
    }

    if ( allowInstall ) {
        auto missing = mMissingDependencies.getModules();

        for ( const auto& moduleIt : missing ) {
            Module tmp;

            if ( mLocalRepository.getModule( moduleIt.mShortName, tmp ) ) {
                if ( !forceVersion && !( tmp.mVersion < moduleIt.mVersion ) ) {
                    std::cout << "Same or newer version ( " << tmp.mVersion.toString() << " vs " << moduleIt.mVersion.toString() << " ) of module \"" << moduleIt.mShortName << "\" already installed" << std::endl;
                    continue;
                }
            }

            installModule( mRemoteRepository.getURL(), moduleIt.mShortName );
        }
    }
}

void installModule( const std::string& repo, const std::string& module )
{
    std::cout << "Installing module \"" << module << "\" from \"" << repo << "\"..." << std::endl;

    auto moduleConfig = mSettings.LibraryFolder + CONFIG_CACHE_MODULES + module + ".json";

    if ( !Utils::Tools::Files::exists( moduleConfig ) ) {
        std::cerr << "!!! Module information missing for module \"" << module << "\"" << std::endl;
        return;
    }

    auto tmpModule = collectModuleData( mSettings.LibraryFolder + CONFIG_CACHE_MODULES, module + ".json" );

    Json::Value config;
    readJsonFile( moduleConfig, config );

    if ( !config.isMember( "target" ) ) {
        std::cerr << "!!! No target entry found in module information" << std::endl;
        return;
    }
    if ( !config[ "target" ].isMember( "type" ) ) {
        std::cerr << "!!! No type entry found in target module information" << std::endl;
        return;
    }

    std::string type = config[ "target" ][ "type" ].asString();
    std::string url;

    if ( type == "external" ) {
        // target is located on a different server
        url = config[ "target" ][ "url" ].asString();
    }
    else if ( type == "internal" ) {
        // target is located on our own server
        url = repo + MODULES + config[ "name_short" ].asString() + "/" + config[ "version" ].asString() + "/module.tar.gz";
    }
    else {
        std::cerr << "!!! invalid target type specified" << std::endl;
        return;
    }

    auto module_archive = mSettings.LibraryFolder + CONFIG_CACHE_MODULES + module + FILE_VERSION_SEPARATOR + config[ "version" ].asString() + ".tar.gz";

    auto result = download( url, module_archive );
    if ( !result ) {
        std::cerr << "!!! Failed to download target" << std::endl;
        return;
    }

    execute( "tar xf " + module_archive + " -C " + mSettings.LibraryFolder );

    for ( const std::string& file : tmpModule.mTarget.InstalledFiles ) {
        execute( CONFIG_SCRIPTS + "addLink.sh \"" + mSettings.LibraryFolder + "/" + module + "/" + file + "\" \"" + mSettings.LibraryFolder + "/" + CONFIG_APPS + "\"" );
    }
}

bool isLocalLibrary()
{
    return Utils::Tools::Files::exists( mSettings.CurrentFolder + CONFIG_FILE );
}

void list()
{
    collectLocalModuleData();

    auto local = mLocalRepository.getModules();

    for ( const auto& localIt : local ) {
        std::cout << localIt.mShortName << VERSION_SEPARATOR << localIt.mVersion.toString() << " - " << localIt.mLongName << std::endl;
    }

    std::cout << local.size() << " module(s) installed." << std::endl;
}

void loadConfig()
{
    readJsonFile( mSettings.LibraryFolder + CONFIG_FILE, mSettings.Config );

    if ( mSettings.Config.isMember( "repository" ) ) {
        auto& entry = mSettings.Config[ "repository" ];

        // authentication
        // {
        if ( !entry.isMember( "authentication" ) ) {
            // if no authentication key is present, silently create one
            entry[ "authentication" ] = Json::Value();
        }

        auto authentication = Repository::Authentication::None;   // default

        if ( entry[ "authentication" ].asString() == "Basic" ) {
            authentication = Repository::Authentication::Basic;   // not yet implemented on server, so don't use it yet
        }
        else if ( entry[ "authentication" ].asString() == "Bearer" ) {
            authentication = Repository::Authentication::Bearer;   // preferred way of authentication
        }
        // }

        // authorization
        // {
        if ( !entry.isMember( "authorization" ) ) {
            // if no authorization key is present, silently create one
            entry[ "authorization" ] = Json::Value();
        }

        auto authorization = entry[ "authorization" ].asString();
        // }

        // repository name
        // {
        if ( !entry.isMember( "name" ) ) {
            std::cerr << "!!! Invalid repository name" << std::endl;
            return;
        }

        auto name = entry[ "name" ].asString();
        // }

        // repository URL
        // {
        if ( !entry.isMember( "url" ) ) {
            std::cerr << "!!! Invalid repository url" << std::endl;
            return;
        }

        auto url = entry[ "url" ].asString();

        // make sure the URL ends with a slash
        if ( url[ url.size() - 1 ] != '/' ) {
            url += '/';
        }
        // }

        Repository repository( name );
        repository.setAuthentication( authentication );
        repository.setAuthorization( authorization );
        repository.setURL( url );

        mRemoteRepository = repository;
    }

    loadRestrictions();
}

void loadRestrictions()
{
    if ( !mSettings.Config.isMember( "restrictions" ) ) {
        mSettings.Config[ "restrictions" ] = Json::Value();
    }

    // add hardcoded max restriction for Slang version ( this can be overwritten by the real restriction config )
    mSettings.LocalRestrictions.insert(
        Restriction( PRODUCT_NAME, "", PRODUCT_VERSION )
    );

    // load restrictions from config
    auto restrictions = mSettings.Config[ "restrictions" ];
    for ( const auto& restrictionName : restrictions.getMemberNames() ) {
        const auto& restriction = restrictions[ restrictionName ];

        std::string versionMin;
        if ( restriction.isMember( "version_min" ) ) {
            versionMin = restriction[ "version_min" ].asString();
        }
        std::string versionMax;
        if ( restriction.isMember( "version_max" ) ) {
            versionMax = restriction[ "version_max" ].asString();
        }

        mSettings.LocalRestrictions.insert(
            Restriction( restrictionName, versionMin, versionMax )
        );
    }
}

void prepareModuleInstallation( const std::string& repo, const Module& installModule )
{
#ifdef SLANG_DEBUG
    std::cout << "Preparing module \"" << installModule.mShortName << " (" << installModule.mVersion.toString() << ")\" from \"" << repo << "\"..." << std::endl;
#endif

    // ( 1 ) download module information from repository
    // ( 2 ) collect dependencies from module information
    // ( 3 ) check dependencies against local repository and download module information for missing modules

    auto path         = mSettings.LibraryFolder + CONFIG_CACHE_MODULES;
    auto filename     = installModule.mShortName + ".json";
    auto moduleConfig = path + filename;
    auto url          = repo + MODULES + installModule.mShortName + "/" + installModule.mVersion.toString() + "/module.json";

    bool result = download( url, moduleConfig );
    if ( !result ) {
        std::cerr << "!!! Download of module information for \"" << installModule.mShortName << "\" failed" << std::endl;
        return;
    }

    if ( mSettings.SkipDependencies ) {
        // skipping dependencies as requested
        return;
    }

    auto module = collectModuleData( path, filename );

    // check module architecture
    if ( !module.mArchitecture.empty() ) {
        if ( module.mArchitecture != mSettings.Architecture ) {
            std::cerr << "!!! module architecture " << module.mArchitecture << " does not match system architecture" << std::endl;
            exit( ERROR_ARCHITECTURE );
        }
    }

    auto localModules = mLocalRepository.getModules();
    for ( const auto& dependency : module.mDependencies ) {
        bool found = false;

        // look up dependency in already installed modules
        for ( const auto& module : localModules ) {
            if ( module.mShortName == dependency.Module ) {
                found = true;
                break;
            }
        }

        if ( !found ) {
            // dependent module is not yet installed
            std::cout << "Need to install dependent module \"" << dependency.Module << "\"" << std::endl;

            Module dependent( dependency.Module, dependency.MinVersion, dependency.Source );

            mMissingDependencies.addModule( dependent );

            prepareModuleInstallation( repo, dependent );
        }
    }
}

bool prepareRemoteRepository()
{
    auto filename = mSettings.LibraryFolder + CONFIG_CACHE_REPOSITORIES + mRemoteRepository.getName() + ".json";

    // check if filename exists
    if ( !Utils::Tools::Files::exists( filename ) ) {
        // no configuration file exists
        std::cerr << "!!! File \"" + filename + "\" not found" << std::endl;
        return false;
    }

    Json::Value config;
    readJsonFile( filename, config );

    // process Json::Value in Repository
    mRemoteRepository.processIndex( config );

    return true;
}

void processRestrictions( const StringList& params )
{
    // ( 1 ) check if the requested module is actually installed
    // ( 2 ) add a version restriction for the given module

    if ( params.empty() ) {
        std::cerr << "!!! Invalid number of parameters: " << params.size() << std::endl;
        return;
    }

    collectLocalModuleData();

    auto& restrictions = mSettings.Config[ "restrictions" ];
    auto paramIt       = params.begin();
    auto module        = ( *paramIt );

    // reset restrictions for module
    restrictions.removeMember( module );

    // add new restrictions
    Json::Value value;

    if ( params.size() == 2 ) {
        ++paramIt;

        std::string maxVersion;
        std::string minVersion;
        Utils::Tools::splitBy( *paramIt, VERSION_SEPARATOR, minVersion, maxVersion );

        if ( !minVersion.empty() ) value[ "version_min" ] = SemanticVersionNumber( minVersion ).toString();
        if ( !maxVersion.empty() ) value[ "version_max" ] = SemanticVersionNumber( maxVersion ).toString();

        restrictions[ module ] = value;
    }

    storeConfig();
}

void purge( const StringList& params )
{
    // ( 1 ) remove the configuration of the requested modules
    // ( 2 ) remove the modules themselves
    // ( 3 ) store configuration

    if ( mParameters.empty() ) {
        std::cerr << "!!! Invalid number of parameters" << std::endl;
        return;
    }

    // ( 1 ) remove the module configurations from config.json
    removeRestriction( params );

    // ( 2 ) remove the modules ( if installed )
    remove( params );

    // ( 3 ) store configuration
    storeConfig();
}

/*
 * Push packages to HTTP repository server
 */
size_t push( const StringList& params )
{
    // ( 0 ) make sure that the module is prepared for upload
    // ( 1 ) check if files "<module>_<version>.json", "<module>_<version>.tar.gz" are present
    // ( 2 ) upload "<module>_<version>.json", "<module>_<version>.tar.gz" into "upload" folder of the repository server
    // ( 3 ) clean up module files after uploading

    if ( params.empty() ) {
        std::cerr << "!!! Invalid number of parameters" << std::endl;
        return 1;
    }

    for ( const auto& param : params )
    {
        std::string path     = param;
        std::string filename = "module.json";

        create( StringList{ path } );

        auto module = collectModuleData( path, filename );

        auto result = upload(
            module.mShortName + FILE_VERSION_SEPARATOR + module.mVersion.toString() + ".json",
            mRemoteRepository.getURL() + UPLOAD_PATH,
            "application/json"
        );

        if ( result ) {
            std::cerr << "!!! Error " << result << " while uploading module to repository '" << mRemoteRepository.getURL() << "'" << std::endl;
        }
        else {
            result = upload(
                module.mShortName + FILE_VERSION_SEPARATOR + module.mVersion.toString() + ".tar.gz",
                mRemoteRepository.getURL() + UPLOAD_PATH,
                "application/tar+gzip"
            );

            if ( result ) {
                std::cerr << "!!! Error " << result << " while uploading module to repository '" << mRemoteRepository.getURL() << "'" << std::endl;
            }
        }

        if ( !result ) {
            std::cout << "Successfully uploaded module '" << param << "' to repository '" << mRemoteRepository.getURL() << "'" << std::endl;
        }

        // cleanup artifacts
        execute( "rm " + module.mShortName + FILE_VERSION_SEPARATOR + module.mVersion.toString() + ".json" );
        execute( "rm " + module.mShortName + FILE_VERSION_SEPARATOR + module.mVersion.toString() + ".tar.gz" );
    }

    return 0;
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

void remove( const StringList& params )
{
    // ( 1 ) check if the requested modules are actually installed
    // ( 2 ) remove them by deleting their complete directory

    if ( mParameters.empty() ) {
        std::cerr << "!!! Invalid number of parameters" << std::endl;
        return;
    }

    collectLocalModuleData();

    auto local = mLocalRepository.getModules();

    for ( const auto& param : params ) {
        bool found = false;

        for ( const auto& localIt : local ) {
            if ( localIt.mShortName == param ) {
                found = true;

                std::cout << "Removing module \"" << localIt.mShortName << "\" from \"" << localIt.mTarget.Directory << "\"..." << std::endl;

                execute( CONFIG_SCRIPTS + "removeLinks.sh \"" + mSettings.LibraryFolder + "/" + CONFIG_APPS + "\" \"" + mSettings.LibraryFolder + "/" + localIt.mShortName + "\"" );
                execute( "rm -r " + localIt.mTarget.Directory );
            }
        }

        if ( !found ) {
            std::cerr << "!!! Module \"" << param << "\" cannot be removed because it is not installed" << std::endl;
        }
    }
}

void removeRestriction( const std::string& module )
{
    Json::Value& restrictions = mSettings.Config[ "restrictions" ];
    restrictions.removeMember( module );
}

void removeRestriction( const StringList& params )
{
    // ( 1 ) check if the requested modules are actually installed
    // ( 2 ) remove them by deleting their complete directory

    if ( mParameters.empty() ) {
        std::cerr << "!!! Invalid number of parameters" << std::endl;
        return;
    }

    for ( const auto& param : params ) {
        removeRestriction( param );
    }
}

void search( const StringList& params )
{
    // ( 1 ) load cached repositories from disk
    // ( 2 ) substr-search through all entries for given params

    auto filename = mSettings.LibraryFolder + CONFIG_CACHE_REPOSITORIES + mRemoteRepository.getName() + ".json";

    // check if filename exists
    if ( !Utils::Tools::Files::exists( filename ) ) {
        // no configuration file exists
        std::cerr << "!!! File \"" + filename + "\" not found" << std::endl;
        return;
    }

    Json::Value config;
    readJsonFile( filename, config );

    if ( !config.isMember( "modules" ) ) {
        std::cerr << "!!! Invalid cache file structure: \"modules\" missing" << std::endl;
        return;
    }


    std::string lookup = params.empty() ? "" : params.front();
    StringList result;

    for ( const auto& member : config[ "modules" ] ) {
        if ( !member.isMember( "name" ) ) {
            std::cerr << "!!! Invalid cache file structure: \"name\" missing" << std::endl;
            return;
        }

        auto description = member.isMember( "description" ) ? member[ "description" ].asString() : "";
        auto longName    = member[ "name_full" ].asString();
        auto shortName   = member[ "name" ].asString();
        auto version     = member[ "version" ].asString();

        if ( member.isMember( "keywords" ) ) {
            auto oldSize = result.size();

            for ( const auto& keyword : member[ "keywords" ] ) {
                if ( findCaseInsensitive( keyword.asString(), lookup ) != std::string::npos ) {
                    result.push_back( shortName + VERSION_SEPARATOR + version + " - " + longName );
                    break;  // one result here is enough
                }
            }

            if ( oldSize != result.size() ) {
                // we obviously have found something
                continue;
            }
        }

        if ( findCaseInsensitive( shortName, lookup ) != std::string::npos ) {
            result.push_back( shortName + VERSION_SEPARATOR + version + " - " + longName );
            continue;
        }

        if ( findCaseInsensitive( description, lookup ) != std::string::npos ) {
            result.push_back( shortName + VERSION_SEPARATOR + version + " - " + longName );
            continue;
        }
    }

    if ( result.empty() ) {
        std::cout << "Nothing found." << std::endl;
    }
    else {
        for ( const auto& resultIt : result ) {
            std::cout << resultIt << std::endl;
        }

        std::cout << result.size() << " result(s) found." << std::endl;
    }
}

void storeConfig()
{
    // write json config to file
    writeJsonFile( mSettings.LibraryFolder + CONFIG_FILE, mSettings.Config );
}

void writeJsonFile( const std::string& filename, Json::Value& result )
{
    // write contents of Json::Value into filename

    Json::StyledWriter writer;
    std::string data = writer.write( result );

    std::fstream stream;
    stream.open( filename.c_str(), std::ios::out );    // open file for writing
    stream.write( data.c_str(), data.size() );
    stream.close();
}

void update()
{
    // download <URL>/modules/index.json

    std::cout << "Updating repository \"" << mRemoteRepository.getName() << "\"..." << std::endl;

    auto filename = mSettings.LibraryFolder + CONFIG_CACHE_REPOSITORIES + mRemoteRepository.getName() + ".json";
    auto url      = mRemoteRepository.getURL() + "/modules/index.json";

    bool result = download( url, filename, false );
    if ( result ) {
        std::cout << "Updated index for \"" << mRemoteRepository.getURL() << "\"" << std::endl;
    }
    else {
        std::cerr << "!!! Error while updating index for " << mRemoteRepository.getURL() << std::endl;
        exit( ERROR_INDEX_UPDATE );
    }
}

void upgrade( const StringList& params )
{
    // ( 1 ) retrieve outdated modules
    // ( 2 ) list all found modules
    // ( 3 ) install new modules if any are available

    collectLocalModuleData();
    if ( !prepareRemoteRepository() ) {
        update();
    }

    Modules outdatedModules;
    checkOutdatedModules( outdatedModules );

    if ( outdatedModules.empty() ) {
        std::cout << "No outdated modules found." << std::endl;
    }
    else {
        // find out if the user wants to upgrade some of our outdated modules
        Modules upgradeModules;
        for ( const auto& outdatedModule : outdatedModules ) {
            // if params contains values upgrade only the modules that are set in mParameters
            if ( params.empty() || contains( params, outdatedModule.mShortName ) ) {
                // add outdated module name to global parameters
                upgradeModules.insert( outdatedModule );
            }
        }
        std::cout << std::endl;

        if ( upgradeModules.empty() ) {
            // no modules added to upgrade
            std::cout << "No upgradeable module selected." << std::endl;
            return;
        }

        std::cout << "Need to upgrade " << upgradeModules.size() << " module(s)..." << std::endl;

        for ( const auto& outdatedModule : upgradeModules ) {
            std::cout << outdatedModule.mShortName << "( " << outdatedModule.mVersion.toString() << " )" << std::endl;

            // install new versions of the selected outdated modules
            install( StringList{ outdatedModule.mShortName } );
        }
    }
}

size_t upload( const std::string& filename, const std::string& url, const std::string& contentType )
{
    // Open the file
    auto* file = fopen( filename.c_str(), "rb" );
    if ( !file ) {
        std::cerr << "!!! Failed to open file <" << filename << ">" << std::endl;
        return 1;
    }

    // Initialize libcurl
    CURL* curl = curl_easy_init();
    CURLcode result;
    struct curl_slist *headers = nullptr;

    if ( curl ) {
        {   // authorization
            switch ( mRemoteRepository.getAuthentication() ) {
                case Repository::Authentication::None: {
                    // No authentication selected
                } break;
                case Repository::Authentication::Basic: {
                    curl_easy_setopt( curl, CURLOPT_USERPWD, mRemoteRepository.getAuthorization().c_str() );
                } break;
                case Repository::Authentication::Bearer: {
                    std::string authorization{ "Authorization: Bearer " + mRemoteRepository.getAuthorization() };

                    headers = curl_slist_append( headers, authorization.c_str() );
                } break;
            }
        }
        {   // set curl options
            curl_easy_setopt( curl, CURLOPT_HTTPHEADER, headers );
            curl_easy_setopt( curl, CURLOPT_NOPROGRESS, 1L );  // disable progress meter, set to 0L to enable and disable debug output
            curl_easy_setopt( curl, CURLOPT_POST, 1L );
            curl_easy_setopt( curl, CURLOPT_READDATA, file );
            curl_easy_setopt( curl, CURLOPT_UPLOAD, 1L );
            curl_easy_setopt( curl, CURLOPT_URL, url.c_str() );
            curl_easy_setopt( curl, CURLOPT_VERBOSE, static_cast<long>( mSettings.Verbose ) );     // Switch on full protocol/debug output while testing
        }
        {   // set the file size
            fseek( file, 0, SEEK_END );
            long file_size = ftell( file );
            fseek( file, 0, SEEK_SET );

            curl_easy_setopt( curl, CURLOPT_INFILESIZE_LARGE, static_cast<curl_off_t>( file_size ) );
        }
        {   // set MIME for uploaded file
            auto* form = curl_mime_init( curl );

            // fill in the file upload field
            auto* field = curl_mime_addpart( form );
            curl_mime_name( field, "file" );
            curl_mime_filedata( field, filename.c_str() );
            curl_mime_type( field, contentType.c_str() );

            curl_easy_setopt( curl, CURLOPT_MIMEPOST, form );
        }

        // perform the file upload
        result = curl_easy_perform( curl );

        if ( result != CURLE_OK ) {
            std::cerr << "!!! curl_easy_perform() failed: " << curl_easy_strerror( result ) << std::endl;
        }

        // Clean up
        curl_slist_free_all( headers );
        curl_easy_cleanup( curl );
    }

    fclose( file );
    return 0;
}

}
