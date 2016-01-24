
// Header
#include "Method.h"

// Library includes
#include <cassert>

// Project includes
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Consts.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include "Object.h"
#include "Repository.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


Method::Method(IScope *parent, const std::string& name, const std::string& type)
: LocalScope(name, parent),
  MethodSymbol(name),
  mOwner(0),
  mRepository(0),
  mTypeName(type)
{
}

Method::~Method()
{
	garbageCollector();
}

bool Method::operator() (const Method& first, const Method& second) const
{
	if (first.getName() == second.getName()) {
		ParameterList firstList = first.provideSignature();
		ParameterList secondList = second.provideSignature();
		// unable to identify return value during method call
		//if ( this->type() != other.type() ) {
		//	return this->type() < other.type();
		//}
		if (firstList.size() == secondList.size()) {
			ParameterList::const_iterator fIt = firstList.begin();
			ParameterList::const_iterator sIt = secondList.begin();
			for (; fIt != firstList.end() && sIt != secondList.end();
					++fIt, ++sIt) {
				if (fIt->type() != sIt->type()) {
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
		setConst(other.isConst());
		setFinal(other.isFinal());
		setLanguageFeatureState(other.languageFeatureState());

		mOwner = other.mOwner;
		mParameter = other.mParameter;
		mRepository = other.mRepository;
		mTokens = other.mTokens;

		setSignature(other.provideSignature());
		visibility(other.visibility());
	}
}

ControlFlow::E Method::execute(const ParameterList& params, Object *result)
{
	assert(mRepository);

	if ( !isSignatureValid(params) ) {
		throw Utils::Exceptions::ParameterCountMissmatch("incorrect number or type of parameters");
	}

	switch ( languageFeatureState() ) {
		case LanguageFeatureState::Deprecated: OSwarn("method '" + getName() + "' is marked as deprecated"); break;
		case LanguageFeatureState::NotImplemented: OSerror("method '" + getName() + "' is marked as not implemented"); throw Utils::Exceptions::NotImplemented(getName()); break;
		case LanguageFeatureState::Stable: /* this is the normal language feature state, so there is no need to log anything here */ break;
		case LanguageFeatureState::Unknown: OSerror("unknown language feature state set for method '" + getName() + "'"); break;
		case LanguageFeatureState::Unstable: OSwarn("method '" + getName() + "' is marked as unstable"); break;
	}

	Interpreter interpreter(this, getName());
	interpreter.setConst(isConst() /*|| mOwner->isConst()*/);
	interpreter.setFinal(isFinal());
	interpreter.setLanguageFeatureState(languageFeatureState());
	interpreter.setRepository(mRepository);
	interpreter.setTokens(mTokens);

	// add parameters as locale variables
	ParameterList::const_iterator paramIt = params.begin();
	for ( ParameterList::const_iterator sigIt = mSignature.begin(); sigIt != mSignature.end(); ++sigIt ) {
		// initialize parameter with default value
		Parameter param(sigIt->name(), sigIt->type(), sigIt->value(), sigIt->hasDefaultValue(), sigIt->isConst(), sigIt->access());

		if ( paramIt != params.end() ) {
			Parameter::AccessMode::E access = sigIt->access();

			// override parameter with correct value
			param = Parameter(sigIt->name(), sigIt->type(), paramIt->value(), sigIt->hasDefaultValue(), sigIt->isConst(), access, paramIt->pointer());
			// next iteration
			paramIt++;
		}

		switch ( param.access() ) {
			case Parameter::AccessMode::Unspecified: {
				throw Utils::Exceptions::AccessMode("unspecified access mode");
			} break;
			case Parameter::AccessMode::ByReference: {
				Object *object = param.pointer();
				object->setConst(param.isConst());	// const references are not supported atm so this should always be false

				interpreter.define(param.name(), object);
			} break;
			case Parameter::AccessMode::ByValue: {
				Object *object = mRepository->createInstance(param.type(), param.name());

				object->setValue(param.value());	// in case we have a default value
				if ( param.pointer() ) {
					*object = Object(*param.pointer());
				}
				object->setConst(param.isConst());

				interpreter.define(param.name(), object);
			} break;
		}
	}

	result->overrideType(getTypeName());
	result->setRepository(mRepository);
	//result->setValue(/*get default value for return type*/);

	ControlFlow::E controlflow = interpreter.execute(result);

	// detect unnatural control flow
	switch ( controlflow ) {
		case ControlFlow::Break:
		case ControlFlow::Continue:
		case ControlFlow::Normal:
			// verify method return reason
			if ( result->getTypeName() != VoidObject::TYPENAME ) {
				throw Utils::Exceptions::Exception("unnatural method return at '" + getName() + "'");
			}

			controlflow = ControlFlow::Normal;
			break;
		case ControlFlow::Return:
			// validate return value
			if ( result->Typename() != getTypeName() ) {
				throw Utils::Exceptions::Exception("invalid return of type '" + result->Typename() + "' in '" + getName() + "'");
			}

			controlflow = ControlFlow::Normal;
			break;
		case ControlFlow::Throw:
			// an ObjectiveScript exception has been thrown
			break;
	}

	return controlflow;
}

void Method::garbageCollector()
{
	for ( Symbols::reverse_iterator it = mSymbols.rbegin(); it != mSymbols.rend(); ) {
		if ( it->first != KEYWORD_THIS &&
			 it->second && it->second->getType() == Symbol::IType::ObjectSymbol ) {
			mRepository->removeReference(static_cast<Object*>(it->second));
		}

		undefine(it->first, it->second);
	}
}

const std::string& Method::getTypeName() const
{
	return mTypeName;
}

bool Method::isSignatureValid(const ParameterList& params) const
{
	// check method signature by:
	// 1) comparing the number of parameters
	//	  by expecting the same number of parameters or less, we can make use of default parameters
	if ( mSignature.size() < params.size() ) {
		// we received more parameters than we expected
		return false;
	}

	// 2) by comparing each parameter one by one
	ParameterList::const_iterator paramIt = params.begin();
	ParameterList::const_iterator sigIt = mSignature.begin();

	while ( sigIt != mSignature.end() ) {
		if ( paramIt != params.end() ) {
			if ( /*(sigIt->access() != paramIt->access()) ||*/
				 /*(sigIt->isConst() != paramIt->isConst()) ||*/
				 (sigIt->type() != paramIt->type()) ) {
				return false;
			}
			paramIt++;
		}
		else {
			if ( !sigIt->hasDefaultValue() ) {
				return false;
			}
		}

		sigIt++;
	}

	// no differences found, nailed it!
	return true;
}

const ParameterList& Method::provideSignature() const
{
	return mSignature;
}

Symbol* Method::resolve(const std::string& name, bool onlyCurrentScope) const
{
	std::string member, parent;
	Tools::split(name, parent, member);

	if ( member.empty() ) {
		member = parent;
		parent = KEYWORD_THIS;
	}

	Symbol *result = LocalScope::resolve(parent, onlyCurrentScope);

	while ( result && !member.empty() ) {
		switch ( result->getType() ) {
			case Symbol::IType::AtomicTypeSymbol:
			case Symbol::IType::MemberSymbol:
			case Symbol::IType::ObjectSymbol: {
				result = static_cast<Object*>(result)->resolve(member);
			} break;
			case Symbol::IType::MethodSymbol:
			case Symbol::IType::NamespaceSymbol:
				return result;
			case Symbol::IType::BluePrintSymbol:
			case Symbol::IType::UnknownSymbol:
				throw Utils::Exceptions::SyntaxError("cannot directly access locales of method/namespace");
		}

		Tools::split(member, parent, member);
	}

	return result;
}

Symbol* Method::resolveMethod(const std::string& name, const ParameterList& params, bool onlyCurrentScope) const
{
	std::string member, parent;
	Tools::split(name, parent, member);

	if ( member.empty() ) {
		member = parent;
		parent = KEYWORD_THIS;
	}

	Symbol *result = LocalScope::resolve(parent, onlyCurrentScope);

	if ( result ) {
		switch ( result->getType() ) {
			case Symbol::IType::AtomicTypeSymbol:
			case Symbol::IType::MemberSymbol:
			case Symbol::IType::ObjectSymbol:
				return static_cast<Object*>(result)->resolveMethod(member, params);
			case Symbol::IType::MethodSymbol:
				return static_cast<Method*>(result)->resolveMethod(member, params, onlyCurrentScope);
			case Symbol::IType::BluePrintSymbol:
			case Symbol::IType::NamespaceSymbol:
			case Symbol::IType::UnknownSymbol:
				throw Utils::Exceptions::SyntaxError("cannot directly access locales of method/namespace");
		}
	}

	return 0;
}

void Method::setOwner(Object *owner)
{
	mOwner = owner;
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


}
}
