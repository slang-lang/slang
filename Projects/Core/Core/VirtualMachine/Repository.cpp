
// Header
#include "Repository.h"

// Library includes

// Project includes
#include <Core/AST/Generator.h>
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/DoubleObject.h>
#include <Core/BuildInObjects/FloatObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/BuildInObjects/UserObject.h>
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Common/Exceptions.h>
#include <Core/Common/Method.h>
#include <Core/Designtime/BluePrintEnum.h>
#include <Core/Designtime/BluePrintObject.h>
#include <Core/Designtime/BuildInTypes/BoolObject.h>
#include <Core/Designtime/BuildInTypes/DoubleObject.h>
#include <Core/Designtime/BuildInTypes/FloatObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Designtime/BuildInTypes/UserObject.h>
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Designtime/Parser/Parser.h>
#include <Core/Tools.h>
#include "Controller.h"

// Namespace declarations


namespace ObjectiveScript {


Repository::Repository()
: mTypeSystem(0)
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
	if ( blueprint->getImplementationType() == ImplementationType::ForwardDeclaration ) {
		// adding duplicate forward declarations doesn't matter
		mForwardDeclarations.insert(blueprint);
	}

	BluePrintEnumMap::iterator it = mBluePrintEnums.find(blueprint->QualifiedTypename());
	if ( it != mBluePrintEnums.end() ) {
		if ( blueprint->getImplementationType() == ImplementationType::ForwardDeclaration ) {
			// we already added this forward declaration to our forward declaration tomb
			return;
		}

		if ( it->second->getImplementationType() != ImplementationType::ForwardDeclaration ) {
			throw Common::Exceptions::Exception("duplicate enum '" + blueprint->QualifiedTypename() + "' added to repository");
		}

		// insert forward declaration into forward declaration tomb ...
		mForwardDeclarations.insert(it->second);

		// ... and remove it from our blueprints
		mBluePrintEnums.erase(it);
	}

	mBluePrintEnums.insert(std::make_pair(blueprint->QualifiedTypename(), blueprint));
}

/*
 * adds a new blue print object to the repository
 */
