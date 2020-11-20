
#ifndef Core_Configuration_Configurator_h
#define Core_Configuration_Configurator_h


// Library includes
#include <list>
#include <map>
#include <string>

// Project includes
#include <Common/Logger.h>
#include <Parsers/Value.h>

// Forward declarations

// Namespace declarations


namespace Utils {
namespace Common {
namespace Configuration {


class Configurator : private Common::Logger
{
public:
	Configurator( const Common::Logger* p, const std::string& file = "" );
	~Configurator();

public:
	// deprecated
	// {
	bool load(const std::string& file);
	// }

	Value getValue(const std::string& key, int idx = -1) const;
	Value getValue(const std::string& parent, int idx, const std::string& key) const;
	bool isMember(const std::string& key, int idx = -1) const;
	bool success() const;

protected:

private:
	typedef std::map<std::string, Value> KeyValueMap;
	typedef std::list<std::string> StringList;

private:
	void split();
	void unload();

private:
	std::string mConfigFile;
	std::fstream mFile;
	std::string mHomePath;
	StringList mLines;
	KeyValueMap mValues;
	bool mSuccess;
};


}
}
}


#endif
