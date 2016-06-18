
// Header
#include "Repository.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/DoubleObject.h>
#include <Core/BuildInObjects/FloatObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/NumberObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/BuildInObjects/UserObject.h>
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Designtime/BuildInTypes/BoolObject.h>
#include <Core/Designtime/BuildInTypes/DoubleObject.h>
#include <Core/Designtime/BuildInTypes/FloatObject.h>
#include <Core/Designtime/BuildInTypes/GenericObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/NumberObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include "Preprocessor.h"
#include "Scope.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


Repository::Repository()
: mScope(new GlobalScope())
{
	addBlueprint(Designtime::BoolObject());
	addBlueprint(Designtime::DoubleObject());
	addBlueprint(Designtime::FloatObject());
	addBlueprint(Designtime::GenericObject());
	addBlueprint(Designtime::IntegerObject());
	addBlueprint(Designtime::NumberObject());
	addBlueprint(Designtime::StringObject());
	addBlueprint(Designtime::VoidObject());
}

Repository::~Repository()
{
	// Cleanup blue prints
	// {
	for ( Designtime::BluePrintMap::iterator it = mBluePrints.begin(); it != mBluePrints.end(); ++it ) {
		it->second.cleanup();
	}
	mBluePrints.clear();
	// }

	// Cleanup instances
	// {
	for ( ReferenceCountedObjects::iterator it = mInstances.begin(); it != mInstances.end(); ++it ) {
		it->first->Destructor();
	}

	for ( ReferenceCountedObjects::iterator it = mInstances.begin(); it != mInstances.end(); ++it ) {
		delete it->first;
	}
	mInstances.clear();
	// }

	// Cleanup prototypes
	// {
	mPrototypes.clear();
	// }

	delete mScope;
}

/*
 * adds a new blue print to our repository
 */
void Repository::addBlueprint(const Designtime::BluePrint& blueprint)
{
	Designtime::BluePrintMap::iterator it = mBluePrints.find(blueprint.Typename());
	if ( it != mBluePrints.end() ) {
		throw Utils::Exceptions::Exception("duplicate object '" + blueprint.Typename() + "' added to repository");
	}

	mBluePrints.insert(std::make_pair(blueprint.Typename(), blueprint));
}

/*
 * DEPRECATED: adds a new prototype (= generic) to our repository
 */
void Repository::addPrototype(const Designtime::Prototype& prototype)
{
	std::string type = prototype.type();

	Designtime::PrototypeMap::iterator it = mPrototypes.find(type);
	if ( it != mPrototypes.end() ) {
		throw Utils::Exceptions::Exception("duplicate object '" + type + "' added to repository");
	}

	mPrototypes.insert(std::make_pair(type, prototype));
}

/*
 * updates (increases) an object's reference count
 */
void Repository::addReference(Runtime::Object *object)
{
	if ( !object ) {
		return;
	}

	ReferenceCountedObjects::iterator it = mInstances.find(object);
	if ( it != mInstances.end() ) {
		// increment reference count
		it->second++;
		return;
	}

	mInstances.insert(std::make_pair(object, 1));
}

void Repository::CollectGarbage()
{
	bool success = true;

	while ( success ) {
		success = false;

		for ( ReferenceCountedObjects::iterator it = mInstances.begin(); it != mInstances.end(); ) {
			if ( it->second > 0 ) {
				++it;
				continue;
			}

			// as soon as we've lost all references, we can destroy our object
			if ( it->first && it->second <= 0 ) {
				// call object's destructor ...
				it->first->Destructor();
				// ... and delete it
/*
				delete it->first;

				it = mInstances.erase(it);
*/
				success = true;
			}
		}
	}
}

/*
 * this does not work because extension methods can not get copied :-(
 */
void Repository::createDefaultMethods(Runtime::Object *object)
{
	assert(object);
	{
		class ToString : public Runtime::Method {
		public:
			ToString()
			: Runtime::Method(0, "ToString", Designtime::StringObject::TYPENAME)
			{
				ParameterList params;

				setSignature(params);
			}

			Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token)
			{
				try {
					ParameterList::const_iterator it = params.begin();
					(void) it;

					*result = Runtime::StringObject(std::string("blablabla"));
				}
				catch (std::exception &e) {
					Runtime::Object *data = mRepository->createInstance(Runtime::StringObject::TYPENAME,
																		ANONYMOUS_OBJECT);
					*data = Runtime::StringObject(std::string(e.what()));

					mExceptionData = Runtime::ExceptionData(data, token.position());
					return Runtime::ControlFlow::Throw;
				}

				return Runtime::ControlFlow::Normal;
			}
		};

		ToString *toString = new ToString();
		toString->setRepository(this);

		object->defineMethod(toString->getName(), toString);
	}
}

