
// Library includes
#include <algorithm>
#include <cstdlib>
#include <set>
#include <string>
#include <sys/utsname.h>
#ifdef _WIN32
#	include <direct.h>
#	define GetCurrentDir _getcwd
#else
#	include <dirent.h>
#	include <unistd.h>
#	define GetCurrentDir getcwd
#endif
#include <curl/curl.h>
#include <json/json.h>

// Project includes
#include <Common/StdOutLogger.h>
#include <Core/Common/Exceptions.h>
#include <Core/Consts.h>
#include <Core/Types.h>
#include <Core/Version.h>
#include <Tools/Files.h>
#include <Tools/Strings.h>
#include <Utils.h>
#include "Defines.h"
#include "Errors.h"
#include "Repository.h"
#include "Restriction.h"

// Namespace declarations


#ifdef __APPLE__
#elif defined _WIN32
	// Memory leak check - Begin
	#define _CRTDBG_MAP_ALLOC
	#include <cstdlib>

	#include <iostream>
	#include <crtdbg.h>
	#ifdef _DEBUG
	#define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
	#define new DEBUG_NEW
	#endif
	// Memory leak check - End

	//#include <vld.h>
#else
#	include <cstdlib>
#endif


enum e_Action {
	Create,
	CreateLocalLibrary,
	Help,
	Info,
	Install,
	List,
	None,
	Purge,
	Push,
	Remove,
	Restrict,
	Search,
	Update,
	Upgrade,
	Version
};


static const std::string CACHE_MODULES = "cache/modules/";
static const std::string CACHE_REPOSITORIES = "cache/repositories/";
static const std::string CONFIG_FILE = ".odepend/config.json";
static const std::string CONFIG_FOLDER = ".odepend/";
static const std::string FILE_VERSION_SEPARATOR = "_";
static const std::string MODULES = "modules/";
static const std::string REMOTE_REPOSITORY_NAME = "main";
static const std::string REMOTE_REPOSITORY_URL = "https://slang-lang.org/repository/stable";
static const std::string TMP = "/tmp/";
static const std::string UPLOAD_PATH = "upload/";
static const char VERSION_SEPARATOR = ':';


void addRestriction( const StringList& params );
void checkOutdatedModules( Modules& outdatedModules );
bool checkRestrictions( const Module& module );
void cleanCache();
void collectLocalModuleData();
Module collectModuleData( const std::string& path, const std::string& filename );
bool contains( const StringList& list, const std::string& value );
void create( const StringList& params );
void createBasicFolderStructure();
void createLocalLibrary();
void deinit();
bool download( const std::string& url, const std::string& target, bool allowCleanup = true );
void execute( const std::string& command );
size_t findCaseInsensitive( std::string data, std::string toSearch, size_t pos = 0 );
void info( const StringList& params );
void init();
void install( const StringList& params );
void installModule( const std::string& repo, const std::string& module );
bool isLocalLibrary();
void list();
void loadConfig();
void loadRestrictions();
void prepareModuleInstallation( const std::string& repo, const Module& installModule );
bool prepareRemoteRepository();
void printUsage();
void printVersion();
void processParameters( int argc, const char* argv[] );
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


e_Action mAction = None;
std::string mArchitecture;
std::string mBaseFolder;
Json::Value mConfig;
std::string mCurrentFolder;
StringList mDownloadedFiles;
std::string mLibraryFolder;
Repository mLocalRepository( "local" );
Restrictions mLocalRestrictions;
Utils::Common::StdOutLogger mLogger;
Repository mMissingDependencies( "missing" );
StringList mParameters;
Repository mRemoteRepository;
bool mSkipDependencies = false;


static size_t write_data( void *ptr, size_t size, size_t nmemb, void *stream )
{
	size_t written = fwrite( ptr, size, nmemb, ( FILE * )stream );
	return written;
}

