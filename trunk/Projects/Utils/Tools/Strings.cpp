
// Header
#include "Strings.h"

// Library includes
#include <algorithm>

// Project includes

// Namespace declarations


namespace Utils {
namespace Tools {


std::string extract(const std::string& source)
{
	std::string result;

	if ( source.empty() ) {
		return result;
	}

	if ( source[0] == '"' ) {
		if ( source[source.length() - 1] == '"' ) {
			for ( unsigned int i = 1; i < source.length() - 1; i++ ) {
				result += source[i];
			}
		}
	}
	else if ( source[0] == '\'' ) {
		if ( source[source.length() - 1] == '\'' ) {
			for ( unsigned int i = 1; i < source.length() - 1; i++ ) {
				result += source[i];
			}
		}
	}

	return result;
}

bool StringCompare(std::string s1, std::string s2)
{
	if ( s1.size() != s2.size() ) {
		return false;
	}

	return !(s1 != s2);
}

bool StringCompareI(const std::string & s1, const std::string& s2)
{
	if ( s1.size() != s2.size() ) {
		return false;
	}

	std::string::const_iterator it1 = s1.begin();
	std::string::const_iterator it2 = s2.begin();

	while ( (it1 != s1.end()) && (it2 != s2.end()) ) {
		if ( ::toupper(*it1) != ::toupper(*it2) ) {// letters differ?
			return false;
		}

		++it1;
		++it2;
	}

	return true;
}

bool stringToBool(const std::string &str)
{
	if ( str.length() == 1 && str[0] == '1' ) {
		return true;
	}
	else if ( str.length() == 4 && StringCompareI(str, "true") ) {
		return true;
	}

	return false;
}

double stringToDouble(const std::string &str)
{
	if ( str.empty() ) {
		return 0.f;
	}

	std::stringstream stream;
	stream << str;
	double d;
	stream >> d;

	return d;
}

float stringToFloat(const std::string &str)
{
	if ( str.empty() ) {
		return 0.f;
	}

	std::stringstream stream;
	stream << str;
	float f;
	stream >> f;

	return f;
}

int stringToInt(const std::string &str)
{
	if ( str.empty() ) {
		return 0;
	}

	std::stringstream stream;
	stream << str;
	int i;
	stream >> i;

	return i;
}

std::string stringTrim(const std::string& source, const std::string& t)
{
	std::string str = source;
	return stringTrimLeft( stringTrimRight(str, t), t );
}

std::string stringTrimLeft( const std::string& source, const std::string& t)
{
	std::string str = source;
	return str.erase(0, source.find_first_not_of(t) );
}

std::string stringTrimRight(const std::string& source, const std::string& t)
{
	std::string str = source;
	return str.erase( str.find_last_not_of(t) + 1 );
}


std::string toLowerCase(std::string data)
{
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);

	return data;
}


}
}
