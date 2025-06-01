
// Header
#include "Module.h"

// Library includes
#include <json/value.h>

// Project includes

// Namespace declarations


static const std::string ARCHITECTURE = "architecture";
static const std::string DEPENDENCIES = "dependencies";
static const std::string DESCRIPTION = "description";
static const std::string DIRECTORY = "directory";
static const std::string INSTALL = "install";
static const std::string KEYWORDS = "keywords";
static const std::string MODULE = "module";
static const std::string NAME = "name";
static const std::string SHORTNAME = "name_short";
static const std::string SOURCE = "source";
static const std::string TARGET = "target";
static const std::string URL = "url";
static const std::string VERSION = "version";
static const std::string VERSION_MAX = "version_max";
static const std::string VERSION_MIN = "version_min";

Module::Module()
: mActionNeeded( Action::None )
{
}

Module::Module( std::string name_short, const std::string& version, std::string source )
: mActionNeeded( Action::None ),
  mShortName( std::move( name_short ) ),
  mSource( std::move( source ) ),
  mVersion( version )
{
}

bool Module::operator<( const Module& other ) const
{
	return mShortName < other.mShortName;
}

bool Module::operator==( const Module& other ) const
{
	return mShortName == other.mShortName;
}

bool Module::isValid() const
{
	return mVersion.isValid();
}

bool Module::loadFromJson( const Json::Value& value )
{
    if ( value.empty() ) {
        return false;
    }

    mArchitecture = value.isMember( ARCHITECTURE ) ? value[ ARCHITECTURE ].asString() : "";
    mDescription  = value[ DESCRIPTION ].asString();
    mLongName     = value[ NAME ].asString();
    mShortName    = value[ SHORTNAME ].asString();
    mSource       = value.isMember( SOURCE ) ? value[ SOURCE ].asString() : "";
    mVersion      = value[ VERSION ].asString();

    if ( value.isMember( DEPENDENCIES ) ) {
        auto dependencies = value[ DEPENDENCIES ];

        for ( const auto& dependency : dependencies ) {
            auto moduleName  = dependency[ MODULE ].asString();
            auto source      = dependency.isMember( SOURCE )      ? dependency[ SOURCE ].asString()      : "";
            auto version_max = dependency.isMember( VERSION_MAX ) ? dependency[ VERSION_MAX ].asString() : "";
            auto version_min = dependency.isMember( VERSION_MIN ) ? dependency[ VERSION_MIN ].asString() : "";

            mDependencies.insert(
                Dependency( moduleName, version_min, version_max, source )
            );
        }
    }

    if ( value.isMember( KEYWORDS ) ) {
        auto keywords = value[ KEYWORDS ];

        for ( const auto& word : keywords ) {
            mKeywords.insert( word.asString() );
        }
    }

    // short name is the default value for the target directory
    mTarget.Directory = value[ SHORTNAME ].asString();

    if ( value.isMember( TARGET ) ) {
        const auto& target = value[ TARGET ];

        // override directory if present
        if ( target.isMember( DIRECTORY ) ) {
            mTarget.Directory = target[ DIRECTORY ].asString();
        }

        if ( target.isMember( INSTALL ) ) {
            auto files = target[ INSTALL ];

            for ( const auto& word : files ) {
                mTarget.InstalledFiles.insert( word.asString() );
            }
        }

        // URL
        if ( target.isMember( URL ) ) {
            mTarget.Internal = false;
            mTarget.URL      = target[ URL ].asString();
        }
    }

    return true;
}

std::string Module::toVersionString() const
{
    return mShortName + ":" + mVersion.toString();
}
