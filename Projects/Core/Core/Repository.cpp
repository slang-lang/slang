
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
#include <Core/Designtime/BluePrintEnum.h>
#include <Core/Designtime/BluePrintGeneric.h>
#include <Core/Designtime/BluePrintObject.h>
#include <Core/Designtime/BuildInTypes/BoolObject.h>
#include <Core/Designtime/BuildInTypes/DoubleObject.h>
#include <Core/Designtime/BuildInTypes/FloatObject.h>
#include <Core/Designtime/BuildInTypes/GenericObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/NumberObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Designtime/Prototype.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include "Preprocessor.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


Repository::Repository()
: mScope(new GlobalScope())
{
	addBluePrint(new Designtime::BoolObject());
	addBluePrint(new Designtime::DoubleObject());
	addBluePrint(new Designtime::FloatObject());
	addBluePrint(new Designtime::GenericObject());
	addBluePrint(new Designtime::IntegerObject());
	addBluePrint(new Designtime::NumberObject());
	addBluePrint(new Designtime::StringObject());
	addBluePrint(new Designtime::VoidObject());
}

Repository::~Repository()
{
	// Cleanup instances
	// {
	for ( ReferenceCountedObjects::iterator it = mInstances.begin(); it != mInstances.end(); ++it ) {
		it->first->Destructor();
	}

	for ( ReferenceCountedObjects::iterator it = mInstances.begin(); it != mInstances.end(); ++it ) {
		// prevent double deletes
		mScope->undefine(it->first->getName(), it->first);

		delete it->first;
	}
	mInstances.clear();
	// }

	delete mScope;

	// Cleanup prototypes
	// {
	//mPrototypes.clear();
	// }

	// Cleanup blue prints
	// {
	for ( BluePrintEnumMap::iterator it = mBluePrintEnums.begin(); it != mBluePrintEnums.end(); ++it ) {
		it->second->cleanup();

		delete it->second;
	}
	mBluePrintEnums.clear();
	// }

	// Cleanup blue prints
	// {
	for ( BluePrintObjectMap::iterator it = mBluePrintObjects.begin(); it != mBluePrintObjects.end(); ++it ) {
		it->second->cleanup();

		delete it->second;
	}
	mBluePrintObjects.clear();
	// }
}

/*
 * add a new blue print to our repository
 */
void Repository::addBluePrint(Designtime::BluePrintEnum* blueprint)
{
	std::string type = blueprint->QualifiedTypename();

	BluePrintEnumMap::iterator it = mBluePrintEnums.find(type);
	if ( it != mBluePrintEnums.end() ) {
		throw Utils::Exceptions::Exception("duplicate object '" + type + "' added to repository");
	}

	mBluePrintEnums.insert(std::make_pair(type, blueprint));
}

/*
 * adds a new blue print to our repository
 */
void Repository::addBluePrint(Designtime::BluePrintObject* blueprint)
{
	std::string type = blueprint->QualifiedTypename();

	BluePrintObjectMap::iterator it = mBluePrintObjects.find(type);
	if ( it != mBluePrintObjects.end() ) {
		throw Utils::Exceptions::Exception("duplicate object '" + type + "' added to repository");
	}

	mBluePrintObjects.insert(std::make_pair(type, blueprint));
}

/*
 * DEPRECATED: adds a new prototype (= generic) to our repository
 */
