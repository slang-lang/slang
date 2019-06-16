
// Header
#include "ExtensionManager.h"
#include <Utils.h>

// Library includes
#include <cassert>
#include <dlfcn.h>

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {


ExtensionManager::ExtensionManager()
{
}

ExtensionManager::~ExtensionManager()
{
	for ( Extensions::iterator it = mExtensions.begin(); it != mExtensions.end(); ++it ) {
		unload( (*it) );
	}
}

void ExtensionManager::close_lib(dynamic_lib_handle handle)
{
	dlclose(handle);
}

AExtension* ExtensionManager::instantiate(const dynamic_lib_handle handle)
{
	if ( handle == nullptr ) {
		return nullptr;
	}

	dynamic_lib_handle maker = dlsym(handle , "factory");

	if ( maker == nullptr ) {
		return nullptr;
	}

	typedef AExtension* (*fptr)();
	fptr func = reinterpret_cast<fptr>( reinterpret_cast<dynamic_lib_handle>( maker ) );

	return func();
}

dynamic_lib_handle ExtensionManager::load_lib(const std::string& path) {
	OSinfo("Loading shared library from '" + path + "'...");

	return dlopen(path.data(), RTLD_NOW); // get a handle to the lib, may be nullptr.
	// RTLD_NOW ensures that all the symbols are resolved immediately. This means that
	// if a symbol cannot be found, the program will crash now instead of later.
}

bool ExtensionManager::load(const std::string& path)
{
	mLibraries.push_back( dynamic_lib(path) );

	dynamic_lib& lib = mLibraries.back();
	lib.handle = load_lib(lib.path);

	mExtensions.push_back( instantiate(lib.handle) );

	return true;
}

bool ExtensionManager::unload(AExtension* extension)
{
	(void)extension;

	return false;
}


}
}
