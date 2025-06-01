
#ifndef Slang_slang_pkg_Module_h
#define Slang_slang_pkg_Module_h


// Library includes
#include <set>
#include <string>

// Project includes
#include <SemVer/Version.h>
#include "Dependency.h"

// Forward declarations
namespace Json {
    class Value;
}

// Namespace declarations


class Module
{
public:
    class Action
    {
    public:
        enum E {
            None,
            Update
        };
    };

    class Target
    {
    public:
        std::string Directory;
        std::set<std::string> InstalledFiles;
        bool Internal{ true };
        std::string URL;
    };

public:
    Module();
    Module( std::string name_short, const std::string& version, std::string source );
    ~Module() = default;

public:
    bool operator<( const Module& other ) const;
    bool operator==( const Module& other ) const;

public:
    bool isValid() const;
    bool loadFromJson( const Json::Value& value );
    std::string toVersionString() const;

public:
    Action::E mActionNeeded;
    std::string mArchitecture;
    std::string mDescription;
    Dependencies mDependencies;
    std::set<std::string> mKeywords;
    std::string mLongName;
    std::string mShortName;
    std::string mSource;
    Target mTarget;
    SemanticVersionNumber mVersion;
};

typedef std::set<Module> Modules;


#endif
