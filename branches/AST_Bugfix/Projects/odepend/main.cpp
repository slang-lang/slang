
// Library includes
#include <dirent.h>
#include <set>
#include <string>
#include <stdlib.h>
#ifdef WINDOWS
#	include <direct.h>
    #define GetCurrentDir _getcwd
#else
#	include <unistd.h>
#	define GetCurrentDir getcwd
#endif
#include <curl/curl.h>
#include <Json/Json.h>

// Project includes
#include <Common/StdOutLogger.h>
#include <Core/Consts.h>
#include <Core/Types.h>
#include <Tools/Files.h>
#include <Tools/Strings.h>
#include <Utils.h>
#include <Core/Common/Exceptions.h>
#include "Repository.h"

// Namespace declarations


#ifdef __APPLE__
#elif defined _WIN32
	// Memory leak check - Begin
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>

	#include <iostream>
	#include <crtdbg.h>
	#ifdef _DEBUG
	#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
	#define new DEBUG_NEW
	#endif
	// Memory leak check - End

	//#include <vld.h>
#else
#	include <stdlib.h>
#endif


enum e_Action {
	Create,
	CreateLocalLibrary,
	Help,
	Info,
	Install,
	List,
	None,
	Remove,
	Search,
	Update,
	Upgrade,
	Version
};


static const char* CACHE = "cache/";
static const char* CACHE_MODULES = "cache/modules/";
static const char* CACHE_REPOSITORIES = "cache/repositories/";
static const char* MODULES = "modules/";
static const char* TMP = "/tmp/";


void checkOutdatedModules(std::set<std::string>& modules);
void cleanCache();
Dependencies collectDependencies(const Json::Value& dependencies);
void collectLocalModuleData();
Module collectModuleData(const std::string& path, const std::string& filename);
void create(const StringList& params);
void createBasicFolderStructure();
void createLocalLibrary();
void deinit();
bool download(const std::string& url, const std::string& target, bool allowCleanup = true);
void execute(const std::string& command);
void init();
void install(const StringList& params);
void installModule(const std::string& repo, const std::string& module);
bool isLocalLibrary();
void list();
void loadConfig();
void prepareModuleInstallation(const std::string& repo, const std::string& moduleName);
void readJsonFile(const std::string& filename, Json::Value& result);
void remove(const StringList& params);
void search(const StringList& params);
void update();
void upgrade(const StringList& params);


std::string mBaseFolder;
std::string mCurrendFolder;
StringList mDownloadedFiles;
std::string mLibraryFolder;
Repository mLocalRepository("local");
Utils::Common::StdOutLogger mLogger;
Repository mMissingDependencies("missing");
StringList mParameters;
Repository mRepository;
e_Action mAction = None;


static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
	size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
	return written;
}

void checkOutdatedModules(std::set<std::string>& outdatedModules)
{
	// compare new index.json with local module information:
	// find all folders in local <repo> folder and compare their corresponding <repo>/list/<module>.json [version] field
	// with the version in the index.json file

	Repository::Modules local = mLocalRepository.getModules();

	std::string filename = mBaseFolder + CACHE_REPOSITORIES + mRepository.getName() + ".json";

	// check if filename exists
	if ( !::Utils::Tools::Files::exists(filename) ) {
		// no configuration file exists
		std::cout << "!!! File '" + filename + "' not found" << std::endl;
		return;

		//throw ObjectiveScript::Common::Exceptions::Exception("!!! File '" + filename + "' not found");
	}

	Json::Value config;
	readJsonFile(filename, config);

	// process Json::Value in Repository
	mRepository.processIndex(config);

	Repository::Modules remote = mRepository.getModules();

	for ( Repository::Modules::const_iterator localIt = local.begin(); localIt != local.end(); ++localIt ) {
		for ( Repository::Modules::const_iterator remoteIt = remote.begin(); remoteIt != remote.end(); ++remoteIt ) {
			if ( localIt->mVersion < remoteIt->mVersion ) {
				outdatedModules.insert(remoteIt->mShortName);
			}
		}
	}
}

