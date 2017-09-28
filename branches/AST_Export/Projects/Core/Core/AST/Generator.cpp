
// Header
#include "Generator.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Common/Method.h>
#include <Core/Common/Namespace.h>
#include <Core/Designtime/BluePrintObject.h>
#include "TreeGenerator.h"

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


Generator::Generator()
{
}

Generator::~Generator()
{
}

/*
 * walk through global namespace and process all methods of all symbols
 */
void Generator::process(MethodScope* base)
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

void Generator::processMethod(Common::Method* method)
{
	if ( !method ) {
		throw Common::Exceptions::Exception("invalid method symbol provided");
	}
	if ( method->isAbstract() || method->isExtensionMethod() ) {
		// abstract or extension methods have no implementation, so there's nothing to parse; adieu..
		return;
	}

	TreeGenerator tg;
	Statements* rootNode = tg.generateAST(method);

	method->setRootNode(rootNode);
}

void Generator::processNamespace(Common::Namespace* space)
{
	if ( !space ) {
		throw Common::Exceptions::Exception("invalid namespace symbol provided");
	}

	process(space);
}


}
}
