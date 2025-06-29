
// Header
#include "System.h"

// Library includes

// Project includes

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {


#ifdef _WIN32
#else
termios mTerminalSettings;

void restoreKeyboardBlockingMode()
{
	tcsetattr(0, TCSANOW, &mTerminalSettings);
}

void storeKeyboardBlockingMode()
{
	tcgetattr(0, &mTerminalSettings);
}

void SetKeyboardBlocking()
{
	termios new_settings;
	tcgetattr(0, &new_settings);

	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= ~ECHO;
	new_settings.c_lflag &= ~ISIG;
	new_settings.c_cc[VMIN] = 0;
	new_settings.c_cc[VTIME] = 0;

	tcsetattr(0, TCSANOW, &new_settings);
}

void SetKeyboardNonBlocking()
{
	termios new_settings;
	tcgetattr(0, &new_settings);

	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= ~ECHO;
	new_settings.c_lflag &= ~ISIG;
	new_settings.c_cc[VMIN] = 0;
	new_settings.c_cc[VTIME] = 0;

	tcsetattr(0, TCSANOW, &new_settings);
}

void setKeyboardBlockingMode(bool blocking)
{
	if ( blocking ) {
		SetKeyboardBlocking();
	}
	else {
		SetKeyboardNonBlocking();
	}
}
#endif


}
}
}
