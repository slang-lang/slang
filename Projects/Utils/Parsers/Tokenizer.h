
#ifndef Utils_Parsers_Tokenizer_h
#define Utils_Parsers_Tokenizer_h


// Library includes
#include <string>

// Project includes
#include "Value.h"

// Forward declarations

// Namespace declarations


namespace Utils {


class Tokenizer 
{
public:
    static const std::string DELIMITERS;

public:
    Tokenizer(std::string  str, const std::string& delimiters = "");

public:
    std::string getRemainingString() const;
    std::string getString() const;
    std::string getToken() const;

    bool hasNext();
    bool nextToken(const std::string& delimiters);
    void reset();

protected:
    std::string	mDelimiters;
    size_t		mOffset;
    std::string	mString;
    std::string	mToken;

private:

};


}


#endif
