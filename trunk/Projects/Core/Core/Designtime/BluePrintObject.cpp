
// Header
#include "BluePrintObject.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Common/Method.h>
#include <Core/Designtime/Parser/Parser.h>
#include <Core/VirtualMachine/Repository.h>
#include <Tools/Strings.h>
#include <Utils.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


BluePrintObject::BluePrintObject()
: MethodScope(ANONYMOUS_OBJECT, 0),
  mIsEnumeration(false),
  mIsPrepared(false),
  mIsReference(false)
{
	mName = ANONYMOUS_OBJECT;
	mType = Symbol::IType::BluePrintObjectSymbol;
}

BluePrintObject::BluePrintObject(const std::string& type, const std::string& filename, const std::string& name)
: BluePrintGeneric(type, filename),
  MethodScope(type, 0),
  mIsEnumeration(false),
  mIsPrepared(false),
  mIsReference(false)
{
	mName = name;
	mType = Symbol::IType::BluePrintObjectSymbol;
}

BluePrintObject::~BluePrintObject()
{
}

BluePrintObject* BluePrintObject::fromPrototype(const PrototypeConstraints& constraints) const
{
	// generate a new blueprint from our prototype
	BluePrintObject* prototype = replicate(Designtime::Parser::buildRuntimeConstraintTypename(QualifiedTypename(), constraints), mFilename);

	// set base type
	prototype->mBasedOnType = QualifiedTypename();

	// clear prototype constraints
	prototype->setPrototypeConstraints(PrototypeConstraints());

	// update members
	// {
	Symbols symbols = prototype->provideSymbols();
	for ( Symbols::const_iterator symIt = symbols.begin(); symIt != symbols.end(); ++symIt ) {
		if ( symIt->second->getSymbolType() != Symbol::IType::BluePrintObjectSymbol ) {
			continue;
		}

		Designtime::BluePrintObject* blue = static_cast<Designtime::BluePrintObject*>(symIt->second);

		if ( blue->isPrototype() ) {
			blue->setPrototypeConstraints(
				blue->getPrototypeConstraints().buildRuntimeConstraints(constraints)
			);
		}
		else {
			std::string type = constraints.lookupType(blue->QualifiedTypename());

			blue->setPrototypeConstraints(PrototypeConstraints());
			blue->setQualifiedTypename(type);
		}
	}
	// }

	// update methods
	// {
	MethodScope::MethodCollection methods = prototype->provideMethods();
	for ( MethodScope::MethodCollection::const_iterator it = methods.begin(); it != methods.end(); ++it ) {
		Common::Method* method = (*it);

		method->initialize(constraints);
	}
	// }

	return prototype;
}

Runtime::AtomicValue BluePrintObject::getValue() const
{
	return mValue;
}

bool BluePrintObject::hasConstructor() const
{
	// return any (private, protected, public) constructor with or without parameters or only default parameters
	Symbol* constructor = resolve(CONSTRUCTOR, true, Visibility::Private);
	if ( constructor && dynamic_cast<class MethodSymbol*>(constructor) ) {
		return true;
	}

	return false;
}

bool BluePrintObject::hasDefaultConstructor() const
{
	// return any (private, protected, public) constructor that has no parameters or only default parameters
	return resolveMethod(CONSTRUCTOR, ParameterList(), true, Visibility::Private) != NULL;
}

bool BluePrintObject::isEnumeration() const
{
	return mIsEnumeration;
}

bool BluePrintObject::isIterable() const
{
	ParameterList params;

	for ( MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		if ( (*it)->getName() == "getIterator" &&  (*it)->isSignatureValid(params) ) {
			return true;
		}
	}

	return false;
}

bool BluePrintObject::isOfType(const std::string& type) const
{
	if ( mQualifiedTypename == type || mBasedOnType == type ) {
		return true;
	}

	return inheritsFrom(type);
}

bool BluePrintObject::isPrepared() const
{
	return mIsPrepared;
}

bool BluePrintObject::isReference() const
{
	return mIsReference;
}

