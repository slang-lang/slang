
// Header
#include "Configurator.h"

// Library includes
#include <stdlib.h>

// Project includes
#include <Parsers/LineParser.h>
#include <Tools/Files.h>
#include <Tools/Tools.h>

// Namespace declarations


namespace Utils {
namespace Common {
namespace Configuration {


Configurator::Configurator(const Utils::Common::Logger *p, const std::string& file)
: Utils::Common::Logger(p, "Configurator"),
  mConfigFile(file),
  mSuccess(false)
{
	char* homepath = getenv("OBJECTIVESCRIPT_HOME");
	if ( homepath ) {
		mHomePath = homepath;
		if ( !mHomePath.empty() ) {
			assert(!mHomePath.empty() && "OBJECTIVESCRIPT_HOME environment variable is not set!");

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

	KeyValueMap::const_iterator it;
	for ( it = mValues.begin(); it != mValues.end(); ++it ) {
		if ( Tools::StringCompare((*it).first, member) ) {
			return (*it).second;
		}
	}

	//error("Key '" + member + "' not found in configuration file '" + mConfigFile + "'!");
	return Value();
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

	KeyValueMap::const_iterator it;
	for ( it = mValues.begin(); it != mValues.end(); ++it ) {
		if ( Tools::StringCompare((*it).first, member) ) {
			return true;
		}
	}

	return false;
}

bool Configurator::load(const std::string& file)
{
	unload();

	mConfigFile = mHomePath + file;
	debug("load('" + mConfigFile + "')");

	if ( !Tools::Files::exists(mConfigFile) ) {
		warn("invalid file '" + mConfigFile + "' provided!");
		return mSuccess;
	}

	mFile.open(mConfigFile.c_str(), std::ios::in);
	std::string data((std::istreambuf_iterator<char>(mFile)), std::istreambuf_iterator<char>());
	mFile.close();

	if ( data.empty() ) {
		warn("could not load configuration file '" + mConfigFile + "'!");
		return mSuccess;
	}

	std::string line;
	for ( std::string::const_iterator it = data.begin(); it != data.end(); ++it ) {
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
