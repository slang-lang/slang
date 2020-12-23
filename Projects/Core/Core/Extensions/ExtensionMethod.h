
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
			 Mutability::E mutabilty = Mutability::Const,
			 MemoryLayout::E memoryLayout = MemoryLayout::Static,
			 LanguageFeatureState::E languageFeatureState = LanguageFeatureState::Stable )
	: Common::Method( parent, name, Common::TypeDeclaration( type ) )
	{
		mIsExtensionMethod = true;
		mLanguageFeatureState = languageFeatureState;
		mMemoryLayout = memoryLayout;
		mMethodMutability = mutabilty;
		mMutability = Mutability::Modify;
	}

	virtual Runtime::ControlFlow::E execute( Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token ) = 0;
};

typedef std::list<ExtensionMethod*> ExtensionMethods;


}
}


#endif
