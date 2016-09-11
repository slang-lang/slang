
// Header
#include "Method.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Runtime/OperatorOverloading.h>
#include <Core/Runtime/TypeCast.h>
#include <Debugger/Debugger.h>
#include <Tools/Strings.h>
#include <Utils.h>
#include "Defines.h"
#include "Repository.h"
#include "StackTrace.h"
#include "Tools.h"
#include "Types.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


Method::Method(IScope* parent, const std::string& name, const std::string& type)
: SymbolScope(name, parent),
  MethodSymbol(name),
  mRepository(0),
  mOwner(parent),
  mQualifiedTypename(type),
  mTypeName(type)
{
}

Method::~Method()
{
	garbageCollector();
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
		mLanguageFeatureState = other.mLanguageFeatureState;
		mMethodType = other.mMethodType;
		mMutability = other.mMutability;
		mQualifiedTypename = other.mQualifiedTypename;
		mRepository = other.mRepository;
		mScopeName = other.mScopeName;
		mScopeType = other.mScopeType;
		mSignature = other.mSignature;
		mThrows = other.mThrows;
		mTokens = other.mTokens;
		mTypeName = other.mTypeName;
		mVisibility = other.mVisibility;
	}
}

ControlFlow::E Method::execute(const ParameterList& params, Object* result, const Token& token)
{
	if ( !mRepository ) {
		throw Common::Exceptions::Exception("mRepository not set");
	}
	if ( isAbstract() ) {
		throw Common::Exceptions::AbstractException("cannot execute abstract method '" + getName() + "'", token.position());
	}
	if ( !isSignatureValid(params) ) {
		throw Common::Exceptions::ParameterCountMissmatch("incorrect number or type of parameters", token.position());
	}

	switch ( getLanguageFeatureState() ) {
		case LanguageFeatureState::Deprecated: OSwarn("method '" + getFullScopeName() + "' is marked as deprecated"); break;
		case LanguageFeatureState::NotImplemented: OSerror("method '" + getFullScopeName() + "' is marked as not implemented"); throw Common::Exceptions::NotImplemented(getFullScopeName()); break;
		case LanguageFeatureState::Stable: /* this is the normal language feature state, so there is no need to log anything here */ break;
		case LanguageFeatureState::Unknown: OSerror("unknown language feature state set for method '" + getFullScopeName() + "'"); break;
		case LanguageFeatureState::Unstable: OSwarn("method '" + getFullScopeName() + "' is marked as unstable"); break;
	}

	Method scope(*this);

	if ( isStatic() ) {		// this allows variable definitions in static methods
		scope.mParent = mRepository->getGlobalScope();
	}

	Interpreter interpreter(&scope);
	interpreter.setRepository(mRepository);
	interpreter.setTokens(mTokens);

	ParameterList executedParams = mergeParameters(params);

	// add parameters as locale variables
	for ( ParameterList::const_iterator it = executedParams.begin(); it != executedParams.end(); ++it ) {
		switch ( it->access() ) {
			case Parameter::AccessMode::ByReference: {
				Object *object = it->pointer();

				object->setConst(it->isConst());
				object->setMutability(it->isConst() ? Mutability::Const : Mutability::Modify);

				scope.define(it->name(), object);
			} break;
			case Parameter::AccessMode::ByValue: {
				Object *object = mRepository->createInstance(it->type(), it->name());

				object->setValue(it->value());	// in case we have a default value
				if ( it->pointer() ) {
					*object = *(it->pointer());
				}
				object->setConst(it->isConst());
				object->setMutability(it->isConst() ? Mutability::Const : Mutability::Modify);

				scope.define(it->name(), object);
			} break;
			case Parameter::AccessMode::Unspecified: {
				throw Common::Exceptions::AccessMode("unspecified access mode");
			} break;
		}
	}

	// record stack trace
	StackTrace::GetInstance().pushStack(getFullScopeName(), executedParams);
	// notify debugger
	Core::Debugger::GetInstance().notifyEnter(&scope, Core::Debugger::immediateBreakToken);

	// do the real method execution
	ControlFlow::E controlflow = interpreter.execute(result);

	// collect exception data no matter what
	mExceptionData = interpreter.getExceptionData();

	// process & update control flow
	controlflow = processControlFlow(controlflow, result);

	// notify debugger
	Core::Debugger::GetInstance().notifyExit(&scope, Core::Debugger::immediateBreakToken);
	// unwind stack trace
	StackTrace::GetInstance().popStack();

	// undefine references to prevent double deletes
	for ( ParameterList::const_iterator it = executedParams.begin(); it != executedParams.end(); ++it ) {
		switch ( it->access() ) {
			case Parameter::AccessMode::ByReference:
				scope.undefine(it->name(), it->pointer());
				break;
			case Parameter::AccessMode::ByValue:
				break;
			case Parameter::AccessMode::Unspecified:
				throw Common::Exceptions::AccessMode("unspecified access mode");;
		}
	}


	return controlflow;
}

