
// Library includes
#include <set>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <curl/curl.h>

// Project includes
#include <Common/StdOutLogger.h>
#include <Core/Types.h>
#include <Tools/Strings.h>
#include <Utils.h>

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


Utils::Common::StdOutLogger mLogger;
std::set<std::string> mOutdatedModules;

bool download(const std::string& url, const std::string& target);
void update();
void upgrade();

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
	size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
	return written;
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
	curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);

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
				// TODO: search
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

void update()
{
	// TODO: implement update
	// (1) download <URL>/<branch>/index/index.json
	// (2) compare new index.json with local module information:
	//     find all folders in local <repo> folder and compare their corresponding <repo>/list/<module>_<*>.json [version] field
	//     with the version in the index.json file
	// (3) list all outdated modules

	std::cout << "Updating..." << std::endl;

	bool result = download("https://michaeladelmann.ticketsharing.net/repo/stable/index/index.json", "index.json");
	if ( result ) {
		std::cout << "Updated index successfully." << std::endl;
	}
}

void upgrade()
{
	// TODO: implement upgrade

	if ( mOutdatedModules.empty() ) {
		std::cout << "No outdated modules found." << std::endl;
		return;
	}

	std::cout << "Upgrading " << mOutdatedModules.size() << " modules..." << std::endl;
}

int main(int argc, const char* argv[])
{
#ifdef _WIN32
	// Memory leak detection
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	// Memory leak detection
#endif

	processParameters(argc, argv);

	return 0;
}
