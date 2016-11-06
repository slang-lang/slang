
#ifndef Utils_Tools_Strings_h
#define Utils_Tools_Strings_h


// Library includes
#include <sstream>
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace Utils {
namespace Tools {


// Compare
bool StringCompare(std::string s1, std::string s2);
bool StringCompareI(const std::string &s1, const std::string &s2);

// Convertion
bool stringToBool(const std::string &str);
double stringToDouble(const std::string &str);
float stringToFloat(const std::string &str);
int stringToInt(const std::string &str);

// Extraction
std::string extract(const std::string& source);

std::string indent(unsigned int level);

// Trim
std::string stringTrim(const std::string& source, const std::string& t = " ");
std::string stringTrimLeft( const std::string& source, const std::string& t = " ");
std::string stringTrimRight(const std::string& source, const std::string& t = " ");

std::string toLowerCase(std::string data);

template <class T>
inline std::string toString(const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}


}
}


#endif
