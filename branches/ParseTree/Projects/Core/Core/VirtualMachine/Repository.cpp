
// Header
#include "Repository.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/DoubleObject.h>
#include <Core/BuildInObjects/FloatObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/BuildInObjects/UserObject.h>
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BluePrintEnum.h>
#include <Core/Designtime/BluePrintObject.h>
#include <Core/Designtime/BuildInTypes/BoolObject.h>
#include <Core/Designtime/BuildInTypes/DoubleObject.h>
#include <Core/Designtime/BuildInTypes/FloatObject.h>
#include <Core/Designtime/BuildInTypes/GenericObject.h>
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
		// adding additional forward declarations doesn't matter
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
		// adding additional forward declarations doesn't matter
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

Designtime::BluePrintObject* Repository::createBluePrintFromPrototype(Designtime::BluePrintObject* blueprint, const PrototypeConstraints& constraints)
{
	if ( !blueprint ) {
		throw Common::Exceptions::Exception("invalid blueprint provided!");
	}

	std::string constraintType = Designtime::Parser::buildConstraintTypename(blueprint->QualifiedTypename(), constraints);

	PrototypeConstraints protoConstraints = blueprint->getPrototypeConstraints();

	if ( protoConstraints != constraints ) {
		throw Common::Exceptions::TypeMismatch("'" + blueprint->QualifiedTypename() + "' prototype constraint missmatch");
	}

	Designtime::BluePrintObject* newBlue = new Designtime::BluePrintObject(constraintType, blueprint->Filename());
	newBlue->setConst(blueprint->isConst());
	newBlue->setFinal(blueprint->isFinal());
	newBlue->setImplementationType(blueprint->getImplementationType());
	newBlue->setLanguageFeatureState(blueprint->getLanguageFeatureState());
	newBlue->setMember(blueprint->isMember());
	newBlue->setMutability(blueprint->getMutability());
	newBlue->setParent(blueprint->getEnclosingScope());
	newBlue->setQualifiedTypename(constraintType);
	newBlue->setSealed(blueprint->isSealed());
	newBlue->setTokens(blueprint->getTokens());
	newBlue->setValue(blueprint->getValue());
	newBlue->setVisibility(blueprint->getVisibility());

	// inheritance
	Designtime::Ancestors ancestors = blueprint->getInheritance();
	for ( Designtime::Ancestors::const_iterator it = ancestors.begin(); it != ancestors.end(); ++it ) {
		newBlue->addInheritance((*it));
	}

	std::string type;

	// symbols
	Symbols symbols = blueprint->provideSymbols();
	for ( Symbols::const_iterator symIt = symbols.begin(); symIt != symbols.end(); ++symIt ) {
		if ( symIt->second->getSymbolType() != Symbol::IType::BluePrintObjectSymbol ) {
			continue;
		}

		Designtime::BluePrintObject* blue = static_cast<Designtime::BluePrintObject*>(symIt->second);

		std::string name = blue->getName();

		type = lookupType(blue->QualifiedTypename(), protoConstraints, constraints);
		if ( !blue->getPrototypeConstraints().empty() ) {
			type += extractType(blue->getPrototypeConstraints(), constraints);
		}

		Designtime::BluePrintObject* member = new Designtime::BluePrintObject(type, blue->Filename(), name);
		member->setFinal(blue->isFinal());
		member->setLanguageFeatureState(blue->getLanguageFeatureState());
		member->setMember(blue->isMember());
		member->setMutability(blue->getMutability());
		member->setParent(newBlue);
		//member->setPrototypeConstraints(blue->getPrototypeConstraints());	// this has already been processed, so we cannot add even more constraints
		member->setQualifiedTypename(type);
		member->setValue(blue->getValue());
		member->setVisibility(blue->getVisibility());

		newBlue->define(name, member);
	}

	StringSet atomicTypes = provideAtomicTypes();

	// methods
	MethodScope::MethodCollection methods = blueprint->provideMethods();
	for ( MethodScope::MethodCollection::const_iterator methIt = methods.begin(); methIt != methods.end(); ++methIt ) {
		Runtime::Method* method = new Runtime::Method(newBlue, (*methIt)->getName(), Designtime::Parser::buildConstraintTypename((*methIt)->QualifiedTypename(), (*methIt)->getPrototypeConstraints()));

		// copy from template
		*method = *(*methIt);

		// Prepare return value
		// {
		type = lookupType(method->QualifiedTypename(), protoConstraints, constraints);
		if ( !method->getPrototypeConstraints().empty() ) {
			type += extractType(method->getPrototypeConstraints(), constraints);
			method->setPrototypeConstraints(PrototypeConstraints());
		}

		method->setQualifiedTypename(type);
		// }

		// Update method signature
		// {
		bool signatureChanged = false;

		ParameterList params = method->provideSignature();
		for ( ParameterList::iterator paramIt = params.begin(); paramIt != params.end(); ++paramIt ) {
			type = lookupType(paramIt->type(), protoConstraints, constraints);
			
			if ( paramIt->type() != type ) {
				Parameter::AccessMode::E access = Parameter::AccessMode::ByValue;

				if ( atomicTypes.find(type) == atomicTypes.end() ) {
					access = Parameter::AccessMode::ByReference;
				}

				(*paramIt) = Parameter::CreateDesigntime(paramIt->name(), type, paramIt->value(), paramIt->hasDefaultValue(), paramIt->isConst(), access, paramIt->reference());

				signatureChanged = true;
			}
		}

		if ( signatureChanged ) {
			method->setSignature(params);
		}
		// }

		// Update method tokens
		// {
		TokenList tokens = method->getTokens();

		for ( TokenList::iterator tokIt = tokens.begin(); tokIt != tokens.end(); ++tokIt ) {
			if ( tokIt->type() == Token::Type::IDENTIFER ) {
				type = lookupType(tokIt->content(), protoConstraints, constraints);

				if ( type != tokIt->content() ) {
					tokIt->resetContentTo(type);
				}
			}
		}

		method->setTokens(tokens);
		// }

		// add prepared method to new blueprint
		newBlue->defineMethod((*methIt)->getName(), method);
	}

	// add new blueprint to repository
	addBluePrint(newBlue);

	// add new blueprint to parent scope
	IScope* parent = blueprint->getEnclosingScope();
	if ( parent ) {
		parent->define(newBlue->QualifiedTypename(), newBlue);
	}

	return newBlue;
}

