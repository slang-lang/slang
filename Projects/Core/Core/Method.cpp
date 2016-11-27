
// Header
#include "Method.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Runtime/OperatorOverloading.h>
#include <Core/Runtime/TypeCast.h>
#include <Core/VirtualMachine/Controller.h>
#include <Debugger/Debugger.h>
#include <Tools/Strings.h>
#include <Utils.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


Method::Method(IScope* parent, const std::string& name, const std::string& type)
: NamedScope(name, parent),
  MethodSymbol(name),
  mIsExtensionMethod(false),
  mQualifiedTypename(type)
{
}

Method::~Method()
{
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

void Method::operator= (const Method& other)
{
	if ( this != &other ) {
		mImplementationType = other.mImplementationType;
		mIsFinal = other.mIsFinal;
		mIsRecursive = other.mIsRecursive;
		mIsSealed = other.mIsSealed;
		mIsStatic = other.mIsStatic;
		mLanguageFeatureState = other.mLanguageFeatureState;
		mMethodType = other.mMethodType;
		mMutability = other.mMutability;
		mPrototypeConstraints = other.mPrototypeConstraints;
		mQualifiedTypename = other.mQualifiedTypename;
		mScopeName = other.mScopeName;
		mScopeType = other.mScopeType;
		mSignature = other.mSignature;
		mThrows = other.mThrows;
		mTokens = other.mTokens;
		mVisibility = other.mVisibility;
	}
}

ControlFlow::E Method::execute(const ParameterList& /*params*/, Object* /*result*/, const Token& token)
{
	throw Common::Exceptions::NotSupported("executing methods directly is not supported!", token.position());
}

bool Method::isExtensionMethod() const
{
	return mIsExtensionMethod;
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
				// we received a const parameter but expect a non-const parameter
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

			paramIt++;
		}
		else if ( !sigIt->hasDefaultValue() ) {
			// we received less parameters than expected and we have no default value set
			return false;
		}

		sigIt++;
	}

	// no differences found, nailed it!
	return true;
}

ParameterList Method::mergeParameters(const ParameterList& params) const
{
	ParameterList result;

	ParameterList::const_iterator paramIt = params.begin();
	ParameterList::const_iterator sigIt = mSignature.begin();

	for ( ; sigIt != mSignature.end(); ++sigIt ) {
		// initialize parameter with default value
		Parameter param(sigIt->name(), sigIt->type(), sigIt->value(), sigIt->hasDefaultValue(), sigIt->isConst(), sigIt->access());

		if ( paramIt != params.end() ) {
			Reference ref = paramIt->reference();

			// override parameter with correct value
			param = Parameter(sigIt->name(), sigIt->type(), paramIt->value(), sigIt->hasDefaultValue(), sigIt->isConst(), sigIt->access(), ref);
			// next iteration
			paramIt++;
		}

		result.push_back(param);
	}

	return result;
}

const ParameterList& Method::provideSignature() const
{
	return mSignature;
}

Symbol* Method::resolveMethod(const std::string& name, const ParameterList& params, bool onlyCurrentScope) const
{
	if ( mMethodType != MethodType::Function ) {
		switch ( mParent->getScopeType() ) {
			case IScope::IType::MethodScope:
				return static_cast<MethodScope*>(mParent)->resolveMethod(name, params, onlyCurrentScope);
			case IScope::IType::NamedScope:
			case IScope::IType::SymbolScope:
			case IScope::IType::UnknownScope:
				throw Common::Exceptions::Exception("invalid/unknown scope type detected!");
		}
	}

	return SymbolScope::resolve(name, onlyCurrentScope);
}

void Method::setParent(IScope *scope)
{
	mParent = scope;
}

void Method::setPrototypeConstraints(const PrototypeConstraints& constraints)
{
	mPrototypeConstraints = constraints;
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
	result += " " + LanguageFeatureState::convert(mLanguageFeatureState);
	result += " " + QualifiedTypename() + " " + getName() + "(" + toString(mSignature) + ")";
	result += " " + Mutability::convert(mMutability);
	if ( isAbstract() ) {
		result += " abstract";
	}
	if ( isRecursive() ) {
		result += " recursive";
	}
	if ( isStatic() ) {
		result += " static";
	}

	return result;
}


}
}
