
#ifndef ObjectiveScript_Extensions_System_System_h
#define ObjectiveScript_Extensions_System_System_h


// Library includes
#include <termios.h>
#include <stdlib.h>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {


extern void restoreKeyboardBlockingMode();
extern void setKeyboardBlockingMode(bool blocking);
extern void storeKeyboardBlockingMode();


}
}
}


#endif
