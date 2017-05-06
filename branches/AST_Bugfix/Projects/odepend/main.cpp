
// Library includes
#include <dirent.h>
#include <set>
#include <string>
#include <stdlib.h>
#include <curl/curl.h>
#include <Json/Json.h>

// Project includes
#include <Common/StdOutLogger.h>
#include <Core/Consts.h>
#include <Core/Types.h>
#include <Tools/Files.h>
#include <Tools/Strings.h>
#include <Utils.h>
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
	None,
	Help,
	Install,
	List,
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


void checkOutdatedModules(std::set<std::string>& modules);
void cleanCache();
Dependencies collectDependencies(const Json::Value& dependencies);
void collectLocalModuleData();
Module collectModuleData(const std::string& path, const std::string& filename);
void createBasicFolderStructur();
void deinit();
bool download(const std::string& url, const std::string& target, bool allowCleanup = true);
void init();
void install(const StringList& params);
void installModule(const std::string& repo, const std::string& module);
void list();
void loadConfig();
void prepareModuleInstallation(const std::string& repo, const std::string& moduleName);
void readJsonFile(const std::string& filename, Json::Value& result);
void remove(const StringList& params);
void search(const StringList& params);
void update();
void upgrade();


std::string mBaseFolder;
StringList mDownloadedFiles;
Repository mLocalRepository("local");
Utils::Common::StdOutLogger mLogger;
Repository mMissingDependencies("missing");
StringList mParameters;
std::list<Repository> mRepositories;
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

	for ( std::list<Repository>::iterator repoIt = mRepositories.begin(); repoIt != mRepositories.end(); ++repoIt ) {
		std::string filename = mBaseFolder + CACHE_REPOSITORIES + repoIt->getName() + "_index.json";

		// check if filename exists
		if ( !::Utils::Tools::Files::exists(filename) ) {
			// no configuration file exists
			std::cout << "!!! File '" + filename + "' not found" << std::endl;
			continue;
		}

		Json::Value config;
		readJsonFile(filename, config);

		// process Json::Value in Repository
		repoIt->processIndex(config);

		Repository::Modules remote = repoIt->getModules();

		for ( Repository::Modules::const_iterator localIt = local.begin(); localIt != local.end(); ++localIt ) {
			for ( Repository::Modules::const_iterator remoteIt = remote.begin(); remoteIt != remote.end(); ++remoteIt ) {
				if ( localIt->mVersion < remoteIt->mVersion ) {
					outdatedModules.insert(remoteIt->mShortName);
				}
			}
		}
	}
}

