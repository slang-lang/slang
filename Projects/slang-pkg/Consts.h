
#ifndef Slang_slang_pkg_Consts_h
#define Slang_slang_pkg_Consts_h


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


// Constants
static const std::string CACHE_MODULES          = "cache/modules/";
static const std::string CACHE_REPOSITORIES     = "cache/repositories/";
static const std::string CONFIG_APPS            = ".slang/apps/";
static const std::string CONFIG_FILE            = ".slang/config.json";
static const std::string CONFIG_FOLDER          = ".slang/";
static const std::string CONFIG_SCRIPTS         = ".slang/scripts/";
static const std::string FILE_VERSION_SEPARATOR = "_";
static const std::string MODULES                = "modules/";
static const std::string REMOTE_REPOSITORY_NAME = "main";
static const std::string REMOTE_REPOSITORY_URL  = "https://slang-lang.org/repository/stable";
static const std::string TMP                    = "/tmp/";
static const std::string UPLOAD_PATH            = "upload/";
static const char VERSION_SEPARATOR             = ':';


// Error codes
static const int32_t OKAY = 0;
static const int32_t ERROR_SYSTEM = 1;
static const int32_t ERROR_ARCHITECTURE = 2;
static const int32_t ERROR_MODULE_DIRECTORY = 3;
static const int32_t ERROR_INDEX_UPDATE = 4;


#endif
