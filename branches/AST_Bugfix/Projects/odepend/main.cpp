
// Library includes
#include <dirent.h>
#include <set>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
using namespace ObjectiveScript;

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


void checkOutdatedModules(std::set<std::string>& modules);
void collectLocalModuleData();
void collectModuleData(const std::string& filename);
void createBasicFolderStructur();
void deinit();
bool download(const std::string& url, const std::string& target);
void init();
void install();
void installModule(const std::string& repo, const std::string& module);
void loadConfig();
void readJsonFile(const std::string& filename, Json::Value& result);
void search(const StringList& params);
void update();
void upgrade();

std::string mBaseFolder;
StringList mDownloadedFiles;
Repository mLocalRepository("local");
Utils::Common::StdOutLogger mLogger;
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
		std::string filename = mBaseFolder + "/cache/repositories/" + repoIt->getName() + "_index.json";

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

void collectLocalModuleData()
{
	// iterate over all directories in the modules directory and collect all "module.json" files

	std::string base = mBaseFolder + "/modules/";

	DIR* dir = opendir(base.c_str());
	if ( !dir ) {
		std::cout << "!!! Error while accessing modules directory" << std::endl;
		return;
	}

 	struct dirent* entry = readdir(dir);

	while ( entry ) {
		if ( entry->d_type == DT_DIR ) {
			std::string filename = base + std::string(entry->d_name) + "/module.json";

			if ( ::Utils::Tools::Files::exists(filename) ) {
				collectModuleData(filename);
			}
		}

		entry = readdir(dir);
	}

	closedir(dir);
}

void collectModuleData(const std::string& filename)
{
	std::cout << "Collecting module data from " << filename << std::endl;

	Json::Value config;
	readJsonFile(filename, config);

	std::string description = config["description"].asString();
	std::string name_long = config["name"].asString();
	std::string name_short = config["name_short"].asString();
	std::string version = config["version"].asString();

	Module module(name_short, version);

	mLocalRepository.addModule(module);
}

void createBasicFolderStructur()
{
	std::string command;
	std::string path;

	// create "<base>/cache/modules" folder
	path = mBaseFolder + "/cache/modules/";
	if ( !Utils::Tools::Files::exists(path) ) {
		command = "mkdir -p " + path;
		system(command.c_str());
	}

	// create "<base>/cache/repositories" folder
	path = mBaseFolder + "/cache/repositories/";
	if ( !Utils::Tools::Files::exists(path) ) {
		command = "mkdir -p " + path;
		system(command.c_str());
	}

	// create "<base>/modules" directory
	path = mBaseFolder + "/modules/";
	if ( !Utils::Tools::Files::exists(path) ) {
		command = "mkdir " + path;
		system(command.c_str());
	}
}

void deinit()
{
	// put de-initialization stuff here
}

bool download(const std::string& url, const std::string& target)
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

	/* open the file */
	pagefile = fopen(target.c_str(), "wb");
	if ( pagefile ) {
		/* write the page body to this file handle */
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile);

		/* get it! */
		curl_easy_perform(curl_handle);

		/* close the header file */
		fclose(pagefile);

		mDownloadedFiles.push_back(target);

		result = true;
	}

	/* cleanup curl stuff */
	curl_easy_cleanup(curl_handle);

	return result;
}

void init()
{
	// put initialization stuff here

	const char* homepath = getenv(OBJECTIVESCRIPT_LIBRARY);
	if ( homepath ) {
		std::string path = std::string(homepath);

		// only read first entry
		if ( !path.empty() ) {
			std::string left;
			std::string right;

			Utils::Tools::splitBy(path, ':', left, right);

			mBaseFolder = left;
		}
	}

	createBasicFolderStructur();

	loadConfig();
}

void install()
{
	if ( mParameters.empty() ) {
		std::cout << "invalid number of parameters!" << std::endl;
		return;
	}

	for ( StringList::const_iterator it = mParameters.begin(); it != mParameters.end(); ++it ) {
		installModule("https://michaeladelmann.ticketsharing.net/repo/stable", (*it));
	}
}

void installModule(const std::string& repo, const std::string& module)
{
	std::string module_config = mBaseFolder + "/cache/modules/" + module + ".json";

	bool result = download(repo + "/modules/" + module + ".json", module_config);
	if ( !result ) {
		std::cout << "!!! Download of module information for '" << module << "' failed" << std::endl;
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

		url = repo + "/modules/" + config["target"]["url"].asString();
	}
	else if ( type == "virtual" ) {
		// no url
	}
	else {
		std::cout << "!!! Currently only internal targets are supported" << std::endl;
		return;
	}

	std::string module_archive = mBaseFolder + "/cache/modules/" + module + "_" + config["version"].asString() + ".tar.gz";

	result = download(url, module_archive);
	if ( !result ) {
		std::cout << "!!! Failed to download target" << std::endl;
		return;
	}

	if ( type != "virtual ") {	// extract module archive to "<module>/"
		std::string command = "tar xf " + module_archive + " -C " + mBaseFolder + "/modules/";
		std::cout << "command = " << command << std::endl;

		system(command.c_str());
	}

	{	// copy module config to "<module>/module.json"
		std::string command = "cp " + module_config + " " + mBaseFolder + "/modules/" + module + "/module.json";
		std::cout << "command = " << command << std::endl;

		system(command.c_str());
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
				std::cout << "invalid repository: entry " << count << std::endl;
				continue;
			}
			std::string name_short = entry["name"].asString();

			if ( !entry.isMember("url") ) {
				std::cout << "invalid repository: entry " << count << std::endl;
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
	std::cout << "list                       List all available modules" << std::endl;
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

void readJsonFile(const std::string& filename, Json::Value& result)
{
	// load contents of filename into Json::Value
	std::fstream stream;
	stream.open(filename.c_str(), std::ios::in);	// open for reading
	std::string data((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());	// read stream
	stream.close();

	result = Json::Parser::parse(data);
}

void search(const StringList& params)
{
	(void)params;
}

void update()
{
	// download <URL>/<branch>/index.json

	std::cout << "Updating " << mRepositories.size()  << " repositories..." << std::endl;

	for ( std::list<Repository>::iterator it = mRepositories.begin(); it != mRepositories.end(); ++it ) {
		std::string filename = mBaseFolder + "/cache/repositories/" + it->getName() + "_index.json";
		std::string url = it->getURL() + "/index.json";

		bool result = download(url, filename);
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
		install();
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
		case None:
		case List:
		case Remove:
		case Search:
			break;
		case Help: printUsage(); break;
		case Install: install(); break;
		case Update: update(); break;
		case Upgrade: upgrade(); break;
		case Version: printVersion(); break;
	}

	// debug only
	for ( StringList::const_iterator it = mDownloadedFiles.begin(); it != mDownloadedFiles.end(); ++it ) {
		std::cout << (*it) << std::endl;
	}

	return 0;
}
