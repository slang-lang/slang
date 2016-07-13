
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
	std::string result;

	for ( MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		result += (*it)->ToString();
	}

	for ( Symbols::const_iterator it = mSymbols.begin(); it != mSymbols.end(); ) {
		result += (*it).second->ToString();
	}

	return result;
}


}
}
