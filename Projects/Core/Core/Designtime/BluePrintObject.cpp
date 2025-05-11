
// Header
#include "BluePrintObject.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Common/Method.h>
#include <Core/Consts.h>
#include <Core/Designtime/Parser/Parser.h>
#include <Core/VirtualMachine/Repository.h>
#include <Tools/Strings.h>
#include "Exceptions.h"

// Namespace declarations


namespace Slang {
namespace Designtime {


BluePrintObject* BluePrintObject::FromParent(BluePrintObject* parent, const std::string& unqualifiedTypename, const std::string& filename)
{
	auto* newBluePrint = new BluePrintObject( unqualifiedTypename, filename );

	for ( auto& method : parent->mMethods ) {
		auto* newMethod = new Common::Method( parent, method->getName(), Common::TypeDeclaration(method->QualifiedTypename()) );
		*newMethod = *method;

		newBluePrint->defineMethod( method->getName(), newMethod );
	}

	for ( auto& symbolIt : parent->mSymbols ) {
		Symbol* symbol = nullptr;

		switch ( symbolIt.second->getSymbolType() ) {
			case Symbol::IType::BluePrintObjectSymbol:
			case Symbol::IType::ObjectSymbol:
				*symbol = *symbolIt.second;
				break;
			default:
				continue;
		}

		newBluePrint->define( symbolIt.first, symbol );
	}

	return newBluePrint;
}


BluePrintObject::BluePrintObject()
: BlueprintSymbol(ANONYMOUS_OBJECT),
  MethodScope(ANONYMOUS_OBJECT, nullptr),
  mIsAtomicType(false),
  mFilename(ANONYMOUS_OBJECT),
  mIsPrepared(false),
  mIsReference(false),
  mQualifiedTypename(ANONYMOUS_OBJECT),
  mUnqualifiedTypename(ANONYMOUS_OBJECT)
{
	mName = ANONYMOUS_OBJECT;
	mType = Symbol::IType::BluePrintObjectSymbol;
}

BluePrintObject::BluePrintObject(const std::string& unqualifiedTypename, std::string filename, const std::string& name)
: BlueprintSymbol(unqualifiedTypename),
  MethodScope(unqualifiedTypename, nullptr),
  mIsAtomicType(false),
  mFilename(std::move(filename)),
  mIsPrepared(false),
  mIsReference(false),
  mQualifiedTypename(unqualifiedTypename),
  mUnqualifiedTypename(unqualifiedTypename)
{
	mName = name;
	mType = Symbol::IType::BluePrintObjectSymbol;
}

void BluePrintObject::addInheritance(const Designtime::Ancestor& inheritance)
{
	if ( inheritance.name().empty() ) {
		throw Common::Exceptions::Exception("invalid inheritance added");
	}

	mInheritance.insert(inheritance);
}

void BluePrintObject::defineMethod(const std::string& name, Common::Method* method)
{
	// try to override abstract methods a.k.a. implement an interface method
	auto* oldMethod = dynamic_cast<Common::Method*>(resolveMethod(method->getName(), method->provideSignature(), true, Visibility::Designtime));
	if ( oldMethod ) {
		if ( oldMethod->getMemoryLayout() != MemoryLayout::Abstract && oldMethod->getMemoryLayout() != MemoryLayout::Virtual ) {
			throw Exceptions::SyntaxError("Method '" + oldMethod->getFullScopeName() + "' is not abstract or marked with " + std::string(Slang::MEMORY_LAYOUT_VIRTUAL ) );
		}
		if ( method->getMethodType() == MethodType::Method && method->getMemoryLayout() != MemoryLayout::Abstract && method->getMemoryLayout() != MemoryLayout::Override ) {
			throw Exceptions::SyntaxError( "Overriding method '" + method->getFullScopeName() + "' is not marked with " + std::string( Slang::MEMORY_LAYOUT_OVERRIDE ) );
		}

		// compare methods
		if ( oldMethod->isConst() != method->isConst() ) {
			throw Exceptions::SyntaxError("Overriding method '" + method->getFullScopeName() + "' has different return value then base method'" );
		}
		if ( oldMethod->isConstMethod() != method->isConstMethod() ) {
			throw Exceptions::SyntaxError("Overriding method '" + method->getFullScopeName() + "' has different mutability then base method" );
		}
		if ( oldMethod->isFinalMethod() ) {
			throw Exceptions::SyntaxError("Method '" + oldMethod->getFullScopeName() + "' is marked with " + std::string(Slang::MEMORY_LAYOUT_FINAL ) + " and cannot be overwritten" );
		}
		if ( oldMethod->isStatic() ) {
			throw Exceptions::SyntaxError("Method '" + oldMethod->getFullScopeName() + "' is marked with " + std::string(Slang::MEMORY_LAYOUT_STATIC ) + " and cannot be overwritten" );
		}
		if ( oldMethod->QualifiedTypename() != method->QualifiedTypename() ) {
			throw Exceptions::SyntaxError("Overriding method '" + method->getFullScopeName() + "' has different return value then base method" );
		}

		// removed old method
		// {
		undefineMethod(oldMethod);

		delete oldMethod;
		// }
	}

	MethodScope::defineMethod(name, method);
}

const std::string& BluePrintObject::Filename() const
{
	return mFilename;
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

Ancestors BluePrintObject::getAncestors() const
{
	Ancestors ancestors;

	for ( const auto& it : mInheritance ) {
		if ( it.ancestorType() == Ancestor::Type::Extends ) {
			ancestors.insert(it);
		}
	}

	return ancestors;
}

Ancestors BluePrintObject::getInheritance() const
{
	return mInheritance;
}

Ancestors BluePrintObject::getImplementations() const
{
	Ancestors implementations;

	for ( const auto& it : mInheritance ) {
		if ( it.ancestorType() == Ancestor::Type::Implements ) {
			implementations.insert(it);
		}
	}

	return implementations;
}

const PrototypeConstraints& BluePrintObject::getPrototypeConstraints() const
{
	return mPrototypeConstraints;
}

const TokenList& BluePrintObject::getTokens() const
{
	return mTokens;
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

bool BluePrintObject::inheritsFrom(const std::string& type) const
{
	for ( const auto& it : mInheritance ) {
		if ( it.name() == type ) {
			return true;
		}
	}

	return false;
}

bool BluePrintObject::isAtomicType() const
{
	return mIsAtomicType;
}

bool BluePrintObject::isAbstract() const
{
	return mBluePrintType == BlueprintType::Interface || mMemoryLayout == MemoryLayout::Abstract;
}

bool BluePrintObject::isEnumeration() const
{
	return mBluePrintType == BlueprintType::Enum;
}

bool BluePrintObject::isInterface() const
{
	return mBluePrintType == BlueprintType::Interface;
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

bool BluePrintObject::isPrototype() const
{
	return !mPrototypeConstraints.empty();
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

const std::string& BluePrintObject::QualifiedTypename() const
{
	return mQualifiedTypename;
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

void BluePrintObject::setPrototypeConstraints(const PrototypeConstraints& constraints)
{
	mPrototypeConstraints = constraints;
}

void BluePrintObject::setQualifiedTypename(const std::string& name)
{
	mQualifiedTypename = name;
}

void BluePrintObject::setTokens(const TokenList& tokens)
{
	mTokens = tokens;
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
