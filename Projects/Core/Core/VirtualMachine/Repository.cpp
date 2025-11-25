
// Header
#include "Repository.h"

// Library includes

// Project includes
#include <Core/AST/TreeGenerator.h>
#include <Core/Common/Exceptions.h>
#include <Core/Common/Method.h>
#include <Core/Designtime/BluePrintObject.h>
#include <Core/Designtime/BuildInTypes/BoolType.h>
#include <Core/Designtime/BuildInTypes/DoubleType.h>
#include <Core/Designtime/BuildInTypes/FloatType.h>
#include <Core/Designtime/BuildInTypes/Int16Type.h>
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/Int64Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Designtime/BuildInTypes/UserType.h>
#include <Core/Designtime/BuildInTypes/VoidType.h>
#include <Core/Designtime/Parser/Parser.h>
#include <Core/Runtime/BuildInTypes/BoolType.h>
#include <Core/Runtime/BuildInTypes/DoubleType.h>
#include <Core/Runtime/BuildInTypes/EnumerationType.h>
#include <Core/Runtime/BuildInTypes/FloatType.h>
#include <Core/Runtime/BuildInTypes/Int16Type.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/Int64Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Runtime/BuildInTypes/UserType.h>
#include <Core/Runtime/BuildInTypes/VoidType.h>
#include <Logger/Logger.h>
#include <Utils.h>
#include "Controller.h"

// Namespace declarations


namespace Slang {


/*
 * adds a new blue print object to the repository
 */
void Repository::addBluePrint(Designtime::BluePrintObject* blueprint)
{
	auto it = mBluePrintObjects.find(blueprint->QualifiedTypename());
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
			throw Common::Exceptions::UnknownIdentifier(constIt->mRunType + " is unknown");
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
		AST::TreeGenerator generator( this );
		generator.process(newBlue);
	}

	return newBlue;
}

/*
 * Creates an instance of the given blueprint
 */
