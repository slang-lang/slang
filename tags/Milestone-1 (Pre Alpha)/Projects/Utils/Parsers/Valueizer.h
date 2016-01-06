
#ifndef Utils_Parsers_Valueizer_h
#define Utils_Parsers_Valueizer_h


// Library includes

// Project includes
#include "Tokenizer.h"

// Forward declarations

// Namespace declarations


namespace Utils {


class Valueizer : public Tokenizer 
{
public:
    Valueizer(const std::string& str);
    Valueizer(const std::string& str, const std::string& delimiters);

public:
	const Value getTokenAsValue() const;

protected:

private:

};


}


#endif
