
// Header
#include "Method.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Runtime/TypeCast.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include <Debugger/Debugger.h>
#include "Repository.h"
#include "StackTrace.h"
#include "Tools.h"
#include "Types.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


Method::Method(IScope *parent, const std::string& name, const std::string& type)
: SymbolScope(name, parent),
  MethodSymbol(name),
  mRepository(0),
  mTypeName(type)
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
		mIsAbstract = other.mIsAbstract;
		mIsConst = other.mIsConst;
		mIsFinal = other.mIsFinal;
		mIsRecursive = other.mIsRecursive;
		mIsSealed = other.mIsSealed;
		mLanguageFeatureState = other.mLanguageFeatureState;
		mMethodType = other.mMethodType;
		mMutability = other.mMutability;
		mRepository = other.mRepository;
		mSignature = other.mSignature;
		mTokens = other.mTokens;
		mTypeName = other.mTypeName;
		mVisibility = other.mVisibility;
	}
}

ControlFlow::E Method::execute(const ParameterList& params, Object *result, const TokenIterator& token)
{
	if ( !mRepository ) {
		throw Utils::Exceptions::Exception("mRepository not set");
	}
	if ( isAbstract() ) {
		throw Utils::Exceptions::AbstractException("cannot execute abstract method '" + getName() + "'", token->position());
	}
	if ( !isSignatureValid(params) ) {
		throw Utils::Exceptions::ParameterCountMissmatch("incorrect number or type of parameters", token->position());
	}

	switch ( getLanguageFeatureState() ) {
		case LanguageFeatureState::Deprecated: OSwarn("method '" + getName() + "' is marked as deprecated"); break;
		case LanguageFeatureState::NotImplemented: OSerror("method '" + getName() + "' is marked as not implemented"); throw Utils::Exceptions::NotImplemented(getName()); break;
		case LanguageFeatureState::Stable: /* this is the normal language feature state, so there is no need to log anything here */ break;
		case LanguageFeatureState::Unknown: OSerror("unknown language feature state set for method '" + getName() + "'"); break;
		case LanguageFeatureState::Unstable: OSwarn("method '" + getName() + "' is marked as unstable"); break;
	}

	Interpreter interpreter(this, getName());
	interpreter.setConst(isConst());
	interpreter.setFinal(isFinal());
	interpreter.setLanguageFeatureState(getLanguageFeatureState());
	interpreter.setMutability(getMutability());
	interpreter.setRepository(mRepository);
	interpreter.setTokens(mTokens);
	interpreter.setVisibility(getVisibility());

	ParameterList executedParams;

	// add parameters as locale variables
	ParameterList::const_iterator paramIt = params.begin();
	for ( ParameterList::const_iterator sigIt = mSignature.begin(); sigIt != mSignature.end(); ++sigIt ) {
		// initialize parameter with default value
		Parameter param(sigIt->name(), sigIt->type(), sigIt->value(), sigIt->hasDefaultValue(), sigIt->isConst(), sigIt->access());

		if ( paramIt != params.end() ) {
			// override parameter with correct value
			param = Parameter(sigIt->name(), sigIt->type(), paramIt->value(), sigIt->hasDefaultValue(), sigIt->isConst(), sigIt->access(), paramIt->pointer());
			// next iteration
			paramIt++;
		}

		executedParams.push_back(param);

		switch ( param.access() ) {
			case Parameter::AccessMode::Unspecified: {
				throw Utils::Exceptions::AccessMode("unspecified access mode");
			} break;
			case Parameter::AccessMode::ByReference: {
				Object *object = param.pointer();

				if ( param.isConst() ) {
					throw Utils::Exceptions::NotImplemented("const reference parameters not supported");
				}

				object->setConst(param.isConst());	// const references are not supported atm so this should always be false
				object->setMutability(param.isConst() ? Mutability::Const : Mutability::Modify);

				interpreter.define(param.name(), object);
			} break;
			case Parameter::AccessMode::ByValue: {
				Object *object = mRepository->createInstance(param.type(), param.name());

				object->setValue(param.value());	// in case we have a default value
				if ( param.pointer() ) {
					*object = *param.pointer();
				}
				object->setConst(param.isConst());
				object->setMutability(param.isConst() ? Mutability::Const : Mutability::Modify);

				interpreter.define(param.name(), object);
			} break;
		}
	}

	// record stack
	StackTrace::GetInstance().pushStack(getFullName(), executedParams);

	// notify debugger (if present)
	Core::Debugger::GetInstance().notify(&interpreter, Core::Debugger::immediateBreak);

	ControlFlow::E controlflow = interpreter.execute(result);	// execute method code

	// notify debugger (if present)
	Core::Debugger::GetInstance().notify(&interpreter, Core::Debugger::immediateBreak);

	mExceptionData = interpreter.getExceptionData();	// collect exception data no matter what

	return processControlFlow(controlflow, result);
}

void Method::garbageCollector()
{
	for ( Symbols::reverse_iterator it = mSymbols.rbegin(); it != mSymbols.rend(); ) {
		if ( it->first != IDENTIFIER_BASE && it->first != IDENTIFIER_THIS &&
			 it->second && it->second->getType() == Symbol::IType::ObjectSymbol ) {
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

ControlFlow::E Method::processControlFlow(ControlFlow::E controlflow, Object *result)
{
	// detect unnatural control flow

	switch ( controlflow ) {
		case ControlFlow::Break:
		case ControlFlow::Continue:
		case ControlFlow::Normal:
			// verify method return reason
			if ( Typename() != VoidObject::TYPENAME && result->Typename() != VoidObject::TYPENAME ) {
				throw Utils::Exceptions::Exception("unnatural method return at '" + getFullName() + "'");
			}

			// correct behaviour detected, override control flow with normal state
			controlflow = ControlFlow::Normal;
			break;
		case ControlFlow::Return:
			// validate return value
			if ( Typename() != VoidObject::TYPENAME && result->Typename() != Typename() ) {
				OSwarn("implicit type conversion from " + result->Typename() + " to " + Typename() + " in " + getFullName());

				typecast(result, Typename(), mRepository);
			}

			// correct behaviour detected, override control flow with normal state
			controlflow = ControlFlow::Normal;
			break;
		case ControlFlow::ExitProgram:
		case ControlFlow::Throw:
			// an ObjectiveScript exception has been thrown
			break;
	}

	StackTrace::GetInstance().popStack();

	return controlflow;
}

const ParameterList& Method::provideSignature() const
{
	return mSignature;
}

Symbol* Method::resolveMethod(const std::string& name, const ParameterList& params, bool onlyCurrentScope) const
{
	if ( mMethodType != MethodType::Function ) {
		switch ( mParent->getType() ) {
			case IScope::IType::MethodScope:
				return static_cast<MethodScope*>(mParent)->resolveMethod(name, params, onlyCurrentScope);
			case IScope::IType::SymbolScope:
			case IScope::IType::UnknownScope:
				throw Utils::Exceptions::Exception("invalid/unknown scope type detected!");
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

std::string Method::ToString() const
{
	std::string result;

	result += Visibility::convert(mVisibility);
	result += " " + LanguageFeatureState::convert(mLanguageFeatureState);
	result += " " + Typename() + " " + getName() + "(" + toString(mSignature) + ")";
	result += " " + Mutability::convert(mMutability);

	return result;
}

const std::string& Method::Typename() const
{
	return mTypeName;
}


}
}
