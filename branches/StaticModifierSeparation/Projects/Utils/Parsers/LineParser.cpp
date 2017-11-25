
// Header
#include "LineParser.h"

// Library includes

// Project includes
#include "Tokenizer.h"

// Namespace declarations


namespace Utils {


Value LineParser::parse(const std::string& line)
{
	Tokenizer t(line);

	if ( !t.hasNext() ) {
		return Value();
	}

	std::string name = t.getToken();
	
	if ( !t.hasNext() ) {
		return Value();
	}

	std::string type = t.getToken();

	std::string value;

	while ( t.hasNext() ) {
		if ( value.length() > 0 ) {
			value += " ";
		}

		value += t.getToken();
	}

	return Value(name, type, value);
}


}
