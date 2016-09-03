
// Header
#include "Namespace.h"

// Library includes

// Project includes
#include <Core/Method.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


Namespace::Namespace(const std::string& name, IScope* parent)
: MethodScope(name, parent),
  NamespaceSymbol(name),
  mTypename(name)
{
}

Namespace::~Namespace()
{
	for ( MethodCollection::iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		undefine((*it)->getName(), (*it));

		delete (*it);
	}
	mMethods.clear();

	for ( Symbols::reverse_iterator it = mSymbols.rbegin(); it != mSymbols.rend(); ) {
		if ( it->second ) {
			switch ( it->second->getSymbolType() ) {
				case Symbol::IType::NamespaceSymbol:
					delete it->second;
					it->second = 0;
					break;
				default:
					break;
			}
		}

		undefine(it->first, it->second);
	}
	mSymbols.clear();
}

std::string Namespace::ToString(unsigned int indent) const
{
	std::string result = Visibility::convert(mVisibility) + " " + RESERVED_WORD_NAMESPACE + " " + getName();

	result += " {\n";

	for ( MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		result += "\t" + (*it)->ToString(indent) + "\n";
	}

	for ( Symbols::const_iterator it = mSymbols.begin(); it != mSymbols.end(); ++it ) {
		switch ( it->second->getSymbolType() ) {
			case Symbol::IType::BluePrintEnumSymbol:
			case Symbol::IType::BluePrintObjectSymbol:
			case Symbol::IType::MethodSymbol:
			case Symbol::IType::UnknownSymbol:
				continue;
			case Symbol::IType::NamespaceSymbol:
			case Symbol::IType::ObjectSymbol:
				result += "\t" + it->second->ToString(indent) + "\n";
				break;
		}
	}

	result += "}";

	return result;
}


}
}
