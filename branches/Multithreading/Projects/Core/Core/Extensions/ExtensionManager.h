
#ifndef ObjectiveScript_Core_Core_Extensions_ExtensionManager_h
#define ObjectiveScript_Core_Core_Extensions_ExtensionManager_h


// Library includes

// Project includes
#include "AExtension.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {


typedef void* dynamic_lib_handle;


class ExtensionManager
{
public:
	AExtension* load(const std::string& path);

private:
	struct dynamic_lib
	{
	public:
		dynamic_lib_handle handle;
		std::string	path;

	public:
		explicit dynamic_lib(const std::string& p)
		: handle(nullptr),
		  path(p)
		{ }

		~dynamic_lib() {
			if ( handle != nullptr ) {
				ExtensionManager::close_lib(handle);

				handle = nullptr;
			}
		}
	};

private:
	typedef std::list<dynamic_lib> Libraries;

private:
	static void close_lib(dynamic_lib_handle handle);
	static dynamic_lib_handle load_lib(const std::string& path);
	static AExtension* instantiate(const dynamic_lib_handle handle);

private:
	Libraries mLibraries;
};


}
}


#endif
