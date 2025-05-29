
#ifndef Slang_slang_pkg_Settings_h
#define Slang_slang_pkg_Settings_h


// Library includes
#include <string>
#include <json/json.h>

// Project includes
#include <Utils.h>
#include "Defines.h"
#include "Restriction.h"

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