void cleanCache()
{
	// delete all downloaded files from cache

	//std::cout << "Cleaning cache..." << std::endl;

	for ( StringList::const_iterator it = mDownloadedFiles.begin(); it != mDownloadedFiles.end(); ++it ) {
		std::string command = "rm " + (*it);

		system(command.c_str());
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

	std::string base = mBaseFolder + MODULES;

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

void createBasicFolderStructur()
{
	std::string command;
	std::string path;

	// create "<base>/cache/modules" folder
	path = mBaseFolder + CACHE_MODULES;
	if ( !Utils::Tools::Files::exists(path) ) {
		command = "mkdir -p " + path;
		system(command.c_str());
	}

	// create "<base>/cache/repositories" folder
	path = mBaseFolder + CACHE_REPOSITORIES;
	if ( !Utils::Tools::Files::exists(path) ) {
		command = "mkdir -p " + path;
		system(command.c_str());
	}

	// create "<base>/modules" directory
	path = mBaseFolder + MODULES;
	if ( !Utils::Tools::Files::exists(path) ) {
		command = "mkdir " + path;
		system(command.c_str());
	}
}

void deinit()
{
	// put de-initialization stuff here
}

bool download(const std::string& url, const std::string& target, bool allowCleanup)
{
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

	//std::cout << "Downloading " << url << " => " << target << std::endl;

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

void init()
{
	// put initialization stuff here

	const char* homepath = getenv(ObjectiveScript::OBJECTIVESCRIPT_LIBRARY);
	if ( homepath ) {
		std::string path = std::string(homepath);

		// only read first entry
		if ( !path.empty() ) {
			std::string left;
			std::string right;

			Utils::Tools::splitBy(path, ':', left, right);

			mBaseFolder = left + "/";
		}
	}

	createBasicFolderStructur();

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

	// TODO: make sure that the repository path ends with an '/'

	for ( StringList::const_iterator it = params.begin(); it != params.end(); ++it ) {
		prepareModuleInstallation("https://michaeladelmann.ticketsharing.net/repo/stable/", (*it));
	}

	// add all other requested modules to missing modules to prevent multiple installations of the same modules
	for ( StringList::const_iterator it = params.begin(); it != params.end(); ++it ) {
		mMissingDependencies.addModule(
			Module((*it), "")
		);
	}

	Repository::Modules missing = mMissingDependencies.getModules();
	for ( Repository::Modules::const_iterator moduleIt = missing.begin(); moduleIt != missing.end(); ++moduleIt ) {
		installModule("https://michaeladelmann.ticketsharing.net/repo/stable/", moduleIt->mShortName);
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
		std::string command = "tar xf " + module_archive + " -C " + mBaseFolder + MODULES;
		//std::cout << "command = " << command << std::endl;

		system(command.c_str());
	}

	{	// copy module config to "<module>/module.json"
		std::string command = "cp " + module_config + " " + mBaseFolder + MODULES + module + "/module.json";
		//std::cout << "command = " << command << std::endl;

		system(command.c_str());
	}
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
	std::string filename = mBaseFolder + "/config.json";

	Json::Value config;
	readJsonFile(filename, config);

	if ( config.isMember("repositories") ) {
		int count = 0;
		Json::Value::Members repos = config["repositories"].members();

		for ( Json::Value::Members::const_iterator repoIt = repos.begin(); repoIt != repos.end(); ++repoIt, ++count ) {
			Json::Value entry = (*repoIt);

			if ( !entry.isMember("name") ) {
				std::cout << "!!! Invalid repository: entry " << count << std::endl;
				continue;
			}
			std::string name_short = entry["name"].asString();

			if ( !entry.isMember("url") ) {
				std::cout << "!!! Invalid repository: entry " << count << std::endl;
				continue;
			}
			std::string url = entry["url"].asString();

			Repository repository(name_short);
			repository.setURL(url);

			mRepositories.push_back(repository);
		}
	}
}

void printUsage()
{
	std::cout << "Usage: odepend [args...]" << std::endl;
	std::cout << std::endl;
	std::cout << "help                       This help" << std::endl;
	std::cout << "install                    Install new module" << std::endl;
	std::cout << "list                       List all installed modules" << std::endl;
	std::cout << "remove                     Remove an installed module" << std::endl;
	std::cout << "search                     Search for a module" << std::endl;
	std::cout << "update                     Update repository indices" << std::endl;
	std::cout << "upgrade                    Upgrade outdated modules" << std::endl;
	std::cout << "version                    Version information" << std::endl;
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

		if ( Utils::Tools::StringCompare(arg1, "help") ) {
			mAction = Help;
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
		else if ( Utils::Tools::StringCompare(arg1, "version") ) {
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

				std::string path = localIt->mInstalledDirectory;

				std::cout << "Removing module '" << localIt->mShortName << "' from '" << path << "'..." << std::endl;

				std::string command = "rm -r " + path;

				system(command.c_str());
			}
		}

		if ( !found ) {
			std::cout << "!!! Module '" << (*moduleIt) << "' cannot be removed because it is not installed" << std::endl;
		}
	}
}

void search(const StringList& params)
{
	if ( params.empty() ) {
		std::cout << "!!! Invalid number of parameters" << std::endl;
		return;
	}

	// TODO: implement search
}

void update()
{
	// download <URL>/<branch>/index.json

	std::cout << "Updating " << mRepositories.size()  << " repositories..." << std::endl;

	for ( std::list<Repository>::iterator it = mRepositories.begin(); it != mRepositories.end(); ++it ) {
		std::string filename = mBaseFolder + CACHE_REPOSITORIES + it->getName() + "_index.json";
		std::string url = it->getURL() + "/index.json";

		bool result = download(url, filename, false);
		if ( result ) {
			std::cout << "Updated index for " << it->getURL() << std::endl;
		}
		else {
			std::cout << "!!! Error while updating index for " << it->getURL() << std::endl;
		}
	}

	std::cout << "Done." << std::endl;
}

void upgrade()
{
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
		case Help: printUsage(); break;
		case Install: install(mParameters); break;
		case List: list(); break;
		case None: break;
		case Remove: remove(mParameters); break;
		case Search: search(mParameters); break;
		case Update: update(); break;
		case Upgrade: upgrade(); break;
		case Version: printVersion(); break;
	}

	cleanCache();

	return 0;
}
