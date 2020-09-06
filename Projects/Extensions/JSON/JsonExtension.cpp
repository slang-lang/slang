
// Header
#include "JsonExtension.h"

// Library includes

// Project includes
#include <Defines.h>
#include "FromJson.h"
#include "ToJson.h"

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace Json {


JsonExtension::JsonExtension()
: AExtension( "Json", "0.0.1" )
{
}

void JsonExtension::initialize( IScope* /*scope*/ )
{
	// nothing to do here
}

void JsonExtension::provideMethods( ExtensionMethods& methods )
{
	assert( methods.empty() );

	methods.push_back( new FromJson() );
	methods.push_back( new ToJson() );
}


}
}
}