/*
 * single point of contact for outsiders to create and instantiate new objects (no matter if atomic or not)
 */
Runtime::Object* Repository::createInstance(const std::string& type, const std::string& name, const std::string& prototype)
{
	// non-reference-based instantiation
	OSdebug("createInstance('" + type + "', '" + name + "', '" + prototype + "')");

	Designtime::BluePrint blueprint;

/*	Not part of this release
	Prototypes::iterator it = mPrototypes.find(prototype);
	if ( it != mPrototypes.end() ) {
		blueprint = it->second.generateBluePrint(type);
	}
	else {
*/
		Designtime::BluePrintMap::iterator it = mBluePrints.find(type);
		if ( it != mBluePrints.end() ) {
			blueprint = it->second;
		}
		else {
			throw Utils::Exceptions::Exception("could not create instance of unknown type '" + type + "'");
		}
/*	Not part of this release
	}
*/

	Runtime::Object *object = createObject(name, &blueprint);

	addReference(object);

	return object;
}

/*
 * creates (and initializes) atomic types and triggers the user defined object creation process
 */
Runtime::Object* Repository::createObject(const std::string& name, Designtime::BluePrint* blueprint)
{
	Runtime::Object *object = 0;

	// instantiate atomic types
	if ( blueprint->Typename() == Runtime::BoolObject::TYPENAME ) {
		object = new Runtime::BoolObject(name, Runtime::BoolObject::DEFAULTVALUE);
	}
	else if ( blueprint->Typename() == Runtime::DoubleObject::TYPENAME ) {
		object = new Runtime::DoubleObject(name, Runtime::DoubleObject::DEFAULTVALUE);
	}
	else if ( blueprint->Typename() == Runtime::FloatObject::TYPENAME ) {
		object = new Runtime::FloatObject(name, Runtime::FloatObject::DEFAULTVALUE);
	}
	else if ( blueprint->Typename() == Runtime::IntegerObject::TYPENAME ) {
		object = new Runtime::IntegerObject(name, Runtime::IntegerObject::DEFAULTVALUE);
	}
	else if ( blueprint->Typename() == Runtime::NumberObject::TYPENAME ) {
		object = new Runtime::NumberObject(name, Runtime::NumberObject::DEFAULTVALUE);
	}
	else if ( blueprint->Typename() == Runtime::StringObject::TYPENAME ) {
		object = new Runtime::StringObject(name, Runtime::StringObject::DEFAULTVALUE);
	}
	else if ( blueprint->Typename() == Runtime::VoidObject::TYPENAME ) {
		object = new Runtime::VoidObject(name);
	}
	// instantiate user defined types
	else {
		object = createUserObject(name, blueprint);
	}

	// TODO: this is no real check, one would have to check every method in an object to verify an objects abstractness
	if ( object->isAbstract() ) {
		throw Utils::Exceptions::AbstractException("cannot instantiate abstract object '" + blueprint->Typename() + "'");
	}

	object->setConst(blueprint->isConst());
	object->setFinal(blueprint->isFinal());
	object->setLanguageFeatureState(blueprint->getLanguageFeatureState());
	object->setMember(blueprint->isMember());
	object->setMutability(blueprint->getMutability());
	object->setParent(mScope);
	object->setRepository(this);
	object->setVisibility(blueprint->getVisibility());

	return object;
}

/*
 * creates and initializes a user defined object type and initializes its base classes
 */
