
// Header
#include "Repository.h"

// Library includes
#include <fstream>
#include <utility>
#include <json/json.h>

// Project includes

// Namespace declarations


Repository::Repository( std::string name )
: mAuthentication( Authentication::None ),
  mName( std::move( name ) )
{
}

void Repository::addModule( const Module& module )
{
	if ( contains( module ) ) {
		// prevent duplicates
		return;
	}

	mModules.insert( module );
}

bool Repository::contains( const Module& module ) const
{
	for ( const auto& m : mModules ) {
		if ( m.mShortName == module.mShortName ) {
			return true;
		}
	}

	return false;
}

bool Repository::getModule( const std::string& shortName, Module& module ) const
{
	for ( const auto& m : mModules ) {
		if ( m.mShortName == shortName ) {
			module = m;
			return true;
		}
	}

	return false;
}

bool Repository::processIndex( const Json::Value& value )
{
	if ( !value.isMember( "modules" ) ) {
		return false;
	}

	auto modules = value[ "modules" ];

	for ( const auto& module : modules ) {
		auto name_short = module[ "name" ].asString();
		auto source     = module.isMember( "source" ) ? module[ "source" ].asString() : mURL;
		auto version    = module[ "version" ].asString();

		mModules.insert( Module( name_short, version, source ) );
	}

	return true;
}