void Method::garbageCollector()
{
	for ( Symbols::reverse_iterator it = mSymbols.rbegin(); it != mSymbols.rend(); ) {
		if ( it->first != IDENTIFIER_BASE && it->first != IDENTIFIER_THIS &&
			 it->second && it->second->getSymbolType() == Symbol::IType::ObjectSymbol ) {
			mRepository->removeReference(static_cast<Object*>(it->second));
		}

		undefine(it->first, it->second);
	}
	mSymbols.clear();
}

const ExceptionData& Method::getExceptionData() const
{
	return mExceptionData;
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
			if ( sigIt->type() != paramIt->type() ) {
				// we received the wrong parameter type
				return false;
			}
			// compare received const-ness with expected const-ness
			if ( paramIt->isConst() && !sigIt->isConst() ) {
				// we received a const parameter but expect a non-const parameter
				return false;
			}
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
			// override parameter with correct value
			param = Parameter(sigIt->name(), sigIt->type(), paramIt->value(), sigIt->hasDefaultValue(), sigIt->isConst(), sigIt->access(), paramIt->pointer());
			// next iteration
			paramIt++;
		}

		result.push_back(param);
	}

	return result;
}

ControlFlow::E Method::processControlFlow(ControlFlow::E controlflow, Object* result)
{
	// detect unnatural control flow

	switch ( controlflow ) {
		case ControlFlow::Break:
		case ControlFlow::Continue:
		case ControlFlow::Normal:
			// verify method return reason
			if ( QualifiedTypename() != VoidObject::TYPENAME && result->QualifiedOutterface() != VoidObject::TYPENAME ) {
				throw Common::Exceptions::Exception("unnatural method return at '" + getFullScopeName() + "'");
			}

			// correct behavior detected, override control flow with normal state
			controlflow = ControlFlow::Normal;
			break;
		case ControlFlow::Return:
			// validate return value
			if ( result->QualifiedOutterface() == NULL_TYPE ) {
				// no type cast necessary for null objects
			}
			else if ( QualifiedTypename() != VoidObject::TYPENAME && result->QualifiedOutterface() != QualifiedTypename() ) {
				if ( !ALLOW_IMPLICIT_CASTS ) {
					throw Runtime::Exceptions::ExplicitCastRequired("Explicit cast required for type conversion from " + result->QualifiedOutterface() + " to " + QualifiedTypename() + " in " + getFullScopeName());
				}

				OSwarn("implicit type conversion from " + result->QualifiedOutterface() + " to " + QualifiedTypename());// + " in " + getFullScopeName());

				typecast(result, QualifiedTypename());
			}

			// correct behavior detected, override control flow with normal state
			controlflow = ControlFlow::Normal;
			break;
		case ControlFlow::ExitProgram:
		case ControlFlow::Throw:
			// an ObjectiveScript exception has been thrown or we want to terminate
			break;
	}

	if ( controlflow == ControlFlow::Normal ) {
		switch ( getMethodType() ) {
			case MethodAttributes::MethodType::Constructor:
				static_cast<Object*>(mParent)->setConstructed(true);
				break;
			case MethodAttributes::MethodType::Destructor:
				static_cast<Object*>(mParent)->setConstructed(false);
				break;
			default:
				break;
		}
	}

	return controlflow;
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

void Method::setRepository(Repository *repository)
{
	mRepository = repository;
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

	return result;
}


}
}