Runtime::Object* Repository::createUserObject(const std::string& name, Designtime::BluePrint* blueprint)
{
	assert(blueprint);

	// create the base object
	Runtime::Object *object = new Runtime::UserObject(name, blueprint->Filename(), blueprint->Typename(), 0);

	Designtime::Ancestors ancestors = blueprint->getInheritance();

	if ( !ancestors.empty() ) {
		// walk through the inheritance and create (and initialize) all base objects
		for ( Designtime::Ancestors::const_iterator ancestorIt = ancestors.begin(); ancestorIt != ancestors.end(); ++ancestorIt ) {
			Designtime::BluePrintMap::iterator blueIt = mBluePrints.find(ancestorIt->name());

			if ( blueIt == mBluePrints.end() ) {
				throw Utils::Exceptions::Exception("trying to initialize unknown object '" + ancestorIt->name() + "'");
			}

			// create base object
			Runtime::Object *ancestor = createObject(name, &blueIt->second);

			// undefine previous base (while using single inheritance none should exist yet)
			object->undefine(IDENTIFIER_BASE, object->resolve(IDENTIFIER_BASE, false));
			// define new base
			object->define(IDENTIFIER_BASE, ancestor);

			// update our reference counter
			addReference(ancestor);

			// add our newly created ancestor to our inheritance
			object->addInheritance((*ancestorIt), ancestor);
		}
	}

	// initialize the base object
	initializeObject(object, blueprint);

	return object;
}

GlobalScope* Repository::getGlobalScope() const
{
	return mScope;
}

/*
 * creates and defines all members and methods of an object
 */
void Repository::initializeObject(Runtime::Object *object, Designtime::BluePrint* blueprint)
{
	// create and define all symbols based on given blueprint
	Symbols symbols = blueprint->provideSymbols();
	for ( Symbols::const_iterator it = symbols.begin(); it != symbols.end(); ++it ) {
		if ( it->second->getType() != Symbol::IType::BluePrintSymbol ) {
			continue;
		}

		Designtime::BluePrint *blue = static_cast<Designtime::BluePrint*>(it->second);

		Runtime::Object *symbol = createInstance(blue->Typename(), blue->getName(), "");
		symbol->setConst(blue->isConst());
		symbol->setFinal(blue->isFinal());
		symbol->setLanguageFeatureState(blue->getLanguageFeatureState());
		symbol->setMember(blue->isMember());
		symbol->setMutability(blue->getMutability());
		symbol->setParent(object);
		symbol->setRepository(this);
		symbol->setVisibility(blue->getVisibility());

		object->define(symbol->getName(), symbol);
	}

	// create and define all methods based on given blueprint
	MethodScope::MethodCollection methods = blueprint->provideMethods();
	for ( MethodScope::MethodCollection::const_iterator it = methods.begin(); it != methods.end(); ++it ) {
		Runtime::Method* method = new Runtime::Method(object, (*it)->getName(), (*it)->Typename());
		*method = *(*it);

		object->defineMethod((*it)->getName(), method);
	}

	object->define(IDENTIFIER_THIS, object);	// define this-symbol
}

bool Repository::isAlreadyKnown(const std::string& name) const
{
	return mBluePrints.find(name) != mBluePrints.end();
}

/*
 * loop over all tokens of a blueprint object and retype all identifier tokens with object names as values with type
 */
void Repository::rebuildBluePrints()
{
	for ( Designtime::BluePrintMap::iterator blueIt = mBluePrints.begin(); blueIt != mBluePrints.end(); ++blueIt ) {
		TokenList tokens = blueIt->second.getTokens();

		if ( tokens.empty() ) {
			continue;
		}

		// loop over all tokens of a blueprint object and retype all identifier tokens with object names as values with type
		// {
		bool replaced = false;

		for ( TokenList::iterator tokenIt = tokens.begin(); tokenIt != tokens.end(); ++tokenIt ) {
			// we found an identifier token
			if ( tokenIt->type() == Token::Type::IDENTIFER ) {
				// check if its content is one of our added blueprint objects
				if ( mBluePrints.find(tokenIt->content()) != mBluePrints.end() ) {
					tokenIt->resetTypeTo(Token::Type::TYPE);

					replaced = true;
				}
			}
		}

		if ( replaced ) {
			blueIt->second.setTokens(tokens);
		}
		// }

		Preprocessor preprocessor(this);
		preprocessor.process(&blueIt->second);
	}
}

/*
 * updates (decreases) an object's reference count
 */
void Repository::removeReference(Runtime::Object *object)
{
	if ( !object ) {
		return;
	}

	ReferenceCountedObjects::iterator it = mInstances.find(object);
	if ( it == mInstances.end() ) {
		return;
		//throw Utils::Exceptions::AccessViolation("possible double delete for '" + object->getFullName() + "'");
	}

	// decrement reference count
	it->second--;

	// as soon as we removed all references, we can destroy our object
	if ( it->first && it->second <= 0 ) {
		// call object's destructor ...
		it->first->Destructor();
		// ... and delete it
		//delete it->first;

		//mInstances.erase(it);
	}
}


}
