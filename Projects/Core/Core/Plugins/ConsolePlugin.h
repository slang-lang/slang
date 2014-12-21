
#ifndef Core_Plugins_ConsolePlugin_h
#define Core_Plugins_ConsolePlugin_h


// Library includes
#include <cassert>

// Project includes
#include <Interfaces/Console/IConsolePlugin.h>
#include <Interfaces/Console/IConsolePrinter.h>
#include <Script/Script.h>
#include <Script/Manager.h>

// Forward declarations

// Namespace declarations

namespace ObjectiveScript {

// Forward declarations
class Settings;

class ConsolePlugin : public Console::IConsolePlugin
{
public:
	ConsolePlugin()
	: Console::IConsolePlugin("script"),
	  mScript(0),
	  mScriptManager(0),
	  mSettings(0)
	{ }

public:
	void connectScriptManager(Manager *m) {
		mScriptManager = m;
		mSettings = mScriptManager->provideSettings();
	}

	void execute(Valueizer *t) {
		assert(mPrinter);
		assert(mScriptManager);

		if ( t->hasNext() ) {
			Value val = t->getTokenAsValue();

			if ( t->hasNext() ) {
				if ( val.ofValue("execute") ) {
					if ( !mScript ) {
						mPrinter->print("execute: no valid script file loaded!");
						return;
					}

					VariablesList params;

					val = t->getTokenAsValue();
					if ( t->hasNext() ) {
						// set up parameters...
					}

					Variable v = mScript->execute(val.toString(), params);
					if ( !v.type().empty() && v.type() != "void" ) {
						mPrinter->print("Result: " + v.value());
					}
				}
				else if ( val.ofValue("load") ) {
					val = t->getTokenAsValue();

					mScript = mScriptManager->create(val.toString());
					if ( !mScript ) {
						mPrinter->print("error while loading script '" + val.toString() + "'!");
						return;
					}

					mPrinter->print("loaded script file.");
				}
			}
			else {
				if ( val.ofValue("explain") ) {
					explain();
				}
				else if ( val.ofValue("help") ) {
					help();
				}
				else if ( val.ofValue("unload") ) {
					mScript = 0;
					mPrinter->print("unloaded script file.");
				}
			}

			// return after all parameters have been processed
			return;
		}

		help();
	}

private:
	void explain() {
		if ( !mScript ) {
			mPrinter->print("explain: no valid script file loaded!");
			return;
		}

		mPrinter->print("explain: ");
	}

	void help() {
		mPrinter->print("Usage:");
		mPrinter->print("   script execute <method name> <parameters>");
		mPrinter->print("   script explain");
		mPrinter->print("   script help");
		mPrinter->print("   script load <script file>");
		mPrinter->print("   script unload");
	}

private:
	Script		*mScript;
	Manager		*mScriptManager;
	Settings	*mSettings;
};


}


#endif
