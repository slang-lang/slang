
// Header
#include "Strings.h"

// Library includes
#include <algorithm>

// Project includes

// Namespace declarations


namespace Utils {
namespace Tools {


std::string extract(const std::string& source) {
    static constexpr char DOUBLE_QUOTE = '"';
    static constexpr char SINGLE_QUOTE = '\'';

    if ( source.empty() ) {
        return "";
    }

    auto stripQuotes = []( const std::string& text, char quoteChar ) -> std::string {
        if ( text.front() == quoteChar && text.back() == quoteChar ) {
            return text.substr( 1, text.length() - 2 );
        }

        return "";
    };

    if ( source.front() == DOUBLE_QUOTE ) {
        return stripQuotes( source, DOUBLE_QUOTE );
    }
    if ( source.front() == SINGLE_QUOTE ) {
        return stripQuotes( source, SINGLE_QUOTE );
    }

    return "";
}

std::string indent(unsigned int level)
{
	std::string result;

	while ( level > 0 ) {
		level--;

		result += "\t";
	}

	return result;
}

void split(const std::string& str, std::string& p, std::string& c)
{
	c = "";

	auto pos = str.find_first_of('.');

	p = str.substr(0, pos);
	if ( p.size() != str.size() ) {
		c = str.substr(pos + 1, str.size());
	}
}

void splitBy(const std::string& str, char splitter, std::string& p, std::string& c)
{
	auto pos = str.find_first_of(splitter);

	p = str.substr(0, pos);
	if ( p.size() != str.size() ) {
		c = str.substr(pos + 1, str.size() - pos - 1);
	}
	else {
		c = "";
	}
}

bool StringCompare(const std::string& s1, const std::string& s2)
{
	return s1 == s2;
}

bool StringCompareI(const std::string& s1, const std::string& s2) {
    if ( s1.size() != s2.size() ) {
        return false;
    }

    return std::equal( s1.begin(), s1.end(), s2.begin(),
        [](char a, char b) { return ::toupper( a ) == ::toupper( b ); } );
}

bool stringToBool(const std::string& str) {
    static const std::string FALSE_VALUE = "false";
    static const std::string NEWLINE = "\n";
    
    // Trim whitespace and convert to lowercase for consistent comparison
    auto normalizedStr = toLowerCase( stringTrim( str ) );
    
    // Return false for empty string, newline, or explicit "false" value
    return !normalizedStr.empty() && 
           normalizedStr != NEWLINE && 
           normalizedStr != FALSE_VALUE;
}

double stringToDouble(const std::string& str)
{
	if ( str.empty() ) {
		return 0.0;
	}

	std::stringstream stream;
	stream << str;
	double d;
	stream >> d;

	return d;
}

float stringToFloat(const std::string& str)
{
	if ( str.empty() ) {
		return 0.0f;
	}

	std::stringstream stream;
	stream << str;
	float f;
	stream >> f;

	return f;
}

int stringToInt(const std::string& str)
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
	return stringTrimLeft( stringTrimRight(source, t), t );
}

std::string stringTrimLeft( const std::string& source, const std::string& t)
{
	auto str = source;

	return str.erase(0, source.find_first_not_of(t) );
}

std::string stringTrimRight(const std::string& source, const std::string& t)
{
	auto str = source;

	return str.erase( str.find_last_not_of(t) + 1 );
}


std::string toLowerCase(std::string data)
{
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);

	return data;
}


}
}