void addRestriction( const StringList& params )
{
	// ( 1 ) check if the requested module is actually installed
	// ( 2 ) add a version restriction for the given module

	if ( params.size() != 3 && params.size() != 5 ) {
		std::cout << "!!! Invalid number of parameters: " << params.size() << std::endl;
		return;
	}

	collectLocalModuleData();

	auto& restrictions = mConfig[ "restrictions" ];

	auto paramIt = params.begin();

	auto module = ( *paramIt );

	restrictions.removeMember( module );

	Json::Value value;
	while ( paramIt != params.end() ) {
		++paramIt;

		if ( ( *paramIt ) == "max" ) {
			++paramIt;

			SemanticVersionNumber version( ( *paramIt ) );

			value[ "version_max" ] = version.toString();
		}
		else if ( ( *paramIt ) == "min" ) {
			++paramIt;

			SemanticVersionNumber version( ( *paramIt ) );

			value[ "version_min" ] = version.toString();
		}
	}

	restrictions[ module ] = value;

	storeConfig();
}

void checkOutdatedModules( Modules& outdatedModules )
{
	// compare new index.json with local module information:
	// find all folders in local <repo> folder and compare their corresponding <repo>/<module>/module.json [ version ] field
	// with the version in the index.json file

	Modules local = mLocalRepository.getModules();
	Modules remote = mRemoteRepository.getModules();

	for ( const auto& localIt : local ) {
		for ( const auto& remoteIt : remote ) {
			if ( localIt.mShortName == remoteIt.mShortName && localIt.mVersion < remoteIt.mVersion ) {
				outdatedModules.insert( remoteIt );
			}
		}
	}
}

