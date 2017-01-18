
#ifndef ObjectiveScript_Extensions_System_IO_Defines_h
#define ObjectiveScript_Extensions_System_IO_Defines_h


// Library includes
#ifdef __APPLE__
#	include <unistd.h>
#elif defined _WIN32
#	include <io.h>
#	pragma warning(disable:4996)
#else
#	include <unistd.h>
#endif
#include <map>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {
namespace IO {


typedef std::map<int /*file handle*/, FILE*> FileHandles;

extern FileHandles mFileHandles;


}
}
}
}


#endif