/*
 * Creates an instance of the given blueprint
 */
Runtime::Object* Repository::createInstance(const std::string& type, const std::string& name, const PrototypeConstraints& constraints, InitilizationType::E initialize)
{
	BluePrintObjectMap::iterator it = mBluePrintObjects.find(type);
	if ( it == mBluePrintObjects.end() ) {
		// workaround for complex member types whose imports have not yet been analysed
		if ( initialize == InitilizationType::None ) {
			Runtime::Object* object = new Runtime::UserObject(name, SYSTEM_LIBRARY, Designtime::Parser::buildConstraintTypename(type, constraints), true);
			Controller::Instance().memory()->newObject(object);
			return object;
		}

		throw Common::Exceptions::Exception("cannot not create instance of unknown type '" + type + "'");
	}

	return createInstance(it->second, name, constraints, initialize);
}

/*
 * Creates an instance of the given blueprint
 */
Runtime::Object* Repository::createInstance(Designtime::BluePrintGeneric* blueprint, const std::string& name, const PrototypeConstraints& constraints, InitilizationType::E initialize)
{
	if ( !blueprint ) {
		throw Common::Exceptions::Exception("invalid blueprint provided!");
	}

	if ( blueprint->getSymbolType() == Symbol::IType::BluePrintEnumSymbol ) {
		// replace enum blueprint with an integer blueprint
		blueprint = findBluePrint(Runtime::IntegerObject::TYPENAME);
	}

	std::string constraintType = Designtime::Parser::buildConstraintTypename(blueprint->QualifiedTypename(), constraints);

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
		// set global scope as fallback parent
		parent = Controller::Instance().stack()->globalScope();
	}

	object->setFinal(blueprint->isFinal());
	object->setLanguageFeatureState(blueprint->getLanguageFeatureState());
	object->setMember(blueprint->isMember());
	object->setMutability(blueprint->getMutability());
	object->setParent(parent);
	object->setQualifiedOuterface(blueprint->QualifiedTypename());
	object->setQualifiedTypename(blueprint->QualifiedTypename());
	object->setVisibility(blueprint->getVisibility());

	return object;
}

/*
 * Creates an instance of the given blueprint and adds a reference to it in the heap memory
 */