bool checkRestrictions( const Module& module )
{
	for ( const auto& mLocalRestriction : mLocalRestrictions ) {
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

	std::string base = mLibraryFolder;

	DIR* dir = opendir( base.c_str() );
	if ( !dir ) {
		std::cout << "!!! Error while accessing modules directory" << std::endl;
		exit( ERROR_MODULE_DIRECTORY );
	}

 	struct dirent* dirEntry = readdir( dir );

	while ( dirEntry ) {
		if ( dirEntry->d_type == DT_DIR ) {
			std::string entry( dirEntry->d_name );

			if ( entry != "." && entry != ".." ) {
				auto filename = "module.json";
				auto path     = base + entry + "/";

				if ( ::Utils::Tools::Files::exists( path + filename ) ) {
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
		std::cout << "!!! Invalid module data in file '" << filename << "'" << std::endl;
		return module;
	}

	module.mInstalledDirectory = path;

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
		std::cout << "!!! Invalid number of parameters" << std::endl;
		return;
	}

	// TODO: module name is not allowed to end with '/'
	std::string path     = params.front();
	std::string filename = "module.json";

	auto module = collectModuleData( path, filename );

	{	// create version specific module information ( "<module>_<version>.json" )
		std::cout << "Creating module information \"" << module.mShortName + FILE_VERSION_SEPARATOR + module.mVersion.toString() + ".json\"" << std::endl;

		execute( "cp " + path + "/" + filename + " " + module.mShortName + FILE_VERSION_SEPARATOR + module.mVersion.toString() + ".json" );
	}
	{	// create package ( "<module>_<version>.tar.gz" )
		std::cout << "Creating module package \"" << module.mShortName + FILE_VERSION_SEPARATOR + module.mVersion.toString() + ".tar.gz\"" << std::endl;

		execute( "tar -cjf " + module.mShortName + FILE_VERSION_SEPARATOR + module.mVersion.toString() + ".tar.gz " + path );
	}
}

void createBasicFolderStructure()
{
	std::string path;

	// create "<base>/cache/modules" folder
	path = mBaseFolder + CACHE_MODULES;
	if ( !Utils::Tools::Files::exists( path ) ) {
		execute( "mkdir -p " + path );
	}

	// create "<base>/cache/repositories" folder
	path = mBaseFolder + CACHE_REPOSITORIES;
	if ( !Utils::Tools::Files::exists( path ) ) {
		execute( "mkdir -p " + path );
	}
}

void createLocalLibrary()
{
	std::cout << "Preparing current directory for slang-pkg..." << std::endl;

	if ( !Utils::Tools::Files::exists( mCurrentFolder + CONFIG_FOLDER ) ) {
		// create folder for library config
		execute( "mkdir " + mCurrentFolder + CONFIG_FOLDER );
	}

	if ( !Utils::Tools::Files::exists( mCurrentFolder + CONFIG_FILE ) ) {
		Json::Value repository;
		repository[ "name" ] = REMOTE_REPOSITORY_NAME;
		repository[ "url" ]  = REMOTE_REPOSITORY_URL;

		Json::Value config;
		config[ "repository" ]   = repository;
		config[ "restrictions" ] = Json::Value();

		writeJsonFile( mCurrentFolder + CONFIG_FILE, config );
	}
}

void deinit()
{
	// put de-initialization stuff here

	// clean up curl library
	curl_global_cleanup();
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
	curl_easy_setopt( curl_handle, CURLOPT_VERBOSE, 0L );

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

void execute( const std::string& command )
{
	int result = system( command.c_str() );
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
		std::cout << "!!! Invalid number of parameters" << std::endl;
		return;
	}

	for ( auto it = params.cbegin(); it != params.cend(); ++it ) {
		if ( it != params.cbegin() ) {
			std::cout << std::endl;
		}

        collectLocalModuleData();
        if ( !prepareRemoteRepository() ) {
            update();
        }

        bool found = false;

        std::string moduleName;
        std::string moduleVersion;

        Utils::Tools::splitBy( ( *it ), VERSION_SEPARATOR, moduleName, moduleVersion );

        if ( moduleVersion.empty() ) {
            Module tmpModule;

            if ( mRemoteRepository.getModule( moduleName, tmpModule ) ) {
                moduleVersion = tmpModule.mVersion.toString();
            }
        }

        Module infoModule;

        {	// look up module in local repository
            Modules local = mLocalRepository.getModules();
            for ( const auto& localIt : local ) {
                if ( localIt.mShortName == moduleName && localIt.mVersion == moduleVersion ) {
                    found = true;

                    infoModule = localIt;
                }
            }
        }

        if ( !found ) {	// lookup module in remote repository
            auto path          = mBaseFolder + CACHE_MODULES;
            auto filename      = moduleName + ".json";
            auto module_config = path + filename;
            auto url           = mRemoteRepository.getURL() + MODULES + moduleName + FILE_VERSION_SEPARATOR + moduleVersion + ".json";

            auto result = download( url, module_config );
            if ( result ) {
                Module tmpModule = collectModuleData( path, filename );
                if ( tmpModule.isValid() ) {
                    found = true;

                    infoModule = tmpModule;
                }
            }
        }

        if ( found ) {	// print out module information if found
            std::cout << infoModule.mShortName << "( " << infoModule.mVersion.toString() << " ): " << infoModule.mLongName << std::endl;
            std::cout << infoModule.mDescription << std::endl;
            std::cout << std::endl;
            std::cout << "Dependencies:" << std::endl;

            if ( infoModule.mDependencies.empty() ) {
                std::cout << "<none>" << std::endl;
            }
            else {
                for ( const auto& dependency : infoModule.mDependencies ) {
                    std::cout << dependency.mModule << "\t\t";
                    std::cout << "min: " << ( dependency.mMinVersion.empty() ? "<not set>" : dependency.mMinVersion );
                    std::cout << "\t\tmax: " << ( dependency.mMaxVersion.empty() ? "<not set>" : dependency.mMaxVersion );
                    std::cout << "\t\tsource: " << ( dependency.mSource.empty() ? "<not set>" : dependency.mSource );
                    std::cout << std::endl;
                }
            }
        }
        else {
            std::cout << "!!! Requested module \"" << moduleName << "\" not found" << std::endl;
        }
	}
}

void init()
{
    struct utsname name{};

    if ( uname( &name ) == -1 ) {
        std::cout << "Cannot get system name!" << std::endl;
        exit( ERROR_SYSTEM );
    }

    mArchitecture = name.machine;

	// put initialization stuff here
	mBaseFolder = TMP;

	{	// set library home path
		const char* homepath = getenv( Slang::SLANG_LIBRARY );
		if ( homepath ) {
			std::string path = std::string( homepath );

			// only read first entry
			if ( !path.empty() ) {
				std::string left;
				std::string right;

				Utils::Tools::splitBy( path, VERSION_SEPARATOR, left, right );

				mLibraryFolder = left + "/";
			}
		}
	}

	{	// set current folder
		char currentPath[ FILENAME_MAX ];
		if ( !GetCurrentDir( currentPath, sizeof( currentPath ) ) )  {
			throw Slang::Common::Exceptions::Exception( "invalid current directory!" );
		}

		currentPath[ sizeof( currentPath ) - 1 ] = '\0'; /* not really required */

		mCurrentFolder = std::string( currentPath ) + "/";

		if ( isLocalLibrary() ) {
			mBaseFolder = mCurrentFolder + CONFIG_FOLDER;
			mLibraryFolder = mCurrentFolder;
		}
	}

	createBasicFolderStructure();

	loadConfig();

	// initialize curl library
	curl_global_init( CURL_GLOBAL_ALL );
}

void install( const StringList& params )
{
	// ( 1 ) prepare dependencies
	// ( 2 ) install missing dependencies
	// ( 3 ) check if we don't violate any module restrictions
	// ( 4 ) install requested modules

	if ( params.empty() ) {
		std::cout << "!!! Invalid number of parameters" << std::endl;
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
				source = tmpModule.mSource;
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
		Modules missing = mMissingDependencies.getModules();
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

	std::string module_config = mBaseFolder + CACHE_MODULES + module + ".json";

	if ( !Utils::Tools::Files::exists( module_config ) ) {
		std::cout << "!!! Module information missing for module \"" << module << "\"" << std::endl;
		return;
	}

	Json::Value config;
	readJsonFile( module_config, config );

	if ( !config.isMember( "target" ) ) {
		std::cout << "!!! No target entry found in module information" << std::endl;
		return;
	}
	if ( !config[ "target" ].isMember( "type" ) ) {
		std::cout << "!!! No type entry found in target module information" << std::endl;
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
		std::cout << "!!! invalid target type specified" << std::endl;
		return;
	}

	std::string module_archive = mBaseFolder + CACHE_MODULES + module + FILE_VERSION_SEPARATOR + config[ "version" ].asString() + ".tar.gz";

	bool result = download( url, module_archive );
	if ( !result ) {
		std::cout << "!!! Failed to download target" << std::endl;
		return;
	}

	execute( "tar xf " + module_archive + " -C " + mLibraryFolder );

/*
	Module tmpModule = collectModuleData( mBaseFolder + CACHE_MODULES, module + ".json" );

	// copy module config to "<module>/module.json"
	execute( "cp " + module_config + " " + mLibraryFolder + tmpModule.mTargetDirectory + "/module.json" );
*/
}

bool isLocalLibrary()
{
	return Utils::Tools::Files::exists( mCurrentFolder + CONFIG_FILE );
}

void list()
{
	collectLocalModuleData();

	Modules local = mLocalRepository.getModules();

	std::cout << local.size() << " module( s ) installed." << std::endl;

	for ( const auto& localIt : local ) {
		std::cout << localIt.mShortName << "( " << localIt.mVersion.toString() << " ): " << localIt.mLongName << std::endl;
	}
}

void loadConfig()
{
	std::string filename = mLibraryFolder + CONFIG_FILE;

	readJsonFile( filename, mConfig );

	if ( mConfig.isMember( "repository" ) ) {
		Json::Value entry = mConfig[ "repository" ];

		// repository name
		// {
		if ( !entry.isMember( "name" ) ) {
			std::cout << "!!! Invalid repository name" << std::endl;
			return;
		}

		std::string name = entry[ "name" ].asString();
		// }

		// repository URL
		// {
		if ( !entry.isMember( "url" ) ) {
			std::cout << "!!! Invalid repository url" << std::endl;
			return;
		}

		std::string url = entry[ "url" ].asString();

		// make sure the URL ends with a slash
		if ( url[ url.size() - 1 ] != '/' ) {
			url += '/';
		}
		// }

		Repository repository( name );
		repository.setURL( url );

		mRemoteRepository = repository;
	}

	if ( !mConfig.isMember( "restrictions" ) ) {
		mConfig[ "restrictions" ] = Json::Value();
	}

	loadRestrictions();
}

void loadRestrictions()
{
	// add hardcoded max restriction for Slang version ( this can be overwritten by the real restriction config )
	mLocalRestrictions.insert(
		Restriction( PRODUCT_NAME, "", PRODUCT_VERSION )
	 );

	// load restrictions from config
	Json::Value restrictions = mConfig[ "restrictions" ];
	for ( const auto& restrictionName : restrictions.getMemberNames() ) {
        auto restriction = restrictions[ restrictionName ];

		std::string versionMin;
		if ( restriction.isMember( "version_min" ) ) {
			versionMin = restriction[ "version_min" ].asString();
		}
		std::string versionMax;
		if ( restriction.isMember( "version_max" ) ) {
			versionMax = restriction[ "version_max" ].asString();
		}

		mLocalRestrictions.insert(
			Restriction( restrictionName, versionMin, versionMax )
		 );
	}
}

void printUsage()
{
	std::cout << "Usage: slang-pkg [ args... ]" << std::endl;
	std::cout << std::endl;
	std::cout << "create                     Create a new module from a given directory" << std::endl;
	std::cout << "help                       This help" << std::endl;
	std::cout << "info                       Print information about requested module" << std::endl;
	std::cout << "install                    Install new module" << std::endl;
	std::cout << "list                       List all installed modules" << std::endl;
	std::cout << "purge                      Remove an installed module and all of its configuration" << std::endl;
	std::cout << "push                       Push module( s ) to repository server" << std::endl;
	std::cout << "remove                     Remove an installed module" << std::endl;
	std::cout << "restrict                   Add version restriction for module" << std::endl;
	std::cout << "search                     Search for a module" << std::endl;
	std::cout << "update                     Update repository indices" << std::endl;
	std::cout << "upgrade                    Upgrade outdated modules" << std::endl;
	std::cout << "--locallibrary             Use current directory as library" << std::endl;
	std::cout << "--skip-dependencies        Skip dependencies while installing or removing modules" << std::endl;
	std::cout << "--version                  Version information" << std::endl;
	std::cout << std::endl;
}

void printVersion()
{
	std::cout << PRODUCT_NAME << " Dependency Manager " << PRODUCT_VERSION << " ( cli ) " << mArchitecture << std::endl;
	std::cout << COPYRIGHT << std::endl;
	std::cout << "" << std::endl;
}

void processParameters( int argc, const char* argv[] )
{
	mAction = Help;

	if ( argc > 1 ) {
		std::string arg1 = argv[ 1 ];

		if ( Utils::Tools::StringCompare( arg1, "create" ) ) {
			mAction = Create;
		}
		else if ( Utils::Tools::StringCompare( arg1, "help" ) ) {
			mAction = Help;
		}
		else if ( Utils::Tools::StringCompare( arg1, "info" ) ) {
			mAction = Info;
		}
		else if ( Utils::Tools::StringCompare( arg1, "install" ) ) {
			mAction = Install;
		}
		else if ( Utils::Tools::StringCompare( arg1, "list" ) ) {
			mAction = List;
		}
		else if ( Utils::Tools::StringCompare( arg1, "purge" ) ) {
			mAction = Purge;
		}
		else if ( Utils::Tools::StringCompare( arg1, "push" ) ) {
			mAction = Push;
		}
		else if ( Utils::Tools::StringCompare( arg1, "remove" ) ) {
			mAction = Remove;
		}
		else if ( Utils::Tools::StringCompare( arg1, "restrict" ) ) {
			mAction = Restrict;
		}
		else if ( Utils::Tools::StringCompare( arg1, "search" ) ) {
			mAction = Search;
		}
		else if ( Utils::Tools::StringCompare( arg1, "update" ) ) {
			mAction = Update;
		}
		else if ( Utils::Tools::StringCompare( arg1, "upgrade" ) ) {
			mAction = Upgrade;
		}
		else if ( Utils::Tools::StringCompare( arg1, "--locallibrary" ) ) {
			mAction = CreateLocalLibrary;
		}
		else if ( Utils::Tools::StringCompare( arg1, "--version" ) ) {
			mAction = Version;
		}
	}

	for ( int i = 2; i < argc; ++i ) {
		if ( Utils::Tools::StringCompare( argv[ i ], "--skip-dependencies" ) ) {
			mSkipDependencies = true;
		}
		else {
			mParameters.push_back( std::string( argv[ i ] ) );
		}
	}
}

void prepareModuleInstallation( const std::string& repo, const Module& installModule )
{
#ifdef SLANG_DEBUG
	std::cout << "Preparing module \"" << installModule.mShortName << "( " << installModule.mVersion.toString() << " )\" from \"" << repo << "\"..." << std::endl;
#endif

	// ( 1 ) download module information from repository
	// ( 2 ) collect dependencies from module information
	// ( 3 ) check dependencies against local repository and download module information for missing modules

	std::string path = mBaseFolder + CACHE_MODULES;
	std::string filename = installModule.mShortName + ".json";
	std::string module_config = path + filename;
	std::string url = repo + MODULES + installModule.mShortName + "/" + installModule.mVersion.toString() + "/module.json";

	bool result = download( url, module_config );
	if ( !result ) {
		std::cout << "!!! Download of module information for \"" << installModule.mShortName << "\" failed" << std::endl;
		return;
	}

	if ( mSkipDependencies ) {
		// skipping dependencies as requested
		return;
	}

	Module module = collectModuleData( path, filename );

	// check module architecture
	if ( !module.mArchitecture.empty() ) {
	    if ( module.mArchitecture != mArchitecture ) {
	        std::cout << "ERROR: module architecture " << module.mArchitecture << " does not match system architecture!" << std::endl;
	        exit( ERROR_ARCHITECTURE );
	    }
	}

	Modules local = mLocalRepository.getModules();
	for ( const auto& mDependencie : module.mDependencies ) {
		bool found = false;

		// look up dependency in already installed modules
		for ( const auto& localIt : local ) {
			if ( localIt.mShortName == mDependencie.mModule ) {
				found = true;
				break;
			}
		}

		if ( !found ) {
			// dependent module is not yet installed
			std::cout << "Need to install dependent module \"" << mDependencie.mModule << "\"" << std::endl;

			Module dependent( mDependencie.mModule, mDependencie.mMinVersion, mDependencie.mSource );

			mMissingDependencies.addModule( dependent );

			prepareModuleInstallation( repo, dependent );
		}
	}
}

bool prepareRemoteRepository()
{
	std::string filename = mBaseFolder + CACHE_REPOSITORIES + mRemoteRepository.getName() + ".json";

	// check if filename exists
	if ( !::Utils::Tools::Files::exists( filename ) ) {
		// no configuration file exists
		std::cout << "!!! File \"" + filename + "\" not found" << std::endl;
		return false;
	}

	Json::Value config;
	readJsonFile( filename, config );

	// process Json::Value in Repository
	mRemoteRepository.processIndex( config );

	return true;
}

void purge( const StringList& params )
{
	// ( 1 ) remove the configuration of the requested modules
	// ( 2 ) remove the modules themselves
	// ( 3 ) store configuration

	if ( mParameters.empty() ) {
		std::cout << "!!! Invalid number of parameters" << std::endl;
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
        std::cout << "!!! Invalid number of parameters" << std::endl;
        return 1;
    }

    for ( const auto& param : params )
    {
        // TODO: module name is not allowed to end with '/'
        std::string path     = param;
        std::string filename = "module.json";

        create( StringList{ path } );

        auto module = collectModuleData( path, filename );

        size_t result{ 0 };
        result = upload( module.mShortName + FILE_VERSION_SEPARATOR + module.mVersion.toString() + ".json",   mRemoteRepository.getURL() + UPLOAD_PATH, "application/json" );
        if ( result ) {
            std::cerr << "Error " << result << " while uploading module to repository '" << mRemoteRepository.getURL() << "'" << std::endl;
        }
        else {
            result = upload( module.mShortName + FILE_VERSION_SEPARATOR + module.mVersion.toString() + ".tar.gz", mRemoteRepository.getURL() + UPLOAD_PATH, "application/tar+gzip" );
            if ( result ) {
                std::cerr << "Error " << result << " while uploading module to repository '" << mRemoteRepository.getURL() << "'" << std::endl;
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
	stream.open( filename.c_str(), std::ios::in );	// open for reading
	std::string data( ( std::istreambuf_iterator<char>( stream ) ), std::istreambuf_iterator<char>() );	// read stream
	stream.close();

    Json::Reader reader;
	reader.parse( data, result );
}

void remove( const StringList& params )
{
	// ( 1 ) check if the requested modules are actually installed
	// ( 2 ) remove them by deleting their complete directory

	if ( mParameters.empty() ) {
		std::cout << "!!! Invalid number of parameters" << std::endl;
		return;
	}

	collectLocalModuleData();

	Modules local = mLocalRepository.getModules();

	for ( const auto& param : params ) {
		bool found = false;

		for ( const auto& localIt : local ) {
			if ( localIt.mShortName == param ) {
				found = true;

				std::cout << "Removing module \"" << localIt.mShortName << "\" from \"" << localIt.mInstalledDirectory << "\"..." << std::endl;

				execute( "rm -r " + localIt.mInstalledDirectory );
			}
		}

		if ( !found ) {
			std::cout << "!!! Module \"" << param << "\" cannot be removed because it is not installed" << std::endl;
		}
	}
}

void removeRestriction( const std::string& module )
{
	Json::Value& restrictions = mConfig[ "restrictions" ];
	restrictions.removeMember( module );
}

void removeRestriction( const StringList& params )
{
	// ( 1 ) check if the requested modules are actually installed
	// ( 2 ) remove them by deleting their complete directory

	if ( mParameters.empty() ) {
		std::cout << "!!! Invalid number of parameters" << std::endl;
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

	std::string filename = mBaseFolder + CACHE_REPOSITORIES + mRemoteRepository.getName() + ".json";

	// check if filename exists
	if ( !::Utils::Tools::Files::exists( filename ) ) {
		// no configuration file exists
		std::cout << "!!! File \"" + filename + "\" not found" << std::endl;
		return;
	}

	Json::Value config;
	readJsonFile( filename, config );

	if ( !config.isMember( "modules" ) ) {
		std::cout << "!!! Invalid cache file structure: \"modules\" missing" << std::endl;
		return;
	}


	std::string lookup = params.empty() ? "" : params.front();
	StringList result;

	for ( const auto& member : config[ "modules" ] ) {
		if ( !member.isMember( "name" ) ) {
			std::cout << "!!! Invalid cache file structure: \"name\" missing" << std::endl;
			return;
		}

		std::string description = member.isMember( "description" ) ? member[ "description" ].asString() : "";
		std::string name = member[ "name" ].asString();
		std::string version = member.isMember( "version" ) ? member[ "version" ].asString() : "";

        if ( member.isMember( "keywords" ) ) {
            auto oldSize = result.size();

            for ( const auto& keyword : member[ "keywords" ] ) {
                if ( findCaseInsensitive( keyword.asString(), lookup ) != std::string::npos ) {
                    result.push_back( name + "( " + version + " )" + description );
                    break;  // one result here is enough
                }
            }

            if ( oldSize != result.size() ) {
                // we obviously have found something
                continue;
            }
        }

		if ( findCaseInsensitive( name, lookup ) != std::string::npos ) {
			result.push_back( name + "( " + version + " )" + description );
			continue;
		}

		if ( findCaseInsensitive( description, lookup ) != std::string::npos ) {
			result.push_back( name + "( " + version + " )" + description );
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
	}
}

void storeConfig()
{
	// write json config to file
	std::string filename = mLibraryFolder + CONFIG_FILE;

	writeJsonFile( filename, mConfig );
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
	// download <URL>/<branch>/index.json

	std::cout << "Updating repository \"" << mRemoteRepository.getName() << "\"..." << std::endl;

	std::string url = mRemoteRepository.getURL() + "modules/index.json";
	std::string filename = mBaseFolder + CACHE_REPOSITORIES + mRemoteRepository.getName() + ".json";

	bool result = download( url, filename, false );
	if ( result ) {
		std::cout << "Updated index for \"" << mRemoteRepository.getURL() << "\"" << std::endl;
	}
	else {
		std::cout << "!!! Error while updating index for " << mRemoteRepository.getURL() << std::endl;
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

        std::cout << "Need to upgrade " << upgradeModules.size() << " module( s )..." << std::endl;

        for ( const auto& outdatedModule : upgradeModules ) {
            std::cout << outdatedModule.mShortName << "( " << outdatedModule.mVersion.toString() << " )" << std::endl;

            // install new versions of the selected outdated modules
            install( StringList{ outdatedModule.mShortName } );
        }
    }
}

size_t upload( const std::string& filename, const std::string& url, const std::string& contentType )
{
    // Initialize libcurl
    CURL* curl;
    CURLcode res;

    // Open the file
    auto* file = fopen( filename.c_str(), "rb" );
    if ( !file ) {
        std::cerr << "Failed to open file <" << filename << ">" << std::endl;
        return 1;
    }

    // Initialize a CURL session
    curl = curl_easy_init();
    if ( curl ) {
        // set curl options
        curl_easy_setopt( curl, CURLOPT_NOPROGRESS, 1L );  // disable progress meter, set to 0L to enable and disable debug output
        curl_easy_setopt( curl, CURLOPT_POST, 1L );
        curl_easy_setopt( curl, CURLOPT_READDATA, file );
        curl_easy_setopt( curl, CURLOPT_UPLOAD, 1L );
        curl_easy_setopt( curl, CURLOPT_URL, url.c_str() );
        curl_easy_setopt( curl, CURLOPT_VERBOSE, 0L );     // Switch on full protocol/debug output while testing

        // Set the file size ( optional but recommended )
        fseek( file, 0, SEEK_END );
        long file_size = ftell( file );
        fseek( file, 0, SEEK_SET );
        curl_easy_setopt( curl, CURLOPT_INFILESIZE_LARGE, static_cast<curl_off_t>( file_size ) );

        {   // set MIME for uploaded file
            auto* form = curl_mime_init( curl );

            // Fill in the file upload field
            auto* field = curl_mime_addpart( form );
            curl_mime_name( field, "file" );
            curl_mime_filedata( field, filename.c_str() );
            curl_mime_type( field, contentType.c_str() );

            curl_easy_setopt( curl, CURLOPT_MIMEPOST, form );
        }

        // Perform the file upload
        res = curl_easy_perform( curl );

        if ( res != CURLE_OK ) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror( res ) << std::endl;
        }

        // Clean up
        curl_easy_cleanup( curl );
    }

    fclose( file );
    return 0;
}

int main( int argc, const char* argv[] )
{
#ifdef _WIN32
	// Memory leak detection
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	// Memory leak detection
#endif

	processParameters( argc, argv );

	init();

	switch ( mAction ) {
		case Create:             create( mParameters ); break;
		case CreateLocalLibrary: createLocalLibrary(); init(); break;
		case Help:               printUsage(); break;
		case Info:               info( mParameters ); break;
		case Install:            install( mParameters ); break;
		case List:               list(); break;
		case None:               /* nothing to do here*/ break;
		case Purge:              purge( mParameters ); break;
		case Push:               push( mParameters ); break;
		case Remove:             remove( mParameters ); break;
		case Restrict:           addRestriction( mParameters ); break;
		case Search:             search( mParameters ); break;
		case Update:             update(); break;
		case Upgrade:            upgrade( mParameters ); break;
		case Version:            printVersion(); break;
	}

	cleanCache();

	return 0;
}