void cleanCache()
{
	// delete all downloaded files from cache

	//std::cout << "Cleaning cache..." << std::endl;

	for ( StringList::const_iterator it = mDownloadedFiles.begin(); it != mDownloadedFiles.end(); ++it ) {
		execute("rm " + (*it));
	}
}

Dependencies collectDependencies(const Json::Value& dependencies)
{
	Dependencies result;

	for ( Json::Value::Members::const_iterator depIt = dependencies.members().begin(); depIt != dependencies.members().end(); ++depIt ) {
		std::string moduleName = (*depIt)["module"].asString();
		std::string version_max = depIt->isMember("version_max") ? (*depIt)["version_max"].asString() : "";
		std::string version_min = (*depIt)["version_min"].asString();

		result.insert(
			Dependency(moduleName, version_min, version_max)
		);
	}

	return result;
}

void collectLocalModuleData()
{
	// iterate over all directories in the modules directory and collect all "module.json" files

	std::string base = mLibraryFolder;

	DIR* dir = opendir(base.c_str());
	if ( !dir ) {
		std::cout << "!!! Error while accessing modules directory" << std::endl;
		return;
	}

 	struct dirent* entry = readdir(dir);

	while ( entry ) {
		if ( entry->d_type == DT_DIR ) {
			std::string filename = "module.json";
			std::string path = base + std::string(entry->d_name) + "/";

			if ( ::Utils::Tools::Files::exists(path + filename) ) {
				mLocalRepository.addModule(
					collectModuleData(path, filename)
				);
			}
		}

		entry = readdir(dir);
	}

	closedir(dir);
}

Module collectModuleData(const std::string& path, const std::string& filename)
{
	//std::cout << "Collecting module data from " << path << std::endl;

	Json::Value config;
	readJsonFile(path + "/" + filename, config);

	std::string description = config["description"].asString();
	std::string name_long = config["name"].asString();
	std::string name_short = config["name_short"].asString();
	std::string version = config["version"].asString();

	Module module(name_short, version);
	module.mDescription = description;
	module.mDependencies = collectDependencies(config["dependencies"]);
	module.mInstalledDirectory = path;
	module.mLongName = name_long;
	module.mVersion = version;

	return module;
}

/*
 * creates a module package ("<module>.json", "<module>_<version>.tar.gz")
 * does NOT upload the package to a repository
 */
void create(const StringList& params)
{
	// (1) collect module information from given "<directory>/module.json"
	// (2) create "<module>.json", "<module>_<version>.tar.gz"

	if ( params.empty() || params.size() != 1 ) {
		std::cout << "!!! Invalid number of parameters" << std::endl;
		return;
	}

	// TODO: module name is not allowed to end with '/'
	std::string moduleName = params.front();
	std::string path = moduleName;
	std::string filename = "module.json";

	Module module = collectModuleData(path, filename);

	{	// create <module>.json
		std::cout << "Creating module information '" << moduleName + ".json'" << std::endl;

		execute("cp " + path + "/" + filename + " " + moduleName + ".json");
	}

	{	// create package
		std::cout << "Creating module package '" << path + "_" + module.mVersion + ".tar.gz'" << std::endl;

		execute("tar -cjf " + path + "_" + module.mVersion + ".tar.gz " + path);
	}
}

void createBasicFolderStructure()
{
	std::string command;
	std::string path;

	// create "<base>/cache/modules" folder
	path = mBaseFolder + CACHE_MODULES;
	if ( !Utils::Tools::Files::exists(path) ) {
		execute("mkdir -p " + path);
	}

	// create "<base>/cache/repositories" folder
	path = mBaseFolder + CACHE_REPOSITORIES;
	if ( !Utils::Tools::Files::exists(path) ) {
		execute("mkdir -p " + path);
	}

	// create config file
	execute("touch " + mLibraryFolder + "/odepend.json");
}

