
#ifndef Core_Defines_h
#define Core_Defines_h


//#define USE_AST_OPTIMIZATION

#ifdef __APPLE__
#define SHARED_LIBRARY_DIRECTORY "/usr/local/share/slang/libs"
#elif _WIN32
#define SHARED_LIBRARY_DIRECTORY ""
#elif __linux__
#define SHARED_LIBRARY_DIRECTORY "/usr/local/share/slang/libs"
#endif


#endif

