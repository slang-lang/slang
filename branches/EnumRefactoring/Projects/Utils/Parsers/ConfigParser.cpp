
// Header
#include "ConfigParser.h"

// Library includes
#include <stdio.h>

// Project includes
#include <Tools/Files.h>
#include <Tools/Strings.h>
#include <Tools/Tools.h>

// Namespace declarations


namespace Utils {


ConfigParser::ConfigParser(const Common::Logger *p)
: Common::Logger(p, "ConfigParser"),
  mFile(0)
{
}

ConfigParser::~ConfigParser()
{
	close();
}

void ConfigParser::close()
{
	if ( mFile ) {
		fclose(mFile);
	}
}

Value ConfigParser::getValue(const std::string& item)
{
	char line[255] = "";

	open();

	do {
		//sprintf(line, "");
		Tools::readstr(mFile, line);

		char str[255];
		sscanf(line, "%s", str);

		if ( Tools::StringCompareI(str, item) ) {
			char *tmpStr = 0;
			char *tmpResult = 0;
			sscanf(line, "%s %s", tmpStr, tmpResult);
			close();
			return Value(item, "undefined", tmpResult);
		}

	} while ( strcmp(line, "") != 0 );

	close();
	return Value("");
}

std::string ConfigParser::readLine()
{
	char line[255];

	//sprintf(line, "");
	Tools::readstr(mFile, line);

	return std::string(line);
}

bool ConfigParser::load(const std::string& filename)
{
	//debug("load('" << filename << "')");

	if ( !Tools::Files::exists(filename) ) {
		//warn("File '" << filename << "' does not exist");
		return false;
	}

	mFilename = filename;

	return true;
}

void ConfigParser::open()
{
#ifdef _MSC_VER
	fopen_s(&mFile, mFilename.c_str(), "rt");
#else
	mFile = fopen(mFilename.c_str(), "rt");
#endif
}


}
