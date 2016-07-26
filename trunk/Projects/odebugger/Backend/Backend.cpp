
// Header
#include "Backend.h"

// Library includes

// Project includes
#include <Common/Settings.h>
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/DoubleObject.h>
#include <Core/BuildInObjects/FloatObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/NumberObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Script.h>
#include <Core/StackTrace.h>
#include <Core/Tokenizer.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine.h>
#include <Debugger/Debugger.h>
#include <Tools/Files.h>
#include <Tools/Strings.h>

// Extension includes
#include <Extensions.h>

// Namespace declarations


namespace ObjectiveScript {


Backend::Backend()
: mAutoWatch(true),
  mBreakOnException(true),
  mContinue(false),
  mDebugger(0),
  mRunning(true),
  mScope(0),
  mSettings(0),
  mTerminal(0),
  mVirtualMachine(0)
{
	mDebugger = &ObjectiveScript::Core::Debugger::GetInstance();
}

Backend::~Backend()
{
	shutdown();

	mDebugger = 0;
}

bool Backend::addBreakPoint(const StringList& tokens)
{
	if ( tokens.size() != 3 && tokens.size() != 6 ) {
		writeln("invalid number of arguments!");
		return false;
	}

	StringList::const_iterator it = tokens.begin();
	it++;	// skip first token

	std::string file = (*it++);
	unsigned line = ::Utils::Tools::stringToInt((*it++));

	Core::BreakPoint breakpoint(Utils::Position(file, line));

	if ( tokens.size() == 6 ) {
		std::string left = (*it++);
		std::string op = (*it++);
		std::string right = (*it++);

		breakpoint.setCondition(
			Core::Condition(left, op, right)
		);
	}

	return mDebugger->addBreakPoint(breakpoint);
}

bool Backend::addLiteralSymbol(const std::string& name, const std::string& value)
{
	Symbols::iterator it = mSymbolCollection.find(name);
	if ( it != mSymbolCollection.end() ) {
		// symbol already cached
		return true;
	}

	Tokenizer t("", value);
	t.process();

	Symbol* symbol = 0;

	TokenList list = t.tokens();
	if ( list.size() > 1 ) {
		Token token = list.front();

		switch ( token.type() ) {
			case Token::Type::CONST_BOOLEAN:
				symbol = new Runtime::BoolObject(token.content());
				break;
			case Token::Type::CONST_DOUBLE:
				symbol = new Runtime::DoubleObject(token.content());
				break;
			case Token::Type::CONST_FLOAT:
				symbol = new Runtime::FloatObject(token.content());
				break;
			case Token::Type::CONST_INTEGER:
				symbol = new Runtime::IntegerObject(token.content());
				break;
			case Token::Type::CONST_LITERAL:
				symbol = new Runtime::StringObject(token.content());
				break;
			case Token::Type::CONST_NUMBER:
				symbol = new Runtime::NumberObject(token.content());
				break;
			default:
				break;
		}
	}

	if ( !symbol ) {
		return false;
	}

	mSymbolCollection.insert(std::make_pair(name, symbol));

	return true;
}

bool Backend::addWatch(const StringList& tokens)
{
	if ( tokens.size() != 2 ) {
		writeln("invalid number of arguments!");
		return false;
	}

	StringList::const_iterator it = tokens.begin();
	it++;	// skip first token

	mWatches.insert(Watch((*it)));

	return true;
}

void Backend::clearSymbolCache()
{
	for ( Symbols::iterator it = mSymbolCollection.begin(); it != mSymbolCollection.end(); ++it ) {
		delete it->second;
	}
	mSymbolCollection.clear();
}

void Backend::connectSettings(Settings *settings)
{
	assert(settings);
	assert(!mSettings);

	mSettings = settings;
}

void Backend::connectTerminal(ITerminal* terminal)
{
	assert(terminal);
	assert(!mTerminal);

	mTerminal = terminal;
}

void Backend::continueExecution()
{
	mContinue = true;
}

int Backend::exec()
{
	// initial checks
	assert(mDebugger);
	assert(!mVirtualMachine);

	// start program execution
	while ( mRunning ) {
		notify(0, Core::Debugger::immediateBreakPoint);
	}

	// program exection is done
	return 0;
}

std::string Backend::executeCommand(const StringList &tokens)
{
	StringList::const_iterator it = tokens.begin();

	if ( it != tokens.end() ) {
		std::string cmd = (*it++);

		if ( cmd == "autowatch" ) {
			toggleAutoWatch();
		}
		else if ( cmd == "backtrace" || cmd == "bt" ) {
			printStackTrace();
		}
		else if ( cmd == "break" || cmd == "b" ) {
			addBreakPoint(tokens);
		}
		else if ( cmd == "breakpoints" ) {
			printBreakPoints();
		}
		else if ( cmd == "continue" || cmd == "c" ) {
			mDebugger->resume();
			continueExecution();
		}
		else if ( cmd == "delete" || cmd == "d" ) {
			removeBreakPoint(tokens);
		}
		else if ( cmd == "execute" || cmd == "e" ) {
			executeSymbol(tokens);
		}
		else if ( cmd == "help" ) {
			printHelp();
		}
		else if ( cmd == "ignore" ) {
			mDebugger->resumeWithoutBreaks();
			continueExecution();
		}
		else if ( cmd == "into" || cmd == "i" ) {
			mDebugger->stepInto();
			continueExecution();
		}
		else if ( cmd == "modify" || cmd == "m" ) {
			modifySymbol(tokens);
		}
		else if ( cmd == "next" || cmd == "n" ) {
			mDebugger->stepOver();
			continueExecution();
		}
		else if ( cmd == "out" || cmd == "o" ) {
			mDebugger->stepOut();
			continueExecution();
		}
		else if ( cmd == "print" || cmd == "p" ) {
			printSymbol(tokens);
		}
		else if ( cmd == "quit" || cmd == "q" ) {
			mRunning = false;

			if ( mScope ) {
				// hack to exit debugger during an active debugging session
				throw Runtime::ControlFlow::ExitProgram;
			}
		}
		else if ( cmd == "run" || cmd == "r" ) {
			if ( mScope ) {
				mDebugger->resume();
				continueExecution();
			}
			else {
				run(tokens);
			}
		}
		else if ( cmd == "unwatch" ) {
			removeWatch(tokens);
		}
		else if ( cmd == "watch" || cmd == "w" ) {
			addWatch(tokens);
		}
		else if ( cmd == "watches" ) {
			refreshWatches();
		}
		else {
			writeln("unknown command '" + cmd + "'");
		}
	}

	return "";
}

void Backend::executeSymbol(const StringList& tokens)
{
	if ( !mScope ) {
		writeln("no scope available!");
		return;
	}

	std::string name;

	StringList::const_iterator it = tokens.begin();
	it++;	// skip first token
	if ( it != tokens.end() ) {
		name = (*it);
	}

	Symbol* symbol = getSymbol(name);
	if ( !symbol ) {
		symbol = getCachedSymbol(name);
	}
	if ( !symbol ) {
		writeln("could not resolve symbol '" + name + "'!");
		return;
	}

	if ( symbol->getSymbolType() != Symbol::IType::MethodSymbol ) {
		writeln("could not execute non-method symbol '" + name + "'!");
		return;
	}

	Runtime::Method* method = static_cast<Runtime::Method*>(symbol);
	try {
		Runtime::Object result;
		method->execute(ParameterList(), &result, Token());

		writeln(result.ToString());
	}
	catch ( std::exception &e ) {
		writeln(e.what());
	}
	catch ( ... ) {
		writeln("unknown exception occured");
	}
}

Symbol* Backend::getCachedSymbol(const std::string& name) const
{
	for ( Symbols::const_iterator it = mSymbolCollection.begin(); it != mSymbolCollection.end(); ++it ) {
		if ( it->first == name ) {
			return it->second;
		}
	}

	return 0;
}

Symbol* Backend::getSymbol(std::string name) const
{
	std::string child;
	std::string parent;
	SymbolScope* scope = mScope;

	do {
		if ( !scope ) {
			return 0;
		}

		Tools::split(name, parent, child);

		if ( !parent.empty() && !child.empty() ) {
			scope = static_cast<ObjectiveScript::Runtime::Object*>(scope->resolve(parent, false));
		}
		else {
			return scope->resolve(parent, false);
		}

		name = child;
	} while ( !name.empty() );

	return 0;
}

bool Backend::modifySymbol(const StringList& tokens)
{
	if ( tokens.size() != 3 ) {
		writeln("invalid number of arguments!");
		return false;
	}

	std::string name;

	StringList::const_iterator it = tokens.begin();
	it++;	// skip first token
	if ( it != tokens.end() ) {
		name = (*it++);
	}

	Symbol* symbol = getSymbol(name);
	if ( !symbol ) {
		writeln("could not resolve symbol '" + name + "'!");
		return false;
	}

	Runtime::Object* object = static_cast<Runtime::Object*>(symbol);
	if ( !object->isAtomicType() ) {
		writeln("can not modify complex type '" + object->Typename() + "' ");
		return false;
	}

	object->setValue(Runtime::AtomicValue((*it)));
	return true;
}

int Backend::notify(SymbolScope* scope, const Core::BreakPoint& breakpoint)
{
	mContinue = false;
	mScope = scope;

	// Condition check
	Core::Condition condition = breakpoint.getCondition();
	Symbol* lhs = getSymbol(condition.lhs());
	Symbol* rhs = getSymbol(condition.rhs());

	if ( !condition.lhs().empty() && !lhs ) {
		if ( addLiteralSymbol(condition.lhs(), condition.lhs()) ) {
			lhs = getCachedSymbol(condition.lhs());
		}
	}
	if ( !condition.rhs().empty() && !rhs ) {
		if ( addLiteralSymbol(condition.rhs(), condition.rhs()) ) {
			rhs = getCachedSymbol(condition.rhs());
		}
	}

	if ( !condition.evaluate(lhs, rhs) ) {
		mContinue = true;
		mScope = 0;
		return 0;
	}

	// Breakpoint check
	if ( scope && !(breakpoint == Core::Debugger::immediateBreakPoint) ) {
		writeln("[Breakpoint " + breakpoint.toString() + " reached]");
	}

	// automatically update watches
	if ( mAutoWatch && mScope ) {
		refreshWatches();
	}

	while ( mRunning && !mContinue ) {
		write(mSettings->prompt());

		std::string command = mTerminal->read();

		executeCommand(
			parseCommands(command)
		);
	}

	mScope = 0;

	return 0;
}

int Backend::notifyEnter(SymbolScope* scope, const Core::BreakPoint& breakpoint)
{
	writeln("[Stepping into " + StackTrace::GetInstance().currentStackLevel().toString() + "]");

	return notify(scope, breakpoint);
}

int Backend::notifyException(SymbolScope* scope, const Core::BreakPoint& breakpoint)
{
	writeln("[Exception has been thrown in " + StackTrace::GetInstance().currentStackLevel().toString() + "]");

	return notify(scope, breakpoint);
}

int Backend::notifyExit(SymbolScope* scope, const Core::BreakPoint& breakpoint)
{
	writeln("[Stepping out of " + StackTrace::GetInstance().currentStackLevel().toString() + "]");

	return notify(scope, breakpoint);
}

StringList Backend::parseCommands(const std::string& commands) const
{
	StringList params;

	// read in parameters
	unsigned count = 0;
	std::string token;

	while ( count < commands.size() ) {
		char c = commands[count];

		if ( c == ' ' ) {
			if ( !token.empty() ) {
				params.push_back(token);
			}
			token = "";
		}
		else {
			token += c;
		}

		count++;
	}

	// add last token
	if ( !token.empty() ) {
		params.push_back(token);
	}

	return params;
}

void Backend::prepare(const StringList& tokens)
{
	std::string paramStr = mSettings->filename();

	StringList::const_iterator it = tokens.begin();
	it++;	// skip first token
	while ( it != tokens.end() ) {
		paramStr += " " + (*it++);
	}

	mParameters.clear();
	mParameters.push_back(ObjectiveScript::Parameter("argc", ObjectiveScript::Runtime::IntegerObject::TYPENAME, 1));
	mParameters.push_back(ObjectiveScript::Parameter("argv", ObjectiveScript::Runtime::StringObject::TYPENAME, paramStr));
}

void Backend::printBreakPoints()
{
	Core::BreakPointCollection list = mDebugger->getBreakPoints();

	writeln("BreakPoints:");

	int idx = 1;
	for ( Core::BreakPointCollection::const_iterator it = list.begin(); it != list.end(); ++it ) {
		writeln(Tools::toString(idx) + ": " + it->toString());

		idx++;
	}
}

void Backend::printHelp()
{
	writeln("Generic commands:");

	writeln("\tautowatch     automatically show watches after reaching breakpoint");
	writeln("\tbreak (b)     add breakpoint");
	writeln("\tbreakpoints   print breakpoints");
	writeln("\tdelete (d)    delete breakpoint");
	writeln("\thelp          print help message");
	writeln("\tquit (q)      quit odebugger");
	writeln("\trun (r)       run program");
	writeln("\tunwatch       remove symbol watch");
	writeln("\twatch (w)     add symbol watch");

	if ( mScope ) {
	writeln("Debugging commands:");
	writeln("\tbacktrace (bt)   print stack trace");
	writeln("\tcontinue (c)     continue program execution");
	writeln("\texecute (e)      execute program function");
	writeln("\tignore           ignore all breakpoints and continue program execution");
	writeln("\tinto (i)         break on next function call");
	writeln("\tmodify (m)       modify (atomic) symbol");
	writeln("\tnext (n)         step over");
	writeln("\tout (o)          break on next function exit");
	writeln("\tprint (p)        print symbol");
	writeln("\twatches (p)      print watched symbols");
	}
}

void Backend::printStackTrace()
{
	StackTrace::Stack stack = StackTrace::GetInstance().getStack();

	for ( StackTrace::Stack::const_iterator it = stack.begin(); it != stack.end(); ++it ) {
		writeln(it->toString());
	}
}

void Backend::printSymbol(const StringList& tokens)
{
	std::string name;

	StringList::const_iterator it = tokens.begin();
	it++;	// skip first token
	if ( it != tokens.end() ) {
		name = (*it);
	}

	Symbol* symbol = getSymbol(name);
	if ( !symbol ) {
		writeln("could not resolve symbol '" + name + "'!");
		return;
	}

	writeln(symbol->ToString());
}

void Backend::refreshWatches()
{
	for ( WatchCollection::iterator it = mWatches.begin(); it != mWatches.end(); ++it ) {
		std::string value = "<not accessible>";

		Symbol* symbol = getSymbol(it->symbol());
		if ( symbol ) {
			value = symbol->ToString();
		}

		writeln("[Watch] " + it->symbol() + ": " + value);
	}
}

bool Backend::removeBreakPoint(const StringList& tokens)
{
	if ( tokens.size() != 2 ) {
		writeln("invalid number of arguments!");
		return false;
	}

	StringList::const_iterator it = tokens.begin();
	it++;	// skip first token

	int idx = ::Utils::Tools::stringToInt((*it));

	Core::BreakPointCollection points = mDebugger->getBreakPoints();

	int count = 1;
	for ( Core::BreakPointCollection::const_iterator it = points.begin(); it != points.end(); ++it, ++count ) {
		if ( count == idx ) {
			mDebugger->removeBreakPoint((*it));
			return true;
		}
	}

	return false;
}

bool Backend::removeWatch(const StringList& tokens)
{
	if ( tokens.size() != 2 ) {
		writeln("invalid number of arguments!");
		return false;
	}

	StringList::const_iterator it = tokens.begin();
	it++;	// skip first token

	WatchCollection::const_iterator watchIt = mWatches.find(Watch((*it)));
	if ( watchIt != mWatches.end() ) {
		mWatches.erase(watchIt);
		return true;
	}

	return false;
}

void Backend::run(const StringList& tokens)
{
	prepare(tokens);

	start();

	stop();
}

void Backend::shutdown()
{
	stop();

	mContinue = false;
	mDebugger->unregisterReceiver(this);
	mRunning = false;
	mScope = 0;

	clearSymbolCache();
}

void Backend::start()
{
	stop();

	mDebugger->breakOnException(mBreakOnException);
	mDebugger->resume();
	StackTrace::GetInstance().clear();

	mVirtualMachine = new VirtualMachine();
	mVirtualMachine->setBaseFolder(mSettings->root());

	// add extensions
#ifdef USE_APACHE_EXTENSION
	mVirtualMachine->addExtension(new ObjectiveScript::Extensions::Apache::ApacheExtension());
#endif
#ifdef USE_JSON_EXTENSION
	mVirtualMachine->addExtension(new ObjectiveScript::Extensions::Json::JsonExtension());
#endif
#ifdef USE_MYSQL_EXTENSION
	mVirtualMachine->addExtension(new ObjectiveScript::Extensions::Mysql::MysqlExtension());
#endif
#ifdef USE_SYSTEM_EXTENSION
	mVirtualMachine->addExtension(new ObjectiveScript::Extensions::System::SystemExtension());
#endif

	try {
		writeln("[Starting program: " + mSettings->filename() + "]");

		ObjectiveScript::Script *script = mVirtualMachine->createScriptFromFile(mSettings->filename(), mParameters);
		assert(script);

		// check if an instance ("main") of a Main object exists
		ObjectiveScript::Runtime::Object *main = static_cast<ObjectiveScript::Runtime::Object*>(script->resolve("main"));

		if ( !main || main->isAtomicType() ) {
			writeln("[Using structured execution mode]");

			ObjectiveScript::Runtime::IntegerObject result;
			script->execute("Main", mParameters, &result);

			writeln("[Process finished with exit code " + result.getValue().toStdString() + "]");
		}

		writeln("[Process exited normally]");
	}
	catch ( std::exception& e ) {
		writeln(e.what());
	}
}

void Backend::stop()
{
	if ( mVirtualMachine ) {
		delete mVirtualMachine;
		mVirtualMachine = 0;
	}
}

void Backend::toggleAutoWatch()
{
	mAutoWatch = !mAutoWatch;

	write("Autowatch is ");
	if ( mAutoWatch ) {
		writeln("on");
	}
	else {
		writeln("off");
	}
}

void Backend::write(std::string text)
{
	if ( mTerminal ) {
		mTerminal->write(text);
	}
}

void Backend::writeln(std::string text)
{
	if ( mTerminal ) {
		mTerminal->writeln(text);
	}
}


}
