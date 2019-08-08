
// Header
#include "LocalClient.h"

// Library includes
#include <fstream>
#include <signal.h>
#include <Json/Json.h>

// Project includes
#include <Common/Settings.h>
#include <Core/AST/TreeLineBuffer.h>
#include <Core/AST/PrintVisitor.h>
#include <Core/Common/Method.h>
#include <Core/Common/Namespace.h>
#include <Core/Designtime/Parser/Tokenizer.h>
#include <Core/Runtime/BuildInTypes/BoolObject.h>
#include <Core/Runtime/BuildInTypes/DoubleObject.h>
#include <Core/Runtime/BuildInTypes/FloatObject.h>
#include <Core/Runtime/BuildInTypes/IntegerObject.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Runtime/Script.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include <Core/VirtualMachine/VirtualMachine.h>
#include <Debugger/Debugger.h>
#include <Tools/Files.h>
#include <Tools/Strings.h>

// Extension includes
#include <Extensions.h>

// Namespace declarations


namespace ObjectiveScript {


/*
* SIGINT handler: sets debugger to immediately break on next command
*/
void handleSIGINT(int signal)
{
	std::cout << "Caught signal SIGINT " << signal << std::endl;

	// set debugger to break on next command
	Core::Debugger::Instance().stepOver();
}


LocalClient::LocalClient()
: mContinue(false),
  mCurrentFrameId(0),
  mCurrentThreadId(0),
  mDebugger(0),
  mRunning(true),
  mScope(0),
  mVirtualMachine(0)
{
	mDebugger = &ObjectiveScript::Core::Debugger::Instance();
}

LocalClient::~LocalClient()
{
	shutdown();

	mDebugger = 0;
}

bool LocalClient::addBreakPoint(const StringList& tokens)
{
	if ( tokens.size() != 3 && tokens.size() != 6 ) {
		writeln("invalid number of arguments!");
		return false;
	}

	StringList::const_iterator it = tokens.begin();
	++it;	// skip first token

	std::string file = Utils::Tools::Files::GetFullname((*it++));
	unsigned int line = (unsigned int)Utils::Tools::stringToInt((*it++));

	Core::BreakPoint breakpoint(Common::Position(file, line));

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

bool LocalClient::addLiteralSymbol(const std::string& name, const std::string& value)
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

bool LocalClient::addWatch(const StringList& tokens)
{
	if ( tokens.size() != 2 ) {
		writeln("invalid number of arguments!");
		return false;
	}

	StringList::const_iterator it = tokens.begin();
	++it;	// skip first token

	mWatches.insert(Watch((*it)));

	return true;
}

void LocalClient::clearSymbolCache()
{
	for ( Symbols::iterator it = mSymbolCollection.begin(); it != mSymbolCollection.end(); ++it ) {
		delete it->second;
	}
	mSymbolCollection.clear();
}

void LocalClient::continueExecution()
{
	mContinue = true;
}

int LocalClient::exec()
{
	// initial checks
	assert(mDebugger);
	assert(!mVirtualMachine);

	// store previous autostart value
	bool autostart = mSettings->autoStart();

	loadConfig();

	// set autostart even though disabled by configuration
	mSettings->autoStart(autostart || mSettings->autoStart());

	// register SIGINT handle
	signal(SIGINT, handleSIGINT);

	// start program execution
	while ( mRunning ) {
		if ( mSettings->autoStart() ) {
			run(StringList());
		}

		handleBreakpoint(0, Core::Debugger::immediateBreakPoint);
	}

	// unregister SIGINT handler
	signal(SIGINT, 0);

	// program exection is done
	return 0;
}

std::string LocalClient::executeCommand(const StringList &tokens)
{
	StringList::const_iterator it = tokens.begin();

	if ( it != tokens.end() ) {
		std::string cmd = (*it++);

		if ( cmd == "autolist" ) {
			toggleAutoList();
		}
		else if ( cmd == "autostart" ) {
			toggleAutoStart();
		}
		else if ( cmd == "autostop" ) {
			toggleAutoStop();
		}
		else if ( cmd == "autowatch" ) {
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
			executeMethod(tokens);
		}
		else if ( cmd == "frame" || cmd == "f" ) {
			setCurrentFrame(tokens);
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
		else if ( cmd == "list" || cmd == "l" ) {
			printScope(mScope);
		}
		else if ( cmd == "load" ) {
			loadConfig();
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
		else if ( cmd == "store" ) {
			saveConfig();
		}
		else if ( cmd == "thread" || cmd == "t" ) {
			setCurrentThread(tokens);
		}
		else if ( cmd == "threads" ) {
			printThreads();
		}
		else if ( cmd == "unwatch" ) {
			removeWatch(tokens);
		}
		else if ( cmd == "watch" || cmd == "w" ) {
			addWatch(tokens);
		}
		else if ( cmd == "watches" ) {
			printWatches();
		}
		else {
			writeln("unknown command '" + cmd + "'");
		}
	}

	return "";
}

void LocalClient::executeMethod(const StringList &tokens)
{
	if ( !mScope ) {
		writeln("no scope available!");
		return;
	}

	std::string name;

	StringList::const_iterator it = tokens.begin();
	++it;	// skip first token
	if ( it != tokens.end() ) {
		name = (*it++);
	}

	ParameterList params;

	for ( ; it != tokens.end(); ++it ) {
		std::string sym = (*it);

		if ( addLiteralSymbol(sym, sym) ) {
			Runtime::Object* object = dynamic_cast<Runtime::Object*>(getCachedSymbol(sym));

			if ( object ) {
				params.push_back(Parameter::CreateRuntime(object->QualifiedTypename(), object->getValue()));
			}
		}
	}

	MethodSymbol* symbol = getMethod(name, params);
	if ( !symbol ) {
		writeln("could not resolve symbol '" + name + "' with parameters (" + toString(params) + ")!");
		return;
	}

	if ( symbol->getSymbolType() != Symbol::IType::MethodSymbol ) {
		writeln("could not execute non-method symbol '" + name + "'!");
		return;
	}

	Common::Method* method = static_cast<Common::Method*>(symbol);
	try {
		Runtime::Object result;

		Controller::Instance().thread(mCurrentThreadId)->execute(NULL, method, params, &result);

		writeln("returned " + result.ToString());
	}
	catch ( std::exception &e ) {
		writeln(e.what());
	}
	catch ( ... ) {
		writeln("unknown exception occured");
	}
}

Symbol* LocalClient::getCachedSymbol(const std::string& name) const
{
	for ( Symbols::const_iterator it = mSymbolCollection.begin(); it != mSymbolCollection.end(); ++it ) {
		if ( it->first == name ) {
			return it->second;
		}
	}

	return 0;
}

MethodSymbol* LocalClient::getMethod(std::string name, const ParameterList& params) const
{
	if ( !mScope ) {
		return 0;
	}

	std::string child;
	std::string parent;
	MethodScope* scope = getEnclosingMethodScope(mScope);

	do {
		if ( !scope ) {
			return 0;
		}

		Utils::Tools::split(name, parent, child);

		if ( !parent.empty() && !child.empty() ) {
			scope = dynamic_cast<ObjectiveScript::Runtime::Object*>(scope->resolve(parent, false));
		}
		else {
			return scope->resolveMethod(parent, params, false);
		}

		name = child;
	} while ( !name.empty() );

	return 0;
}

Common::Method* LocalClient::getMethodFromScope(IScope *scope) const
{
	while ( scope ) {
		if ( scope->getScopeType() == IScope::IType::NamedScope ) {
			Common::Method* result = dynamic_cast<Common::Method*>(scope);
			if ( result ) {
				return result;
			}
		}

		scope = scope->getEnclosingScope();
	}

	return 0;
}

MethodScope* LocalClient::getEnclosingMethodScope(IScope* scope) const
{
	while ( scope ) {
		IScope* parent = scope->getEnclosingScope();

		if ( parent && parent->getScopeType() == IScope::IType::NamedScope ) {
			return dynamic_cast<MethodScope*>(parent);
		}

		scope = parent;
	}

	return 0;
}

Runtime::Object* LocalClient::getEnclosingObject(IScope* scope) const
{
	while ( scope ) {
		IScope* parent = scope->getEnclosingScope();

		if ( parent && parent->getScopeType() == IScope::IType::MethodScope ) {
			Runtime::Object* result = dynamic_cast<Runtime::Object*>(parent);
			if ( result ) {
				return result;
			}
		}

		scope = parent;
	}

	return 0;
}

Symbol* LocalClient::getSymbol(std::string name) const
{
	std::string child;
	std::string parent;
	IScope* scope = mScope;

	do {
		if ( !scope ) {
			return 0;
		}

		Utils::Tools::split(name, parent, child);

		if ( !parent.empty() && !child.empty() ) {
			scope = dynamic_cast<ObjectiveScript::Runtime::Object*>(scope->resolve(parent, false));
		}
		else {
			return scope->resolve(parent, false);
		}

		name = child;
	} while ( !name.empty() );

	return 0;
}

int LocalClient::handleBreakpoint(IScope* scope, const Core::BreakPoint& breakpoint)
{
    mContinue = false;
    mScope = scope;

    mBreakpoint = breakpoint;

    // automatically print scope
    if ( mSettings->autoList() ) {
        printScope(mScope);
    }

    // automatically update watches
    if ( mSettings->autoWatch() && mScope ) {
        refreshWatches();
    }

    while ( mRunning && !mContinue ) {
        if ( !mSettings->remoteClient() ) {			// only print prompt for local clients
            write(mSettings->prompt());
        }

        std::string command = read();				// read command from local or remote terminal

        executeCommand(
            parseCommands(command)
        );
    }

    mScope = 0;

    return 0;
}

void LocalClient::loadConfig()
{
	std::string filename = mSettings->filename() + ".dbg";

	if ( !::Utils::Tools::Files::exists(filename) ) {
		// no configuration file exists
		return;
	}

	writeln("Loading configuration...");

	// reset current configuration
	mDebugger->clearBreakPoints();
	mWatches.clear();

	std::fstream stream;
	stream.open(filename.c_str(), std::ios::in);	// open for reading
	std::string data((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());	// read stream
	stream.close();

	Json::Value config = Json::Parser::parse(data);

	// (1) odebugger config
	if ( config.isMember("autolist") ) {
		mSettings->autoList(config["autolist"].asBool());
	}
	if ( config.isMember("autostart") ) {
		mSettings->autoStart(config["autostart"].asBool());
	}
	if ( config.isMember("autostop") ) {
		mSettings->autoStop(config["autostop"].asBool());
	}
	if ( config.isMember("autowatch") ) {
		mSettings->autoWatch(config["autowatch"].asBool());
	}
	if ( config.isMember("breakonexceptioncatch") ) {
		mSettings->breakOnExceptionCatch(config["breakonexceptioncatch"].asBool());
	}
	if ( config.isMember("breakonexceptionthrow") ) {
		mSettings->breakOnExceptionThrow(config["breakonexceptionthrow"].asBool());
	}

	// (2) breakpoints
	if ( config.isMember("breakpoints") ) {
		// parse breakpoints
		Json::Value::Members breakpoints = config["breakpoints"].members();
		for ( Json::Value::Members::const_iterator it = breakpoints.begin(); it != breakpoints.end(); ++it ) {
			std::string command = "breakpoint " + it->asString();

			addBreakPoint(
				parseCommands(command)
			);
		}
	}

	// (3) watches
	if ( config.isMember("watches") ) {
		// parse watches
		Json::Value::Members watches = config["watches"].members();
		for ( Json::Value::Members::const_iterator it = watches.begin(); it != watches.end(); ++it ) {
			std::string command = "watch " + it->asString();

			addWatch(
				parseCommands(command)
			);
		}
	}
}

bool LocalClient::modifySymbol(const StringList& tokens)
{
	if ( tokens.size() != 3 ) {
		writeln("invalid number of arguments!");
		return false;
	}

	std::string name;

	StringList::const_iterator it = tokens.begin();
	++it;	// skip first token
	if ( it != tokens.end() ) {
		name = (*it++);
	}

	Symbol* symbol = getSymbol(name);
	if ( !symbol ) {
		writeln("could not resolve symbol '" + name + "'!");
		return false;
	}

	Runtime::Object* object = dynamic_cast<Runtime::Object*>(symbol);
	if ( !object ) {
		writeln("'" + name + "' is not a variable");
		return false;
	}

	if ( !object->isAtomicType() ) {
		writeln("can not modify complex type '" + object->QualifiedTypename() + "' ");
		return false;
	}

	object->setValue(Runtime::AtomicValue((*it)));
	return true;
}

int LocalClient::notify(IScope* scope, const Core::BreakPoint& breakpoint)
{
    writeln("[Breakpoint " + breakpoint.toString() + " reached]");

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

    if ( condition.isValid() && !condition.evaluate(lhs, rhs) ) {
        mContinue = true;
        return 0;
    }

    mSettings->autoStop(false);

    return handleBreakpoint(scope, breakpoint);
}

int LocalClient::notifyEnter(IScope* scope, const Core::BreakPoint& breakpoint)
{
    writeln("[Stepping into " + Controller::Instance().thread(mCurrentThreadId)->currentFrame()->toString() + "]");

    return handleBreakpoint(scope, breakpoint);
}

int LocalClient::notifyExceptionCatch(IScope *scope, const Core::BreakPoint &breakpoint)
{
	writeln("[Caught exception in " + Controller::Instance().thread(mCurrentThreadId)->currentFrame()->toString() + "]");

	return handleBreakpoint(scope, breakpoint);
}

int LocalClient::notifyExceptionThrow(IScope *scope, const Core::BreakPoint &breakpoint)
{
	writeln("[Exception has been thrown in " + Controller::Instance().thread(mCurrentThreadId)->currentFrame()->toString() + "]");

	return handleBreakpoint(scope, breakpoint);
}

int LocalClient::notifyExit(IScope* scope, const Core::BreakPoint& breakpoint)
{
    writeln("[Stepping out of " + Controller::Instance().thread(mCurrentThreadId)->currentFrame()->toString() + "]");

    return handleBreakpoint(scope, breakpoint);
}

StringList LocalClient::parseCommands(const std::string& commands) const
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

void LocalClient::prepare(const StringList& tokens)
{
	std::string paramStr = mSettings->filename();

	StringList::const_iterator it = tokens.begin();
	++it;	// skip first token
	while ( it != tokens.end() ) {
		paramStr += "\n" + (*it++);
	}

	mParameters.clear();
	mParameters.push_back(ObjectiveScript::Parameter::CreateRuntime(ObjectiveScript::Runtime::IntegerObject::TYPENAME, (int)tokens.size()));
	mParameters.push_back(ObjectiveScript::Parameter::CreateRuntime(ObjectiveScript::Runtime::StringObject::TYPENAME, paramStr));
}

void LocalClient::printBreakPoints()
{
	Core::BreakPointCollection list = mDebugger->getBreakPoints();

	writeln("BreakPoints:");

	int idx = 1;
	for ( Core::BreakPointCollection::const_iterator it = list.begin(); it != list.end(); ++it ) {
		writeln(Utils::Tools::toString(idx) + ": " + it->toString());

		idx++;
	}
}

void LocalClient::printHelp()
{
	writeln("Generic commands:");

	writeln("\tautolist      automatically list source code after reaching breakpoint");
	writeln("\tautostart     automatically run program after startup");
	writeln("\tautowatch     automatically show watches after reaching breakpoint");
	writeln("\tbreak (b)     add breakpoint");
	writeln("\tbreakpoints   print all breakpoints");
	writeln("\tdelete (d)    delete breakpoint");
	writeln("\thelp          print this help message");
	writeln("\tload          load configuration");
	writeln("\tquit (q)      quit odebugger");
	writeln("\trun (r)       run or resume program");
	writeln("\tstore         store configuration");
	writeln("\tunwatch       remove symbol watch");
	writeln("\twatch (w)     add symbol watch");
	writeln("\twatches       print all watched symbols");

	if ( mScope ) {
		writeln("Debugging commands:");
		writeln("\tbacktrace (bt)   print stack trace");
		writeln("\tcontinue (c)     continue program execution");
		writeln("\texecute (e)      execute program function");
		writeln("\tframe (f)        select frame");
		writeln("\tignore           ignore all breakpoints and continue program execution");
		writeln("\tinto (i)         break on next function call");
		writeln("\tlist (l)         print current method");
		writeln("\tmodify (m)       modify (atomic) symbol");
		writeln("\tnext (n)         step over");
		writeln("\tout (o)          break on next function exit");
		writeln("\tprint (p)        print symbol");
		writeln("\tthread (t)       select thread");
		writeln("\tthreads          list current threads");
	}
}

void LocalClient::printScope(IScope* scope)
{
	Common::Method* method = getMethodFromScope(scope);
	if ( !method ) {
		return;
	}

	AST::TreeLineBuffer buffer;
	AST::TreeLineBuffer::Lines lines;
	AST::PrintVisitor visitor;

	visitor.generate(method->getRootNode(), buffer);

	buffer.getLines(lines);

	unsigned int activeLine = mBreakpoint.getLine();
	unsigned int currentLine = 0;
	unsigned int previousLine = 0;

	AST::TreeLineBuffer::Lines::const_iterator it = lines.begin();

	while ( it != lines.end() ) {
		currentLine = it->first.mLine;

		if ( currentLine != previousLine ) {
			std::cout << std::endl;
			if ( currentLine == activeLine ) {
				std::cout << "> ";
			}
			else {
				std::cout << "  ";
			}
			std::cout << it->first.mLine << ": ";
			previousLine = currentLine;
		}

		std::cout << it->second;

		it++;
	}

	std::cout << std::endl << std::endl;
}

void LocalClient::printStackTrace()
{
	if ( !mVirtualMachine ) {
		return;
	}

	Controller::Instance().threads()->print();
}

void LocalClient::printSymbol(const StringList& tokens)
{
	std::string name;

	StringList::const_iterator it = tokens.begin();
	++it;	// skip first token
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

void LocalClient::printThreads()
{
	writeln("Threads:");

	Controller::Instance().threads()->print();
}

void LocalClient::printWatches()
{
	writeln("Watches:");

	refreshWatches();
}

std::string LocalClient::read()
{
	std::string result;

	getline(std::cin >> std::ws, result);
	std::cin.clear();

	return result;
}

void LocalClient::refreshWatches()
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

bool LocalClient::removeBreakPoint(const StringList& tokens)
{
	if ( tokens.size() != 2 ) {
		writeln("invalid number of arguments!");
		return false;
	}

	StringList::const_iterator it = tokens.begin();
	++it;	// skip first token

	int idx = ::Utils::Tools::stringToInt((*it));

	Core::BreakPointCollection points = mDebugger->getBreakPoints();

	int count = 1;
	for ( Core::BreakPointCollection::const_iterator breakIt = points.begin(); breakIt != points.end(); ++breakIt, ++count ) {
		if ( count == idx ) {
			mDebugger->removeBreakPoint((*breakIt));
			return true;
		}
	}

	return false;
}

bool LocalClient::removeWatch(const StringList& tokens)
{
	if ( tokens.size() != 2 ) {
		writeln("invalid number of arguments!");
		return false;
	}

	StringList::const_iterator it = tokens.begin();
	++it;	// skip first token

	WatchCollection::const_iterator watchIt = mWatches.find(Watch((*it)));
	if ( watchIt != mWatches.end() ) {
		mWatches.erase(watchIt);
		return true;
	}

	return false;
}

void LocalClient::run(const StringList& tokens)
{
	prepare(tokens);

	start();

	stop();
}

void LocalClient::saveConfig()
{
	writeln("Storing configuration...");

	Json::Value config;

	// (1) odebugger config
	config.addMember("autolist", Json::Value(mSettings->autoList()));
	config.addMember("autostart", Json::Value(mSettings->autoStart()));
	config.addMember("autostop", Json::Value(mSettings->autoStop()));
	config.addMember("autowatch", Json::Value(mSettings->autoWatch()));
	config.addMember("breakonexceptioncatch", Json::Value(mSettings->breakOnExceptionCatch()));
	config.addMember("breakonexceptionthrow", Json::Value(mSettings->breakOnExceptionThrow()));

	// (2) write breakpoints to config
	Json::Value breakpoints;
	Core::BreakPointCollection breakpointList = mDebugger->getBreakPoints();
	for ( Core::BreakPointCollection::const_iterator it = breakpointList.begin(); it != breakpointList.end(); ++it ) {
		breakpoints.addElement(it->toConfigString());
	}
	config.addMember("breakpoints", breakpoints);

	// (3) write watches to config
	Json::Value watches;
	for ( WatchCollection::const_iterator it = mWatches.begin(); it != mWatches.end(); ++it ) {
		watches.addElement(it->symbol());
	}
	config.addMember("watches", watches);

	// serialize config to string
	Json::StyledWriter writer;
	std::string data = writer.toString(config);

	std::string filename = mSettings->filename() + ".dbg";

	// write config string to file
	std::fstream stream;
	stream.open(filename.c_str(), std::ios::out);    // open file for writing
	stream.write(data.c_str(), data.size());
	stream.close();
}

void LocalClient::setCurrentFrame(Common::FrameId frameId)
{
	if ( frameId >= Controller::Instance().thread(mCurrentThreadId)->getNumFrames() ) {
		writeln("invalid frame selected!");
		return;
	}

	// update current frame id
	mCurrentFrameId = frameId;

	// update current stack/scope
	mScope = Controller::Instance().thread(mCurrentThreadId)->frame(mCurrentFrameId)->getScope();

	// automatically print scope
	if ( mSettings->autoList() ) {
		printScope(mScope);
	}

	// automatically update watches
	if ( mSettings->autoWatch() && mScope ) {
		refreshWatches();
	}
}

void LocalClient::setCurrentFrame(const StringList& tokens)
{
	if ( tokens.size() != 2 ) {
		writeln("invalid number of arguments!");
		return;
	}

	StringList::const_iterator it = tokens.begin();
	++it;	// skip first token

	setCurrentFrame((Common::FrameId)::Utils::Tools::stringToInt((*it++)));
}

void LocalClient::setCurrentThread(Common::ThreadId threadId)
{
	if ( threadId >= Controller::Instance().threads()->getNumThreads() ) {
		writeln("invalid thread selected!");
		return;
	}

	// update current thread id
	mCurrentThreadId = threadId;

	// print stack trace for select thread
	printStackTrace();

	// reset current frame to newest in thread
	setCurrentFrame(Controller::Instance().thread(mCurrentThreadId)->getNumFrames() - 1);
}

void LocalClient::setCurrentThread(const StringList& tokens)
{
	if ( tokens.size() != 2 ) {
		writeln("invalid number of arguments!");
		return;
	}

	StringList::const_iterator it = tokens.begin();
	++it;	// skip first token

	setCurrentThread((Common::FrameId)::Utils::Tools::stringToInt((*it++)));
}

void LocalClient::shutdown()
{
	stop();

	mContinue = false;
	mDebugger->clearBreakPoints();
	mDebugger->unregisterReceiver(this);
	mRunning = false;
	mScope = 0;
	mWatches.clear();

	clearSymbolCache();
}

void LocalClient::start()
{
	stop();

	mDebugger->breakOnExceptionCatch(mSettings->breakOnExceptionCatch());
	mDebugger->breakOnExceptionThrow(mSettings->breakOnExceptionThrow());
	mDebugger->init();
    mDebugger->stepInto();      // automatically stop before executing the first line

	mVirtualMachine = new VirtualMachine();
	for ( StringSet::const_iterator it = mSettings->libraryFolders().begin(); it != mSettings->libraryFolders().end(); ++it ) {
		mVirtualMachine->addLibraryFolder((*it));
	}

	// add extensions
#ifdef USE_APACHE_EXTENSION
	//mVirtualMachine->addExtension(new ObjectiveScript::Extensions::Apache::ApacheExtension());
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

		Runtime::Object result;

		Script *script = mVirtualMachine->createScriptFromFile(mSettings->filename());
		assert(script);

		mVirtualMachine->run(script, mParameters, &result);

		writeln("[Process finished" + (result.getValue().type() == Runtime::AtomicValue::Type::UNKNOWN ? "" : " with exit code " + result.getValue().toStdString()) + "]");

		if ( mSettings->autoStop() ) {
			mRunning = false;
		}
	}
	catch ( std::exception& e ) {
		writeln(e.what());
	}
}

void LocalClient::stop()
{
	if ( mVirtualMachine ) {
		delete mVirtualMachine;
		mVirtualMachine = 0;
	}

	mBreakpoint = Core::BreakPoint();
}

void LocalClient::toggleAutoList()
{
	mSettings->autoList(!mSettings->autoList());

	write("AutoList is ");
	if ( mSettings->autoList() ) {
		writeln("on");
	}
	else {
		writeln("off");
	}
}

void LocalClient::toggleAutoStart()
{
	mSettings->autoStart(!mSettings->autoStart());

	write("AutoStart is ");
	if ( mSettings->autoStart() ) {
		writeln("on");
	}
	else {
		writeln("off");
	}
}

void LocalClient::toggleAutoStop()
{
	mSettings->autoStop(!mSettings->autoStop());

	write("AutoStop is ");
	if ( mSettings->autoStop() ) {
		writeln("on");
	}
	else {
		writeln("off");
	}
}

void LocalClient::toggleAutoWatch()
{
	mSettings->autoWatch(!mSettings->autoWatch());

	write("AutoWatch is ");
	if ( mSettings->autoWatch() ) {
		writeln("on");
	}
	else {
		writeln("off");
	}
}

void LocalClient::write(const std::string& text)
{
	std::cout << text;
}

void LocalClient::writeln(const std::string& text)
{
	std::cout << text << std::endl;
}


}
