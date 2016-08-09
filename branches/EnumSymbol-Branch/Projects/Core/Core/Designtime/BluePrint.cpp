
// Header
#include "BluePrint.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Object.h>
#include <Core/Utils/Exceptions.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


BluePrint::BluePrint()
: MethodScope(ANONYMOUS_OBJECT, 0),
  BluePrintSymbol(ANONYMOUS_OBJECT),
  mIsInterface(false),
  mVisibility(Visibility::Public)
{
	mName = ANONYMOUS_OBJECT;
}

BluePrint::BluePrint(const std::string& type, const std::string& filename, const std::string& name)
: BluePrintGeneric(type, filename),
  MethodScope(type, 0),
  BluePrintSymbol(type),
  mIsInterface(false),
  mVisibility(Visibility::Public)
{
	mName = name;
}

BluePrint::~BluePrint()
{
}

void BluePrint::addInheritance(const Designtime::Ancestor& inheritance)
{
	if ( inheritance.name().empty() ) {
		throw Utils::Exceptions::Exception("invalid inheritance added");
	}

	mInheritance.insert(inheritance);
}

void BluePrint::cleanup()
{
	for ( MethodCollection::iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		undefine((*it)->getName(), (*it));

		delete (*it);
	}
	mMethods.clear();

	for ( Symbols::iterator it = mSymbols.begin(); it != mSymbols.end(); ++it ) {
		if ( it->first == IDENTIFIER_BASE || it->first == IDENTIFIER_THIS || !it->second ) {
			continue;
		}

		if ( it->second->getSymbolType() == Symbol::IType::BluePrintSymbol ) {
			static_cast<BluePrint*>(it->second)->cleanup();
		}

		delete it->second;
	}
	mSymbols.clear();
}

Designtime::Ancestors BluePrint::getAncestors() const
{
	Designtime::Ancestors ancestors;

	for ( Designtime::Ancestors::const_iterator it = mInheritance.begin(); it != mInheritance.end(); ++it ) {
		if ( it->type() == Designtime::Ancestor::Type::Extends ) {
			ancestors.insert((*it));
		}
	}

	return ancestors;
}

Designtime::Ancestors BluePrint::getInheritance() const
{
	return mInheritance;
}

Designtime::Ancestors BluePrint::getImplementations() const
{
	Designtime::Ancestors implementations;

	for ( Designtime::Ancestors::const_iterator it = mInheritance.begin(); it != mInheritance.end(); ++it ) {
		if ( it->type() == Designtime::Ancestor::Type::Implements ) {
			implementations.insert((*it));
		}
	}

	return implementations;
}

Runtime::AtomicValue BluePrint::getValue() const
{
	return mValue;
}

Visibility::E BluePrint::getVisibility() const
{
	return mVisibility;
}

bool BluePrint::isAbstract() const
{
	for ( MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		if ( (*it)->isAbstract() ) {
			return true;
		}
	}

	return ObjectAttributes::isAbstract();
}

bool BluePrint::isInterface() const
{
	return mIsInterface;
}

void BluePrint::setAbstract(bool state)
{
	mIsAbstract = state;
}

void BluePrint::setInterface(bool state)
{
	mIsInterface = state;
}

void BluePrint::setParent(IScope* parent)
{
	mParent = parent;
}

void BluePrint::setValue(Runtime::AtomicValue value)
{
	mValue = value;
}

void BluePrint::setVisibility(Visibility::E v)
{
	mVisibility = v;
}

std::string BluePrint::ToString() const
{
	return Typename() + " " + getName();
}


}
}