void Repository::addBluePrint(Designtime::BluePrintObject* blueprint)
{
	if ( blueprint->getImplementationType() == ImplementationType::ForwardDeclaration ) {
		// adding duplicate forward declarations doesn't matter
		mForwardDeclarations.insert(blueprint);
	}

	BluePrintObjectMap::iterator it = mBluePrintObjects.find(blueprint->QualifiedTypename());
	if ( it != mBluePrintObjects.end() ) {
		if ( blueprint->getImplementationType() == ImplementationType::ForwardDeclaration ) {
			// we already added this forward declaration to our forward declaration tomb
			return;
		}

		if ( it->second->getImplementationType() != ImplementationType::ForwardDeclaration ) {
			throw Common::Exceptions::Exception("duplicate object '" + blueprint->QualifiedTypename() + "' added to repository");
		}

		// insert forward declaration into forward declaration tomb ...
		mForwardDeclarations.insert(it->second);

		// ... and remove it from our blueprints
		mBluePrintObjects.erase(it);
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

Designtime::BluePrintObject* Repository::createBluePrintFromPrototype(Designtime::BluePrintObject* blueprint, PrototypeConstraints constraints)
{
	if ( !blueprint ) {
		throw Common::Exceptions::Exception("invalid blueprint provided!");
	}
	if ( blueprint->getPrototypeConstraints() != constraints ) {
		throw Common::Exceptions::TypeMismatch("'" + blueprint->QualifiedTypename() + "' prototype constraint mismatch");
	}

	// merge design time and run time constraints
	constraints = Designtime::mergeConstraints(blueprint->getPrototypeConstraints(), constraints);
	for ( PrototypeConstraints::const_iterator constIt = constraints.begin(); constIt != constraints.end(); ++constIt ) {
		if ( constIt->mConstraint.empty() ) {
			continue;
		}
		if ( constIt->mRunType == constIt->mConstraint ) {
			// same types are okay
			continue;
		}

		Designtime::BluePrintGeneric* generic = findBluePrint(constIt->mRunType);
		if ( !generic ) {
			throw Common::Exceptions::UnknownIdentifer(constIt->mRunType + " is unknown");
		}

		if ( !generic->inheritsFrom(constIt->mConstraint) ) {
			throw Common::Exceptions::TypeMismatch(constIt->mRunType + " does not inherit from " + constIt->mConstraint);
		}
	}

	Designtime::BluePrintObject* newBlue = blueprint->fromPrototype(constraints);

	// add new blueprint to repository
	addBluePrint(newBlue);
	// initialize newly created blueprint
	initBluePrintObject(newBlue);

	// add new blueprint to parent scope
	IScope* parent = blueprint->getEnclosingScope();
	if ( parent ) {
		parent->define(newBlue->QualifiedTypename(), newBlue);
	}

	AST::Generator generator;
	generator.process(newBlue);

	return newBlue;
}

/*
 * Creates an instance of the given blueprint
 */
Runtime::Object* Repository::createInstance(const std::string& type, const std::string& name, PrototypeConstraints constraints, InitilizationType::E initialize)
{
	// look up type in blueprint enums (because there are generally less blueprint enums defined than blueprint objects)
	BluePrintEnumMap::iterator enumIt = mBluePrintEnums.find(type);
	if ( enumIt != mBluePrintEnums.end() ) {
		return createInstance(enumIt->second, name, constraints, initialize);
	}

	// look up type in blueprint objects
	BluePrintObjectMap::iterator objectIt = mBluePrintObjects.find(type);
	if ( objectIt != mBluePrintObjects.end() ) {
		return createInstance(objectIt->second, name, constraints, initialize);
	}

	// workaround for complex member types whose imports have not yet been analysed
	if ( initialize == InitilizationType::None ) {
		return new Runtime::UserObject(name, SYSTEM_LIBRARY, Designtime::Parser::buildRuntimeConstraintTypename(type, constraints), true);
	}

	// no entry found for given type
	throw Common::Exceptions::Exception("cannot not create instance of unknown type '" + type + "'");
}

/*
 * Creates an instance of the given blueprint
 */
Runtime::Object* Repository::createInstance(Designtime::BluePrintGeneric* blueprint, const std::string& name, PrototypeConstraints constraints, InitilizationType::E initialize)
{
	if ( !blueprint ) {
		throw Common::Exceptions::Exception("invalid blueprint provided!");
	}

	if ( blueprint->getSymbolType() == Symbol::IType::BluePrintEnumSymbol ) {
		// replace enum blueprint with an integer blueprint
		blueprint = findBluePrint(Runtime::IntegerObject::TYPENAME);
	}

	if ( constraints != blueprint->getPrototypeConstraints() ) {
		if ( constraints.size() < blueprint->getPrototypeConstraints().size() ) {
			constraints = blueprint->getPrototypeConstraints().buildRawConstraints(constraints);
		}
		else {
			throw Common::Exceptions::TypeMismatch("'" + blueprint->QualifiedTypename() + "' prototype constraint mismatch");
		}
	}

	std::string constraintType = Designtime::Parser::buildRuntimeConstraintTypename(blueprint->QualifiedTypename(), constraints);

	if ( blueprint->QualifiedTypename() != constraintType ) {
		// we have to handle a prototyped blueprint
		BluePrintObjectMap::iterator it = mBluePrintObjects.find(constraintType);
		if ( it == mBluePrintObjects.end() ) {
			// a not yet used prototype has been requested => construct the new type
			blueprint = createBluePrintFromPrototype(static_cast<Designtime::BluePrintObject*>(blueprint), constraints);
		}
		else {
			blueprint = it->second;
		}
	}

	Runtime::Object* object = createObject(name, static_cast<Designtime::BluePrintObject*>(blueprint), initialize);

	if ( initialize == InitilizationType::Final ) {
		if ( object->isAbstract() ) {
			throw Common::Exceptions::AbstractException("cannot instantiate abstract object '" + constraintType + "'");
		}

		// TODO: verify me
		//Controller::Instance().memory()->newObject(object);
	}

	return object;
}

/*
 * creates (and initializes) atomic types and triggers the user defined object creation process
 */
Runtime::Object* Repository::createObject(const std::string& name, Designtime::BluePrintObject* blueprint, InitilizationType::E initialize)
{
	assert(blueprint);

	Runtime::Object *object = 0;

	// instantiate atomic types
	if ( blueprint->QualifiedTypename() == Runtime::BoolObject::TYPENAME ) {
		object = new Runtime::BoolObject(name, Runtime::BoolObject::DEFAULTVALUE);
	}
	else if ( blueprint->QualifiedTypename() == Runtime::DoubleObject::TYPENAME ) {
		object = new Runtime::DoubleObject(name, Runtime::DoubleObject::DEFAULTVALUE);
	}
	else if ( blueprint->QualifiedTypename() == Runtime::FloatObject::TYPENAME ) {
		object = new Runtime::FloatObject(name, Runtime::FloatObject::DEFAULTVALUE);
	}
	else if ( blueprint->QualifiedTypename() == Runtime::IntegerObject::TYPENAME ) {
		object = new Runtime::IntegerObject(name, Runtime::IntegerObject::DEFAULTVALUE);
	}
	else if ( blueprint->QualifiedTypename() == Runtime::StringObject::TYPENAME ) {
		object = new Runtime::StringObject(name, Runtime::StringObject::DEFAULTVALUE);
	}
	else if ( blueprint->QualifiedTypename() == Runtime::VoidObject::TYPENAME ) {
		object = new Runtime::VoidObject(name);
	}
	// instantiate user defined types
	else {
		object = createUserObject(name, blueprint, initialize);
	}

	IScope* parent = blueprint->getEnclosingScope();
	if ( !parent ) {
		// set global scope as fallback parent
		parent = Controller::Instance().stack()->globalScope();
	}

	object->setBluePrint(blueprint);
	object->setIsReference(blueprint->isReference());
	object->setLanguageFeatureState(blueprint->getLanguageFeatureState());
	object->setMember(blueprint->isMember());
	object->setMemoryLayout(blueprint->getMemoryLayout());
	object->setMutability(blueprint->getMutability());
	object->setParent(parent);
	object->setVisibility(blueprint->getVisibility());

	return object;
}

/*
 * Creates an instance of the given blueprint and adds a reference to it to the heap memory
 */
Runtime::Object* Repository::createReference(const std::string& type, const std::string& name, PrototypeConstraints constraints, InitilizationType::E initialize)
{
	// look up type in blueprint enums (because there are generally less blueprint enums defined than blueprint objects)
	BluePrintEnumMap::iterator enumIt = mBluePrintEnums.find(type);
	if ( enumIt != mBluePrintEnums.end() ) {
		return createReference(enumIt->second, name, constraints, initialize);
	}

	// look up type in blueprint objects
	BluePrintObjectMap::iterator objectIt = mBluePrintObjects.find(type);
	if ( objectIt != mBluePrintObjects.end() ) {
		return createReference(objectIt->second, name, constraints, initialize);
	}

	// no entry found for given type
	throw Common::Exceptions::Exception("cannot not create reference of unknown type '" + type + "'");
}

/*
 * Creates an instance of the given blueprint and adds a reference to it in the heap memory
 */
Runtime::Object* Repository::createReference(Designtime::BluePrintGeneric* blueprint, const std::string& name, PrototypeConstraints constraints, InitilizationType::E initialize)
{
	Runtime::Object* object = createInstance(blueprint, name, constraints, initialize);

	if ( initialize == InitilizationType::Final ) {
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
Runtime::Object* Repository::createUserObject(const std::string& name, Designtime::BluePrintObject* blueprint, InitilizationType::E initialize)
{
	assert(blueprint);

	if ( blueprint->getImplementationType() == ImplementationType::ForwardDeclaration ) {
		throw Common::Exceptions::NotImplemented("cannot create instance of forward declared type '" + blueprint->QualifiedTypename() + "'");
	}

	// create the base object
	Runtime::Object* object = new Runtime::UserObject(name, blueprint->Filename(),
													  Designtime::Parser::buildRuntimeConstraintTypename(blueprint->QualifiedTypename(),
																										 blueprint->getPrototypeConstraints()));

	if ( initialize >= InitilizationType::AllowAbstract ) {
		Designtime::Ancestors ancestors = blueprint->getInheritance();

		if ( !ancestors.empty() ) {
			// walk through the inheritance and create (and initialize) all base objects
			for ( Designtime::Ancestors::const_iterator ancestorIt = ancestors.begin(); ancestorIt != ancestors.end(); ++ancestorIt ) {
				BluePrintObjectMap::iterator blueIt = mBluePrintObjects.find(ancestorIt->name());

				if ( blueIt == mBluePrintObjects.end() ) {
					throw Common::Exceptions::Exception("trying to initialize unknown object '" + ancestorIt->name() + "'");
				}

				switch ( ancestorIt->ancestorType() ) {
					case Designtime::Ancestor::Type::Extends:
					case Designtime::Ancestor::Type::Replicates: {
						// undefine previous base (while using single inheritance none should exist yet)
						object->undefine(IDENTIFIER_BASE);

						// create base object
						Runtime::Object *ancestor = createReference(blueIt->second, IDENTIFIER_BASE, ancestorIt->constraints(), InitilizationType::AllowAbstract);
						ancestor->setParent(blueprint->getEnclosingScope());
						ancestor->undefine(IDENTIFIER_THIS);
						ancestor->define(IDENTIFIER_THIS, object);

						// define new base
						object->define(IDENTIFIER_BASE, ancestor);

						// add our newly created ancestor to our inheritance
						object->addInheritance((*ancestorIt), ancestor);
					} break;
					case Designtime::Ancestor::Type::Implements: {
						Runtime::Object *ancestor = createReference(blueIt->second, name, ancestorIt->constraints(), InitilizationType::None);
						ancestor->setParent(blueprint->getEnclosingScope());

						// TODO: fix memleak here
						// define ancestor to prevent memleaks
						//object->define(blueIt->second->QualifiedTypename(), ancestor);

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
	// clean up the unused forward declarations (TODO: find a better solution for this)
	cleanupForwardDeclarations();

	// cleanup blue prints
	mBluePrintEnums.clear();

	// cleanup blue prints
	mBluePrintObjects.clear();
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
	// Initialize virtual machine stuff
	mTypeSystem = Controller::Instance().typeSystem();

	IScope* scope = Controller::Instance().stack()->globalScope();

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
		Designtime::UserObject* obj = new Designtime::UserObject();
		obj->setIsReference(true);
		addBluePrint(obj);

		scope->define(Designtime::UserObject::TYPENAME, obj);
	}
	{	// "int" type
		Designtime::IntegerObject* obj = new Designtime::IntegerObject();
		addBluePrint(obj);

		scope->define(Designtime::IntegerObject::TYPENAME, obj);
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
		Runtime::UserObject* nullObject = new Runtime::UserObject(VALUE_NULL, SYSTEM_LIBRARY, _object, true);
		nullObject->setConst(true);
		nullObject->setConstructed(false);
		nullObject->setIsReference(true);
		nullObject->setMemoryLayout(MemoryLayout::Static);
		nullObject->setMutability(Mutability::Const);
		nullObject->setVisibility(Visibility::Public);
		nullObject->setSealed(true);

		scope->define(VALUE_NULL, nullObject);
	}
}

/*
 * this allows asyncronous initialization of blueprints so that the order of imports does not matter
 */
void Repository::initializeBlueprints()
{
	// initialize blueprint enums
	for ( BluePrintEnumMap::iterator it = mBluePrintEnums.begin(); it != mBluePrintEnums.end(); ++it ) {
		initTypeSystem(it->second);
	}

	// initialize blueprint objects
	for ( BluePrintObjectMap::iterator it = mBluePrintObjects.begin(); it != mBluePrintObjects.end(); ++it ) {
		initBluePrintObject(it->second);
	}
}

/*
 * creates and defines all members and methods of an object
 */
void Repository::initializeObject(Runtime::Object* destObj, Designtime::BluePrintObject* srcObj)
{
	// create and define all symbols based on given blueprint
	Symbols symbols = srcObj->provideSymbols();
	for ( Symbols::const_iterator it = symbols.begin(); it != symbols.end(); ++it ) {
		if ( it->second->getSymbolType() != Symbol::IType::BluePrintObjectSymbol ) {
			continue;
		}
		if ( it->first == IDENTIFIER_BASE || it->first == IDENTIFIER_THIS ) {
			// skip "base" && "this" symbols
			continue;
		}

		Designtime::BluePrintObject* blue = static_cast<Designtime::BluePrintObject*>(it->second);

		Runtime::Object *symbol = createInstance(blue->QualifiedTypename(), blue->getName(), blue->getPrototypeConstraints(), InitilizationType::None);
		symbol->setBluePrint(blue);
		symbol->setLanguageFeatureState(blue->getLanguageFeatureState());
		symbol->setMember(blue->isMember());
		symbol->setMutability(blue->getMutability());
		symbol->setParent(destObj);
		symbol->setValue(blue->getValue());
		symbol->setVisibility(blue->getVisibility());

		destObj->defineMember(symbol->getName(), symbol);
	}

	// create and define all methods based on given blueprint
	MethodScope::MethodCollection methods = srcObj->provideMethods();
	for ( MethodScope::MethodCollection::const_iterator it = methods.begin(); it != methods.end(); ++it ) {
		// create new method and ...
		Common::Method* method = new Common::Method(destObj, (*it)->getName(), (*it)->QualifiedTypename());
		// ... copy its data from our template method
		*method = *(*it);

		destObj->defineMethod((*it)->getName(), method);
	}

	destObj->define(IDENTIFIER_THIS, destObj);	// define this-symbol
}

/*
 * initializes a given blueprint object (i.e. triggers type system initialization)
 */
void Repository::initBluePrintObject(Designtime::BluePrintObject *blueprint)
{
	if ( blueprint->isAtomicType() ) {
		// atomic types should have been initialized at compile time
		return;
	}
	if ( blueprint->isPrototype() ) {
		// prototypes will get initialized during tree generation phase
		return;
	}

	// prepare inheritance
	Designtime::Ancestors ancestors = blueprint->getAncestors();
	for ( Designtime::Ancestors::const_iterator it = ancestors.begin(); it != ancestors.end(); ++it ) {
		Designtime::BluePrintGeneric* base = findBluePrint(it->name());
		if ( base ) {
			blueprint->define(IDENTIFIER_BASE, base);
		}
	}

	// prepare members
	Symbols symbols = blueprint->provideSymbols();
	for ( Symbols::const_iterator it = symbols.begin(); it != symbols.end(); ++it ) {
		if ( it->second->getSymbolType() != Symbol::IType::BluePrintObjectSymbol ) {
			continue;
		}
		if ( it->first == IDENTIFIER_BASE || it->first == IDENTIFIER_THIS ) {
			// skip "base" && "this" symbols
			continue;
		}

		Designtime::BluePrintObject* blue = static_cast<Designtime::BluePrintObject*>(it->second);
		if ( blue->isPrototype() ) {
			Common::TypeDeclaration typeDeclaration(blue->QualifiedTypename(), blue->getPrototypeConstraints());

			// prepare type
			prepareType(typeDeclaration);
			// set qualified typename to constraint type
			blue->setQualifiedTypename(Designtime::Parser::buildRuntimeConstraintTypename(typeDeclaration.mName, typeDeclaration.mConstraints));
			// reset constraints
			blue->setPrototypeConstraints(PrototypeConstraints());
		}
	}

/*
	// prepare methods
	MethodScope::MethodCollection methods = blueprint->provideMethods();
	for ( MethodScope::MethodCollection::const_iterator it = methods.begin(); it != methods.end(); ++it ) {
		Common::TypeDeclaration typeDeclaration((*it)->QualifiedTypename(), (*it)->getPrototypeConstraints());

		// prepare type
		prepareType(typeDeclaration);
		// set qualified typename to constraint type
		(*it)->setQualifiedTypename(Designtime::Parser::buildRuntimeConstraintTypename(typeDeclaration.mName, typeDeclaration.mConstraints));
		// reset constraints
		(*it)->setPrototypeConstraints(PrototypeConstraints());
	}
*/

	initTypeSystem(blueprint);
}

/*
 * initializes type system for given blueprint enum
 */
void Repository::initTypeSystem(Designtime::BluePrintEnum* blueprint)
{
	// add default assignment entry for int assignments
	mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::ASSIGN, _int, blueprint->QualifiedTypename());
	mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_EQUAL, _int, blueprint->QualifiedTypename());
	mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_GREATER, _int, blueprint->QualifiedTypename());
	mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_GREATER_EQUAL, _int, blueprint->QualifiedTypename());
	mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_LESS, _int, blueprint->QualifiedTypename());
	mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_LESS_EQUAL, _int, blueprint->QualifiedTypename());
	mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_UNEQUAL, _int, blueprint->QualifiedTypename());

	// add default assignment entry for type system if it doesn't exist yet
	if ( !mTypeSystem->exists(blueprint->QualifiedTypename(), Token(Token::Type::ASSIGN, "="), blueprint->QualifiedTypename()) ) {
		mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::ASSIGN, blueprint->QualifiedTypename(), blueprint->QualifiedTypename());
	}
	// add equality operator entries for type system if it doesn't exist yet
	if ( !mTypeSystem->exists(blueprint->QualifiedTypename(), Token(Token::Type::COMPARE_EQUAL, "=="), blueprint->QualifiedTypename()) ) {
		mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_EQUAL, blueprint->QualifiedTypename(), blueprint->QualifiedTypename());
		mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_UNEQUAL, blueprint->QualifiedTypename(), blueprint->QualifiedTypename());
	}
}

