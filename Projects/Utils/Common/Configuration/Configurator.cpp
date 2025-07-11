
// Header
#include "Configurator.h"

// Library includes
#include <cstdlib>

// Project includes
#include <Parsers/LineParser.h>
#include <Tools/Files.h>
#include <Tools/Strings.h>

// Namespace declarations


namespace Utils {
namespace Common {
namespace Configuration {


Configurator::Configurator( const Logger* p, const std::string& file )
: Logger( p, "Configurator" ),
  mConfigFile(file),
  mSuccess(false)
{
	char* homepath = getenv( "SLANG_HOME" );
	if ( homepath ) {
		mHomePath = homepath;
		if ( !mHomePath.empty() ) {
			assert(!mHomePath.empty() && "SLANG_HOME environment variable is not set!");

			mHomePath += "/";
		}
	}

	if ( !file.empty() ) {
		load(file);
	}
}

Configurator::~Configurator()
{
	unload();
}

Value Configurator::getValue(const std::string& key, int idx) const
{
	std::string member = key;
	if ( idx != -1 ) {
		member += ":" + Tools::toString(idx);
	}

	for ( const auto& pair : mValues ) {
		if ( Tools::StringCompare( pair.first, member ) ) {
			return pair.second;
		}
	}

	//error("Key '" + member + "' not found in configuration file '" + mConfigFile + "'!");
	return {};
}

Value Configurator::getValue(const std::string& parent, int idx, const std::string& key) const
{
	return getValue(parent + ":" + Tools::toString(idx) + "." + key);
}

bool Configurator::isMember(const std::string& key, int idx) const
{
	std::string member = key;
	if ( idx != -1 ) {
		member += ":" + Tools::toString(idx);
	}

	for ( const auto& pair : mValues ) {
		if ( Tools::StringCompare( pair.first, member ) ) {
			return true;
		}
	}

	return false;
}

bool Configurator::load(const std::string& file)
{
	unload();

	mConfigFile = mHomePath + file;
	//debug("load('" + mConfigFile + "')");

	if ( !Tools::Files::exists(mConfigFile) ) {
		//warn("invalid file '" + mConfigFile + "' provided!");
		return mSuccess;
	}

	mFile.open(mConfigFile.c_str(), std::ios::in);
	std::string data((std::istreambuf_iterator<char>(mFile)), std::istreambuf_iterator<char>());
	mFile.close();

	if ( data.empty() ) {
		//warn("could not load configuration file '" + mConfigFile + "'!");
		return mSuccess;
	}

	std::string line;
	for ( auto it = data.begin(); it != data.end(); ++it ) {
		if ( (*it) == '\n' ) {
			mLines.push_back(line);
			line = "";
			continue;
		}

		line += (*it);
	}

	split();

	mSuccess = true;
	return mSuccess;
}

void Configurator::split()
{
	mValues.clear();

	for ( StringList::const_iterator it = mLines.begin(); it != mLines.end(); ++it ) {
		Value value = LineParser::parse((*it));

		if ( !value.getName().empty() ) {
			mValues[value.getName()] = value;
		}
	}
}

bool Configurator::success() const
{
	return mSuccess;
}

void Configurator::unload()
{
	mConfigFile = "";
	mFile.clear();
	mLines.clear();
	mSuccess = false;
	mValues.clear();
}


}
}
}
