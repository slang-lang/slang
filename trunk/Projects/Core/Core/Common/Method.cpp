
// Header
#include "Method.h"

// Library includes

// Project includes
#include <Core/AST/Statement.h>
#include <Core/Designtime/Parser/Parser.h>
#include <Core/Runtime/Exceptions.h>
#include <Tools/Strings.h>
#include <Utils.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Common {


Method::Method(IScope* parent, const std::string& name, const std::string& type)
: NamedScope(name, parent),
  MethodSymbol(name),
  mIsExtensionMethod(false),
  mAllowDelete(true),
  mReturnType(TypeDeclaration(type)),
  mRootNode(0)
{
}

Method::Method(const Method& other)
: NamedScope(other.getName(), other.getEnclosingScope()),
  MethodSymbol(other.getName())
{
	mAlgorithm = other.mAlgorithm;
	mAllowDelete = false;
	mCheckedExceptions = other.mCheckedExceptions;
	mIsExtensionMethod = other.mIsExtensionMethod;
	mIsSealed = other.mIsSealed;
	mLanguageFeatureState = other.mLanguageFeatureState;
	mMemoryLayout = other.mMemoryLayout;
	mMethodType = other.mMethodType;
	mMutability = other.mMutability;
	mReturnType = other.mReturnType;
	mRootNode = other.mRootNode;
	mScopeName = other.mScopeName;
	mScopeType = other.mScopeType;
	mSignature = other.mSignature;
	mTokens = other.mTokens;
	mVirtuality = other.mVirtuality;
	mVisibility = other.mVisibility;
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
		mIsSealed = other.mIsSealed;
		mLanguageFeatureState = other.mLanguageFeatureState;
		mMemoryLayout = other.mMemoryLayout;
		mMethodType = other.mMethodType;
		mMutability = other.mMutability;
		mReturnType = other.mReturnType;
		mRootNode = other.mRootNode;
		mScopeName = other.mScopeName;
		mScopeType = other.mScopeType;
		mSignature = other.mSignature;
		mTokens = other.mTokens;
		mVirtuality = other.mVirtuality;
		mVisibility = other.mVisibility;
	}

	return *this;
}

Runtime::ControlFlow::E Method::execute(const ParameterList& /*params*/, Runtime::Object* /*result*/, const Token& token)
{
	throw Common::Exceptions::NotSupported("executing methods directly is not supported!", token.position());
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

	for ( ParameterList::iterator paramIt = mSignature.begin(); paramIt != mSignature.end(); ++paramIt ) {
		// look up parameter type in object-wide prototype constraints
		type = constraints.lookupType(paramIt->type());

		// combine parameter type with
		if ( paramIt->typeConstraints().size() ) {
			type += constraints.extractTypes(paramIt->typeConstraints());
		}

		if ( paramIt->type() != type ) {
			AccessMode::E access = AccessMode::ByValue;

			if ( atomicTypes.find(type) == atomicTypes.end() ) {
				access = AccessMode::ByReference;
			}

			(*paramIt) = Parameter::CreateDesigntime(paramIt->name(),
													 TypeDeclaration(type, PrototypeConstraints()),
													 paramIt->value(),
													 paramIt->hasDefaultValue(),
													 paramIt->mutability(),
													 access);
		}
	}
	// }

	// Update method tokens
	// {
	for ( TokenList::iterator tokIt = mTokens.begin(); tokIt != mTokens.end(); ++tokIt ) {
		if ( tokIt->type() == Token::Type::IDENTIFIER ) {
			type = constraints.lookupType(tokIt->content());

			if ( type != tokIt->content() ) {
				tokIt->resetContentTo(type);
			}
		}
	}
	// }
}

bool Method::isEmpty() const
{
	return !mIsExtensionMethod && !mRootNode;
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
	ParameterList::const_iterator paramIt = params.begin();
	ParameterList::const_iterator sigIt = mSignature.begin();

	while ( sigIt != mSignature.end() ) {
		if ( paramIt != params.end() ) {
			// compare received type with expected type
			if ( sigIt->type() != paramIt->type() && sigIt->type() != VALUE_NONE ) {
				// we received the wrong parameter type
				return false;
			}
/*
			// compare received const-ness with expected const-ness
			if ( paramIt->isConst() && !sigIt->isConst() ) {
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
		throw Common::Exceptions::ParameterCountMissmatch("incorrect number or type of parameters");
	}

	ParameterList result;

	ParameterList::const_iterator paramIt = params.begin();
	ParameterList::const_iterator sigIt = mSignature.begin();

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
			sigIt->name(), TypeDeclaration(sigIt->type()), value, sigIt->hasDefaultValue(), sigIt->mutability(), sigIt->access(), ref
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

void Method::setParent(IScope *scope)
{
	mParent = scope;
}

void Method::setPrototypeConstraints(const PrototypeConstraints& constraints)
{
/*
	mReturnType.mCombinedName = Designtime::Parser::buildRuntimeConstraintTypename(mReturnType.mName, constraints);
	mReturnType.mConstraints = PrototypeConstraints();
*/

	mReturnType.mConstraints = constraints;
}

void Method::setQualifiedTypename(const std::string& type)
{
	mReturnType.mCombinedName = Designtime::Parser::buildRuntimeConstraintTypename(type, mReturnType.mConstraints);
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
	//result += " " + LanguageFeatureState::convert(mLanguageFeatureState);
	result += " " + QualifiedTypename() + " " + getName() + "(" + toString(mSignature) + ")";
	result += " " + Mutability::convert(mMutability);
	result += " " + CheckedExceptions::convert(mCheckedExceptions);
	result += " " + MemoryLayout::convert(mMemoryLayout);
	result += " " + Virtuality::convert(mVirtuality);

	return result;
}


}
}