void BluePrintObject::prepareParents(Repository* repository)
{
	Ancestors ancestors = getAncestors();
	for ( Ancestors::const_iterator it = ancestors.begin(); it != ancestors.end(); ++it ) {
		BluePrintObject* parent = repository->findBluePrintObject(it->typeDeclaration());

		if ( !parent ) {
			throw Common::Exceptions::UnknownIdentifer("Unknown parent identifier '" + it->typeDeclaration().mName + "'");
		}

		if ( !parent->isPrepared() ) {
			// recursively prepare parent objects
			parent->prepareParents(repository);
		}

		// locally define parent's public and protected symbols
		Symbols symbols = parent->provideSymbols();
		for ( Symbols::const_iterator symIt = symbols.begin(); symIt != symbols.end(); ++symIt ) {
			if ( symIt->second->getVisibility() >= Visibility::Protected ) {
				defineExternal(symIt->first, symIt->second);
			}
		}

		// locally define parent's public and protected methods
		MethodCollection methods = parent->provideMethods();
		for ( MethodCollection::const_iterator methIt = methods.begin(); methIt != methods.end(); ++methIt ) {
			if ( (*methIt)->getVisibility() >= Visibility::Protected ) {
				defineExternalMethod((*methIt)->QualifiedTypename(), (*methIt));
			}
		}
	}

	mIsPrepared = true;
}

MethodScope::MethodCollection BluePrintObject::provideMethods() const
{
	return mMethods;
}

Symbols BluePrintObject::provideSymbols() const
{
	return mSymbols;
}

BluePrintObject* BluePrintObject::replicate(const std::string& newType, const std::string& filename, BluePrintObject* target) const
{
	BluePrintObject* replica = target ? target : new BluePrintObject(newType, filename);

	// set base type
	replica->mBasedOnType = QualifiedTypename();

	// replicate basic blueprint data
	replica->setConst(isConst());
	replica->setImplementationType(getImplementationType());
	replica->setLanguageFeatureState(getLanguageFeatureState());
	replica->setMember(isMember());
	replica->setMemoryLayout(getMemoryLayout());
	replica->setMutability(getMutability());
	replica->setParent(getEnclosingScope());
	replica->setPrototypeConstraints(getPrototypeConstraints());
	replica->setSealed(isSealed());
	replica->setTokens(getTokens());
	replica->setValue(getValue());
	replica->setVisibility(getVisibility());

	// replicate inheritance
	Designtime::Ancestors ancestors = getInheritance();
	for ( Designtime::Ancestors::const_iterator it = ancestors.begin(); it != ancestors.end(); ++it ) {
		replica->addInheritance(Designtime::Ancestor(
			Common::TypeDeclaration((*it).name(), (*it).constraints()),
			(*it).ancestorType(),
			(*it).visibility()
		));
	}

	// replicate members
	for ( Symbols::const_iterator symIt = mSymbols.begin(); symIt != mSymbols.end(); ++symIt ) {
		if ( symIt->second->getSymbolType() != Symbol::IType::BluePrintObjectSymbol ) {
			continue;
		}

		Designtime::BluePrintObject* blue = dynamic_cast<Designtime::BluePrintObject*>(symIt->second);

		Designtime::BluePrintObject* member = new Designtime::BluePrintObject(blue->QualifiedTypename(), blue->Filename(), blue->getName());
		member->setIsEnumeration(blue->isEnumeration());
		member->setLanguageFeatureState(blue->getLanguageFeatureState());
		member->setMember(blue->isMember());
		member->setMemoryLayout(blue->getMemoryLayout());
		member->setMutability(blue->getMutability());
		member->setParent(replica);
		member->setPrototypeConstraints(blue->getPrototypeConstraints());
		member->setQualifiedTypename(blue->QualifiedTypename());
		member->setValue(blue->getValue());
		member->setVisibility(blue->getVisibility());

		replica->define(blue->getName(), member);
	}

	// replicate methods
	for ( MethodScope::MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		// create new method and ...
		Common::Method* method = new Common::Method(replica, (*it)->getName(), (*it)->QualifiedTypename());
		// ... copy its data from our template method
		*method = *(*it);

		replica->defineMethod((*it)->getName(), method);
	}

	return replica;
}

void BluePrintObject::setIsEnumeration(bool state)
{
	mIsEnumeration = state;
}

void BluePrintObject::setIsReference(bool state)
{
	mIsReference = state;
}

void BluePrintObject::setParent(IScope* parent)
{
	mParent = parent;
}

void BluePrintObject::setValue(Runtime::AtomicValue value)
{
	mValue = value;
}

std::string BluePrintObject::ToString(unsigned int indent) const
{
	return ::Utils::Tools::indent(indent) + QualifiedTypename() + " " + getName();
}


}
}
