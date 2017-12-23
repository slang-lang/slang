
// Header
#include "BluePrintObject.h"

// Library includes

// Project includes
#include <Core/Common/Method.h>
#include <Parser/Parser.h>
#include <Tools/Strings.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


BluePrintObject::BluePrintObject()
: MethodScope(ANONYMOUS_OBJECT, 0),
  mIsReference(false)
{
	mName = ANONYMOUS_OBJECT;
	mType = Symbol::IType::BluePrintObjectSymbol;
}

BluePrintObject::BluePrintObject(const std::string& type, const std::string& filename, const std::string& name)
: BluePrintGeneric(type, filename),
  MethodScope(type, 0),
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
	std::string constraintType = Designtime::Parser::buildRuntimeConstraintTypename(QualifiedTypename(), constraints);

	BluePrintObject* prototype = replicate(constraintType, mFilename);

	// blueprint data
	prototype->setPrototypeConstraints(PrototypeConstraints());

	// inheritance should be fine

	// update members
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

	// update methods
	StringSet atomicTypes = provideAtomicTypes();

	MethodScope::MethodCollection methods = prototype->provideMethods();
	for ( MethodScope::MethodCollection::const_iterator it = methods.begin(); it != methods.end(); ++it ) {
		Common::Method* method = (*it);

		// Prepare return value
		// {
		std::string type = constraints.lookupType(method->QualifiedTypename());
		if ( !method->getPrototypeConstraints().empty() ) {
			type += constraints.extractTypes(method->getPrototypeConstraints());

			method->setPrototypeConstraints(PrototypeConstraints());	// reset prototype constraints
		}

		method->setQualifiedTypename(type);
		// }

		// Update method signature
		// {
		bool signatureChanged = false;

		ParameterList params = method->provideSignature();
		for ( ParameterList::iterator paramIt = params.begin(); paramIt != params.end(); ++paramIt ) {
			type = constraints.lookupType(paramIt->type());
			if ( paramIt->typeConstraints().size() ) {
				type += constraints.extractTypes(paramIt->typeConstraints());
			}

			if ( paramIt->type() != type ) {
				AccessMode::E access = AccessMode::ByValue;

				if ( atomicTypes.find(type) == atomicTypes.end() ) {
					access = AccessMode::ByReference;
				}

				(*paramIt) = Parameter::CreateDesigntime(paramIt->name(),
														 type,
														 paramIt->value(),
														 paramIt->hasDefaultValue(),
														 paramIt->mutability(),
														 access);

				signatureChanged = true;
			}
		}

		if ( signatureChanged ) {
			method->setSignature(params);
		}
		// }

		// Update method tokens
		// {
		bool tokenChanged = false;

		TokenList tokens = method->getTokens();
		for ( TokenList::iterator tokIt = tokens.begin(); tokIt != tokens.end(); ++tokIt ) {
			if ( tokIt->type() == Token::Type::IDENTIFIER ) {
				type = constraints.lookupType(tokIt->content());

				if ( type != tokIt->content() ) {
					tokIt->resetContentTo(type);

					tokenChanged = true;
				}
			}
		}

		if ( tokenChanged ) {
			method->setTokens(tokens);
		}
		// }
	}

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

bool BluePrintObject::isIterable() const
{
	ParameterList params;

/*	this has to be used as soon as 'this' is passed to methods as first parameter
	params.push_back(
		Parameter::CreateDesigntime(IDENTIFIER_THIS, Common::TypeDeclaration(QualifiedTypename(), getPrototypeConstraints()))
	);
*/

	for ( MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		if ( (*it)->getName() == "getIterator" &&  (*it)->isSignatureValid(params) ) {
			return true;
		}
	}

	return false;
}

bool BluePrintObject::isReference() const
{
	return mIsReference;
}

MethodScope::MethodCollection BluePrintObject::provideMethods() const
{
	return mMethods;
}

Symbols BluePrintObject::provideSymbols() const
{
	return mSymbols;
}

BluePrintObject* BluePrintObject::replicate(const std::string& newType, const std::string& filename) const
{
	BluePrintObject* replica = new BluePrintObject(newType, filename);

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

		Designtime::BluePrintObject* blue = static_cast<Designtime::BluePrintObject*>(symIt->second);

		Designtime::BluePrintObject* member = new Designtime::BluePrintObject(blue->QualifiedTypename(), blue->Filename(), blue->getName());
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
