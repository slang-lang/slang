
// Header
#include "Script.h"

// Library includes
// #include <iostream>
#include <vector>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Common/Method.h>
#include <Core/Common/Namespace.h>
#include <Core/Runtime/ControlFlow.h>
#include <Core/VirtualMachine/Controller.h>
#include <Utils.h>

// Namespace declarations


namespace
{

	std::vector<std::string> split(std::string s, char delim);

}

namespace Slang {


void Script::execute(ThreadId threadId, const std::string& method, const ParameterList& params, Runtime::Object* result)
{
	MethodScope* scope = Controller::Instance().globalScope();

	auto spaces = split( method, '.' );
	for ( size_t i = 0; i < spaces.size() - 1; ++i ) {
		auto* symbol = scope->resolve( spaces[i] );

		auto* ms = dynamic_cast<MethodScope*>( symbol );
		if ( !ms ) {
			throw Common::Exceptions::Exception( "could not resolve named scope '" + spaces[i] + "'" );
		}

		scope = ms;
	}

	// std::cout << "Namespace: " << scope->getFullScopeName() << std::endl;
	// for ( auto methodIt = dynamic_cast<MethodScope*>(scope)->beginMethods(); methodIt != dynamic_cast<MethodScope*>(scope)->endMethods(); ++methodIt ) {
	// 	std::cout << "  Method: " << (*methodIt)->ToString() << std::endl;
	// }

	auto* methodSymbol = dynamic_cast<Common::Method*>( scope->resolveMethod( spaces.back(), params, true, Visibility::Public ) );
	if ( !methodSymbol ) {
		throw Common::Exceptions::Exception("could not resolve method '" + method + "(" + toString(params) + ")'");
	}

	auto controlflow = Controller::Instance().thread(threadId)->execute(nullptr, methodSymbol, params, result);

	if ( controlflow == Runtime::ControlFlow::Throw ) {
		auto data = Controller::Instance().thread(threadId)->exception();

		std::string text = "Exception raised in " + data.getPosition().toString() + ":\n";
					text += data.getData()->ToString() + "\n";
					text += data.getStackTrace();

		throw Common::Exceptions::Exception(text);
	}
}

Symbol* Script::resolve(const std::string &symbol)
{
	return Controller::Instance().globalScope()->resolve(symbol);
}

Symbol* Script::resolveMethod(const std::string &method, const ParameterList &params)
{
	return Controller::Instance().globalScope()->resolveMethod(method, params);
}


}


namespace
{

	std::vector<std::string> split( std::string s, char delim ) {
		std::vector<std::string> result;
		size_t start = 0;

		while ( true ) {
			auto pos = s.find( delim, start );
			if ( pos == std::string::npos ) {
				result.emplace_back( s.substr( start ) );
				return result;
			}

			result.emplace_back( s.substr( start, pos - start ) );
			start = pos + 1;
		}
	}

}