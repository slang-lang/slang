
#ifndef Slang_Core_Core_Extensions_ExtensionMethod_h
#define Slang_Core_Core_Extensions_ExtensionMethod_h


// Library includes
#include <list>
#include <string>

// Project includes
#include <Core/Common/Method.h>
#include <Core/Common/Types.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {


class ExtensionMethod : public Common::Method
{
public:
	ExtensionMethod( IScope* parent,
					 const std::string& name,
					 const std::string& type,
					 Mutability::E mutability = Mutability::Const,
					 MemoryLayout::E memoryLayout = MemoryLayout::Static,
					 LanguageFeatureState::E languageFeatureState = LanguageFeatureState::Stable )
	: Common::Method( parent, name, Common::TypeDeclaration( type ) )
	{
		mIsExtensionMethod    = true;
		mLanguageFeatureState = languageFeatureState;
		mMemoryLayout         = memoryLayout;
		mMethodMutability     = mutability;
		mMutability           = Mutability::Modify;
	}

	virtual Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result ) = 0;
};

typedef std::list<ExtensionMethod*> ExtensionMethods;


}
}


#endif
