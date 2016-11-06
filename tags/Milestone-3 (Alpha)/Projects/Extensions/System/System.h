
#ifndef ObjectiveScript_Extensions_System_System_h
#define ObjectiveScript_Extensions_System_System_h


// Library includes
#ifdef _WIN32
#else
#	include <termios.h>
#	include <stdlib.h>
#endif

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {

#ifdef _WIN32
#else
extern void restoreKeyboardBlockingMode();
extern void setKeyboardBlockingMode(bool blocking);
extern void storeKeyboardBlockingMode();
#endif


}
}
}


#endif