void Repository::addPrototype(Designtime::Prototype* /*prototype*/)
{
assert(!"prototypes not supported!");
/*
	std::string type = prototype.type();

	Designtime::PrototypeMap::iterator it = mPrototypes.find(type);
	if ( it != mPrototypes.end() ) {
		throw Utils::Exceptions::Exception("duplicate object '" + type + "' added to repository");
	}

	mPrototypes.insert(std::make_pair(type, prototype));
*/
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
					Runtime::Object *data = mRepository->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
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
Runtime::Object* Repository::createInstance(const std::string& type, const std::string& name, bool initialize)
{
	// non-reference-based instantiation
	OSdebug("createInstance('" + type + "', '" + name + "', " + (initialize ? "true" : "false") + ")");

	BluePrintObjectMap::iterator it = mBluePrintObjects.find(type);
	if ( it == mBluePrintObjects.end() ) {
		throw Utils::Exceptions::Exception("could not create instance of unknown type '" + type + "'");
	}

	Runtime::Object *object = createObject(name, it->second, initialize);

	addReference(object);

	return object;
}

Runtime::Object* Repository::createInstance(Designtime::BluePrintObject* blueprint, const std::string& name, bool initialize)
{
	// non-reference-based instantiation

	if ( !blueprint ) {
		throw Utils::Exceptions::Exception("invalid blueprint provided!");
	}

	OSdebug("createInstance('" + blueprint->QualifiedTypename() + "', '" + name + "', " + (initialize ? "true" : "false") + ")");

	Runtime::Object* object = createObject(name, blueprint, initialize);

	addReference(object);

	return object;
}

/*
 * creates (and initializes) atomic types and triggers the user defined object creation process
 */
Runtime::Object* Repository::createObject(const std::string& name, Designtime::BluePrintObject* blueprint, bool initialize)
{
	Runtime::Object *object = 0;

	// instantiate atomic types
	if ( blueprint->Typename() == Runtime::BoolObject::TYPENAME ) {
		object = new Runtime::BoolObject(name, Runtime::BoolObject::DEFAULTVALUE.toBool());
	}
	else if ( blueprint->Typename() == Runtime::DoubleObject::TYPENAME ) {
		object = new Runtime::DoubleObject(name, Runtime::DoubleObject::DEFAULTVALUE.toDouble());
	}
	else if ( blueprint->Typename() == Runtime::FloatObject::TYPENAME ) {
		object = new Runtime::FloatObject(name, Runtime::FloatObject::DEFAULTVALUE.toFloat());
	}
	else if ( blueprint->Typename() == Runtime::IntegerObject::TYPENAME ) {
		object = new Runtime::IntegerObject(name, Runtime::IntegerObject::DEFAULTVALUE.toInt());
	}
	else if ( blueprint->Typename() == Runtime::NumberObject::TYPENAME ) {
		object = new Runtime::NumberObject(name, Runtime::NumberObject::DEFAULTVALUE);
	}
	else if ( blueprint->Typename() == Runtime::StringObject::TYPENAME ) {
		object = new Runtime::StringObject(name, Runtime::StringObject::DEFAULTVALUE.toStdString());
	}
	else if ( blueprint->Typename() == Runtime::VoidObject::TYPENAME ) {
		object = new Runtime::VoidObject(name);
	}
	// instantiate user defined types
	else {
		object = createUserObject(name, blueprint, initialize);
	}

	if ( object->isAbstract() ) {
		throw Utils::Exceptions::AbstractException("cannot instantiate abstract object '" + blueprint->Typename() + "'");
	}

	object->setFinal(blueprint->isFinal());
	object->setLanguageFeatureState(blueprint->getLanguageFeatureState());
	object->setMember(blueprint->isMember());
	object->setMutability(blueprint->getMutability());
	object->setParent(blueprint->getEnclosingScope());
	object->setQualifiedTypename(blueprint->QualifiedTypename());
	object->setRepository(this);
	object->setVisibility(blueprint->getVisibility());

	return object;
}

/*
 * creates and initializes a user defined object type and initializes its base classes
 */
Runtime::Object* Repository::createUserObject(const std::string& name, Designtime::BluePrintObject* blueprint, bool initialize)
{
	assert(blueprint);

	// create the base object
	Runtime::Object *object = new Runtime::UserObject(name, blueprint->Filename(), blueprint->Typename());

	Designtime::Ancestors ancestors = blueprint->getInheritance();

	if ( !ancestors.empty() ) {
		// walk through the inheritance and create (and initialize) all base objects
		for ( Designtime::Ancestors::const_iterator ancestorIt = ancestors.begin(); ancestorIt != ancestors.end(); ++ancestorIt ) {
			BluePrintObjectMap::iterator blueIt = mBluePrintObjects.find(ancestorIt->name());

			if ( blueIt == mBluePrintObjects.end() ) {
				throw Utils::Exceptions::Exception("trying to initialize unknown object '" + ancestorIt->name() + "'");
			}

			switch ( ancestorIt->type() ) {
				case Designtime::Ancestor::Type::Extends:
				case Designtime::Ancestor::Type::Replicates: {
					// undefine previous base (while using single inheritance none should exist yet)
					object->undefine(IDENTIFIER_BASE, object->resolve(IDENTIFIER_BASE, true));

					// create base object
					Runtime::Object *ancestor = createInstance(blueIt->second, name, initialize);

					// define new base
					object->define(IDENTIFIER_BASE, ancestor);

					// add our newly created ancestor to our inheritance
					object->addInheritance((*ancestorIt), ancestor);
				} break;
				case Designtime::Ancestor::Type::Implements:
					// implement interface
					if ( initialize ) {
						initializeObject(object, blueIt->second);
					}
					break;
				case Designtime::Ancestor::Type::Unknown:
					throw Utils::Exceptions::Exception("invalid inheritance detected");
			}
		}
	}

	if ( initialize ) {
		// initialize the base object
		initializeObject(object, blueprint);
	}

	return object;
}

Designtime::BluePrintGeneric* Repository::findBluePrint(const std::string& type) const
{
	Designtime::BluePrintGeneric* blueprint = findBluePrintEnum(type);

	if ( !blueprint ) {
		blueprint = findBluePrintObject(type);
	}

	return blueprint;
}

Designtime::BluePrintEnum* Repository::findBluePrintEnum(const std::string& type) const
{
	BluePrintEnumMap::const_iterator it = mBluePrintEnums.find(type);

	if ( it != mBluePrintEnums.end() ) {
		return it->second;
	}

	return 0;
}

Designtime::BluePrintObject* Repository::findBluePrintObject(const std::string& type) const
{
	BluePrintObjectMap::const_iterator it = mBluePrintObjects.find(type);

	if ( it != mBluePrintObjects.end() ) {
		return it->second;
	}

	return 0;
}

GlobalScope* Repository::getGlobalScope() const
{
	return mScope;
}

/*
 * creates and defines all members and methods of an object
 */
void Repository::initializeObject(Runtime::Object *object, Designtime::BluePrintObject* blueprint)
{
	object->undefine(IDENTIFIER_THIS, object->resolve(IDENTIFIER_THIS, true));

	// create and define all symbols based on given blueprint
	Symbols symbols = blueprint->provideSymbols();
	for ( Symbols::const_iterator it = symbols.begin(); it != symbols.end(); ++it ) {
		if ( it->second->getSymbolType() != Symbol::IType::BluePrintObjectSymbol ) {
			continue;
		}

		Designtime::BluePrintObject *blue = static_cast<Designtime::BluePrintObject*>(it->second);

		Runtime::Object *symbol = createInstance(blue, blue->getName(), false);
		symbol->setFinal(blue->isFinal());
		symbol->setLanguageFeatureState(blue->getLanguageFeatureState());
		symbol->setMember(blue->isMember());
		symbol->setMutability(blue->getMutability());
		symbol->setParent(object);
		symbol->setQualifiedTypename(blue->QualifiedTypename());
		symbol->setRepository(this);
		symbol->setValue(blue->getValue());
		symbol->setVisibility(blue->getVisibility());

		object->define(symbol->getName(), symbol);
	}

	// create and define all methods based on given blueprint
	MethodScope::MethodCollection methods = blueprint->provideMethods();
	for ( MethodScope::MethodCollection::const_iterator it = methods.begin(); it != methods.end(); ++it ) {
		Runtime::Method* method = new Runtime::Method(object, (*it)->getName(), (*it)->Typename());
		*method = *(*it);

		// try to override abstract methods a.k.a. implement an interface method
		Runtime::Method* old = static_cast<Runtime::Method*>(object->resolveMethod((*it)->getName(), method->provideSignature(), true));
		if ( old && old->isAbstract() ) {
			object->undefineMethod(old);
		}

		object->defineMethod((*it)->getName(), method);
	}

	object->define(IDENTIFIER_THIS, object);	// define this-symbol
}

void Repository::insertBluePrintEnumsIntoScopes()
{
	for ( BluePrintEnumMap::iterator it = mBluePrintEnums.begin(); it != mBluePrintEnums.end(); ++it ) {
		SymbolScope* scope = mScope;

		std::string name = it->second->QualifiedTypename();
		std::string parent;
		std::string type;

		for ( ; ; ) {
			Tools::split(name, parent, type);

			if ( type.empty() ) {
				break;
			}

			scope = dynamic_cast<SymbolScope*>(scope->resolve(parent, true));

			name = type;
		}

		assert(scope);
		scope->define(parent, it->second);
	}
}

void Repository::insertBluePrintObjectsIntoScopes()
{
	for ( BluePrintObjectMap::iterator it = mBluePrintObjects.begin(); it != mBluePrintObjects.end(); ++it ) {
		SymbolScope* scope = mScope;

		std::string name = it->second->QualifiedTypename();
		std::string parent;
		std::string type;

		for ( ; ; ) {
			Tools::split(name, parent, type);

			if ( type.empty() ) {
				break;
			}

			scope = dynamic_cast<SymbolScope*>(scope->resolve(parent, true));

			name = type;
		}

		assert(scope);
		scope->define(parent, it->second);
	}
}

bool Repository::isAlreadyKnown(const std::string& name) const
{
	return mBluePrintObjects.find(name) != mBluePrintObjects.end();
}

/*
 * loop over all tokens of a blueprint object and retype all identifier tokens with object names as values with type
 */
void Repository::rebuildBluePrints()
{
	rebuildBluePrintEnums();
	rebuildBluePrintObjects();
}

void Repository::rebuildBluePrintEnums()
{
	for ( BluePrintEnumMap::iterator blueIt = mBluePrintEnums.begin(); blueIt != mBluePrintEnums.end(); ++blueIt ) {
		TokenList tokens = blueIt->second->getTokens();

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
				if ( mBluePrintEnums.find(tokenIt->content()) != mBluePrintEnums.end() ) {
					tokenIt->resetTypeTo(Token::Type::TYPE);

					replaced = true;
				}
/*
				else if ( blueIt->second->getEnclosingScope() ) {
					std::string scope = blueIt->second->getEnclosingScope()->getScopeName();

					if ( mBluePrintEnums.find(scope + "." + tokenIt->content()) != mBluePrintEnums.end()) {
						tokenIt->resetTypeTo(Token::Type::TYPE);

						replaced = true;
					}
				}
*/
			}
		}

		if ( replaced ) {
			blueIt->second->setTokens(tokens);
		}
		// }

		Preprocessor preprocessor(this);
		preprocessor.process(blueIt->second);
	}

	//insertBluePrintEnumsIntoScopes();
}

void Repository::rebuildBluePrintObjects()
{
	for ( BluePrintObjectMap::iterator blueIt = mBluePrintObjects.begin(); blueIt != mBluePrintObjects.end(); ++blueIt ) {
		TokenList tokens = blueIt->second->getTokens();

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
				if ( mBluePrintObjects.find(tokenIt->content()) != mBluePrintObjects.end() ) {
					tokenIt->resetTypeTo(Token::Type::TYPE);

					replaced = true;
				}
				else if ( blueIt->second->getEnclosingScope() ) {
					std::string scope = blueIt->second->getEnclosingScope()->getScopeName();

					if ( mBluePrintObjects.find(scope + "." + tokenIt->content()) != mBluePrintObjects.end()) {
						tokenIt->resetTypeTo(Token::Type::TYPE);

						replaced = true;
					}
				}
			}
		}

		if ( replaced ) {
			blueIt->second->setTokens(tokens);
		}
		// }

		Preprocessor preprocessor(this);
		preprocessor.process(blueIt->second);
	}

	insertBluePrintObjectsIntoScopes();
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