/*
 * initializes type system for given blueprint object
 */
void Repository::initTypeSystem(Designtime::BluePrintObject* blueprint)
{
	MethodScope::MethodCollection methods = blueprint->provideMethods();
	for ( MethodScope::MethodCollection::const_iterator it = methods.begin(); it != methods.end(); ++it ) {
		std::string name = (*it)->getName();
		ParameterList params = (*it)->provideSignature();

		if ( name == "operator=" && params.size() == 1 ) {
			mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::ASSIGN, params.front().type(), blueprint->QualifiedTypename());
		}
		else if ( name == "operator&" && params.size() == 1 ) {
			mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::BITAND, params.front().type(), blueprint->QualifiedTypename());
		}
		else if ( name == "operator|" && params.size() == 1 ) {
			mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::BITOR, params.front().type(), blueprint->QualifiedTypename());
		}
		else if ( name == "operator~" && params.size() == 1 ) {
			mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::BITCOMPLEMENT, params.front().type(), blueprint->QualifiedTypename());
		}
		else if ( name == "operator==" && params.size() == 1 ) {
			mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_EQUAL, params.front().type(), blueprint->QualifiedTypename());
			mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_UNEQUAL, params.front().type(), blueprint->QualifiedTypename());
		}
		else if ( name == "operator<" && params.size() == 1 ) {
			mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_LESS, params.front().type(), blueprint->QualifiedTypename());
		}
		else if ( name == "operator<=" && params.size() == 1 ) {
			mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_LESS_EQUAL, params.front().type(), blueprint->QualifiedTypename());
		}
		else if ( name == "operator>" && params.size() == 1 ) {
			mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_GREATER, params.front().type(), blueprint->QualifiedTypename());
		}
		else if ( name == "operator>=" && params.size() == 1 ) {
			mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_GREATER_EQUAL, params.front().type(), blueprint->QualifiedTypename());
		}
		else if ( name == "operator+" && params.size() == 1 ) {
			mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::MATH_ADDITION, params.front().type(), blueprint->QualifiedTypename());
		}
		else if ( name == "operator/" && params.size() == 1 ) {
			mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::MATH_DIVIDE, params.front().type(), blueprint->QualifiedTypename());
		}
		else if ( name == "operator%" && params.size() == 1 ) {
			mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::MATH_MODULO, params.front().type(), blueprint->QualifiedTypename());
		}
		else if ( name == "operator*" && params.size() == 1 ) {
			mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::MATH_MULTIPLY, params.front().type(), blueprint->QualifiedTypename());
		}
		else if ( name == "operator-" && params.size() == 1 ) {
			mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::MATH_SUBTRACT, params.front().type(), blueprint->QualifiedTypename());
		}
