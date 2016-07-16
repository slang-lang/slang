
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
  mTypename(RESERVED_WORD_NAMESPACE)
{
}

Namespace::~Namespace()
{
}

std::string Namespace::ToString() const
{
	std::string result = Visibility::convert(mVisibility) + " " + Typename() + " " + getName();

	result += " {\n";

	for ( MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		result += "\t" + (*it)->ToString() + "\n";
	}

	for ( Symbols::const_iterator it = mSymbols.begin(); it != mSymbols.end(); ++it ) {
		switch ( it->second->getSymbolType() ) {
			case Symbol::IType::BluePrintSymbol:
			case Symbol::IType::MethodSymbol:
			case Symbol::IType::UnknownSymbol:
				continue;
			case Symbol::IType::NamespaceSymbol:
			case Symbol::IType::ObjectSymbol:
				result += "\t" + it->second->ToString() + "\n";
				break;
		}
	}

	result += "}";

	return result;
}


}
}
