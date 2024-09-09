
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

	for ( auto& tmpMethod : tmpMethods ) {
		for ( auto& tmpSymbol : tmpSymbols ) {
			if ( tmpSymbol.second == tmpMethod ) {
				mSymbols.erase(tmpSymbol.first);
			}
		}

		mMethods.erase(tmpMethod);
		delete tmpMethod;
	}

	tmpSymbols = mSymbols;
	for ( auto& tmpSymbol : tmpSymbols ) {
		if ( tmpSymbol.second ) {
			switch ( tmpSymbol.second->getSymbolType() ) {
				case Symbol::IType::NamespaceSymbol:
					delete tmpSymbol.second;
					tmpSymbol.second = 0;

					mSymbols.erase(tmpSymbol.first);
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

	for ( const auto& symbol : mSymbols ) {
		switch ( symbol.second->getSymbolType() ) {
			case Symbol::IType::BluePrintObjectSymbol:
				continue;
			case Symbol::IType::MethodSymbol:
			case Symbol::IType::NamespaceSymbol:
			case Symbol::IType::ObjectSymbol:
				result += symbol.second->ToString(indent + 1) + "\n";
				break;
		}
	}

	result += ::Utils::Tools::indent(indent) + "}";

	return result;
}


}
}
