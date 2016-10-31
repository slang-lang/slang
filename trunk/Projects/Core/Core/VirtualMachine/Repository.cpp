
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
#include <Core/Common/Exceptions.h>
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
#include <Core/Designtime/BuildInTypes/UserObject.h>
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Designtime/Prototype.h>
#include <Core/Preprocessor.h>
#include <Core/Tools.h>
#include <Utils.h>
#include "Controller.h"

// Namespace declarations


namespace ObjectiveScript {


Repository::Repository()
{
}

Repository::~Repository()
{
}

/*
 * add a new blue print enum to the repository
 */
void Repository::addBluePrint(Designtime::BluePrintEnum* blueprint)
{
	BluePrintEnumMap::iterator it = mBluePrintEnums.find(blueprint->QualifiedTypename());
	if ( it != mBluePrintEnums.end() ) {
		if ( blueprint->getImplementationType() == ImplementationType::ForwardDeclaration ) {
			// adding additional forward declarations doesn't matter
			mForwardDeclarations.insert(blueprint);
			return;
		}

		if ( it->second->getImplementationType() != ImplementationType::ForwardDeclaration ) {
			throw Common::Exceptions::Exception("duplicate object '" + blueprint->QualifiedTypename() + "' added to repository");
		}

		// clean up forward declaration
		// {
		BluePrintSymbol* symbol = it->second;

		mBluePrintEnums.erase(it);

		delete symbol;
		// }
	}

	mBluePrintEnums.insert(std::make_pair(blueprint->QualifiedTypename(), blueprint));
}

/*
 * adds a new blue print object to the repository
 */
void Repository::addBluePrint(Designtime::BluePrintObject* blueprint)
{
	BluePrintObjectMap::iterator it = mBluePrintObjects.find(blueprint->QualifiedTypename());
	if ( it != mBluePrintObjects.end() ) {
		if ( blueprint->getImplementationType() == ImplementationType::ForwardDeclaration ) {
			// adding additional forward declarations doesn't matter
			mForwardDeclarations.insert(blueprint);
			return;
		}

		if ( it->second->getImplementationType() != ImplementationType::ForwardDeclaration ) {
			throw Common::Exceptions::Exception("duplicate object '" + blueprint->QualifiedTypename() + "' added to repository");
		}

		// clean up forward declaration
		// {
		BluePrintSymbol* symbol = it->second;

		mBluePrintObjects.erase(it);

		delete symbol;
		// }
	}

	mBluePrintObjects.insert(std::make_pair(blueprint->QualifiedTypename(), blueprint));
}

void Repository::cleanupForwardDeclarations()
{
	ForwardDeclarationTomb tmp = mForwardDeclarations;
	for ( ForwardDeclarationTomb::iterator it = tmp.begin(); it != tmp.end(); ++it ) {
		delete (*it);
	}
	mForwardDeclarations.clear();
}

/*
 * single point of contact for outsiders to create and instantiate new objects (no matter if atomic or not)
 */
Runtime::Object* Repository::createInstance(const std::string& type, const std::string& name, bool initialize)
{
	OSdebug("createInstance('" + type + "', '" + name + "', " + (initialize ? "true" : "false") + ")");

	BluePrintObjectMap::iterator it = mBluePrintObjects.find(type);
	if ( it == mBluePrintObjects.end() ) {
		throw Common::Exceptions::Exception("could not create instance of unknown type '" + type + "'");
	}

	Runtime::Object *object = createObject(name, it->second, initialize);

	if ( initialize ) {
		Controller::Instance().memory()->newObject(object);
	}

	return object;
}

/*
 * Creates an instance of the given blueprint WITHOUT adding it to the heap memory
 */
Runtime::Object* Repository::createInstance(Designtime::BluePrintObject* blueprint, const std::string& name, bool initialize)
{
	if ( !blueprint ) {
		throw Common::Exceptions::Exception("invalid blueprint provided!");
	}

	OSdebug("createInstance('" + blueprint->QualifiedTypename() + "', '" + name + "', " + (initialize ? "true" : "false") + ")");

	Runtime::Object* object = createObject(name, blueprint, initialize);

	if ( initialize ) {
		if ( object->isAbstract() ) {
			throw Common::Exceptions::AbstractException("cannot instantiate abstract object '" + blueprint->QualifiedTypename() + "'");
		}
	}

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

	IScope* parent = blueprint->getEnclosingScope();
	if ( !parent ) {
		parent = Controller::Instance().stack()->globalScope();
	}

	object->setFinal(blueprint->isFinal());
	object->setLanguageFeatureState(blueprint->getLanguageFeatureState());
	object->setMember(blueprint->isMember());
	object->setMutability(blueprint->getMutability());
	object->setOutterface(blueprint->Typename());
	object->setParent(parent);
	object->setQualifiedOutterface(blueprint->QualifiedTypename());
	object->setQualifiedTypename(blueprint->QualifiedTypename());
	object->setVisibility(blueprint->getVisibility());

	return object;
}

/*
 * Creates an instance of the given blueprint and adds a reference to it in the heap memory
 */
Runtime::Object* Repository::createReference(Designtime::BluePrintObject* blueprint, const std::string& name, bool initialize)
{
	if ( !blueprint ) {
		throw Common::Exceptions::Exception("invalid blueprint provided!");
	}

	OSdebug("createInstance('" + blueprint->QualifiedTypename() + "', '" + name + "', " + (initialize ? "true" : "false") + ")");

	Runtime::Object* object = createObject(name, blueprint, initialize);

	if ( initialize ) {
		if ( object->isAbstract() ) {
			throw Common::Exceptions::AbstractException("cannot instantiate abstract object '" + blueprint->QualifiedTypename() + "'");
		}

		Controller::Instance().memory()->newObject(object);
	}

	return object;
}

/*
 * creates and initializes a user defined object type and initializes its base classes
 */
Runtime::Object* Repository::createUserObject(const std::string& name, Designtime::BluePrintObject* blueprint, bool initialize)
{
	assert(blueprint);

	if ( blueprint->getImplementationType() == ImplementationType::ForwardDeclaration ) {
		throw Common::Exceptions::NotImplemented("cannot create instance of forward declared type '" + blueprint->QualifiedTypename() + "'");
	}

	// create the base object
	Runtime::Object *object = new Runtime::UserObject(name, blueprint->Filename(), blueprint->Typename());

	if ( initialize ) {
		Designtime::Ancestors ancestors = blueprint->getInheritance();

		if ( !ancestors.empty() ) {
			// walk through the inheritance and create (and initialize) all base objects
			for ( Designtime::Ancestors::const_iterator ancestorIt = ancestors.begin(); ancestorIt != ancestors.end(); ++ancestorIt ) {
				BluePrintObjectMap::iterator blueIt = mBluePrintObjects.find(ancestorIt->name());

				if ( blueIt == mBluePrintObjects.end() ) {
					throw Common::Exceptions::Exception("trying to initialize unknown object '" + ancestorIt->name() + "'");
				}

				switch ( ancestorIt->type() ) {
					case Designtime::Ancestor::Type::Extends:
					case Designtime::Ancestor::Type::Replicates: {
						// undefine previous base (while using single inheritance none should exist yet)
						object->undefine(IDENTIFIER_BASE, object->resolve(IDENTIFIER_BASE, true));

						// create base object
						Runtime::Object *ancestor = createReference(blueIt->second, name, initialize);
						ancestor->setParent(blueprint->getEnclosingScope());
						ancestor->undefine(IDENTIFIER_THIS, 0);
						ancestor->define(IDENTIFIER_THIS, object);

						// define new base
						object->define(IDENTIFIER_BASE, ancestor);

						// add our newly created ancestor to our inheritance
						object->addInheritance((*ancestorIt), ancestor);
					} break;
					case Designtime::Ancestor::Type::Implements: {
						// create base object
						Runtime::Object *ancestor = createUserObject(name, blueIt->second, initialize);

						// add our newly created ancestor to our inheritance
						object->addInheritance((*ancestorIt), ancestor);
					} break;
					case Designtime::Ancestor::Type::Unknown:
						throw Common::Exceptions::Exception("invalid inheritance detected");
				}
			}
		}

		// initialize the base object
		initializeObject(object, blueprint);
	}

	return object;
}

void Repository::deinit()
{
	// Cleanup prototypes
	// {
	//mPrototypes.clear();
	// }

	// Cleanup blue prints
	// {
	mBluePrintEnums.clear();
	// }

	// Cleanup blue prints
	// {
	mBluePrintObjects.clear();
	// }
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

void Repository::init()
{
	initialize();
}

void Repository::initialize()
{
	SymbolScope* scope = Controller::Instance().stack()->globalScope();

	// add atomic types
	{	// "bool" type
		Designtime::BoolObject* obj = new Designtime::BoolObject();
		addBluePrint(obj);

		scope->define(Designtime::BoolObject::TYPENAME, obj);
	}
	{	// "double" type
		Designtime::DoubleObject* obj = new Designtime::DoubleObject();
		addBluePrint(obj);

		scope->define(Designtime::DoubleObject::TYPENAME, obj);
	}
	{	// "float" type
		Designtime::FloatObject* obj = new Designtime::FloatObject();
		addBluePrint(obj);

		scope->define(Designtime::FloatObject::TYPENAME, obj);
	}
	{	// "Object" type
		Designtime::GenericObject* obj = new Designtime::GenericObject();
		addBluePrint(obj);

		scope->define(Designtime::GenericObject::TYPENAME, obj);
	}
	{	// "int" type
		Designtime::IntegerObject* obj = new Designtime::IntegerObject();
		addBluePrint(obj);

		scope->define(Designtime::IntegerObject::TYPENAME, obj);
	}
	{	// "number" type
		Designtime::NumberObject* obj = new Designtime::NumberObject();
		addBluePrint(obj);

		scope->define(Designtime::NumberObject::TYPENAME, obj);
	}
	{	// "string" type
		Designtime::StringObject* obj = new Designtime::StringObject();
		addBluePrint(obj);

		scope->define(Designtime::StringObject::TYPENAME, obj);
	}
	{	// "void" type
		Designtime::VoidObject* obj = new Designtime::VoidObject();
		addBluePrint(obj);

		scope->define(Designtime::VoidObject::TYPENAME, obj);
	}

	// add predefined runtime objects
	{	// null
		Runtime::Object* nullObject = new Runtime::Object(VALUE_NULL, SYSTEM_LIBRARY, NULL_TYPE, 0);
		nullObject->setConst(true);
		nullObject->setConstructed(false);
		nullObject->setFinal(false);
		nullObject->setMutability(Mutability::Const);
		nullObject->setVisibility(Visibility::Public);
		nullObject->setSealed(true);

		scope->define(VALUE_NULL, nullObject);
	}
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
			delete old;
		}

		object->defineMethod((*it)->getName(), method);
	}

	object->define(IDENTIFIER_THIS, object);	// define this-symbol
}


}
