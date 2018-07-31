
// Header
#include "Repository.h"

// Library includes

// Project includes
#include <Core/AST/Generator.h>
#include <Core/Common/Exceptions.h>
#include <Core/Common/Method.h>
#include <Core/Designtime/BluePrintObject.h>
#include <Core/Designtime/BuildInTypes/BoolObject.h>
#include <Core/Designtime/BuildInTypes/DoubleObject.h>
#include <Core/Designtime/BuildInTypes/FloatObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Designtime/BuildInTypes/UserObject.h>
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Designtime/Parser/Parser.h>
#include <Core/Runtime/BuildInTypes/BoolObject.h>
#include <Core/Runtime/BuildInTypes/DoubleObject.h>
#include <Core/Runtime/BuildInTypes/EnumerationObject.h>
#include <Core/Runtime/BuildInTypes/FloatObject.h>
#include <Core/Runtime/BuildInTypes/IntegerObject.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Runtime/BuildInTypes/UserObject.h>
#include <Core/Runtime/BuildInTypes/VoidObject.h>
#include <Core/Tools.h>
#include <Utils.h>
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
 * adds a new blue print object to the repository
 */
void Repository::addBluePrint(Designtime::BluePrintObject* blueprint)
{
	BluePrintObjectMap::iterator it = mBluePrintObjects.find(blueprint->QualifiedTypename());
	if ( it != mBluePrintObjects.end() ) {
		throw Common::Exceptions::Exception("duplicate object '" + blueprint->QualifiedTypename() + "' added to repository");
	}

	mBluePrintObjects.insert(std::make_pair(blueprint->QualifiedTypename(), blueprint));
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
		Designtime::BluePrintObject* generic = findBluePrintObject(constIt->mRunType);

		if ( !generic ) {
			throw Common::Exceptions::UnknownIdentifer(constIt->mRunType + " is unknown");
		}
		if ( !constIt->mConstraint.empty() && generic->QualifiedTypename() != constIt->mConstraint && !generic->inheritsFrom(constIt->mConstraint) ) {
			throw Common::Exceptions::TypeMismatch(constIt->mRunType + " is no or does not inherit from " + constIt->mConstraint);
		}

		initBluePrintObject(generic);
	}

	Designtime::BluePrintObject* newBlue = blueprint->fromPrototype(constraints);

	// add new blueprint to repository
	addBluePrint(newBlue);

	// add new blueprint to parent scope
	IScope* parent = blueprint->getEnclosingScope();
	if ( parent ) {
		parent->define(newBlue->QualifiedTypename(), newBlue);
	}

	// initialize newly created blueprint
	initBluePrintObject(newBlue);

	if ( Controller::Instance().phase() > Controller::Phase::Preparation ) {
		AST::Generator generator;
		generator.process(newBlue);
	}

	return newBlue;
}

/*
 * Creates an instance of the given blueprint
 */
Runtime::Object* Repository::createInstance(const std::string& type, const std::string& name, PrototypeConstraints constraints, InitilizationType::E initialize)
{
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
Runtime::Object* Repository::createInstance(Designtime::BluePrintObject* blueprint, const std::string& name, PrototypeConstraints constraints, InitilizationType::E initialize)
{
	if ( !blueprint ) {
		throw Common::Exceptions::Exception("invalid blueprint provided!");
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
			blueprint = createBluePrintFromPrototype(blueprint, constraints);
		}
		else {
			blueprint = it->second;
		}
	}

	Runtime::Object* object = createObject(name, blueprint, initialize);

	if ( initialize == InitilizationType::Final ) {
		if ( object->isAbstract() ) {
			throw Common::Exceptions::AbstractException("cannot instantiate abstract object '" + constraintType + "'");
		}

		// TODO: verify me
		//Controller::Instance().memory()->newObject(object);
	}

	if ( Controller::Instance().phase() == Controller::Phase::Preparation ) {
		switch ( object->getLanguageFeatureState() ) {
			case LanguageFeatureState::Deprecated: OSwarn("Used type '" + object->QualifiedTypename() + "' is marked as deprecated"); break;
			case LanguageFeatureState::NotImplemented: OSerror("Used type '" + object->QualifiedTypename() + "' is marked as not implemented"); break;
			case LanguageFeatureState::Unstable: OSwarn("Used type '" + object->QualifiedTypename() + "' is marked as unstable"); break;
			default: break;
		}
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
	else if ( blueprint->isEnumeration() ) {
		object = new Runtime::EnumerationObject(name, blueprint->QualifiedTypename(), blueprint->getValue());
	}
	// instantiate user defined types
	else {
		object = createUserObject(name, blueprint, initialize);
	}

	IScope* parent = blueprint->getEnclosingScope();
	if ( !parent ) {
		// set global scope as fallback parent
		parent = Controller::Instance().globalScope();
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
Runtime::Object* Repository::createReference(Designtime::BluePrintObject* blueprint, const std::string& name, PrototypeConstraints constraints, InitilizationType::E initialize)
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
					case Designtime::Ancestor::Type::Extends: {
						// create base object
						Runtime::Object *ancestor = createReference(blueIt->second, IDENTIFIER_THIS, ancestorIt->constraints(), InitilizationType::AllowAbstract);
						ancestor->setParent(blueprint->getEnclosingScope());

						// define new base
						object->define(IDENTIFIER_BASE, ancestor);

						// add our newly created ancestor to our inheritance
						object->addInheritance((*ancestorIt), ancestor);
					} break;
					case Designtime::Ancestor::Type::Implements: {
						Runtime::Object *ancestor = createReference(blueIt->second, name, ancestorIt->constraints(), InitilizationType::None);
						ancestor->setParent(blueprint->getEnclosingScope());

						// add our newly created ancestor to our inheritance
						object->addInheritance((*ancestorIt), ancestor);
					} break;
					case Designtime::Ancestor::Type::Replicates: {

					} break;
					case Designtime::Ancestor::Type::Unknown:
						throw Common::Exceptions::Exception("invalid inheritance detected");
				}
			}
		}

		// initialize the base object
		initializeObject(blueprint, object);
	}

	return object;
}