void createLocalLibrary()
{
	// create config file
	execute("touch " + mCurrendFolder + "/odepend.json");
}

void deinit()
{
	// put de-initialization stuff here
}

bool download(const std::string& url, const std::string& target, bool allowCleanup)
{
	//std::cout << "Downloading " << url << " => " << target << std::endl;

	CURL *curl_handle;
	FILE *pagefile;
	bool result = false;

	curl_global_init(CURL_GLOBAL_ALL);

	/* init the curl session */
	curl_handle = curl_easy_init();

	/* set URL to get here */
	curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());

	/* Switch on full protocol/debug output while testing */
	curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 0L);

	/* disable progress meter, set to 0L to enable and disable debug output */
	curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);

	/* send all data to this function  */
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

	/* open the file */
	pagefile = fopen(target.c_str(), "wb");
	if ( pagefile ) {
		/* write the page body to this file handle */
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile);

		/* get it! */
		curl_easy_perform(curl_handle);

		/* close the header file */
		fclose(pagefile);

		if ( allowCleanup ) {
			mDownloadedFiles.push_back(target);
		}

		result = true;
	}

	/* cleanup curl stuff */
	curl_easy_cleanup(curl_handle);

	return result;
}

void execute(const std::string& command)
{
	//std::cout << "Executing '" << command << "'" << std::endl;

	system(command.c_str());
}

void info(const StringList& params)
{
	// (1) collect local module data
	// (2) print module information for requested module

	if ( params.empty() || params.size() != 1 ) {
		std::cout << "!!! Invalid number of parameters" << std::endl;
		return;
	}

	collectLocalModuleData();

	bool found = false;
	Repository::Modules local = mLocalRepository.getModules();
	std::string demandedModule = params.front();

	for ( Repository::Modules::const_iterator localIt = local.begin(); localIt != local.end(); ++localIt ) {
		if ( localIt->mShortName == demandedModule ) {
			found = true;

			std::cout << localIt->mShortName << "(" << localIt->mVersion << "): " << localIt->mLongName << std::endl;
		}
	}

	if ( !found ) {
		std::cout << "!!! Requested module '" << demandedModule << "' is not installed" << std::endl;
	}
}

void init()
{
	// put initialization stuff here
	mBaseFolder = TMP;

	{	// set library home path
		const char* homepath = getenv(ObjectiveScript::OBJECTIVESCRIPT_LIBRARY);
		if ( homepath ) {
			std::string path = std::string(homepath);

			// only read first entry
			if ( !path.empty() ) {
				std::string left;
				std::string right;

				Utils::Tools::splitBy(path, ':', left, right);

				mLibraryFolder = left + "/";
			}
		}
	}

	{	// set current folder
		char cCurrentPath[FILENAME_MAX];
		if ( !GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)) )  {
			return;
		}

		cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

		mCurrendFolder = std::string(cCurrentPath) + "/";

		if ( isLocalLibrary() ) {
			mLibraryFolder = mCurrendFolder;
		}
	}

	createBasicFolderStructure();

	loadConfig();
}

void install(const StringList& params)
{
	// (1) prepare dependencies
	// (2) install missing dependencies
	// (3) installed requested modules

	if ( params.empty() ) {
		std::cout << "!!! Invalid number of parameters" << std::endl;
		return;
	}

	collectLocalModuleData();

	std::cout << "Preparing dependencies..." << std::endl;

	for ( StringList::const_iterator it = params.begin(); it != params.end(); ++it ) {
		std::string moduleName;
		std::string version;

		Utils::Tools::splitBy((*it), ':', moduleName, version);

		prepareModuleInstallation(mRepository.getURL(), moduleName);
	}

	// add all other requested modules to missing modules to prevent multiple installations of the same modules
	for ( StringList::const_iterator it = params.begin(); it != params.end(); ++it ) {
		std::string moduleName;
		std::string version;

		Utils::Tools::splitBy((*it), ':', moduleName, version);

		mMissingDependencies.addModule(
			Module(moduleName, version)
		);
	}

	Repository::Modules missing = mMissingDependencies.getModules();
	for ( Repository::Modules::const_iterator moduleIt = missing.begin(); moduleIt != missing.end(); ++moduleIt ) {
		installModule(mRepository.getURL(), moduleIt->mShortName);
	}
}

