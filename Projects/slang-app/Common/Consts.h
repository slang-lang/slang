
#ifndef Slang_slang_app_Consts_h
#define Slang_slang_app_Consts_h


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


// Constants
static const std::string CONFIG_FOLDER             = ".slang/";
static const std::string CONFIG_SERVER             = ".slang/server.json";
#ifdef __APPLE__
static const std::string CONFIG_SCRIPTS            = "/var/lib/slang/scripts/";
#endif
#ifdef __linux__
static const std::string CONFIG_SCRIPTS            = "/var/lib/slang/scripts/";
#endif
#ifdef _WIN32
static const std::string CONFIG_SCRIPTS            = "";
#endif
static const std::string TMP                       = "/tmp/";
static const char PATH_SEPARATOR                   = ':';


#endif