// TODO: verify me
/*
		else if ( name == "operator--" && params.size() == 1 ) {
			mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::OPERATOR_DECREMENT, params.front().type(), blueprint->QualifiedTypename());
		}
		else if ( name == "operator++" && params.size() == 1 ) {
			mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::OPERATOR_INCREMENT, params.front().type(), blueprint->QualifiedTypename());
		}
*/
		else if ( name == "=operator" && params.size() == 1 ) {
			mTypeSystem->define((*it)->QualifiedTypename(), Token::Type::ASSIGN, blueprint->QualifiedTypename(), (*it)->QualifiedTypename());
		}
	}

	// add default assignment entry for null assignments
	mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::ASSIGN, NULL_TYPE, blueprint->QualifiedTypename());
	mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_EQUAL, NULL_TYPE, blueprint->QualifiedTypename());
	mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_UNEQUAL, NULL_TYPE, blueprint->QualifiedTypename());

	// add default assignment entry for type system if it doesn't exist yet
	if ( !mTypeSystem->exists(blueprint->QualifiedTypename(), Token(Token::Type::ASSIGN, "="), blueprint->QualifiedTypename()) ) {
		mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::ASSIGN, blueprint->QualifiedTypename(), blueprint->QualifiedTypename());
	}
	// add assignment entries for extended and implemented objects
	{
		Designtime::Ancestors ancestors = blueprint->getInheritance();

		for ( Designtime::Ancestors::const_iterator it = ancestors.begin(); it != ancestors.end(); ++it ) {
			if ( !mTypeSystem->exists(it->name(), Token(Token::Type::ASSIGN, "="), blueprint->QualifiedTypename()) ) {
				mTypeSystem->define(it->name(), Token::Type::ASSIGN, blueprint->QualifiedTypename(), blueprint->QualifiedTypename());
			}
		}
	}
	// add equality operator entries for type system if it doesn't exist yet
	if ( !mTypeSystem->exists(blueprint->QualifiedTypename(), Token(Token::Type::COMPARE_EQUAL, "=="), blueprint->QualifiedTypename()) ) {
		mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_EQUAL, blueprint->QualifiedTypename(), blueprint->QualifiedTypename());
		mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_UNEQUAL, blueprint->QualifiedTypename(), blueprint->QualifiedTypename());
	}
}

void Repository::prepareType(const Common::TypeDeclaration& type)
{
	// resolve type constraints
	std::string resolvedType = Designtime::Parser::buildRuntimeConstraintTypename(type.mName, type.mConstraints);

	// lookup resolved type
	Designtime::BluePrintGeneric* blueprint = findBluePrint(resolvedType);
	if ( !blueprint ) {
		// lookup pure type without constraints
		blueprint = findBluePrint(type.mName);

		if ( !blueprint ) {
			// pure type not available
			throw Common::Exceptions::UnknownIdentifer(resolvedType);
		}

		// build new prototype from pure type with constraints
		createBluePrintFromPrototype(static_cast<Designtime::BluePrintObject*>(blueprint), type.mConstraints);
	}
}


}
