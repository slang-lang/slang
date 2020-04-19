
// Header
#include "Namespace.h"

// Library includes

// Project includes
#include <Tools/Strings.h>
#include "Method.h"

// Namespace declarations


namespace Slang {
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

void Namespace::defineMethod(const std::string& name, Common::Method* method)
{
	MethodScope::defineMethod(name, method);

	method->initialize();
}

std::string Namespace::ToString(unsigned int indent) const
{
	std::string result;

	result += ::Utils::Tools::indent(indent);
	result += Visibility::convert(mVisibility);
	result += " " + LanguageFeatureState::convert(mLanguageFeatureState);
	result += " " + std::string(RESERVED_WORD_NAMESPACE) + " " + getName();
	result += " " + Mutability::convert(mMutability);
	result += " {\n";

	for ( Symbols::const_iterator it = mSymbols.begin(); it != mSymbols.end(); ++it ) {
		switch ( it->second->getSymbolType() ) {
			case Symbol::IType::BluePrintObjectSymbol:
				continue;
			case Symbol::IType::MethodSymbol:
			case Symbol::IType::NamespaceSymbol:
			case Symbol::IType::ObjectSymbol:
				result += it->second->ToString(indent + 1) + "\n";
				break;
		}
	}

	result += ::Utils::Tools::indent(indent) + "}";

	return result;
}


}
}