void installModule(const std::string& repo, const std::string& module)
{
	std::cout << "Installing module '" << module << "' from '" << repo << "'..." << std::endl;

	std::string module_config = mBaseFolder + CACHE_MODULES + module + ".json";

	if ( !Utils::Tools::Files::exists(module_config) ) {
		std::cout << "!!! Module information missing for module '" << module << "'" << std::endl;
		return;
	}

	Json::Value config;
	readJsonFile(module_config, config);

	if ( !config.isMember("target") ) {
		std::cout << "!!! No target entry found in module information" << std::endl;
		return;
	}
	if ( !config["target"].isMember("type") ) {
		std::cout << "!!! No type entry found in target module information" << std::endl;
		return;
	}

	std::string type = config["target"]["type"].asString();
	std::string url;

	if ( type == "internal" ) {
		if ( !config["target"].isMember("url") ) {
			std::cout << "!!! No url entry found in target module information" << std::endl;
			return;
		}

		url = repo + MODULES + config["target"]["url"].asString();
	}
	else if ( type == "virtual" ) {
		// no url
	}
	else {
		std::cout << "!!! Currently only internal targets are supported" << std::endl;
		return;
	}

	std::string module_archive = mBaseFolder + CACHE_MODULES + module + "_" + config["version"].asString() + ".tar.gz";

	bool result = download(url, module_archive);
	if ( !result ) {
		std::cout << "!!! Failed to download target" << std::endl;
		return;
	}

	if ( type != "virtual ") {	// extract module archive to "<module>/"
		execute("tar xf " + module_archive + " -C " + mLibraryFolder);
	}

	// copy module config to "<module>/module.json"
	execute("cp " + module_config + " " + mLibraryFolder + module + "/module.json");
}

bool isLocalLibrary()
{
	return Utils::Tools::Files::exists(mCurrendFolder + "/odepend.json");
}

void list()
{
	collectLocalModuleData();

	Repository::Modules local = mLocalRepository.getModules();

	std::cout << local.size() << " module(s) installed." << std::endl;

	for ( Repository::Modules::const_iterator localIt = local.begin(); localIt != local.end(); ++localIt ) {
		std::cout << localIt->mShortName << "(" << localIt->mVersion << "): " << localIt->mLongName << std::endl;
	}
}

void loadConfig()
{
	std::string filename = mLibraryFolder + "odepend.json";

	Json::Value config;
	readJsonFile(filename, config);

	if ( !config.isMember("repository") ) {
		throw ObjectiveScript::Common::Exceptions::Exception("invalid repository condifuration");
	}

	Json::Value entry = config["repository"];

	// repository name
	// {
	if ( !entry.isMember("name") ) {
		std::cout << "!!! Invalid repository name" << std::endl;
		return;
	}

	std::string name = entry["name"].asString();
	// }

	// repository URL
	// {
	if ( !entry.isMember("url") ) {
		std::cout << "!!! Invalid repository url" << std::endl;
		return;
	}

	std::string url = entry["url"].asString();

	// make sure the URL ends with a slash
	if ( url[url.size() - 1] != '/' ) {
		url += '/';
	}
	// }

	Repository repository(name);
	repository.setURL(url);

	mRepository = repository;
}

void printUsage()
{
	std::cout << "Usage: odepend [args...]" << std::endl;
	std::cout << std::endl;
	std::cout << "create                     Create a new module from a given directory" << std::endl;
	std::cout << "help                       This help" << std::endl;
	std::cout << "info                       Print information about requested module" << std::endl;
	std::cout << "install                    Install new module" << std::endl;
	std::cout << "list                       List all installed modules" << std::endl;
	std::cout << "remove                     Remove an installed module" << std::endl;
	std::cout << "search                     Search for a module" << std::endl;
	std::cout << "update                     Update repository indices" << std::endl;
	std::cout << "upgrade                    Upgrade outdated modules" << std::endl;
	std::cout << "--locallibrary             Use current directory as library" << std::endl;
	std::cout << "--version                  Version information" << std::endl;
	std::cout << std::endl;
}

