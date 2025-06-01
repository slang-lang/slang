
#ifndef Slang_slang_pkg_Application_Settings_h
#define Slang_slang_pkg_Application_Settings_h


// Library includes
#include <string>
#include <json/json.h>

// Project includes
#include <Common/Consts.h>
#include <Common/Restriction.h>
#include <Utils.h>

// Forward declarations

// Namespace declarations


class Settings
{
public:
    e_Action Action{ None };
    std::string Architecture;
    Json::Value Config;
    std::string CurrentFolder;
    std::string LibraryFolder;
    Restrictions LocalRestrictions;
    bool SkipDependencies{ false };
    bool Verbose{ false };
};


#endif
