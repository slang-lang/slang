
// Header
#include "TreeOptimizer.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Common/Method.h>
#include <Core/Common/Namespace.h>
#include <Core/Designtime/BluePrintObject.h>
#include <Utils.h>
#include "TreeGenerator.h"

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


TreeOptimizer::TreeOptimizer()
{
}

TreeOptimizer::~TreeOptimizer()
{
}

/*
* walk through global namespace and process all methods of all symbols
*/
void TreeOptimizer::process(MethodScope* base)
{
	if ( !base ) {
		throw Common::Exceptions::Exception("invalid scope symbol provided");
	}

	for ( SymbolScope::Symbols::const_iterator it = base->beginSymbols(); it != base->endSymbols(); ++it ) {
		switch ( it->second->getSymbolType() ) {
			case Symbol::IType::MethodSymbol:
				throw Common::Exceptions::Exception("invalid symbol found: " + it->second->getName());
			case Symbol::IType::BluePrintObjectSymbol:
				processBluePrint(static_cast<Designtime::BluePrintObject*>(it->second));
				break;
			case Symbol::IType::NamespaceSymbol:
				processNamespace(static_cast<Common::Namespace*>(it->second));
				break;
			case Symbol::IType::BluePrintEnumSymbol:
				break;	// enums don't have an implementation
			case Symbol::IType::ObjectSymbol:
				break;	// ignore runtime symbols
		}
	}

	for ( MethodScope::MethodCollection::const_iterator it = base->beginMethods(); it != base->endMethods(); ++it ) {
		processMethod(static_cast<Common::Method*>((*it)));
	}
}

void TreeOptimizer::processBluePrint(Designtime::BluePrintObject* object)
{
	if ( !object ) {
		throw Common::Exceptions::Exception("invalid blueprint symbol provided");
	}
	if ( object->isInterface() ) {
		// interfaces have no implementation, so there's nothing to optimize; adieu..
		return;
	}
	if ( object->provideMethods().empty() && object->provideSymbols().empty() ) {
		// an object without methods and symbols... maybe a primitive?
		return;
	}
	if ( !object->getPrototypeConstraints().empty() ) {
		// skip prototypes; not optimizing prototypes will hurt us during prototype usage though
		return;
	}

	process(object);
}

void TreeOptimizer::processMethod(Common::Method* method)
{
	if ( !method ) {
		throw Common::Exceptions::Exception("invalid method symbol provided");
	}
	if ( method->isAbstract() || method->isExtensionMethod() ) {
		// abstract or extension methods have no implementation, so there's nothing to optimize; adieu..
		return;
	}

	// loop through all nodes of a method and decide if we keep or remove them

	Node* rootNode = method->getRootNode();
	if ( !rootNode ) {
		//OSinfo("method \"" + method->getFullScopeName() + "\" is empty");
		return;
	}


}

void TreeOptimizer::processNamespace(Common::Namespace* space)
{
	if ( !space ) {
		throw Common::Exceptions::Exception("invalid namespace symbol provided");
	}

	process(space);
}


}
}