void printVersion()
{
	std::cout << "ObjectiveScript Package Manager 0.5.7 (cli)" << std::endl;
	std::cout << "Copyright (c) 2014-2017 Michael Adelmann" << std::endl;
	std::cout << "" << std::endl;
}

void processParameters(int argc, const char* argv[])
{
	mAction = Help;

	if ( argc > 1 ) {
		std::string arg1 = argv[1];

		if ( Utils::Tools::StringCompare(arg1, "create") ) {
			mAction = Create;
		}
		else if ( Utils::Tools::StringCompare(arg1, "help") ) {
			mAction = Help;
		}
		else if ( Utils::Tools::StringCompare(arg1, "info") ) {
			mAction = Info;
		}
		else if ( Utils::Tools::StringCompare(arg1, "install") ) {
			mAction = Install;
		}
		else if ( Utils::Tools::StringCompare(arg1, "list") ) {
			mAction = List;
		}
		else if ( Utils::Tools::StringCompare(arg1, "remove") ) {
			mAction = Remove;
		}
		else if ( Utils::Tools::StringCompare(arg1, "search") ) {
			mAction = Search;
		}
		else if ( Utils::Tools::StringCompare(arg1, "update") ) {
			mAction = Update;
		}
		else if ( Utils::Tools::StringCompare(arg1, "upgrade") ) {
			mAction = Upgrade;
		}
		else if ( Utils::Tools::StringCompare(arg1, "--locallibrary") ) {
			mAction = CreateLocalLibrary;
		}
		else if ( Utils::Tools::StringCompare(arg1, "--version") ) {
			mAction = Version;
		}
	}

	for ( int i = 2; i < argc; ++i ) {
		mParameters.push_back(std::string(argv[i]));
	}
}

void prepareModuleInstallation(const std::string& repo, const std::string& moduleName)
{
	//std::cout << "Preparing module '" << moduleName << "' from '" << repo << "'..." << std::endl;

	// (1) download module information from repository
	// (2) collect dependencies from module information
	// (3) check dependencies against local repository and download module information for missing modules

	std::string path = mBaseFolder + CACHE_MODULES;
	std::string filename = moduleName + ".json";
	std::string module_config = path + filename;

	bool result = download(repo + "/" + MODULES + moduleName + ".json", module_config);
	if ( !result ) {
		std::cout << "!!! Download of module information for '" << moduleName << "' failed" << std::endl;
		return;
	}

	Module module = collectModuleData(path, filename);

	Repository::Modules local = mLocalRepository.getModules();
	for ( Dependencies::const_iterator depIt = module.mDependencies.begin(); depIt != module.mDependencies.end(); ++depIt ) {
		bool found = false;

		// look up dependency in already installed modules
		for ( Repository::Modules::const_iterator localIt = local.begin(); localIt != local.end(); ++localIt ) {
			if ( localIt->mShortName == depIt->mModule ) {
				found = true;
				break;
			}
		}

		if ( !found ) {
			// dependee module is not yet installed
			std::cout << "Need to install dependend module '" << depIt->mModule << "'" << std::endl;

			Module dependee(depIt->mModule, depIt->mMinVersion);

			mMissingDependencies.addModule(dependee);

			prepareModuleInstallation(repo, dependee.mShortName);
		}
	}
}