void Repository::deinit()
{
	// cleanup blue prints
	mBluePrintObjects.clear();
}

Designtime::BluePrintObject* Repository::findBluePrintObject(const std::string& type) const
{
	BluePrintObjectMap::const_iterator it = mBluePrintObjects.find(type);

	if ( it != mBluePrintObjects.end() ) {
		return it->second;
	}

	return 0;
}

Designtime::BluePrintObject* Repository::findBluePrintObject(const Common::TypeDeclaration& typeDeclaration) const
{
	return findBluePrintObject(
		Designtime::Parser::buildRuntimeConstraintTypename(typeDeclaration.mName, typeDeclaration.mConstraints)
	);
}

void Repository::init()
{
	// Initialize virtual machine stuff
	mTypeSystem = Controller::Instance().typeSystem();

	IScope* scope = Controller::Instance().globalScope();

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
	{	// "Object" type
		Designtime::UserObject* obj = new Designtime::UserObject();
		obj->setIsReference(true);
		addBluePrint(obj);

		scope->define(Designtime::UserObject::TYPENAME, obj);
	}

	// add predefined runtime objects
	{	// null
		Runtime::UserObject* nullObject = new Runtime::UserObject(VALUE_NULL, SYSTEM_LIBRARY, _object, true);
		nullObject->setConst(true);
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
	// prepare inheritance
	for ( BluePrintObjectMap::iterator blueIt = mBluePrintObjects.begin(); blueIt != mBluePrintObjects.end(); ++blueIt ) {
		Designtime::BluePrintObject* blueprint = blueIt->second;

		Designtime::Ancestors ancestors = blueprint->getInheritance();
		for ( Designtime::Ancestors::const_iterator ancestorIt = ancestors.begin(); ancestorIt != ancestors.end(); ++ancestorIt ) {
			prepareType(Common::TypeDeclaration(ancestorIt->name(), ancestorIt->constraints()));

			Designtime::BluePrintObject* base = findBluePrintObject(
				Designtime::Parser::buildRuntimeConstraintTypename(ancestorIt->name(), ancestorIt->constraints())
			);

			switch ( ancestorIt->ancestorType() ) {
				case Designtime::Ancestor::Type::Extends: {
					blueprint->define(IDENTIFIER_BASE, base);
				} break;
				case Designtime::Ancestor::Type::Implements:
					// nothing to do here
					break;
				case Designtime::Ancestor::Type::Replicates: {
					blueIt->second = base->replicate(
						blueprint->QualifiedTypename(), blueprint->Filename(), blueIt->second
					);
				} break;
				case Designtime::Ancestor::Type::Unknown:
					throw Common::Exceptions::Exception("invalid inheritance detected");
			}
		}
	}

	// initialize blueprint objects
	for ( BluePrintObjectMap::iterator it = mBluePrintObjects.begin(); it != mBluePrintObjects.end(); ++it ) {
		initBluePrintObject(it->second);
	}
}

/*
 * creates and defines all members and methods of an object
 */
void Repository::initializeObject(Designtime::BluePrintObject* srcObj, Runtime::Object* destObj)
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

		Designtime::BluePrintObject* blue = dynamic_cast<Designtime::BluePrintObject*>(it->second);
		if ( blue->isStatic() ) {
			continue;
		}
		if ( blue->getName() == ANONYMOUS_OBJECT ) {
			// this is a type declaration
			continue;
		}

		Runtime::Object *symbol = createInstance(blue->QualifiedTypename(), blue->getName(), blue->getPrototypeConstraints(), InitilizationType::None);
		symbol->setBluePrint(blue);
		symbol->setIsReference(blue->isEnumeration() ? false : blue->isReference());
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
		if ( method->isStatic() ) {
			continue;
		}

		// ... copy its data from our template method
		*method = *(*it);

		destObj->defineMethod((*it)->getName(), method);
	}

	destObj->define(IDENTIFIER_THIS, destObj);	// define this-symbol
}

