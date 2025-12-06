
#ifndef Slang_slang_app_Application_Settings_h
#define Slang_slang_app_Application_Settings_h


// Library includes
#include <string>
#include <vector>
#include <json/json.h>

// Project includes
#include <Common/Consts.h>
#include <Utils.h>

// Forward declarations
class Service;

// Namespace declarations


class Settings
{
public:
    Json::Value Config;
    std::string CurrentFolder;
    Service* DefaultService{ nullptr };
    std::string LibraryFolder;
    std::string Script;
    std::vector<Service*> Services;
    bool Verbose{ false };
};


#endif