void readJsonFile(const std::string& filename, Json::Value& result)
{
	// load contents of filename into Json::Value

	std::fstream stream;
	stream.open(filename.c_str(), std::ios::in);	// open for reading
	std::string data((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());	// read stream
	stream.close();

	result = Json::Parser::parse(data);
}

void remove(const StringList& params)
{
	// (1) check if the requested modules are actually installed
	// (2) remove them by deleting their complete directory

	if ( mParameters.empty() ) {
		std::cout << "!!! Invalid number of parameters" << std::endl;
		return;
	}

	collectLocalModuleData();

	Repository::Modules local = mLocalRepository.getModules();

	for ( StringList::const_iterator moduleIt = params.begin(); moduleIt != params.end(); ++ moduleIt ) {
		bool found = false;

		for ( Repository::Modules::const_iterator localIt = local.begin(); localIt != local.end(); ++localIt ) {
			if ( localIt->mShortName == (*moduleIt) ) {
				found = true;

				std::cout << "Removing module '" << localIt->mShortName << "' from '" << localIt->mInstalledDirectory << "'..." << std::endl;

				execute("rm -r " + localIt->mInstalledDirectory);
			}
		}

		if ( !found ) {
			std::cout << "!!! Module '" << (*moduleIt) << "' cannot be removed because it is not installed" << std::endl;
		}
	}
}

void search(const StringList& params)
{
	// (1) load cached repositories from disk
	// (2) substr-search through all entries for given params

	if ( params.empty() || params.size() != 1 ) {
		std::cout << "!!! Invalid number of parameters" << std::endl;
		return;
	}

	std::string filename = mBaseFolder + CACHE_REPOSITORIES + mRepository.getName() + ".json";

	// check if filename exists
	if ( !::Utils::Tools::Files::exists(filename) ) {
		// no configuration file exists
		std::cout << "!!! File '" + filename + "' not found" << std::endl;
		return;
	}

	Json::Value config;
	readJsonFile(filename, config);

	// TODO: implement search
}

void update()
{
	// download <URL>/<branch>/index.json

	std::cout << "Updating repository \"" << mRepository.getName() << "\"..." << std::endl;

	std::string url = mRepository.getURL() + "/index.json";
	std::string filename = mBaseFolder + CACHE_REPOSITORIES + mRepository.getName() + ".json";

	bool result = download(url, filename, false);
	if ( result ) {
		std::cout << "Updated index for \"" << mRepository.getURL() << "\"" << std::endl;
	}
	else {
		std::cout << "!!! Error while updating index for " << mRepository.getURL() << std::endl;
	}
}

void upgrade(const StringList& params)
{
	(void)params;

	// (1) retrieve outdated modules
	// (2) list all found modules
	// (3) install new modules if any are available

	collectLocalModuleData();

	std::set<std::string> outdatedModules;

	checkOutdatedModules(outdatedModules);

	std::cout << "Need to upgrade " << outdatedModules.size() << " module(s)..." << std::endl;

	if ( !outdatedModules.empty() ) {
		// replace current parameters with outdated modules to install
		mParameters.clear();

		std::cout << "New module(s): ";
		for ( std::set<std::string>::const_iterator it = outdatedModules.begin(); it != outdatedModules.end(); ++it ) {
			std::cout << (*it) << " ";

			// add outdated module name to global parameters
			mParameters.push_back((*it));
		}
		std::cout << std::endl;

		// TODO: if mParameters contains values upgrade only the modules that are set in mParameters

		// install new versions of all outdated modules
		install(mParameters);
	}
}

int main(int argc, const char* argv[])
{
#ifdef _WIN32
	// Memory leak detection
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	// Memory leak detection
#endif

	processParameters(argc, argv);

	init();

	switch ( mAction ) {
		case Create: create(mParameters); break;
		case CreateLocalLibrary: createLocalLibrary(); break;
		case Help: printUsage(); break;
		case Info: info(mParameters); break;
		case Install: install(mParameters); break;
		case List: list(); break;
		case None: break;
		case Remove: remove(mParameters); break;
		case Search: search(mParameters); break;
		case Update: update(); break;
		case Upgrade: upgrade(mParameters); break;
		case Version: printVersion(); break;
	}

	cleanCache();

	return 0;
}
