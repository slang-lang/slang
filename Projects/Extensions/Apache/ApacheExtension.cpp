
// Header
#include "ApacheExtension.h"

// Library includes
#include <cstdio>
#include <list>
#include <stdlib.h>
#include <string.h>

// Project includes
#include "Defs.h"
#include "Get.h"
#include "IsSet.h"
#include "Post.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Apache {


const char HEX2DEC[256] = 
{
    /*       0  1  2  3   4  5  6  7   8  9  A  B   C  D  E  F */
    /* 0 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 1 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 2 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 3 */  0, 1, 2, 3,  4, 5, 6, 7,  8, 9,-1,-1, -1,-1,-1,-1,
    
    /* 4 */ -1,10,11,12, 13,14,15,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 5 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 6 */ -1,10,11,12, 13,14,15,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 7 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    
    /* 8 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 9 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* A */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* B */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    
    /* C */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* D */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* E */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* F */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1
};

// Only alphanum is safe.
const char SAFE[256] =
{
    /*      0 1 2 3  4 5 6 7  8 9 A B  C D E F */
    /* 0 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    /* 1 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    /* 2 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    /* 3 */ 1,1,1,1, 1,1,1,1, 1,1,0,0, 0,0,0,0,
    
    /* 4 */ 0,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,
    /* 5 */ 1,1,1,1, 1,1,1,1, 1,1,1,0, 0,0,0,0,
    /* 6 */ 0,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,
    /* 7 */ 1,1,1,1, 1,1,1,1, 1,1,1,0, 0,0,0,0,
    
    /* 8 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    /* 9 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    /* A */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    /* B */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    
    /* C */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    /* D */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    /* E */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    /* F */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0
};

std::string UriDecode(const std::string & sSrc)
{
    // Note from RFC1630:  "Sequences which start with a percent sign
    // but are not followed by two hexadecimal characters (0-9, A-F) are reserved
    // for future extension"
    
    const unsigned char * pSrc = (const unsigned char *)sSrc.c_str();
	const int SRC_LEN = sSrc.length();
    const unsigned char * const SRC_END = pSrc + SRC_LEN;
    const unsigned char * const SRC_LAST_DEC = SRC_END - 2;   // last decodable '%' 

    char * const pStart = new char[SRC_LEN];
    char * pEnd = pStart;

    while ( pSrc < SRC_LAST_DEC ) {
		if ( *pSrc == '%' ) {
            char dec1, dec2;
            if ( -1 != (dec1 = HEX2DEC[*(pSrc + 1)])
                && -1 != (dec2 = HEX2DEC[*(pSrc + 2)]) ) {
                *pEnd++ = (dec1 << 4) + dec2;
                pSrc += 3;
                continue;
            }
        }

        *pEnd++ = *pSrc++;
	}

    // the last 2- chars
    while ( pSrc < SRC_END ) {
		*pEnd++ = *pSrc++;
	}

    std::string sResult(pStart, pEnd);
    delete [] pStart;
	return sResult;
}

std::string UriEncode(const std::string & sSrc)
{
    const char DEC2HEX[16 + 1] = "0123456789ABCDEF";
    const unsigned char * pSrc = (const unsigned char *)sSrc.c_str();
    const int SRC_LEN = sSrc.length();
    unsigned char * const pStart = new unsigned char[SRC_LEN * 3];
    unsigned char * pEnd = pStart;
    const unsigned char * const SRC_END = pSrc + SRC_LEN;

    for ( ; pSrc < SRC_END; ++pSrc ) {
		if ( SAFE[*pSrc] ) {
			*pEnd++ = *pSrc;
		}
        else {
            // escape this char
            *pEnd++ = '%';
            *pEnd++ = DEC2HEX[*pSrc >> 4];
            *pEnd++ = DEC2HEX[*pSrc & 0x0F];
        }
	}

    std::string sResult((char *)pStart, (char *)pEnd);
    delete [] pStart;
    return sResult;
}



ApacheExtension::ApacheExtension()
: AExtension("Apache")
{
}

void ApacheExtension::initialize(IScope* scope)
{
	AExtension::initialize(scope);

	readGetData();
	readPostData();
}

void ApacheExtension::provideMethods(ExtensionMethods &methods)
{
	assert(methods.empty());

	methods.push_back(new Get());
	methods.push_back(new IsSet());
	methods.push_back(new Post());
}

void ApacheExtension::readGetData()
{
	char *query = getenv(QUERY_STRING);
	if ( !query ) {
		// ups
		return;
	}

	std::list<char*> stringlist;

	char* base = strtok(query, "&");
	while ( base != NULL ) {
		stringlist.push_back(base);

		base = strtok(NULL, "&");
	}

	for ( std::list<char*>::reverse_iterator it = stringlist.rbegin(); it != stringlist.rend(); ++it ) {
		char* key = strtok((*it), "=");
		char* value = strtok(NULL, "");

		std::string strvalue;
		if ( value ) {
			strvalue = std::string(value);
		}

		mGetQueryString.insert(std::make_pair(
			std::string(key),
			UriDecode(strvalue))
		);
	}
}

void ApacheExtension::readPostData()
{
	char* len_ = getenv("CONTENT_LENGTH");
	if ( !len_ ) {
		// no CONTENT_LENGTH received
		return;
	}

	size_t len = strtol(len_, NULL, 10);

	char* postdata = (char*)malloc(len + 1);

	if ( !postdata ) {
		/* handle error or */
		exit(EXIT_FAILURE);
	}

	fgets(postdata, len + 1, stdin);

	std::list<char*> stringlist;

	char* base = strtok(postdata, "&");
	while ( base != NULL ) {
		stringlist.push_back(base);

		base = strtok(NULL, "&");
	}

	for ( std::list<char*>::reverse_iterator it = stringlist.rbegin(); it != stringlist.rend(); ++it ) {
		char* key = strtok((*it), "=");
		char* value = strtok(NULL, "");

		std::string strvalue;
		if ( value ) {
			strvalue = std::string(value);
		}

		mPostQueryString.insert(std::make_pair(
			std::string(key),
			UriDecode(strvalue))
		);
	}

	free(postdata);
}

}
}
}