/*
 * initializes a given blueprint object (i.e. triggers type system initialization)
 */
void Repository::initBluePrintObject(Designtime::BluePrintObject* blueprint)
{
	if ( blueprint->isAtomicType() && !blueprint->isEnumeration() ) {
		// atomic types have been initialized at compile time
		return;
	}
	if ( blueprint->isPrototype() ) {
		// prototypes will get initialized during tree generation phase
		return;
	}

	// prepare members
	Symbols symbols = blueprint->provideSymbols();
	for ( Symbols::const_iterator it = symbols.begin(); it != symbols.end(); ++it ) {
		if ( it->second->getSymbolType() != Symbol::IType::BluePrintObjectSymbol ) {
			continue;
		}
		if ( it->first == IDENTIFIER_THIS ) {
			// skip "this" symbols
			continue;
		}

		Designtime::BluePrintObject* member = static_cast<Designtime::BluePrintObject*>(it->second);

		Designtime::BluePrintObject* baseType = findBluePrintObject(member->QualifiedTypename());
		if ( !baseType ) {
			throw Common::Exceptions::UnknownIdentifer("unknown member type '" + member->QualifiedTypename() + "'!");
		}
		if ( !baseType->isPrototype() && member->isPrototype() ) {
			throw Common::Exceptions::TypeMismatch("base type '" + baseType->QualifiedTypename() + "' is no prototype!");
		}

		if ( baseType->isPrototype() ) {
			Common::TypeDeclaration typeDeclaration(
				member->QualifiedTypename(),
				baseType->getPrototypeConstraints().buildRawConstraints(member->getPrototypeConstraints())
			);

			// prepare type
			prepareType(typeDeclaration);
			// set qualified typename to constraint type
			member->setQualifiedTypename(Designtime::Parser::buildRuntimeConstraintTypename(typeDeclaration.mName, typeDeclaration.mConstraints));
			// reset constraints
			member->setPrototypeConstraints(PrototypeConstraints());
		}
	}

	// prepare methods
	MethodScope::MethodCollection methods = blueprint->provideMethods();
	for ( MethodScope::MethodCollection::const_iterator it = methods.begin(); it != methods.end(); ++it ) {
		Common::Method* method = (*it);

		Designtime::BluePrintObject* baseType = findBluePrintObject(method->QualifiedTypename());
		if ( !baseType ) {
			throw Common::Exceptions::UnknownIdentifer("unknown type '" + method->QualifiedTypename() + "'!");
		}
		if ( !baseType->isPrototype() && method->isPrototype() ) {
			throw Common::Exceptions::TypeMismatch("base type '" + baseType->QualifiedTypename() + "' is no prototype!");
		}

		if ( baseType->isPrototype() ) {
			Common::TypeDeclaration typeDeclaration(
				method->QualifiedTypename(),
				baseType->getPrototypeConstraints().buildRawConstraints(method->getPrototypeConstraints())
			);

			// prepare type
			prepareType(typeDeclaration);
			// set qualified typename to constraint type
			method->setQualifiedTypename(Designtime::Parser::buildRuntimeConstraintTypename(typeDeclaration.mName, typeDeclaration.mConstraints));
			// reset constraints
			method->setPrototypeConstraints(PrototypeConstraints());
		}
	}

	if ( !blueprint->isPrepared() ) {
		blueprint->prepareParents(this);
	}

	initTypeSystem(blueprint);
}

/*
 * initializes type system for given blueprint object
 */
