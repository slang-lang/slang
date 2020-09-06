
#ifndef Slang_Core_Core_Extensions_ExtensionManager_h
#define Slang_Core_Core_Extensions_ExtensionManager_h


// Library includes

// Project includes
#include <utility>

#include "AExtension.h"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {


typedef void* dynamic_lib_handle;


class ExtensionManager
{
public:
	AExtension* load( const std::string& path );

private:
	struct dynamic_lib
	{
	public:
		dynamic_lib_handle handle;
		std::string	path;

	public:
		explicit dynamic_lib( std::string p )
		: handle( nullptr ),
		  path( std::move( p ) )
		{ }

		~dynamic_lib() {
			if ( handle != nullptr ) {
				ExtensionManager::close_lib( handle );

				handle = nullptr;
			}
		}
	};

private:
	typedef std::list<dynamic_lib> Libraries;

private:
	static void close_lib( dynamic_lib_handle handle );
	static dynamic_lib_handle load_lib( const std::string& path );
	static AExtension* instantiate( dynamic_lib_handle handle );

private:
	Libraries mLibraries;
};


}
}


#endif