Runtime::Object* Repository::createInstance(const std::string& type, const std::string& name, const PrototypeConstraints& constraints, InitilizationType::E initialize)
{
	// look up type in blueprint objects
	auto objectIt = mBluePrintObjects.find(type);
	if ( objectIt != mBluePrintObjects.end() ) {
		return createInstance(objectIt->second, name, constraints, initialize);
	}

	// workaround for complex member types whose imports have not yet been analysed
	if ( initialize == InitilizationType::None ) {
		return new Runtime::UserType(name, SYSTEM_LIBRARY, Designtime::Parser::buildRuntimeConstraintTypename(type, constraints), true);
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
		auto it = mBluePrintObjects.find(constraintType);
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
	}

	if ( Controller::Instance().phase() == Controller::Phase::Preparation ) {
		switch ( object->getLanguageFeatureState() ) {
			case LanguageFeatureState::Deprecated: OSwarn("Used type '" + object->QualifiedTypename() + "' is marked as deprecated"); break;
			case LanguageFeatureState::NotImplemented: OSerror("Used type '" + object->QualifiedTypename() + "' is marked as not implemented"); break;
			case LanguageFeatureState::Stable: /* this is fine */ break;
			case LanguageFeatureState::Unspecified: OSerror("Unknown language feature state set for type '" + object->QualifiedTypename() + "'"); break;
			case LanguageFeatureState::Unstable: OSwarn("Used type '" + object->QualifiedTypename() + "' is marked as unstable"); break;
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

	Runtime::Object *object = nullptr;

	// instantiate atomic types
	if ( blueprint->QualifiedTypename() == Runtime::BoolType::TYPENAME ) {
		object = new Runtime::BoolType(name, Runtime::BoolType::DEFAULTVALUE);
	}
	else if ( blueprint->QualifiedTypename() == Runtime::DoubleType::TYPENAME ) {
		object = new Runtime::DoubleType(name, Runtime::DoubleType::DEFAULTVALUE);
	}
	else if ( blueprint->QualifiedTypename() == Runtime::FloatType::TYPENAME ) {
		object = new Runtime::FloatType(name, Runtime::FloatType::DEFAULTVALUE);
	}
	else if ( blueprint->QualifiedTypename() == Runtime::Int16Type::TYPENAME ) {
		object = new Runtime::Int16Type(name, Runtime::Int16Type::DEFAULTVALUE);
	}
	else if ( blueprint->QualifiedTypename() == Runtime::Int32Type::TYPENAME ) {
		object = new Runtime::Int32Type(name, Runtime::Int32Type::DEFAULTVALUE);
	}
	else if ( blueprint->QualifiedTypename() == Runtime::Int64Type::TYPENAME ) {
		object = new Runtime::Int64Type(name, Runtime::Int64Type::DEFAULTVALUE);
	}
	else if ( blueprint->QualifiedTypename() == Runtime::StringType::TYPENAME ) {
		object = new Runtime::StringType(name, Runtime::StringType::DEFAULTVALUE);
	}
	else if ( blueprint->QualifiedTypename() == Runtime::VoidType::TYPENAME ) {
		object = new Runtime::VoidType(name);
	}
	else if ( blueprint->isEnumeration() ) {
		object = new Runtime::EnumerationType(name, blueprint->QualifiedTypename(), blueprint->getValue());
	}
	// instantiate user defined types
	else {
		object = createUserType(name, blueprint, initialize);
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
Runtime::Object* Repository::createReference(const std::string& type, const std::string& name, const PrototypeConstraints& constraints, InitilizationType::E initialize)
{
	// look up type in blueprint objects
	auto objectIt = mBluePrintObjects.find(type);
	if ( objectIt != mBluePrintObjects.end() ) {
		return createReference(objectIt->second, name, constraints, initialize);
	}

	// no entry found for given type
	throw Common::Exceptions::Exception("cannot not create reference of unknown type '" + type + "'");
}

/*
 * Creates an instance of the given blueprint and adds a reference to it in the heap memory
 */
Runtime::Object* Repository::createReference(Designtime::BluePrintObject* blueprint, const std::string& name, const PrototypeConstraints& constraints, InitilizationType::E initialize)
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
Runtime::Object* Repository::createUserType(const std::string& name, Designtime::BluePrintObject* blueprint, InitilizationType::E initialize)
{
	assert(blueprint);

	// create the base object
	auto* object = new Runtime::UserType(name, blueprint->Filename(), Designtime::Parser::buildRuntimeConstraintTypename(blueprint->QualifiedTypename(), blueprint->getPrototypeConstraints()));

	if ( initialize >= InitilizationType::AllowAbstract ) {
		Designtime::Ancestors ancestors = blueprint->getInheritance();

		if ( !ancestors.empty() ) {
			// walk through the inheritance and create (and initialize) all base objects
			for ( const auto& ancestorIt : ancestors ) {
				auto blueIt = mBluePrintObjects.find(ancestorIt.name());

				if ( blueIt == mBluePrintObjects.end() ) {
					throw Common::Exceptions::Exception("trying to initialize unknown object '" + ancestorIt.name() + "'");
				}

				switch ( ancestorIt.ancestorType() ) {
					case Designtime::Ancestor::Type::Extends: {
						// create base object
						auto* ancestor = createReference(blueIt->second, IDENTIFIER_THIS, ancestorIt.constraints(), InitilizationType::AllowAbstract);
						ancestor->setParent(blueprint->getEnclosingScope());

						// define new base
						object->define(IDENTIFIER_BASE, ancestor);

						// add our newly created ancestor to our inheritance
						object->addInheritance(ancestorIt, ancestor);
					} break;
					case Designtime::Ancestor::Type::Hidden: {
						// ignore hidden ancestors
					} break;
					case Designtime::Ancestor::Type::Implements: {
						auto* ancestor = createReference(blueIt->second, name, ancestorIt.constraints(), InitilizationType::None);
						ancestor->setParent(blueprint->getEnclosingScope());

						// add our newly created ancestor to our inheritance
						object->addInheritance(ancestorIt, ancestor);
					} break;
					case Designtime::Ancestor::Type::Replicates: {
						// this is empty by intend
					} break;
					case Designtime::Ancestor::Type::Unknown:
						throw Common::Exceptions::Exception("invalid inheritance detected");
				}
			}
		}

		// create and define all symbols based on given blueprint
		const Symbols& symbols = blueprint->provideSymbols();
		for ( auto symbolIt = symbols.cbegin(); symbolIt != symbols.cend(); ++symbolIt ) {
			if ( symbolIt->second->getSymbolType() != Symbol::IType::BluePrintObjectSymbol ) {
				continue;
			}
			if ( symbolIt->first == IDENTIFIER_BASE || symbolIt->first == IDENTIFIER_THIS ) {
				// skip "base" && "this" symbols
				continue;
			}

			auto* blue = dynamic_cast<Designtime::BluePrintObject*>(symbolIt->second);
			if ( blue->isStatic() ) {
				continue;
			}
			if ( blue->getName() == ANONYMOUS_OBJECT ) {
				// this is a type declaration
				continue;
			}

			auto* symbol = createInstance(blue->QualifiedTypename(), blue->getName(), blue->getPrototypeConstraints(), InitilizationType::None);
			symbol->setBluePrint(blue);
			symbol->setIsReference(!blue->isEnumeration() && blue->isReference());
			symbol->setLanguageFeatureState(blue->getLanguageFeatureState());
			symbol->setMember(blue->isMember());
			symbol->setMutability(blue->getMutability());
			symbol->setParent(object);
			symbol->setValue(blue->getValue());
			symbol->setVisibility(blue->getVisibility());

			object->defineMember(symbol->getName(), symbol);
		}

		// create and define all methods based on given blueprint
		for ( const auto& method : blueprint->provideMethods() ) {
			if ( method->isStatic() ) {
				continue;
			}

			// create new method and ...
			auto* newMethod = new Common::Method(object, method->getName(), Common::TypeDeclaration(method->QualifiedTypename()));

			// ... copy its data from our template method
			*newMethod = *method;

			object->defineMethod(method->getName(), newMethod);
		}
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
	auto it = mBluePrintObjects.find(type);

	if ( it != mBluePrintObjects.end() ) {
		return it->second;
	}

	return nullptr;
}

Designtime::BluePrintObject* Repository::findBluePrintObject(const Common::TypeDeclaration& typeDeclaration) const
{
	return findBluePrintObject(
		Designtime::Parser::buildRuntimeConstraintTypename(typeDeclaration.mName, typeDeclaration.mConstraints)
	);
}

void Repository::init()
{
	TypeSystem::init();

	auto* scope = Controller::Instance().globalScope();

	// add atomic types
	{	// "bool" type
		auto* obj = new Designtime::BoolType();
		addBluePrint(obj);

		scope->define(Designtime::BoolType::TYPENAME, obj);
	}
	{	// "double" type
		auto* obj = new Designtime::DoubleType();
		addBluePrint(obj);

		scope->define(Designtime::DoubleType::TYPENAME, obj);
	}
	{	// "float" type
		auto* obj = new Designtime::FloatType();
		addBluePrint(obj);

		scope->define(Designtime::FloatType::TYPENAME, obj);
	}
	{	// "int16" type
		auto* obj = new Designtime::Int16Type();
		addBluePrint(obj);

		scope->define(Designtime::Int16Type::TYPENAME, obj);
	}
	{	// "int32" type
		auto* obj = new Designtime::Int32Type();
		addBluePrint(obj);

		scope->define(Designtime::Int32Type::TYPENAME, obj);
	}
	{	// "int64" type
		auto* obj = new Designtime::Int64Type();
		addBluePrint(obj);

		scope->define(Designtime::Int64Type::TYPENAME, obj);
	}
	{	// "string" type
		auto* obj = new Designtime::StringType();
		addBluePrint(obj);

		scope->define(Designtime::StringType::TYPENAME, obj);
	}
	{	// "void" type
		auto* obj = new Designtime::VoidType();
		addBluePrint(obj);

		scope->define(Designtime::VoidType::TYPENAME, obj);
	}
	{	// "Object" type
		auto* obj = new Designtime::UserType();
		obj->setIsReference(true);
		addBluePrint(obj);

		scope->define(Designtime::UserType::TYPENAME, obj);
	}

	// add predefined runtime objects
	{	// null
		auto* nullObject = new Runtime::UserType(VALUE_NULL, SYSTEM_LIBRARY, _object, true);
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
	for ( auto& blueprintIt : mBluePrintObjects) {
		auto* blueprint = blueprintIt.second;

		Designtime::Ancestors ancestors = blueprint->getInheritance();
		for ( const auto& ancestor : ancestors) {
			prepareType(Common::TypeDeclaration(ancestor.name(), ancestor.constraints()));

			auto* base = findBluePrintObject(
				Designtime::Parser::buildRuntimeConstraintTypename(ancestor.name(), ancestor.constraints())
			);

/*
			for ( const auto& a : base->getInheritance() ) {
				Designtime::Ancestor ancestor( a.typeDeclaration(), Designtime::Ancestor::Type::Hidden, a.visibility() );

				blueprint->addInheritance( ancestor );
			}
*/

			switch ( ancestor.ancestorType() ) {
				case Designtime::Ancestor::Type::Extends: {
					blueprint->define(IDENTIFIER_BASE, base);
				} break;
				case Designtime::Ancestor::Type::Hidden: {
					// ignore hidden ancestors
				} break;
				case Designtime::Ancestor::Type::Implements: {
					// nothing to do here
				} break;
				case Designtime::Ancestor::Type::Replicates: {
					blueprintIt.second = base->replicate(
						blueprint->QualifiedTypename(), blueprint->Filename(), blueprintIt.second
					);
				} break;
				case Designtime::Ancestor::Type::Unknown:
					throw Common::Exceptions::Exception("invalid inheritance detected");
			}
		}
	}

	// initialize blueprint objects
	for ( auto& blueprint : mBluePrintObjects) {
		initBluePrintObject(blueprint.second);
	}
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

		auto* member = dynamic_cast<Designtime::BluePrintObject*>(it->second);

		Designtime::BluePrintObject* baseType = findBluePrintObject(member->QualifiedTypename());
		if ( !baseType ) {
			throw Common::Exceptions::UnknownIdentifier("unknown member type '" + member->QualifiedTypename() + "'!");
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
	for ( auto method : methods ) {
		Designtime::BluePrintObject* baseType = findBluePrintObject(method->QualifiedTypename());
		if ( !baseType ) {
			throw Common::Exceptions::UnknownIdentifier("unknown type '" + method->QualifiedTypename() + "'!");
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

		method->initialize();
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
	if ( exists(blueprint->QualifiedTypename(), Token::Type::ASSIGN, blueprint->QualifiedTypename()) ) {
		return;
	}

	// enumeration types
	if ( blueprint->isEnumeration() ) {
		// assignment operator
		define(blueprint->QualifiedTypename(), Token::Type::ASSIGN, blueprint->QualifiedTypename(), blueprint->QualifiedTypename());
		//define(_int32, Token::Type::ASSIGN, blueprint->QualifiedTypename(), blueprint->QualifiedTypename());
		//define(_string, Token::Type::ASSIGN, blueprint->QualifiedTypename(), blueprint->QualifiedTypename());
		define(_int32, Token::Type::ASSIGN, blueprint->QualifiedTypename(), _int32);
		define(_string, Token::Type::ASSIGN, blueprint->QualifiedTypename(), _string);

		// comparison operators (enum vs enum)
		define(blueprint->QualifiedTypename(), Token::Type::COMPARE_EQUAL,         blueprint->QualifiedTypename(), _bool);
		define(blueprint->QualifiedTypename(), Token::Type::COMPARE_LESS,          blueprint->QualifiedTypename(), _bool);
		define(blueprint->QualifiedTypename(), Token::Type::COMPARE_LESS_EQUAL,    blueprint->QualifiedTypename(), _bool);
		define(blueprint->QualifiedTypename(), Token::Type::COMPARE_GREATER,       blueprint->QualifiedTypename(), _bool);
		define(blueprint->QualifiedTypename(), Token::Type::COMPARE_GREATER_EQUAL, blueprint->QualifiedTypename(), _bool);
		define(blueprint->QualifiedTypename(), Token::Type::COMPARE_UNEQUAL,       blueprint->QualifiedTypename(), _bool);

		// comparison operators (enum vs int)
		define(blueprint->QualifiedTypename(),      Token::Type::COMPARE_EQUAL,         Designtime::Int32Type::TYPENAME, _bool);
		define(blueprint->QualifiedTypename(),      Token::Type::COMPARE_LESS,          Designtime::Int32Type::TYPENAME, _bool);
		define(blueprint->QualifiedTypename(),      Token::Type::COMPARE_LESS_EQUAL,    Designtime::Int32Type::TYPENAME, _bool);
		define(blueprint->QualifiedTypename(),      Token::Type::COMPARE_GREATER,       Designtime::Int32Type::TYPENAME, _bool);
		define(blueprint->QualifiedTypename(),      Token::Type::COMPARE_GREATER_EQUAL, Designtime::Int32Type::TYPENAME, _bool);
		define(blueprint->QualifiedTypename(),      Token::Type::COMPARE_UNEQUAL,       Designtime::Int32Type::TYPENAME, _bool);

		// comparison operators (int vs enum)
		define(Designtime::Int32Type::TYPENAME, Token::Type::COMPARE_EQUAL,         blueprint->QualifiedTypename(), _bool);
		define(Designtime::Int32Type::TYPENAME, Token::Type::COMPARE_LESS,          blueprint->QualifiedTypename(), _bool);
		define(Designtime::Int32Type::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    blueprint->QualifiedTypename(), _bool);
		define(Designtime::Int32Type::TYPENAME, Token::Type::COMPARE_GREATER,       blueprint->QualifiedTypename(), _bool);
		define(Designtime::Int32Type::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, blueprint->QualifiedTypename(), _bool);
		define(Designtime::Int32Type::TYPENAME, Token::Type::COMPARE_UNEQUAL,       blueprint->QualifiedTypename(), _bool);

		// arithmetic operators
		define(blueprint->QualifiedTypename(), Token::Type::MATH_ADDITION, blueprint->QualifiedTypename(), blueprint->QualifiedTypename());
		define(blueprint->QualifiedTypename(), Token::Type::MATH_DIVIDE,   blueprint->QualifiedTypename(), blueprint->QualifiedTypename());
		define(blueprint->QualifiedTypename(), Token::Type::MATH_MODULO,   blueprint->QualifiedTypename(), _float);
		define(blueprint->QualifiedTypename(), Token::Type::MATH_MULTIPLY, blueprint->QualifiedTypename(), blueprint->QualifiedTypename());
		define(blueprint->QualifiedTypename(), Token::Type::MATH_SUBTRACT, blueprint->QualifiedTypename(), blueprint->QualifiedTypename());

		// typecast operator
		define(_int32, Token::Type::TYPECAST, blueprint->QualifiedTypename(), _int32);
		define(_string, Token::Type::TYPECAST, blueprint->QualifiedTypename(), _string);

		return;
	}

	MethodScope::MethodCollection methods = blueprint->provideMethods();
	for ( auto method : methods ) {
		const std::string& name = method->getName();
		auto params = method->provideSignature();

		if ( name == "operator=" && params.size() == 1 ) {
			define(blueprint->QualifiedTypename(), Token::Type::ASSIGN, params.front().type(), blueprint->QualifiedTypename());
		}
		else if ( name == "operator&" && params.size() == 1 ) {
			define(blueprint->QualifiedTypename(), Token::Type::BITAND, params.front().type(), blueprint->QualifiedTypename());
		}
		else if ( name == "operator|" && params.size() == 1 ) {
			define(blueprint->QualifiedTypename(), Token::Type::BITOR, params.front().type(), blueprint->QualifiedTypename());
		}
		else if ( name == "operator~" && params.size() == 1 ) {
			define(blueprint->QualifiedTypename(), Token::Type::BITCOMPLEMENT, params.front().type(), blueprint->QualifiedTypename());
		}
		else if ( name == "operator==" && params.size() == 1 ) {
			define(blueprint->QualifiedTypename(), Token::Type::COMPARE_EQUAL, params.front().type(), method->QualifiedTypename());
			define(blueprint->QualifiedTypename(), Token::Type::COMPARE_EQUAL_CONTENT, params.front().type(), method->QualifiedTypename());
		}
		else if ( name == "operator<" && params.size() == 1 ) {
			define(blueprint->QualifiedTypename(), Token::Type::COMPARE_LESS, params.front().type(), method->QualifiedTypename());
		}
		else if ( name == "operator<=" && params.size() == 1 ) {
			define(blueprint->QualifiedTypename(), Token::Type::COMPARE_LESS_EQUAL, params.front().type(), method->QualifiedTypename());
		}
		else if ( name == "operator>" && params.size() == 1 ) {
			define(blueprint->QualifiedTypename(), Token::Type::COMPARE_GREATER, params.front().type(), method->QualifiedTypename());
		}
		else if ( name == "operator>=" && params.size() == 1 ) {
			define(blueprint->QualifiedTypename(), Token::Type::COMPARE_GREATER_EQUAL, params.front().type(), method->QualifiedTypename());
		}
		else if ( name == "operator+" && params.size() == 1 ) {
			define(blueprint->QualifiedTypename(), Token::Type::MATH_ADDITION, params.front().type(), blueprint->QualifiedTypename());
		}
		else if ( name == "operator/" && params.size() == 1 ) {
			define(blueprint->QualifiedTypename(), Token::Type::MATH_DIVIDE, params.front().type(), blueprint->QualifiedTypename());
		}
		else if ( name == "operator%" && params.size() == 1 ) {
			define(blueprint->QualifiedTypename(), Token::Type::MATH_MODULO, params.front().type(), blueprint->QualifiedTypename());
		}
		else if ( name == "operator*" && params.size() == 1 ) {
			define(blueprint->QualifiedTypename(), Token::Type::MATH_MULTIPLY, params.front().type(), blueprint->QualifiedTypename());
		}
		else if ( name == "operator-" && params.size() == 1 ) {
			define(blueprint->QualifiedTypename(), Token::Type::MATH_SUBTRACT, params.front().type(), blueprint->QualifiedTypename());
		}
		else if ( name == "operator--" && params.empty() ) {
			define(blueprint->QualifiedTypename(), Token::Type::OPERATOR_DECREMENT, _void, blueprint->QualifiedTypename());
		}
		else if ( name == "operator++" && params.empty() ) {
			define(blueprint->QualifiedTypename(), Token::Type::OPERATOR_INCREMENT, _void, blueprint->QualifiedTypename());
		}
		else if ( name == "operator<<" && params.size() == 1 ) {
			define(blueprint->QualifiedTypename(), Token::Type::OPERATOR_SHIFT_LEFT, params.front().type(), blueprint->QualifiedTypename());
		}
		else if ( name == "operator>>" && params.size() == 1 ) {
			define(blueprint->QualifiedTypename(), Token::Type::OPERATOR_SHIFT_RIGHT, params.front().type(), blueprint->QualifiedTypename());
		}
		else if ( name == "=operator" && params.size() == 1 ) {
			define(method->QualifiedTypename(), Token::Type::ASSIGN, blueprint->QualifiedTypename(), method->QualifiedTypename());
			define(method->QualifiedTypename(), Token::Type::TYPECAST, blueprint->QualifiedTypename(), method->QualifiedTypename());
		}
	}

	// add default entries for pointer comparison etc.
	define(blueprint->QualifiedTypename(), Token::Type::COMPARE_EQUAL,   _object,                        _bool);
	define(_object,                        Token::Type::COMPARE_EQUAL,   blueprint->QualifiedTypename(), _bool);

	// add default assignment entry for type system
	define(blueprint->QualifiedTypename(), Token::Type::ASSIGN,   blueprint->QualifiedTypename(), blueprint->QualifiedTypename());

	// add default typecast entry for type system
	define(blueprint->QualifiedTypename(), Token::Type::TYPECAST, blueprint->QualifiedTypename(), blueprint->QualifiedTypename());

	// add equality operator entries for type system
	define(blueprint->QualifiedTypename(), Token::Type::COMPARE_EQUAL,   blueprint->QualifiedTypename(), _bool);
	define(blueprint->QualifiedTypename(), Token::Type::COMPARE_EQUAL_CONTENT, blueprint->QualifiedTypename(), _bool);

	// add assignment entries for extended and implemented objects
	{
		Designtime::Ancestors ancestors = blueprint->getInheritance();

		for ( const auto& ancestor : ancestors ) {
			define(ancestor.name(), Token::Type::ASSIGN,   blueprint->QualifiedTypename(), ancestor.name());
			define(ancestor.name(), Token::Type::TYPECAST, blueprint->QualifiedTypename(), ancestor.name());
		}
	}
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
			throw Common::Exceptions::UnknownIdentifier( "pure type '" + resolvedType + "' not available" );
		}

		// build new prototype from pure type with constraints
		createBluePrintFromPrototype(blueprint, type.mConstraints);
	}
}


}
