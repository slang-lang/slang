
// Library includes
#include <set>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <curl/curl.h>
#include <Json/Json.h>

// Project includes
#include <Common/StdOutLogger.h>
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


Utils::Common::StdOutLogger mLogger;
std::list<Repository> mRepositories;

void deinit();
bool download(const std::string& url, const std::string& target);
void init();
void search(const StringList& params);
void update();
void upgrade();


static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
	size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
	return written;
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

		result = true;
	}

	/* cleanup curl stuff */
	curl_easy_cleanup(curl_handle);

	return result;
}

void init()
{
	// put initialization stuff here

	Repository base_prerelease("ticketsharing_prerelease");
	base_prerelease.setURL("https://michaeladelmann.ticketsharing.net/repo/prerelease");

	mRepositories.push_back(base_prerelease);

	Repository base_stable("ticketsharing_stable");
	base_stable.setURL("https://michaeladelmann.ticketsharing.net/repo/stable");

	mRepositories.push_back(base_stable);
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
	StringList params;

	if ( argc > 1 ) {
		for ( int i = 1; i < argc; i++ ) {
			if ( Utils::Tools::StringCompare(argv[i], "help") ) {
				printUsage();

				exit(0);
			}
			else if ( Utils::Tools::StringCompare(argv[i], "install") ) {
				// TODO: install
			}
			else if ( Utils::Tools::StringCompare(argv[i], "list") ) {
				// TODO: list
			}
			else if ( Utils::Tools::StringCompare(argv[i], "remove") ) {
				// TODO: remove
			}
			else if ( Utils::Tools::StringCompare(argv[i], "search") ) {
				return search(params);
			}
			else if ( Utils::Tools::StringCompare(argv[i], "update") ) {
				return update();
			}
			else if ( Utils::Tools::StringCompare(argv[i], "upgrade") ) {
				return upgrade();
			}
			else if ( Utils::Tools::StringCompare(argv[i], "version") ) {
				printVersion();

				exit(0);
			}
		}
	}

	// no parameters found
	printUsage();

	exit(0);
}

void search(const StringList& params)
{
	(void)params;
}

void update()
{
	// TODO: implement update
	// (1) download <URL>/<branch>/index/index.json
	// (2) compare new index.json with local module information:
	//     find all folders in local <repo> folder and compare their corresponding <repo>/list/<module>_<*>.json [version] field
	//     with the version in the index.json file
	// (3) list all outdated modules

	std::cout << "Updating..." << std::endl;

	for ( std::list<Repository>::iterator it = mRepositories.begin(); it != mRepositories.end(); ++it ) {
		std::string filename = "tmp/indices/" + it->getName() + "_index.json";

		bool result = download(it->getURL() + "/index.json", filename);
		if ( result ) {
			std::cout << "Successfully updated index for " << it->getURL() << std::endl;
		}
		else {
			std::cout << "!!! Error while updating index for " << it->getURL() << std::endl;
		}
	}
}

void upgrade()
{
	std::set<std::string> outdatedModules;

	for ( std::list<Repository>::iterator repoIt = mRepositories.begin(); repoIt != mRepositories.end(); ++repoIt ) {
		std::string filename = "tmp/indices/" + repoIt->getName() + "_index.json";

		// check if filename exists
		if ( !::Utils::Tools::Files::exists(filename) ) {
			// no configuration file exists
			std::cout << "!!! File '" + filename + "' not found" << std::endl;
			continue;
		}

		// load contents of filename into Json::Value
		std::fstream stream;
		stream.open(filename.c_str(), std::ios::in);	// open for reading
		std::string data((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());	// read stream
		stream.close();

		Json::Value config = Json::Parser::parse(data);

		// process Json::Value in Repository
		repoIt->processIndex(config);

		Repository::Modules modules = repoIt->getModules();

		for ( Repository::Modules::const_iterator moduleIt = modules.begin(); moduleIt != modules.end(); ++moduleIt ) {
			if ( moduleIt->mActionNeeded == Module::Action::Update ) {
				outdatedModules.insert(moduleIt->mShortName);
			}
		}
	}

	std::cout << "Need to upgrade " << outdatedModules.size() << " modules..." << std::endl;

	// TODO: implement the actual upgrade
}

int main(int argc, const char* argv[])
{
#ifdef _WIN32
	// Memory leak detection
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	// Memory leak detection
#endif

	init();

	processParameters(argc, argv);

	return 0;
}
