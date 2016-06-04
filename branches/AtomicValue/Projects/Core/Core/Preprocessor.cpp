
// Header
#include "Preprocessor.h"

// Library includes

// Project includes
#include <Core/Designtime/BluePrint.h>
#include <Core/Parser/Parser.h>
#include <Core/Utils/Exceptions.h>
#include "Repository.h"
#include "Tokenizer.h"

// Namespace declarations


namespace ObjectiveScript {


Preprocessor::Preprocessor(Repository *repo)
: mBluePrint(0),
  mRepository(repo),
  mScope(0)
{
}

Designtime::BluePrint* Preprocessor::createMember(TokenIterator token) const
{
	std::string languageFeature;
	std::string name;
	std::string type;
	std::string visibility;
	bool isConst = false;
	bool isFinal = false;

	// look for the visibility token
	visibility = (*token++).content();
	// look for an optional language feature token
	if ( token->isOptional() ) {
		languageFeature = (*token++).content();
	}
	// look for the type token
	type = (*token++).content();
	// look for the identifier token
	name = (*token++).content();

	if ( Visibility::convert(visibility) == Visibility::Public ) {
		// beware: public members are deprecated, remember the "Law of Demeter"
		// consider using wrappers (getter, setter) instead of directly providing access to members to outsiders
		// haven't you heard? outsiders, or sometimes called strangers, are evil
		throw Utils::Exceptions::LawOfDemeterViolated("public member " + name + " violates \"Law of Demeter\"", token->position());
	}

	if ( token->category() == Token::Category::Modifier ) {
		if ( (*token).content() == MODIFIER_CONST ) {
			isConst = true;
		}
		else if ( (*token).content() == MODIFIER_FINAL ) {
			isFinal = true;
		}

		token++;
	}

	if ( (*token).type() != Token::Type::SEMICOLON ) {
		throw Utils::Exceptions::Exception("initialization not allowed during member declaration", token->position());
	}

	Designtime::BluePrint* blue = new Designtime::BluePrint(type, mFilename, name);
	blue->setConst(isConst);
	blue->setFinal(isFinal);
	blue->setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
	blue->setMember(true);		// every object created here is a member object
	blue->setVisibility(Visibility::convert(visibility));

	return blue;
}

Runtime::Method* Preprocessor::createMethod(TokenIterator token) const
{
	bool isAbstract = false;
	bool isConst = true;		// extreme const correctness: all methods are const by default
	bool isFinal = false;
	bool isRecursive = false;
	std::string languageFeature;
	MethodAttributes::MethodType::E methodType = MethodAttributes::MethodType::Method;
	std::string name;
	std::string type;
	std::string visibility;
	int numConstModifiers = 0;

	// look for the visibility token
	visibility = (*token++).content();
	// look for an optional language feature token
	if ( token->isOptional() ) {
		languageFeature = (*token++).content();
	}
	// look for the type token
	type = (*token++).content();
	// look for the identifier token
	name = (*token++).content();

	if ( name == mBluePrint->Typename() ) {
		// these methods have the same name as their containing object,
		// so this has to be a constructor or a destructor;
		// they can never ever be const, ever
		isConst = false;
		methodType = MethodAttributes::MethodType::Constructor;
	}
	else if ( name == "~" + mBluePrint->Typename() ) {
		// these methods have the same name as their containing object,
		// so this has to be a constructor or a destructor;
		// they can never ever be const, ever
		isConst = false;
		methodType = MethodAttributes::MethodType::Destructor;
	}

	// look for the next opening parenthesis
	if ( (*token).type() != Token::Type::PARENTHESIS_OPEN ) {
		throw Utils::Exceptions::SyntaxError("parameter declaration expected");
	}

	ParameterList params = Parser::parseParameters(token);

	// look at possible attributes (abstract, const, final, modify, etc.)
	// while looking for the next opening curly bracket
	bool isModifierToken = true;
	do {
		token++;

		if ( token->category() == Token::Category::Modifier ) {
			if ( token->content() == MODIFIER_ABSTRACT ) {
				isAbstract = true;
			}
			else if ( token->content() == MODIFIER_CONST ) {
				isConst = true;
				numConstModifiers++;
			}
			else if ( token->content() == MODIFIER_FINAL ) {
				isFinal = true;
			}
			else if ( token->content() == MODIFIER_MODIFY ) {
				isConst = false;
				numConstModifiers++;
			}
			else if ( token->content() == MODIFIER_RECURSIVE ) {
				isRecursive = true;
			}
		}
		else {
			isModifierToken = false;
		}
	} while ( isModifierToken && token->type() != Token::Type::BRACKET_CURLY_OPEN );

	if ( numConstModifiers > 1 ) {
		throw Utils::Exceptions::Exception("modifiers 'const' & 'modify' are exclusive");
	}

	if ( isConst &&
		(methodType == MethodAttributes::MethodType::Constructor || methodType == MethodAttributes::MethodType::Destructor) ) {
		throw Utils::Exceptions::SyntaxError("constructor or destructor cannot be const");
	}

	// collect all tokens of this method
	TokenList tokens;
	if ( token->type() == Token::Type::BRACKET_CURLY_OPEN ) {
		tokens = Parser::collectScopeTokens(token);
	}

	if ( isAbstract && !tokens.empty() ) {
		throw Utils::Exceptions::SyntaxError("abstract methods cannot have an implementation");
	}

	// create a new method with the corresponding return value
	Runtime::Method *method = new Runtime::Method(mScope, name, type);
	method->setAbstract(isAbstract || mBluePrint->isInterface());
	method->setConst(isConst);
	method->setFinal(isFinal);
	method->setLanguageFeatureState(LanguageFeatureState::convert(languageFeature));
	method->setMethodType(methodType);
	method->setRecursive(isRecursive);
	method->setRepository(mRepository);
	method->setSignature(params);
	method->setTokens(tokens);
	method->setVisibility(Visibility::convert(visibility));

	return method;
}

void Preprocessor::generateObject()
{
	assert(mBluePrint);

	typedef std::list<TokenIterator> TokenIteratorList;
	TokenIteratorList visList;

	// find all visibility keywords which we use as starting point for our interpreter
	for ( TokenIterator it = mTokens.begin(); it != mTokens.end(); ++it ) {
		if ( it->type() == Token::Type::VISIBILITY ) {
			visList.push_back(it);
		}
	}

	// loop over all visibility declarations and check if we have a member declaration or a method declaration
	for ( TokenIteratorList::const_iterator it = visList.begin(); it != visList.end(); ++it ) {
		if ( Parser::isMemberDeclaration((*it)) || Parser::isAlternateMemberDeclaration((*it)) ) {
			Designtime::BluePrint *member = createMember((*it));

			mBluePrint->define(member->getName(), member);
		}
		else if ( Parser::isMethodDeclaration((*it)) || Parser::isAlternateMethodDeclaration((*it)) ) {
			Runtime::Method *method = createMethod((*it));

			mBluePrint->defineMethod(method->getName(), method);
		}
	}
}

void Preprocessor::generateTokens(const std::string& content)
{
	Tokenizer t(mFilename, content);
	t.process();

	mTokens = t.tokens();
}

void Preprocessor::process(Designtime::BluePrint* blueprint)
{
	assert(blueprint);
	mBluePrint = blueprint;

	mFilename = mBluePrint->Filename();
	mTokens = mBluePrint->getTokens();

	// build object from tokens
	generateObject();

	mBluePrint = 0;
}


}
