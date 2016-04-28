
// Header
#include "ApacheExtension.h"

// Library includes
#include <list>

// Project includes
#include "Defs.h"
#include "Get.h"
#include "Post.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Apache {


ApacheExtension::ApacheExtension()
{
	initialize();
}

std::string ApacheExtension::convert(const std::string& str) const
{
	return str;
}

void ApacheExtension::initialize()
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
		mQueryString.insert(
				std::make_pair(std::string(key), convert(std::string(value)))
		);
	}
}

void ApacheExtension::provideMethods(ExtensionMethods &methods)
{
	assert(methods.empty());

	methods.push_back(new Get());
	methods.push_back(new Post());
}


}
}
}
