
#ifndef Slang_slang_pkg_Consts_h
#define Slang_slang_pkg_Consts_h


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


// Constants
static const std::string CONFIG_APPS               = ".slang/apps/";
static const std::string CONFIG_CACHE_MODULES      = ".slang/cache/modules/";
static const std::string CONFIG_CACHE_REPOSITORIES = ".slang/cache/repositories/";
static const std::string CONFIG_FILE               = ".slang/config.json";
static const std::string CONFIG_FOLDER             = ".slang/";
#ifdef __APPLE__
static const std::string CONFIG_SCRIPTS            = "/var/lib/slang/scripts/";
#endif
#ifdef __linux__
static const std::string CONFIG_SCRIPTS            = "/var/lib/slang/scripts/";
#endif
#ifdef _WIN32
static const std::string CONFIG_SCRIPTS            = "";
#endif
static const std::string FILE_VERSION_SEPARATOR    = "_";
static const std::string MODULES                   = "modules/";
static const std::string REMOTE_REPOSITORY_NAME    = "main";
static const std::string REMOTE_REPOSITORY_URL     = "https://slang-lang.org/repository/stable";
static const std::string TMP                       = "/tmp/";
static const std::string UPLOAD_PATH               = "upload/";
static const char VERSION_SEPARATOR                = ':';


// Actions
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


// Error codes
static const int32_t OKAY = 0;
static const int32_t ERROR_SYSTEM = 1;
static const int32_t ERROR_ARCHITECTURE = 2;
static const int32_t ERROR_MODULE_DIRECTORY = 3;
static const int32_t ERROR_INDEX_UPDATE = 4;


#endif
