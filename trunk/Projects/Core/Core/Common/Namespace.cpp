
// Header
#include "Namespace.h"

// Library includes

// Project includes
#include "Method.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Common {


Namespace::Namespace(const std::string& name, IScope* parent)
: MethodScope(name, parent),
  NamespaceSymbol(name),
  mTypename(name)
{
}

Namespace::~Namespace()
{
	MethodCollection tmpMethods = mMethods;
	Symbols tmpSymbols = mSymbols;

	for ( MethodCollection::iterator methIt = tmpMethods.begin(); methIt != tmpMethods.end(); ++methIt ) {
		for ( Symbols::iterator symIt = tmpSymbols.begin(); symIt != tmpSymbols.end(); ++symIt ) {
			if ( symIt->second == (*methIt) ) {
				mSymbols.erase(symIt->first);
			}
		}

		mMethods.erase((*methIt));
		delete (*methIt);
	}

	tmpSymbols = mSymbols;
	for ( Symbols::iterator symIt = tmpSymbols.begin(); symIt != tmpSymbols.end(); ++symIt) {
		if ( symIt->second ) {
			switch ( symIt->second->getSymbolType() ) {
				case Symbol::IType::NamespaceSymbol:
					delete symIt->second;
					symIt->second = 0;

					mSymbols.erase(symIt->first);
					break;
				default:
					break;
			}
		}
	}
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
			case Symbol::IType::UnknownSymbol:
				continue;
			case Symbol::IType::MethodSymbol:
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