void Repository::initTypeSystem(Designtime::BluePrintObject* blueprint)
{
	// no duplicates allowed
	if ( mTypeSystem->exists(blueprint->QualifiedTypename(), Token::Type::ASSIGN, blueprint->QualifiedTypename()) ) {
		return;
	}

	// enumeration types
	if ( blueprint->isEnumeration() ) {
		// assignment operator
		mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::ASSIGN, blueprint->QualifiedTypename(), blueprint->QualifiedTypename());

		// comparison operators
		mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_EQUAL,         blueprint->QualifiedTypename(), _bool);
		mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_LESS,          blueprint->QualifiedTypename(), _bool);
		mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_LESS_EQUAL,    blueprint->QualifiedTypename(), _bool);
		mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_GREATER,       blueprint->QualifiedTypename(), _bool);
		mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_GREATER_EQUAL, blueprint->QualifiedTypename(), _bool);
		mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_UNEQUAL,       blueprint->QualifiedTypename(), _bool);

		// arithmetic operators
		mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::MATH_ADDITION, blueprint->QualifiedTypename(), blueprint->QualifiedTypename());
		mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::MATH_DIVIDE,   blueprint->QualifiedTypename(), blueprint->QualifiedTypename());
		mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::MATH_MODULO,   blueprint->QualifiedTypename(), _float);
		mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::MATH_MULTIPLY, blueprint->QualifiedTypename(), blueprint->QualifiedTypename());
		mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::MATH_SUBTRACT, blueprint->QualifiedTypename(), blueprint->QualifiedTypename());

		return;
	}

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
			mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_EQUAL, params.front().type(), (*it)->QualifiedTypename());
			mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_UNEQUAL, params.front().type(), (*it)->QualifiedTypename());
		}
		else if ( name == "operator<" && params.size() == 1 ) {
			mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_LESS, params.front().type(), (*it)->QualifiedTypename());
		}
		else if ( name == "operator<=" && params.size() == 1 ) {
			mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_LESS_EQUAL, params.front().type(), (*it)->QualifiedTypename());
		}
		else if ( name == "operator>" && params.size() == 1 ) {
			mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_GREATER, params.front().type(), (*it)->QualifiedTypename());
		}
		else if ( name == "operator>=" && params.size() == 1 ) {
			mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_GREATER_EQUAL, params.front().type(), (*it)->QualifiedTypename());
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
		else if ( name == "operator--" && params.size() == 0 ) {
			mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::OPERATOR_DECREMENT, _void, blueprint->QualifiedTypename());
		}
		else if ( name == "operator++" && params.size() == 0 ) {
			mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::OPERATOR_INCREMENT, _void, blueprint->QualifiedTypename());
		}
		else if ( name == "=operator" && params.size() == 1 ) {
			mTypeSystem->define((*it)->QualifiedTypename(), Token::Type::ASSIGN, blueprint->QualifiedTypename(), (*it)->QualifiedTypename());
		}
	}

	// add default entries for pointer comparison etc.
	mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_EQUAL,   _object,                        _bool);
	mTypeSystem->define(_object,                        Token::Type::COMPARE_EQUAL,   blueprint->QualifiedTypename(), _bool);

	// add default assignment entry for type system if it doesn't exist yet
	//if ( !mTypeSystem->exists(blueprint->QualifiedTypename(), Token::Type::ASSIGN, blueprint->QualifiedTypename()) ) {
		mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::ASSIGN, blueprint->QualifiedTypename(), blueprint->QualifiedTypename());
	//}

	// add assignment entries for extended and implemented objects
	{
		Designtime::Ancestors ancestors = blueprint->getInheritance();

		for ( Designtime::Ancestors::const_iterator it = ancestors.begin(); it != ancestors.end(); ++it ) {
			//if ( !mTypeSystem->exists(it->name(), Token::Type::ASSIGN, blueprint->QualifiedTypename()) ) {
				mTypeSystem->define(it->name(), Token::Type::ASSIGN, blueprint->QualifiedTypename(), it->name());
			//}
		}
	}

	// add equality operator entries for type system if it doesn't exist yet
	//if ( !mTypeSystem->exists(blueprint->QualifiedTypename(), Token::Type::COMPARE_EQUAL, blueprint->QualifiedTypename()) ) {
		// compare with same type
		mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_EQUAL,   blueprint->QualifiedTypename(), _bool);
		mTypeSystem->define(blueprint->QualifiedTypename(), Token::Type::COMPARE_UNEQUAL, blueprint->QualifiedTypename(), _bool);
	//}
}

void Repository::prepareType(const Common::TypeDeclaration& type)
{
	// resolve type constraints
	std::string resolvedType = Designtime::Parser::buildRuntimeConstraintTypename(type.mName, type.mConstraints);

	// lookup resolved type
	Designtime::BluePrintObject* blueprint = findBluePrintObject(resolvedType);
	if ( !blueprint ) {
		// lookup pure type without constraints
		blueprint = findBluePrintObject(type.mName);

		if ( !blueprint ) {
			// pure type not available
			throw Common::Exceptions::UnknownIdentifer(resolvedType);
		}

		// build new prototype from pure type with constraints
		createBluePrintFromPrototype(blueprint, type.mConstraints);
	}
}


}