Runtime::Object* Repository::createReference(Designtime::BluePrintGeneric* blueprint, const std::string& name, const PrototypeConstraints& constraints, InitilizationType::E initialize)
{
	if ( !blueprint ) {
		throw Common::Exceptions::Exception("invalid blueprint provided!");
	}

	if ( blueprint->getSymbolType() == Symbol::IType::BluePrintEnumSymbol ) {
		// replace enum blueprint with an integer blueprint
		blueprint = findBluePrint(Runtime::IntegerObject::TYPENAME);
	}

	std::string constraintType = Designtime::Parser::buildConstraintTypename(blueprint->QualifiedTypename(), constraints);

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
	Runtime::Object* object = new Runtime::UserObject(name, blueprint->Filename(), Designtime::Parser::buildConstraintTypename(blueprint->QualifiedTypename(), blueprint->getPrototypeConstraints()));

	if ( initialize >= InitilizationType::AllowAbstract ) {
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
						object->undefine(IDENTIFIER_BASE, 0);

						// create base object
						Runtime::Object *ancestor = createReference(blueIt->second, name, ancestorIt->constraints(), InitilizationType::AllowAbstract);
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
						//Runtime::Object *ancestor = createUserObject(name, blueIt->second, initialize);
						// define ancestor to prevent memleaks
						//object->define(blueIt->second->QualifiedTypename(), ancestor);

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
		Runtime::UserObject* nullObject = new Runtime::UserObject(VALUE_NULL, SYSTEM_LIBRARY, NULL_TYPE, true);
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
void Repository::initializeObject(Runtime::Object* object, Designtime::BluePrintObject* blueprint)
{
	//object->undefine(IDENTIFIER_THIS, 0);

	// create and define all symbols based on given blueprint
	Symbols symbols = blueprint->provideSymbols();
	for ( Symbols::const_iterator it = symbols.begin(); it != symbols.end(); ++it ) {
		if ( it->second->getSymbolType() != Symbol::IType::BluePrintObjectSymbol ) {
			continue;
		}

		Designtime::BluePrintObject* blue = static_cast<Designtime::BluePrintObject*>(it->second);

		Runtime::Object *symbol = createInstance(blue->QualifiedTypename(), blue->getName(), blue->getPrototypeConstraints(), InitilizationType::None);
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
		Runtime::Method* method = new Runtime::Method(object, (*it)->getName(), (*it)->QualifiedTypename());
		*method = *(*it);

		// try to override abstract methods a.k.a. implement an interface method
		Runtime::Method* old = static_cast<Runtime::Method*>(object->resolveMethod((*it)->getName(), method->provideSignature(), true, Visibility::Designtime));
		if ( old && old->isAbstract() ) {
			Runtime::Object* base = dynamic_cast<Runtime::Object*>(object->resolve(IDENTIFIER_BASE, true, Visibility::Designtime));
			base->undefineMethod(old);

			delete old;
		}

		object->defineMethod((*it)->getName(), method);
	}

	object->define(IDENTIFIER_THIS, object);	// define this-symbol
}

std::string Repository::extractType(const PrototypeConstraints& blueprintConstraints, const PrototypeConstraints& implConstraints) const
{
	std::string result;

	for ( PrototypeConstraints::const_iterator blueConIt = blueprintConstraints.begin(); blueConIt != blueprintConstraints.end(); ++blueConIt ) {
		for ( PrototypeConstraints::const_iterator conIt = implConstraints.begin(); conIt != implConstraints.end(); ++conIt ) {
			if ( blueConIt->mIndex == conIt->mIndex ) {
				if ( result.size() ) {
					result += ",";
				}
				result += conIt->mType;
			}
		}
	}

	return "<" + result + ">";
}

std::string Repository::lookupType(const std::string& type, const PrototypeConstraints& blueprintConstraints, const PrototypeConstraints& implConstraints) const
{
	for ( PrototypeConstraints::const_iterator blueConIt = blueprintConstraints.begin(); blueConIt != blueprintConstraints.end(); ++blueConIt ) {
		if ( type == blueConIt->mType ) {
			for ( PrototypeConstraints::const_iterator conIt = implConstraints.begin(); conIt != implConstraints.end(); ++conIt ) {
				if ( blueConIt->mIndex == conIt->mIndex ) {
					return conIt->mType;
				}
			}
		}
	}

	return type;
}


}
