
// Header
#include "Method.h"

// Library includes

// Project includes
#include <Core/AST/Statement.h>
#include <Core/Designtime/Parser/Parser.h>
#include <Core/Runtime/Exceptions.h>
#include <Tools/Strings.h>
#include <Utils.h>

#include <utility>

// Namespace declarations


namespace Slang {
namespace Common {


Method::Method(IScope* parent, const std::string& name, TypeDeclaration type)
: NamedScope(name, parent),
  MethodSymbol(name),
  mIsExtensionMethod(false),
  mAllowDelete(true),
  mIsInitialized(false),
  mReturnType(std::move(type)),
  mRootNode(nullptr)
{
}

Method::Method(const Method& other, bool shallowCopy)
: NamedScope(other.mName, other.mParent),
  MethodSymbol(other.mName),
  mIsExtensionMethod(other.mIsExtensionMethod),
  mAllowDelete(!shallowCopy),
  mIsInitialized(other.mIsInitialized),
  mReturnType(other.mReturnType),
  mRootNode(other.mRootNode),
  mSignature(other.mSignature)
{
	mAlgorithm = other.mAlgorithm;
	mCheckedExceptions = other.mCheckedExceptions;
	mIsSealed = other.mIsSealed;
	mLanguageFeatureState = other.mLanguageFeatureState;
	mMemoryLayout = other.mMemoryLayout;
	mMethodMutability = other.mMethodMutability;
	mMethodType = other.mMethodType;
	mMutability = other.mMutability;
	mScopeName = other.mScopeName;
	mScopeType = other.mScopeType;
	mVisibility = other.mVisibility;

	if ( !shallowCopy ) {
		mTokens = other.mTokens;
	}
}

Method::~Method()
{
	if ( mAllowDelete ) {
		delete mRootNode;
	}
}

bool Method::operator() (const Method& first, const Method& second) const
{
	if ( first.getName() == second.getName() ) {
		ParameterList firstList = first.provideSignature();
		ParameterList secondList = second.provideSignature();

		// unable to identify return value during method call
		//if ( this->type() != other.type() ) {
		//	return this->type() < other.type();
		//}

		if ( firstList.size() == secondList.size() ) {
			ParameterList::const_iterator fIt = firstList.begin();
			ParameterList::const_iterator sIt = secondList.begin();
			for ( ; fIt != firstList.end() && sIt != secondList.end(); ++fIt, ++sIt ) {
				if ( fIt->type() != sIt->type() ) {
					return fIt->type() < sIt->type();
				}
			}
		}

		return firstList.size() < secondList.size();
	}

	return first.getName() < second.getName();
}

bool Method::operator< (const Method& other) const
{
	if ( this->getName() == other.getName() ) {
		ParameterList firstList = this->provideSignature();
		ParameterList secondList = other.provideSignature();

		// unable to identify return value during method call
		//if ( this->type() != other.type() ) {
		//	return this->type() < other.type();
		//}

		if ( firstList.size() == secondList.size() ) {
			ParameterList::const_iterator fIt = firstList.begin();
			ParameterList::const_iterator sIt = secondList.begin();

			for ( ; fIt != firstList.end() && sIt != secondList.end(); ++fIt, ++sIt ) {
				if ( fIt->type() != sIt->type() ) {
					return fIt->type() < sIt->type();
				}
			}
		}

		return firstList.size() < secondList.size();
	}

	return this->getName() < other.getName();
}

Method& Method::operator= (const Method& other)
{
	if ( this != &other ) {
		mAlgorithm = other.mAlgorithm;
		mAllowDelete = false;
		mCheckedExceptions = other.mCheckedExceptions;
		mIsExtensionMethod = other.mIsExtensionMethod;
		mIsInitialized = other.mIsInitialized;
		mIsSealed = other.mIsSealed;
		mLanguageFeatureState = other.mLanguageFeatureState;
		mMemoryLayout = other.mMemoryLayout;
		mMethodMutability = other.mMethodMutability;
		mMethodType = other.mMethodType;
		mMutability = other.mMutability;
		mReturnType = other.mReturnType;
		mRootNode = other.mRootNode;
		mScopeName = other.mScopeName;
		mScopeType = other.mScopeType;
		mSignature = other.mSignature;
		mTokens = other.mTokens;
		mVisibility = other.mVisibility;
	}

	return *this;
}

const PrototypeConstraints& Method::getPrototypeConstraints() const
{
	return mReturnType.mConstraints;
}

AST::Statements* Method::getRootNode() const
{
	return mRootNode;
}

const TokenList& Method::getTokens() const
{
	return mTokens;
}

void Method::initialize(const PrototypeConstraints& constraints)
{
	if ( mIsInitialized ) {
		return;	// no need for doing this twice
	}

	// Prepare return type
	// {
	std::string type = constraints.lookupType(mReturnType.mName);

	if ( !mReturnType.mConstraints.empty() ) {
		type += constraints.extractTypes(mReturnType.mConstraints);
	}

	mReturnType.mCombinedName = type;
	mReturnType.mConstraints = PrototypeConstraints();	// reset prototype constraints
	// }

	// Update method signature
	// {
	StringSet atomicTypes = provideAtomicTypes();

	for ( auto& paramIt : mSignature ) {
		// look up parameter type in object-wide prototype constraints
		type = constraints.lookupType(paramIt.type());

		// combine parameter type with
		if ( !paramIt.typeConstraints().empty() ) {
			type += constraints.extractTypes(paramIt.typeConstraints());
		}

		if ( paramIt.type() != type ) {
			AccessMode::E access = AccessMode::ByValue;

			if ( atomicTypes.find(type) == atomicTypes.end() ) {
				access = AccessMode::ByReference;
			}

			paramIt = Parameter::CreateDesigntime(paramIt.name(),
													 TypeDeclaration(type, PrototypeConstraints(), paramIt.mutability()),
													 paramIt.value(),
													 paramIt.hasDefaultValue(),
													 paramIt.mutability(),
													 access);
		}
	}
	// }

	// Update method tokens
	// {
	for ( auto& mToken : mTokens ) {
		if ( mToken.type() == Token::Type::IDENTIFIER ) {
			type = constraints.lookupType(mToken.content());

			if ( type != mToken.content() ) {
				mToken.resetContentTo(type);
			}
		}
	}
	// }

	mIsInitialized = true;
}

bool Method::isExtensionMethod() const
{
	return mIsExtensionMethod;
}

bool Method::isPrototype() const
{
	return !mReturnType.mConstraints.empty();
}

bool Method::isSignatureValid(const ParameterList& params) const
{
	// check method signature by:
	// 1) comparing the number of parameters
	//	  by expecting the same number of parameters or less, we can make use of default parameters
	if ( params.size() > mSignature.size() ) {
		// we received more parameters than we expected
		return false;
	}

	// 2) by comparing each parameter one by one
	auto paramIt = params.begin();
	auto sigIt = mSignature.begin();

	while ( sigIt != mSignature.end() ) {
		if ( paramIt != params.end() ) {
			// compare received type with expected type
			if ( sigIt->type() != paramIt->type() && sigIt->type() != VALUE_NONE ) {
				// we received the wrong parameter type
				return false;
			}

/*
			// compare received const-ness with expected const-ness
			if ( paramIt->mutability() == sigIt->mutability() ||
				 (paramIt->mutability() == Mutability::Modify && sigIt->mutability() == Mutability::Const) ) {
				// we received a const parameter but expect a modifiable parameter
				return false;
			}
*/
/*
			// compare access types
			if ( paramIt->access() != sigIt->access() ) {
				// received wrong access type
				return false;
			}
*/

			++paramIt;
		}
		else if ( !sigIt->hasDefaultValue() ) {
			// we received less parameters than expected and we have no default value set
			return false;
		}

		++sigIt;
	}

	// no differences found, nailed it!
	return true;
}

ParameterList Method::mergeParameters(const ParameterList& params) const
{
	if ( !isSignatureValid(params) ) {
		throw Common::Exceptions::ParameterCountMismatch("incorrect number or type of parameters");
	}

	ParameterList result;

	auto paramIt = params.begin();
	auto sigIt = mSignature.begin();

	Runtime::Reference ref;
	Runtime::AtomicValue value;

	for ( ; sigIt != mSignature.end(); ++sigIt ) {
		// initialize parameter with default value
		value = sigIt->value();

		if ( paramIt != params.end() ) {
			// override parameter with correct value
			ref = paramIt->reference();
			value = paramIt->value();

			// next iteration
			++paramIt;
		}

		result.push_back(Parameter(
			sigIt->name(), TypeDeclaration(sigIt->type(), PrototypeConstraints(), sigIt->mutability()), value, sigIt->hasDefaultValue(), sigIt->mutability(), sigIt->access(), ref
		));
	}

	return result;
}

const ParameterList& Method::provideSignature() const
{
	return mSignature;
}

const std::string& Method::QualifiedTypename() const
{
	return mReturnType.mCombinedName;
}

const TypeDeclaration& Method::ReturnType() const
{
	return mReturnType;
}

void Method::setParent(IScope *scope)
{
	mParent = scope;
}

void Method::setPrototypeConstraints(const PrototypeConstraints& constraints)
{
	mReturnType.mConstraints = constraints;
}

void Method::setQualifiedTypename(const std::string& type)
{
	mReturnType.mCombinedName = type;
	mReturnType.mName = type;
}

void Method::setRootNode(AST::Statements* node)
{
	mRootNode = node;
}

void Method::setSignature(const ParameterList& params)
{
	mSignature = params;
}

void Method::setTokens(const TokenList& tokens)
{
	mTokens = tokens;
}

std::string Method::ToString(unsigned int indent) const
{
	std::string result;

	result += ::Utils::Tools::indent(indent);
	result += Visibility::convert(mVisibility);
	result += " " + MemoryLayout::convert(mMemoryLayout);
	if ( mLanguageFeatureState != LanguageFeatureState::Stable ) {
		result += " " + LanguageFeatureState::convert(mLanguageFeatureState);
	}
	result += " " + QualifiedTypename() + " " + getName() + "( " + toString(mSignature) + " )";
	result += " " + Mutability::convert(mMutability);
	if ( mCheckedExceptions != CheckedExceptions::Unspecified ) {
		result += " " + CheckedExceptions::convert(mCheckedExceptions);
	}

	return result;
}


}
}
