
#ifndef Utils_Parsers_ConfigParser_h
#define Utils_Parsers_ConfigParser_h


// Library includes
#include <string>

// Project includes
#include <Common/Logger.h>
#include "Value.h"

// Forward declarations

// Namespace declarations


namespace Utils {


class ConfigParser : public Common::Logger
{
public:
	ConfigParser(const Common::Logger *p);
	~ConfigParser();

public:
	Value getValue(const std::string& item);
	bool load(const std::string& filename);

protected:

private:
	void close();
	void open();
	std::string readLine();

private:
	FILE *mFile;
	std::string mFilename;
};


}


#endif
