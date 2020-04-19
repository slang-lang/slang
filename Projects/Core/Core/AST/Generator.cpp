
// Header
#include "Generator.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Common/Method.h>
#include <Core/Common/Namespace.h>
#include <Core/Designtime/BluePrintObject.h>
#include <Core/Object.h>
#include <Core/VirtualMachine/Controller.h>
#include <Utils.h>
#include "TreeGenerator.h"

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


Generator::Generator(bool collectErrors)
: mCollectErrors(collectErrors),
  mErrorCount(0),
  mRepository(nullptr)
{
	mRepository = Controller::Instance().repository();
}

/*
 * returns the number of errors that occurred during AST generation
 */
size_t Generator::hasErrors() const
{
	return mErrorCount;
}

/*
 * walk through global namespace and process all methods of all symbols
 */
void Generator::process(MethodScope* base)
{
	if ( !base ) {
		throw Common::Exceptions::Exception("invalid scope symbol provided");
	}

	for ( auto it = base->beginSymbols(); it != base->endSymbols(); ++it ) {
		switch ( it->second->getSymbolType() ) {
			case Symbol::IType::MethodSymbol:
				throw Common::Exceptions::Exception("invalid symbol found: " + it->second->getName());
			case Symbol::IType::BluePrintObjectSymbol:
				processBluePrint(dynamic_cast<Designtime::BluePrintObject*>(it->second));
				break;
			case Symbol::IType::NamespaceSymbol:
				processNamespace(dynamic_cast<Common::Namespace*>(it->second));
				break;
			case Symbol::IType::ObjectSymbol:
				break;	// ignore runtime symbols
		}
	}

	if ( base->beginMethods() != base->endMethods() ) {
		for ( auto it = base->beginMethods(); it != base->endMethods(); ++it ) {
			processMethod(static_cast<Common::Method*>((*it)));
		}
	}
}

/*
 * walk through a blueprint and process all members and methods
 */
void Generator::processBluePrint(Designtime::BluePrintObject* object)
{
	if ( !object ) {
		throw Common::Exceptions::Exception("invalid blueprint symbol provided");
	}
	if ( object->isInterface() ) {
		// interfaces have no implementation, so there's nothing to parse; adieu..
		return;
	}
	if ( object->provideMethods().empty() && object->provideSymbols().empty() ) {
		// an object without methods and symbols... maybe a primitive?
		return;
	}
	if ( !object->getPrototypeConstraints().empty() ) {
		// skip prototypes
		return;
	}

	process(object);
}

/*
 * generates the AST for a single function/method
 */
void Generator::processMethod(Common::Method* method)
{
	if ( !method ) {
		throw Common::Exceptions::Exception("invalid method symbol provided");
	}
	if ( method->isAbstract() || method->isExtensionMethod() || method->isNotImplemented() ) {
		// abstract, extension or not implemented methods have no implementation, so there's nothing to parse...
		return;
	}

	try {
		TreeGenerator tg;

		method->setRootNode(
			tg.generateAST(method)
		);
	}
	catch ( Common::Exceptions::Exception& e ) {
		if ( !mCollectErrors ) {
			// rethrow error
			throw;
		}

		// increment error count
		mErrorCount++;

		// write error to log device
		OSerror(e.what());
	}
}

/*
 * walks through a complete namespace with all blueprints & methods
 */
void Generator::processNamespace(Common::Namespace* space)
{
	if ( !space ) {
		throw Common::Exceptions::Exception("invalid namespace symbol provided");
	}

	process(space);
}


}
}
