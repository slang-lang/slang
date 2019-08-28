
#ifndef ObjectiveScript_Core_Defines_h
#define ObjectiveScript_Core_Defines_h


//#define USE_AST_OPTIMIZATION

#ifdef __APPLE__
#define SHARED_LIBRARY_DIRECTORY "/usr/local/share/oscript/libs"
#elif _WIN32
#define SHARED_LIBRARY_DIRECTORY ""
#elif __linux__
#define SHARED_LIBRARY_DIRECTORY "/usr/local/share/oscript/libs"
#endif


#endif

