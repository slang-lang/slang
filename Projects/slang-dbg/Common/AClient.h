
#ifndef Slang_slang_dbg_Common_AClient_h
#define Slang_slang_dbg_Common_AClient_h


// Library includes
#include <string>

// Project includes
#include <Core/Common/Types.h>
#include <Interfaces/ITerminal.h>

// Forward declarations

// Namespace declarations


namespace Slang {

// Forward declarations
class Settings;

class AClient
{
public:
	AClient();
	virtual ~AClient() = default;

public:
	virtual int exec() = 0;

public:
	void connectSettings( Settings* s );

protected:
	Settings* mSettings;
};

}


#endif Slang_slang_dbg_Common_AClient_h
