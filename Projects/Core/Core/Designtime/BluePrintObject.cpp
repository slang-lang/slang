
// Header
#include "BluePrintObject.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Common/Method.h>
#include <Core/Designtime/Parser/Parser.h>
#include <Core/VirtualMachine/Repository.h>
#include <Tools/Strings.h>
#include "Exceptions.h"

// Namespace declarations


namespace Slang {
namespace Designtime {


BluePrintObject::BluePrintObject()
: MethodScope(ANONYMOUS_OBJECT, nullptr),
  mIsPrepared(false),
  mIsReference(false)
{
	mName = ANONYMOUS_OBJECT;
	mType = Symbol::IType::BluePrintObjectSymbol;
}

BluePrintObject::BluePrintObject(const std::string& type, const std::string& filename, const std::string& name)
: BluePrintGeneric(type, filename),
  MethodScope(type, nullptr),
  mIsPrepared(false),
  mIsReference(false)
{
	mName = name;
	mType = Symbol::IType::BluePrintObjectSymbol;
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

		auto* blue = dynamic_cast<Designtime::BluePrintObject*>(symIt->second);

		if ( blue->isPrototype() ) {
			blue->setPrototypeConstraints(
				blue->getPrototypeConstraints().buildRuntimeConstraints(constraints)
			);
		}
		else {
			const std::string& type = constraints.lookupType(blue->QualifiedTypename());

			blue->setPrototypeConstraints(PrototypeConstraints());
			blue->setQualifiedTypename(type);
		}
	}
	// }

	// update methods
	// {
	MethodScope::MethodCollection methods = prototype->provideMethods();
	for ( auto& method : methods ) {
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
	Symbol* constructor = resolve(RESERVED_WORD_CONSTRUCTOR, true, Visibility::Private);
	if ( constructor && dynamic_cast<class MethodSymbol*>(constructor) ) {
		return true;
	}

	return false;
}

bool BluePrintObject::hasDefaultConstructor() const
{
	// return any (private, protected, public) constructor that has no parameters or only default parameters
	return resolveMethod(RESERVED_WORD_CONSTRUCTOR, ParameterList(), true, Visibility::Private) != nullptr;
}

bool BluePrintObject::isEnumeration() const
{
	return mBluePrintType == BlueprintType::Enum;
}

bool BluePrintObject::isIterable() const
{
	ParameterList params;

	if ( isOfType("ICollection") ) {
	    return true;
	}

	for ( auto& mMethod : mMethods ) {
		if ( mMethod->getName() == "getIterator" && mMethod->isSignatureValid(params) ) {
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
/*
	// collect all parents
	// {
	bool foundNewParents = false;
	std::set<std::string> tmpAncestors;

	do {
		foundNewParents = false;

		for ( Ancestors::iterator it = mInheritance.begin(); it != mInheritance.end(); ++it ) {
			BluePrintObject* parent = repository->findBluePrintObject(it->typeDeclaration());

			Ancestors tmpInheritance = parent->getInheritance();
			for ( Ancestors::iterator tmpIt = tmpInheritance.begin(); tmpIt != tmpInheritance.end(); ++tmpIt ) {
				std::pair<std::set<std::string>::iterator, bool> insert = tmpAncestors.insert( tmpIt->name() );

				if ( insert.second ) {
					// a new ancestor has been inserted
					foundNewParents = true;

					mInheritance.insert( *tmpIt );
				}
			}
		}
	} while ( foundNewParents );
	// }
*/

	for ( const auto& it : mInheritance ) {
		BluePrintObject* parent = repository->findBluePrintObject(it.typeDeclaration());

		if ( !parent ) {
			throw Common::Exceptions::UnknownIdentifier("Unknown parent identifier '" + it.typeDeclaration().mName + "'");
		}

		// detect circular inheritance
		if ( parent->inheritsFrom(QualifiedTypename()) ) {
			throw Exceptions::DesigntimeException("Circular inheritance detected for type '" + QualifiedTypename() + "'!");
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
		for ( auto& method : methods ) {
			if ( method->getVisibility() >= Visibility::Protected ) {
				defineExternalMethod(method->QualifiedTypename(), method);
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
	replica->setBluePrintType(getBluePrintType());
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
	for ( const auto& ancestor : ancestors ) {
		replica->addInheritance(Designtime::Ancestor(
			Common::TypeDeclaration(ancestor.name(), ancestor.constraints()),
			ancestor.ancestorType(),
			ancestor.visibility()
		));
	}

	// replicate members
	for ( const auto& mSymbol : mSymbols ) {
		if ( mSymbol.second->getSymbolType() != Symbol::IType::BluePrintObjectSymbol ) {
			continue;
		}

		auto* blue = dynamic_cast<Designtime::BluePrintObject*>(mSymbol.second);

		auto* member = new Designtime::BluePrintObject(blue->QualifiedTypename(), blue->Filename(), blue->getName());
		member->setBluePrintType(BlueprintType::Enum);
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
	for ( auto& mMethod : mMethods ) {
		// create new method and ...
		auto* method = new Common::Method(replica, mMethod->getName(), Common::TypeDeclaration(mMethod->QualifiedTypename()));
		// ... copy its data from our template method
		*method = *mMethod;

		replica->defineMethod(mMethod->getName(), method);
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

void BluePrintObject::setValue(const Runtime::AtomicValue& value)
{
	mValue = value;
}

std::string BluePrintObject::ToString(unsigned int indent) const
{
	return ::Utils::Tools::indent(indent) + QualifiedTypename() + " " + getName();
}


}
}
