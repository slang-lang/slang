
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
#include "TreeGenerator.h"

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


Generator::Generator()
: mRepository(0)
{
	mRepository = Controller::Instance().repository();
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

	if ( base->beginMethods() != base->endMethods() ) {
		Runtime::Object* thisObject = 0;

		// we have methods, no check if we're part of an object
		Designtime::BluePrintObject* symbol = dynamic_cast<Designtime::BluePrintObject*>(base);
		if ( symbol ) {
			// instantiate object once and pass it to our methods to prevent multiple this-object instantiations
			thisObject = mRepository->createInstance(symbol->QualifiedTypename(), IDENTIFIER_THIS, symbol->getPrototypeConstraints(), Repository::InitilizationType::Final);
		}

		for ( MethodScope::MethodCollection::const_iterator it = base->beginMethods(); it != base->endMethods(); ++it ) {
			processMethod(static_cast<Common::Method*>((*it)), thisObject);
		}

		delete thisObject;
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

void Generator::processMethod(Common::Method* method, Runtime::Object* thisObject)
{
	if ( !method ) {
		throw Common::Exceptions::Exception("invalid method symbol provided");
	}
	if ( method->isAbstract() || method->isExtensionMethod() ) {
		// abstract or extension methods have no implementation, so there's nothing to parse; adieu..
		return;
	}

	TreeGenerator tg;

	method->setRootNode(
		tg.generateAST(method, thisObject)
	);
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
