
#ifndef ObjectiveScript_Extensions_Apache_Defs_h
#define ObjectiveScript_Extensions_Apache_Defs_h


// Library includes
#include <map>
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Apache {


typedef std::map<std::string, std::string> StringMap;


extern const char* QUERY_STRING;
extern StringMap mGetQueryString;
extern StringMap mPostQueryString;


}
}
}

#endif
