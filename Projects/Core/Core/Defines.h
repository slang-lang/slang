
#ifndef Core_Defines_h
#define Core_Defines_h


//#define USE_AST_OPTIMIZATION

#ifdef __APPLE__
#define SHARED_EXTENSION_DIRECTORY "/var/lib/slang/extensions/"
#define SHARED_LIBRARY_DIRECTORY   "/var/lib/slang/library/"
#elif _WIN32
#define SHARED_EXTENSION_DIRECTORY ""
#define SHARED_LIBRARY_DIRECTORY   ""
#elif __linux__
#define SHARED_EXTENSION_DIRECTORY "/var/lib/slang/extensions/"
#define SHARED_LIBRARY_DIRECTORY   "/var/lib/slang/library/"
#endif


#ifdef _WIN32
#  define SLANG_API __declspec(dllexport)
#else
#  define SLANG_API __attribute__((visibility("default")))
#endif


#endif

