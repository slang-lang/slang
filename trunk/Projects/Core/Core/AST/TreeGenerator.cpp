
// Header
#include "TreeGenerator.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/DoubleObject.h>
#include <Core/BuildInObjects/FloatObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Common/Exceptions.h>
#include <Core/Common/Method.h>
#include <Core/Common/Namespace.h>
#include <Core/Designtime/BluePrintEnum.h>
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Designtime/Exceptions.h>
#include <Core/Designtime/Parser/Parser.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Runtime/OperatorOverloading.h>
#include <Core/Runtime/TypeCast.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include <Utils.h>

// AST includes
#include "ControlStatements.h"
#include "Keywords.h"

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


TreeGenerator::TreeGenerator()
: mHasReturnStatement(false),
  mMethod(0),
  mStackFrame(0)
{
	// initialize virtual machine stuff
	mRepository = Controller::Instance().repository();
	mTypeSystem = Controller::Instance().typeSystem();
}

TreeGenerator::~TreeGenerator()
{
}

/*
 * collects all tokens of a given scope (excluding the surrounding curly brackets)
 */
void TreeGenerator::collectScopeTokens(TokenIterator& token, TokenList& tokens)
{
	expect(Token::Type::BRACKET_CURLY_OPEN, token);

	// find next balanced '{' & '}' pair for loop-body
	TokenIterator bodyEnd = findNextBalancedCurlyBracket(token, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

	++token;			// don't collect {-token

	while ( token != bodyEnd ) {
		tokens.push_back((*token++));
	}

	token = bodyEnd;	// don't collect }-token

	expect(Token::Type::BRACKET_CURLY_CLOSE, token);
}

void TreeGenerator::deinitialize()
{
	// pop tokens;
	mStackFrame->popTokens();
	// pop scope
	mStackFrame->popScope();
	// delete stack frame
	delete mStackFrame;
	mStackFrame = 0;

	// verify return statement existance
	if ( mMethod->QualifiedTypename() != Designtime::VoidObject::TYPENAME && !mHasReturnStatement ) {
		Token last;
		if ( !mMethod->getTokens().empty() ) {
			last = mMethod->getTokens().back();
		}

		throw Common::Exceptions::Exception("return statement missing in '" + mMethod->getFullScopeName() + "'", last.position());
	}

	// reset reuseable members
	mMethod = 0;
	mHasReturnStatement = false;
}

Node* TreeGenerator::expression(TokenIterator& start)
{
	Node* expression = parseCondition(start);

	for ( ; ; ) {
		Token::Type::E op = start->type();
		if ( op != Token::Type::AND &&
			 op != Token::Type::NAND &&
			 op != Token::Type::NOR &&
			 op != Token::Type::OR ) {
			return expression;
		}

		expression = new BooleanBinaryExpression(expression, (*start), parseCondition(++start));
	}
}

/*
 * executes the given tokens in a separate scope
 */
Statements* TreeGenerator::generate(const TokenList &tokens, bool allowBreakAndContinue)
{
	Statements* statements = 0;

	pushScope(0, allowBreakAndContinue);
		pushTokens(tokens);
			TokenIterator start = getTokens().begin();
			TokenIterator end = getTokens().end();

			statements = process(start, end);
		popTokens();
	popScope();

	return statements;
}

/*
 * generates the abstract syntax tree that is executed by the TreeInterpreter for the given method
 */
Statements* TreeGenerator::generateAST(Common::Method *method)
{
	Common::Method scope(*method);

	initialize(&scope);

	// generate AST
	Statements* statements = generate(mMethod->getTokens());

	deinitialize();

	return statements;
}

MethodScope* TreeGenerator::getEnclosingMethodScope(IScope* scope) const
{
	while ( scope ) {
		MethodScope* methodScope = dynamic_cast<MethodScope*>(scope->getEnclosingScope());
		if ( methodScope ) {
			return methodScope;
		}

		scope = scope->getEnclosingScope();
	}

	return 0;
}

MethodScope* TreeGenerator::getMethodScope(IScope* scope) const
{
	MethodScope* result = dynamic_cast<MethodScope*>(scope);

	return result ? result : getEnclosingMethodScope(scope);
}

IScope* TreeGenerator::getScope() const
{
	return mStackFrame->getScope();
}

const TokenList& TreeGenerator::getTokens() const
{
	return mStackFrame->getTokens();
}

inline Symbol* TreeGenerator::identify(TokenIterator& token) const
{
	Symbol *result = 0;
	bool onlyCurrentScope = false;
	std::string prev_identifier;	// hack to allow special 'this'-handling

	while ( token->type() == Token::Type::IDENTIFIER || token->type() == Token::Type::TYPE ) {
		std::string identifier = token->content();

		if ( !result ) {
			result = getScope()->resolve(identifier, onlyCurrentScope, Visibility::Private);

			prev_identifier = identifier;
		}
		else {
			switch ( result->getSymbolType() ) {
				case Symbol::IType::BluePrintEnumSymbol:
					result = dynamic_cast<Designtime::BluePrintEnum*>(result)->resolve(identifier, onlyCurrentScope, Visibility::Public);
					break;
				case Symbol::IType::BluePrintObjectSymbol:
					result = dynamic_cast<Designtime::BluePrintObject*>(result)->resolve(identifier, onlyCurrentScope, Visibility::Public);
					break;
				case Symbol::IType::NamespaceSymbol:
					result = dynamic_cast<Common::Namespace*>(result)->resolve(identifier, onlyCurrentScope, Visibility::Public);
					break;
				case Symbol::IType::ObjectSymbol:
					result = dynamic_cast<Runtime::Object*>(result)->resolve(identifier, onlyCurrentScope,
																	(prev_identifier == IDENTIFIER_THIS) ? Visibility::Private : Visibility::Public);
					break;
				case Symbol::IType::MethodSymbol:
					throw Common::Exceptions::NotSupported("cannot directly access locales of method");
			}

			onlyCurrentScope = true;
		}

		if ( lookahead(token)->type() != Token::Type::SCOPE ) {
			break;
		}

		token++;

		TokenIterator tmp = token;
		tmp++;
		if ( tmp->type() != Token::Type::IDENTIFIER && tmp->type() != Token::Type::TYPE ) {
			break;
		}

		token++;
	}

	return result;
}

void TreeGenerator::initialize(Common::Method* method)
{
	// initialize reuseable members
	mHasReturnStatement = false;
	mMethod = method;

	switch ( mMethod->getLanguageFeatureState() ) {
		case LanguageFeatureState::Deprecated: OSwarn("method '" + mMethod->getFullScopeName() + "' is marked as deprecated"); break;
		case LanguageFeatureState::NotImplemented: OSerror("method '" + mMethod->getFullScopeName() + "' is marked as not implemented"); throw Common::Exceptions::NotImplemented(mMethod->getFullScopeName()); break;
		case LanguageFeatureState::Stable: /* this is the normal language feature state, so there is no need to log anything here */ break;
		case LanguageFeatureState::Unknown: OSerror("unknown language feature state set for method '" + mMethod->getFullScopeName() + "'"); break;
		case LanguageFeatureState::Unstable: OSwarn("method '" + mMethod->getFullScopeName() + "' is marked as unstable"); break;
	}

	// create new stack frame
	mStackFrame = new StackFrame(0, mMethod, mMethod->provideSignature());
	// push scope
	mStackFrame->pushScope(mMethod, false, false);
	// push tokens
	mStackFrame->pushTokens(mMethod->getTokens());

	IScope* scope = getScope();

	// add 'this' and 'base' symbol to method
	Designtime::BluePrintObject* owner = dynamic_cast<Designtime::BluePrintObject*>(scope->getEnclosingScope());
	if ( owner && !method->isStatic() ) {
		Runtime::Object *object = mRepository->createInstance(owner->QualifiedTypename(), IDENTIFIER_THIS, PrototypeConstraints());
		object->setConst(mMethod->isConst());

		scope->define(IDENTIFIER_THIS, object);

		Designtime::Ancestors ancestors = owner->getAncestors();

		// BEWARE: this is only valid as long as we have single inheritance!!!
		for ( Designtime::Ancestors::const_iterator it = ancestors.begin(); it != ancestors.end(); ++it ) {
			Runtime::Object *base = mRepository->createInstance((*it).name(), IDENTIFIER_BASE, PrototypeConstraints());
			base->setConst(mMethod->isConst());

			scope->define(IDENTIFIER_BASE, base);
		}
	}

	// add parameters as locale variables
	for ( ParameterList::const_iterator it = mMethod->provideSignature().begin(); it != mMethod->provideSignature().end(); ++it ) {
		Runtime::Object *object = mRepository->createInstance(it->type(), it->name(), PrototypeConstraints());
		object->setMutability(it->mutability());

		scope->define(it->name(), object);
	}
}

AccessMode::E TreeGenerator::parseAccessMode(TokenIterator &token, bool isAtomicType)
{
	AccessMode::E result = isAtomicType ? AccessMode::ByValue : AccessMode::ByReference;

	if ( token->type() == Token::Type::RESERVED_WORD ) {
		result = AccessMode::convert(token->content());

		if ( result == AccessMode::Unspecified ) {
			// invalid type
			throw Common::Exceptions::SyntaxError("invalid token '" + token->content() + "' found", token->position());
		}

		++token;
	}

	return result;
}

Node* TreeGenerator::parseCondition(TokenIterator& start)
{
	Node* condition = parseExpression(start);

	for ( ; ; ) {
		Token::Type::E op = start->type();
		if ( op != Token::Type::COMPARE_EQUAL &&
			 op != Token::Type::COMPARE_GREATER &&
			 op != Token::Type::COMPARE_GREATER_EQUAL &&
			 op != Token::Type::COMPARE_LESS &&
			 op != Token::Type::COMPARE_LESS_EQUAL &&
			 op != Token::Type::COMPARE_UNEQUAL ) {
			 return condition;
		}

		condition = new BooleanBinaryExpression(condition, (*start), parseExpression(++start));
	}
}

Node* TreeGenerator::parseExpression(TokenIterator& start)
{
	Node* expression = parseFactors(start);

	for ( ; ; ) {
		Token::Type::E op = start->type();
		if ( op != Token::Type::BITAND &&
			 op != Token::Type::BITCOMPLEMENT &&
			 op != Token::Type::BITOR &&
			 op != Token::Type::MATH_ADDITION &&
			 op != Token::Type::MATH_SUBTRACT ) {
			return expression;
		}

		Token token = (*start);
		Node* right = parseFactors(++start);
		std::string type = resolveType(expression, token, right);

		expression = new BinaryExpression(expression, token, right, type);
	}
}

Node* TreeGenerator::parseFactors(TokenIterator& start)
{
	Node* factor = parseInfixPostfix(start);

	for ( ; ; ) {
		Token::Type::E op = start->type();
		if ( op != Token::Type::MATH_DIVIDE &&
			 op != Token::Type::MATH_MODULO &&
			 op != Token::Type::MATH_MULTIPLY ) {
			return factor;
		}

		Token token = (*start);
		Node* right = parseInfixPostfix(++start);
		std::string type = resolveType(factor, token, right);

		factor = new BinaryExpression(factor, token, right, type);
	}
}

Node* TreeGenerator::parseInfixPostfix(TokenIterator& start)
{
	Node* infixPostfix = 0;

	Token::Type::E op = start->type();

	// infix
	switch ( op ) {
		case Token::Type::MATH_ADDITION:
		case Token::Type::MATH_SUBTRACT:
			infixPostfix = new UnaryExpression((*start), parseTerm(++start));
			break;
		case Token::Type::OPERATOR_DECREMENT:
		case Token::Type::OPERATOR_INCREMENT:
			infixPostfix = new UnaryExpression((*start), parseTerm(++start), UnaryExpression::ValueType::LValue);
			break;
		case Token::Type::OPERATOR_NOT:
			infixPostfix = new BooleanUnaryExpression((*start), parseTerm(++start));
			break;
		default:
			infixPostfix = parseTerm(start);
			break;
	}

	op = start->type();

	// postfix
	switch ( op ) {
		case Token::Type::BRACKET_OPEN: {
			assert(!"[] operator not supported");
		} break;
		case Token::Type::OPERATOR_DECREMENT:
		case Token::Type::OPERATOR_INCREMENT: {
			Token tmp = (*start++);
			infixPostfix = new UnaryExpression(tmp, infixPostfix, UnaryExpression::ValueType::LValue);
		} break;
		case Token::Type::OPERATOR_NOT: {
			Token tmp = (*start++);
			tmp.resetTypeTo(Token::Type::OPERATOR_VALIDATE);

			infixPostfix = new UnaryExpression(tmp, infixPostfix);
		} break;
		case Token::Type::OPERATOR_IS: {
			++start;
			SymbolExpression* symbol = resolveWithThis(start, getScope());

			infixPostfix = new IsExpression(infixPostfix, symbol->getResultType());
		} break;
		default:
			break;
	}

	return infixPostfix;
}

Mutability::E TreeGenerator::parseMutability(TokenIterator& token)
{
	Mutability::E result = Mutability::Modify;

	if ( token->type() == Token::Type::MODIFIER ) {
		result = Mutability::convert(token->content());

		if ( result != Mutability::Const && result != Mutability::Modify ) {
			// local variables are only allowed to by modifiable or constant
			throw Common::Exceptions::SyntaxError("invalid token '" + token->content() + "' found", token->position());
		}

		++token;
	}

	return result;
}

SymbolExpression* TreeGenerator::parseSymbol(TokenIterator& token)
{
	SymbolExpression* exp = new RuntimeSymbolExpression(token->content(), "", false, false);
	++token;

	while ( token->type() == Token::Type::SCOPE ) {
		exp->mSymbolExpression = parseSymbol(++token);
	}

	return exp;
}

Node* TreeGenerator::parseTerm(TokenIterator& start)
{
	Node* term = 0;

	switch ( start->type() ) {
		case Token::Type::CONST_BOOLEAN: {
			term = new BooleanLiteralExpression(Tools::stringToBool(start->content()));
			++start;
		} break;
		case Token::Type::CONST_DOUBLE: {
			term = new DoubleLiteralExpression(Tools::stringToDouble(start->content()));
			++start;
		} break;
		case Token::Type::CONST_FLOAT: {
			term = new FloatLiteralExpression(Tools::stringToFloat(start->content()));
			++start;
		} break;
		case Token::Type::CONST_INTEGER: {
			term = new IntegerLiteralExpression(Tools::stringToInt(start->content()));
			++start;
		} break;
		case Token::Type::CONST_LITERAL: {
			term = new StringLiteralExpression(start->content());
			++start;
		} break;
		case Token::Type::IDENTIFIER:
		case Token::Type::TYPE: {
			term = process_identifier(start, true);
		} break;
		case Token::Type::KEYWORD: {
			term = process_expression_keyword(start);
		} break;
		case Token::Type::PARENTHESIS_OPEN: {
			++start;	// consume operator token

			term = expression(start);

			expect(Token::Type::PARENTHESIS_CLOSE, start);
			++start;	// consume operator token
		} break;
		default:
			throw Common::Exceptions::SyntaxError("identifier, literal or constant expected but " + start->content() + " found", start->position());
	}

	return term;
}

void TreeGenerator::popScope()
{
	mStackFrame->popScope();
}

void TreeGenerator::popTokens()
{
	mStackFrame->popTokens();
}

/*
 * loop through all tokens and redirect to the corresponding method
 */
Statements* TreeGenerator::process(TokenIterator& token, TokenIterator end)
{
	if ( token == end ) {
		// empty method provided
		return 0;
	}

	Statements* statements = new Statements((*token));

	TokenIterator localEnd = getTokens().end();

	while ( ( (token != localEnd) && (token != end) ) && (token->type() != Token::Type::ENDOFFILE) ) {
		Node* node = process_statement(token);

		if ( node ) {
			statements->mNodes.push_back(node);
		}
	}

	return statements;
}

/*
 * syntax:
 * assert( <expression> );
 */
Statement* TreeGenerator::process_assert(TokenIterator& token)
{
	Token start = (*token);

	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

	Common::Position position = token->position();

	Node* exp = expression(token);

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	++token;

	return new AssertStatement(start, exp);
}

/*
 * syntax:
 * break;
 */
Statement* TreeGenerator::process_break(TokenIterator& token)
{
	Token start = (*token);

	if ( !mStackFrame->allowBreakAndContinue() ) {
		throw Common::Exceptions::Exception("break not allowed here", token->position());
	}

	expect(Token::Type::SEMICOLON, token);
	++token;

	return new BreakStatement(start);
}

/*
 * syntax:
 * continue;
 */
Statement* TreeGenerator::process_continue(TokenIterator& token)
{
	Token start = (*token);

	if ( !mStackFrame->allowBreakAndContinue() ) {
		throw Common::Exceptions::Exception("continue not allowed here", token->position());
	}

	expect(Token::Type::SEMICOLON, token);
	++token;

	return new ContinueStatement(start);
}

/*
 * syntax:
 * copy <identifier>;
 */
Expression* TreeGenerator::process_copy(TokenIterator& token)
{
	Node* exp = expression(token);

	expect(Token::Type::SEMICOLON, token);
	++token;

	return new CopyExpression(exp);
}

/*
 * syntax:
 * delete <identifier>;
 */
Statement* TreeGenerator::process_delete(TokenIterator& token)
{
	Token start = (*token);

	Node* exp = expression(token);

	expect(Token::Type::SEMICOLON, token);
	++token;

	return new DeleteStatement(start, exp);
}

/*
 * syntax:
 * exit;
 */
Statement* TreeGenerator::process_exit(TokenIterator& token)
{
	Token start = (*token);

	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

	Node* exp = expression(token);

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	++token;

	return new ExitStatement(start, exp);
}

Expression* TreeGenerator::process_expression_keyword(TokenIterator& token)
{
	Expression* expression = 0;

	std::string keyword = (*token++).content();

	if ( keyword == KEYWORD_COPY ) {
		expression = process_copy(token);
	}
	else if ( keyword == KEYWORD_NEW ) {
		expression = process_new(token);
	}
	else if ( keyword == KEYWORD_TYPEID ) {
		expression = process_typeid(token);
	}
	else {
		throw Common::Exceptions::SyntaxError("invalid token '" + token->content() + "' found", token->position());
	}

	return expression;
}

/*
 * syntax:
 * for ( [<expression>]; [<condition>]; [<expression>] ) { ... }
 */
Statement* TreeGenerator::process_for(TokenIterator& token)
{
	Token start = (*token);

	expect(Token::Type::PARENTHESIS_OPEN, token);

	TokenIterator initializationBegin = ++token;

	const TokenIterator conditionBegin = ++findNext(initializationBegin, Token::Type::SEMICOLON);
	const TokenIterator increaseBegin = ++findNext(conditionBegin, Token::Type::SEMICOLON);

	TokenIterator expressionEnd = findNext(increaseBegin, Token::Type::PARENTHESIS_CLOSE);
	token = ++expressionEnd;

	// process our declaration part
	// {
	Node* initialization = process_statement(initializationBegin);
	// }

	// Condition parsing
	// {
	TokenIterator condBegin = conditionBegin;

	Node* condition = 0;
	if ( std::distance(condBegin, increaseBegin) > 1 ) {
		condition = expression(condBegin);
	}
	// }

	// Expression parsing
	// {
	TokenIterator exprBegin = increaseBegin;

	Node* iteration = process_statement(exprBegin);
	// }

	// Body parsing
	// {
	Node* loopBody = process_statement(token, true);
	// }

	return new ForStatement(start, initialization, condition, iteration, loopBody);
}

/*
 * syntax:
 * for ( <type definition> <identifier> : <instance> ) { ... }
 */
Statement* TreeGenerator::process_foreach(TokenIterator& token)
{
	Token start = (*token);

	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

	TypeDeclaration* typeDeclaration = process_type(token, Initialization::NotAllowed);

	expect(Token::Type::COLON, token);
	++token;

	expect(Token::Type::IDENTIFIER, token);

	SymbolExpression* symbol = parseSymbol(token);

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	++token;

	return new ForeachStatement(start, typeDeclaration, symbol, process_statement(token, true));
}

/*
 * executes a method, processes an assign statement and instantiates new types
 */
Node* TreeGenerator::process_identifier(TokenIterator& token, bool allowTypeCast)
{
	Node* node = 0;

	TokenIterator old = token;
	SymbolExpression* symbol = resolveWithThis(token, getScope());
	TokenIterator op = token;

	// type cast (followed by identifier or 'copy' || 'new' keyword)
	if ( allowTypeCast && (op->category() == Token::Category::Constant || op->type() == Token::Type::IDENTIFIER || op->type() == Token::Type::KEYWORD) ) {
		node = new TypecastExpression(old->content(), expression(++old));

		token = old;
	}
	// type declaration
	else if ( !allowTypeCast && op->type() == Token::Type::IDENTIFIER ) {
		node = process_type(old, Initialization::Allowed);

		token = old;
	}
	// method call
	else if ( op->type() == Token::Type::PARENTHESIS_OPEN ) {
		node = process_method(symbol, token);
	}
	// assignment
	else if ( op->category() == Token::Category::Assignment ) {
		if ( symbol->isConst() ) {
			throw Common::Exceptions::ConstCorrectnessViolated("tried to modify const symbol '" + symbol->mName + "'", op->position());
		}

		Token assignment(Token::Category::Assignment, Token::Type::ASSIGN, "=", op->position());

		Node* right = expression(++token);

		if ( op->type() != Token::Type::ASSIGN ) {
			Token operation;

			switch ( op->type() ) {
				case Token::Type::ASSIGN_ADDITION: operation = Token(Token::Category::Operator, Token::Type::MATH_ADDITION, "+", op->position()); break;
				case Token::Type::ASSIGN_BITAND: operation = Token(Token::Category::Operator, Token::Type::BITAND, "&", op->position()); break;
				case Token::Type::ASSIGN_BITCOMPLEMENT: operation = Token(Token::Category::Operator, Token::Type::BITCOMPLEMENT, "~", op->position()); break;
				case Token::Type::ASSIGN_BITOR: operation = Token(Token::Category::Operator, Token::Type::BITOR, "|", op->position()); break;
				case Token::Type::ASSIGN_DIVIDE: operation = Token(Token::Category::Operator, Token::Type::MATH_DIVIDE, "/", op->position()); break;
				case Token::Type::ASSIGN_MODULO: operation = Token(Token::Category::Operator, Token::Type::MATH_MODULO, "%", op->position()); break;
				case Token::Type::ASSIGN_MULTIPLY: operation = Token(Token::Category::Operator, Token::Type::MATH_MULTIPLY, "*", op->position()); break;
				case Token::Type::ASSIGN_SUBTRACT: operation = Token(Token::Category::Operator, Token::Type::MATH_SUBTRACT, "-", op->position()); break;
				default: throw Common::Exceptions::SyntaxError("assignment type expected", token->position());
			}

			right = new BinaryExpression(symbol, operation, right, resolveType(symbol, operation, right));
		}

		node = new Assignment(symbol, (*op), right, resolveType(symbol, assignment, right));
	}
	// --
	else if ( op->type() == Token::Type::OPERATOR_DECREMENT ) {
		if ( symbol->isConst() ) {
			throw Common::Exceptions::ConstCorrectnessViolated("tried to modify const symbol '" + symbol->mName + "'", op->position());
		}

		node = new UnaryExpression((*token), symbol, UnaryExpression::ValueType::LValue);
		++token;
	}
	// ++
	else if ( op->type() == Token::Type::OPERATOR_INCREMENT ) {
		if ( symbol->isConst() ) {
			throw Common::Exceptions::ConstCorrectnessViolated("tried to modify const symbol '" + symbol->mName + "'", op->position());
		}

		node = new UnaryExpression((*token), symbol, UnaryExpression::ValueType::LValue);
		++token;
	}
	// variable usage
	else {
		node = symbol;
	}

	return node;
}

/*
 * syntax:
 * if ( <expression> ) { ... }
 * else { ... }
 */
Statement* TreeGenerator::process_if(TokenIterator& token)
{
	Token start = (*token);

	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

	Node* exp = expression(token);

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	++token;

	Node* ifBlock = process_statement(token);

	Node* elseBlock = 0;
	if ( token != getTokens().end() &&
		 token->type() == Token::Type::KEYWORD && token->content() == KEYWORD_ELSE ) {
		++token;

		elseBlock = process_statement(token);
	}

	return new IfStatement(start, exp, ifBlock, elseBlock);
}

Node* TreeGenerator::process_keyword(TokenIterator& token)
{
	Node* node = 0;

	std::string keyword = (*token++).content();

	if ( keyword == KEYWORD_ASSERT ) {
		node = process_assert(token);
	}
	else if ( keyword == KEYWORD_BREAK ) {
		node = process_break(token);
	}
	else if ( keyword == KEYWORD_CONTINUE ) {
		node = process_continue(token);
	}
	else if ( keyword == KEYWORD_DELETE ) {
		node = process_delete(token);
	}
	else if ( keyword == KEYWORD_EXIT ) {
		node = process_exit(token);
	}
	else if ( keyword == KEYWORD_FOR ) {
		node = process_for(token);
	}
	else if ( keyword == KEYWORD_FOREACH ) {
		node = process_foreach(token);
	}
	else if ( keyword == KEYWORD_IF ) {
		node = process_if(token);
	}
	else if ( keyword == KEYWORD_PRINT ) {
		node = process_print(token);
	}
	else if ( keyword == KEYWORD_RETURN ) {
		node = process_return(token);
	}
	else if ( keyword == KEYWORD_SWITCH ) {
		node = process_switch(token);
	}
	else if ( keyword == KEYWORD_THROW ) {
		node = process_throw(token);
	}
	else if ( keyword == KEYWORD_TRY ) {
		node = process_try(token);
	}
	else if ( keyword == KEYWORD_WHILE ) {
		node = process_while(token);
	}
	else {
		throw Common::Exceptions::Exception("invalid keyword '" + token->content() + "' found", token->position());
	}

	return node;
}

/*
 * syntax:
 * <type> <identifier>(<parameter list>);
 */
MethodExpression* TreeGenerator::process_method(SymbolExpression* symbol, TokenIterator& token)
{
	Token start = (*token);

	TokenIterator tmp = token;

	TokenIterator opened = findNext(tmp, Token::Type::PARENTHESIS_OPEN);
	TokenIterator closed = findNextBalancedParenthesis(++opened);

	ParameterList params;
	ExpressionList parameterList;

	tmp = opened;
	// loop through all parameters separated by commas
	while ( tmp != closed ) {
		Node* exp = expression(tmp);

		params.push_back(Parameter::CreateDesigntime(
			ANONYMOUS_OBJECT,
			static_cast<Expression*>(exp)->getResultType()
		));
		parameterList.push_back(exp);

		if ( std::distance(tmp, closed) <= 0 ) {
			break;
		}
		tmp = findNext(tmp, Token::Type::COMMA);
		if ( std::distance(tmp, closed) < 0 ) {
			break;
		}
		tmp++;
	}

	token = ++closed;


	Common::Method* method = static_cast<Common::Method*>(resolveMethod(symbol, params, Visibility::Private));
	if ( !method ) {
		throw Common::Exceptions::UnknownIdentifer("method '" + symbol->toString() + "(" + toString(params) + ")' not found", token->position());
	}

	// prevent calls to non-const methods from const methods
	if ( mMethod->isConst() && method->getEnclosingScope() == mMethod->getEnclosingScope() && !method->isConst() ) {
		throw Common::Exceptions::ConstCorrectnessViolated("only calls to const methods are allowed in const method '" + mMethod->getFullScopeName() + "'", start.position());
	}

	// prevent calls to non-const method from const symbol
	if ( symbol->isConst() && !method->isConst() ) {
		throw Common::Exceptions::ConstCorrectnessViolated("usage of non-const symbol not allowed from within const symbol '" + symbol->toString() + "'", start.position());
	}

	return new MethodExpression(symbol, parameterList, method->QualifiedTypename(), method->isConst(), method->getEnclosingScope() == mMethod->getEnclosingScope());
}

/*
 * syntax:
 * new <Typename>([<parameter list>]);
 */
Expression* TreeGenerator::process_new(TokenIterator& token)
{
	TokenIterator start = token;

	Symbol* symbol = identify(start);
	if ( !symbol ) {
		throw Common::Exceptions::UnknownIdentifer("symbol '" + start->content() + "' not found", token->position());
	}
	if ( symbol->getSymbolType() != Symbol::IType::BluePrintEnumSymbol &&
		 symbol->getSymbolType() != Symbol::IType::BluePrintObjectSymbol ) {
		throw Common::Exceptions::InvalidSymbol("invalid symbol type found", token->position());
	}

	SymbolExpression* exp = resolveWithExceptions(token, getScope());

	SymbolExpression* inner = exp;
	while ( true ) {
		if ( inner->mSymbolExpression ) {
			inner = inner->mSymbolExpression;
		}
		else {
			inner->mSymbolExpression = new DesigntimeSymbolExpression("Constructor", "", false);
			inner->mSymbolExpression->mSurroundingScope = static_cast<Designtime::BluePrintObject*>(symbol);
			break;
		}
	}

	return new NewExpression(static_cast<Designtime::BluePrintObject*>(symbol)->QualifiedTypename(), process_method(exp, token));
}

/*
 * syntax:
 * print(<expression>);
 */
Statement* TreeGenerator::process_print(TokenIterator& token)
{
	Token start = (*token);

	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

	Common::Position position = token->position();
	Node* exp = expression(token);

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	++token;

	expect(Token::Type::SEMICOLON, token);
	++token;

	return new PrintStatement(start, exp);
}

/*
 * syntax:
 * return [<expression>];
 */
Statement* TreeGenerator::process_return(TokenIterator& token)
{
	Token start = (*token);
	mHasReturnStatement = true;

	Node* exp = 0;
	std::string returnType = Designtime::VoidObject::TYPENAME;

	if ( token->type() != Token::Type::SEMICOLON ) {
		exp = expression(token);
		returnType = static_cast<Expression*>(exp)->getResultType();
	}

	if ( mMethod->QualifiedTypename() != returnType ) {
		throw Common::Exceptions::TypeMismatch("returned type '" + returnType + "' does not match declared return type '" + mMethod->QualifiedTypename() + "'", token->position());
	}

	expect(Token::Type::SEMICOLON, token);
	++token;

	return new ReturnStatement(start, exp);
}

// syntax:
// { [<statements>] }
Statements* TreeGenerator::process_scope(TokenIterator& token, bool allowBreakAndContinue)
{
	TokenList scopeTokens;
	collectScopeTokens(token, scopeTokens);

	++token;

	return generate(scopeTokens, allowBreakAndContinue);
}

Node* TreeGenerator::process_statement(TokenIterator& token, bool allowBreakAndContinue)
{
	Node* node = 0;

	switch ( token->type() ) {
		case Token::Type::IDENTIFIER:
		case Token::Type::TYPE:
			node = process_identifier(token);
			break;
		case Token::Type::KEYWORD:
			node = process_keyword(token);
			break;
		case Token::Type::BRACKET_CURLY_OPEN:
			node = process_scope(token, allowBreakAndContinue);	// this opens a new scope
			break;
		case Token::Type::SEMICOLON:
			++token;
			break;
		default:
			throw Common::Exceptions::SyntaxError("invalid token '" + token->content() + "' found", token->position());
	}

	return node;
}

/*
 * syntax:
 * switch ( <expression> ) {
 *		[ case <identifier>: { ... } ]
 *		[ default: { ... } ]
 * }
 */
Statement* TreeGenerator::process_switch(TokenIterator& token)
{
	Token start = (*token);

	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

	// evaluate switch-expression
	Node* switchExpression = expression(token);

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	++token;

	expect(Token::Type::BRACKET_CURLY_OPEN, token);
	++token;

	CaseStatements caseStatements;
	Statements* defaultStatement = 0;

	// collect all case-blocks
	while ( token->type() != Token::Type::BRACKET_CURLY_CLOSE ) {
		if ( token->type() == Token::Type::KEYWORD && token->content() == KEYWORD_CASE ) {
			Token start = (*token);

			// skip case-label
			++token;

			Node* caseExpression = expression(token);

			expect(Token::Type::COLON, token);
			++token;

			TokenList caseTokens;
			collectScopeTokens(token, caseTokens);

			// process case-block tokens
			caseStatements.push_back(
				new CaseStatement(start, caseExpression, generate(caseTokens, true))
			);
		}
		else if ( token->type() == Token::Type::KEYWORD && token->content() == KEYWORD_DEFAULT ) {
			if ( defaultStatement ) {
				throw Common::Exceptions::SyntaxError("duplicate default entry for switch statement", token->position());
			}

			// skip default-label
			++token;

			expect(Token::Type::COLON, token);
			++token;

			TokenList defaultTokens;
			collectScopeTokens(token, defaultTokens);

			// process default-block tokens
			defaultStatement = generate(defaultTokens, true);
		}
		else {
			throw Common::Exceptions::Exception("invalid token '" + token->content() + "' found", token->position());
		}

		++token;
	}
	++token;

	return new SwitchStatement(start, switchExpression, caseStatements, defaultStatement);
}

/*
 * syntax:
 * throw [<expression>];
 */
Statement* TreeGenerator::process_throw(TokenIterator& token)
{
	Token start = (*token);

	if ( !mMethod->throws() ) {
		// this method is not marked as 'throwing', so we can't throw exceptions here
		throw Common::Exceptions::Exception(mMethod->getFullScopeName() + " throws although it is not marked with 'throws'", token->position());
	}

	Node* exp = 0;

	if ( token->type() != Token::Type::SEMICOLON ) {
		exp = expression(token);
	}

	expect(Token::Type::SEMICOLON, token);
	++token;

	return new ThrowStatement(start, exp);
}

/*
 * syntax:
 * try { ... }
 * [ catch { ... } ]
 * [ finally { ... } ]
 */
Statement* TreeGenerator::process_try(TokenIterator& token)
{
	Token start = (*token);

	expect(Token::Type::BRACKET_CURLY_OPEN, token);

	TokenList tryTokens;
	collectScopeTokens(token, tryTokens);

	// process try-block
	Statements* tryBlock = generate(tryTokens);

	TokenIterator tmp = ++token;
	TokenIterator localEnd = getTokens().end();

	std::list<TokenIterator> catchTokens;
	TokenIterator finallyToken = localEnd;

	// collect all catch- and finally-blocks
	for ( ; ; ) {
		if ( tmp != localEnd && tmp->content() == KEYWORD_CATCH ) {
			catchTokens.push_back(tmp);

			tmp = findNextBalancedCurlyBracket(tmp, localEnd, 0, Token::Type::BRACKET_CURLY_CLOSE);

			if ( std::distance(token, tmp) ) {
				token = tmp;	// set exit token
			}
		}
		else if ( tmp != localEnd && tmp->content() == KEYWORD_FINALLY ) {
			if ( finallyToken != localEnd ) {
				throw Common::Exceptions::SyntaxError("multiple finally blocks are not allowed");
			}

			finallyToken = tmp;
			tmp = findNextBalancedCurlyBracket(tmp, localEnd, 0, Token::Type::BRACKET_CURLY_CLOSE);

			if ( std::distance(token, tmp) ) {
				token = tmp;	// set exit token
			}
		}
		else {
			break;	// reached end of try-catch-finally-block
		}

		tmp++;
	}

	CatchStatements catchStatements;

	// process catch-blocks (if present)
	for ( std::list<TokenIterator>::const_iterator it = catchTokens.begin(); it != catchTokens.end(); ++it ) {
		TokenIterator catchIt = (*it);
		Token start = (*catchIt);

		++catchIt;

		pushScope();	// push a new scope to allow reuse of the same exception instance name

		TypeDeclaration* typeDeclaration = 0;

		// parse exception type (if present)
		if ( catchIt->type() == Token::Type::PARENTHESIS_OPEN ) {
			++catchIt;

			Symbol* symbol = identify(catchIt);
			if ( !symbol ) {
				throw Common::Exceptions::UnknownIdentifer("identifier '" + catchIt->content() + "' not found", catchIt->position());
			}
			if ( symbol->getSymbolType() != Symbol::IType::BluePrintEnumSymbol && symbol->getSymbolType() != Symbol::IType::BluePrintObjectSymbol ) {
				throw Common::Exceptions::SyntaxError("invalid symbol type '" + symbol->getName() + "' found", catchIt->position());
			}

			// create new exception type instance
			typeDeclaration = process_type(catchIt, Initialization::NotAllowed);

			expect(Token::Type::PARENTHESIS_CLOSE, catchIt);
			++catchIt;
		}

		TokenList tokens;
		collectScopeTokens(catchIt, tokens);

		catchStatements.push_back(
			new CatchStatement(start, typeDeclaration, generate(tokens))
		);

		popScope();		// pop exception instance scope
	}

	Statements* finallyBlock = 0;

	// process finally-block (if present)
	if ( finallyToken != localEnd ) {
		++finallyToken;

		TokenList finallyTokens;
		collectScopeTokens(finallyToken, finallyTokens);

		finallyBlock = generate(finallyTokens);
	}

	++token;

	return new TryStatement(start, tryBlock, catchStatements, finallyBlock);
}

/*
 * syntax:
 * <type> <identifier> [const|modify] [ref|val] [= <initialization>]
 */
TypeDeclaration* TreeGenerator::process_type(TokenIterator& token, Initialization::E initialization)
{
	Token start = (*token);

	SymbolExpression* symbolExp = resolveWithExceptions(token, getScope());
	if ( !symbolExp ) {
		throw Common::Exceptions::InvalidSymbol("invalid symbol '" + token->content() + "'", token->position());
	}

	std::string type = symbolExp->getResultType();

	PrototypeConstraints constraints = Designtime::Parser::collectRuntimePrototypeConstraints(token);

	expect(Token::Type::IDENTIFIER, token);

	std::string name = token->content();
	++token;

	Mutability::E mutability = parseMutability(token);

	Runtime::Object* object = mRepository->createInstance(type, name, constraints, Repository::InitilizationType::Final);
	object->setConst(mutability == Mutability::Const);

	getScope()->define(name, object);

	// non-atomic types are references by default
	AccessMode::E accessMode = parseAccessMode(token, object->isAtomicType());


	Node* assignment = 0;

	if ( token->type() == Token::Type::ASSIGN ) {
		if ( initialization != Initialization::Allowed ) {
			// type declaration without initialization has been requested
			throw Common::Exceptions::NotSupported("initialization is not allowed here", token->position());
		}

		Token copy = (*token);
		++token;

		assignment = expression(token);

/*
		if ( accessMode == AccessMode::ByReference &&
			static_cast<Expression*>(assignment)->getExpressionType() != Expression::ExpressionType::NewExpression ) {
			throw Runtime::Exceptions::InvalidAssignment("reference type expected", token->position());
		}
		else if ( accessMode == AccessMode::ByValue &&
			static_cast<Expression*>(assignment)->getExpressionType() == Expression::ExpressionType::NewExpression ) {
			throw Runtime::Exceptions::InvalidAssignment("value type expected", token->position());
		}
*/

		mTypeSystem->getType(type, copy, static_cast<Expression*>(assignment)->getResultType());
	}
	else if ( initialization == Initialization::Required ) {
		// initialization is required (probably because type inference is used) but no initialization sequence found
		throw Common::Exceptions::NotSupported("initialization required here", token->position());
	}
	else if ( initialization >= Initialization::Allowed &&
			  accessMode == AccessMode::ByReference &&
			  object->isAtomicType() ) {
		// atomic reference without initialization found
		throw Common::Exceptions::NotSupported("atomic references need to be initialized", token->position());
	}

	return new TypeDeclaration(start, type, constraints, name, mutability == Mutability::Const, accessMode == AccessMode::ByReference, assignment);
}

/*
 * typeid ( <expression> );
 */
Expression* TreeGenerator::process_typeid(TokenIterator& token)
{
	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

	Node* exp = expression(token);

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	++token;

	return new TypeidExpression(exp);
}

/*
 * syntax:
 * while ( <condition> ) { ... }
 */
Statement* TreeGenerator::process_while(TokenIterator& token)
{
	Token start = (*token);

	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

	Node* exp = expression(token);

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	++token;

	return new WhileStatement(start, exp, process_statement(token, true));
}

void TreeGenerator::pushScope(IScope* scope, bool allowBreakAndContinue)
{
	bool allowDelete = !scope;

	if ( !scope ) {
		scope = new SymbolScope(mStackFrame->getScope());
	}

	mStackFrame->pushScope(scope, allowDelete, allowBreakAndContinue || mStackFrame->allowBreakAndContinue());
}

void TreeGenerator::pushTokens(const TokenList& tokens)
{
	mStackFrame->pushTokens(tokens);
}

SymbolExpression* TreeGenerator::resolve(TokenIterator& token, IScope* base, bool onlyCurrentScope) const
{
	if ( !base ) {
		throw Common::Exceptions::Exception("invalid base scope");
	}

	// retrieve symbol for token from base scope
	Symbol* result = base->resolve(token->content(), onlyCurrentScope, onlyCurrentScope ? Visibility::Public : Visibility::Private);
	if ( !result ) {
		return 0;
	}

	++token;

	std::string name = result->getName();
	IScope* scope = 0;
	std::string type;

	SymbolExpression* symbol = 0;

	// set scope & type according to symbol type
	switch ( result->getSymbolType() ) {
		case Symbol::IType::BluePrintEnumSymbol:
			scope = static_cast<Designtime::BluePrintEnum*>(result);
			type = static_cast<Designtime::BluePrintEnum*>(result)->QualifiedTypename();

			if ( !static_cast<Designtime::BluePrintEnum*>(result)->isMember() ) {
				name = static_cast<Designtime::BluePrintEnum*>(result)->UnqualifiedTypename();
			}

			symbol = new DesigntimeSymbolExpression(name, type, static_cast<Designtime::BluePrintEnum*>(result)->isConst());
			break;
		case Symbol::IType::BluePrintObjectSymbol: {
			type = static_cast<Designtime::BluePrintObject*>(result)->QualifiedTypename();

			if ( !static_cast<Designtime::BluePrintObject*>(result)->isMember() ) {
				name = static_cast<Designtime::BluePrintObject*>(result)->UnqualifiedTypename();
			}

			scope = static_cast<Designtime::BluePrintObject*>(mRepository->findBluePrint(type));

			symbol = new DesigntimeSymbolExpression(name, type, static_cast<Designtime::BluePrintObject*>(result)->isConst());
		} break;
		case Symbol::IType::NamespaceSymbol:
			scope = static_cast<Common::Namespace*>(result);
			type = static_cast<Common::Namespace*>(result)->QualifiedTypename();

			symbol = new DesigntimeSymbolExpression(name, type, static_cast<Common::Namespace*>(result)->isConst());
			break;
		case Symbol::IType::ObjectSymbol: {
			// set scope according to result type
			scope = static_cast<Runtime::Object*>(result)->isAtomicType() ? 0 : static_cast<Runtime::Object*>(result)->getBluePrint();
			type = static_cast<Runtime::Object*>(result)->QualifiedTypename();

			symbol = new RuntimeSymbolExpression(name, type, static_cast<Runtime::Object*>(result)->isConst(), static_cast<Runtime::Object*>(result)->isMember());
		} break;
		case Symbol::IType::MethodSymbol:
			scope = 0;
			// don't set the result type yet because we first have to determine which method should get executed in case overloaded methods are present
			// this will be done in a later step (during method resolution)

			symbol = new RuntimeSymbolExpression(name, type, false, false);
			break;
	}

	if ( token->type() == Token::Type::SCOPE ) {
		symbol->mSymbolExpression = resolve(++token, scope, true);

		if ( !symbol->mSymbolExpression ) {
			// because exceptions are not allowed here we have to return 0 (without leaving memleaks)
			delete symbol;

			return 0;
		}
	}
	symbol->mSurroundingScope = base;

	return symbol;
}

SymbolExpression* TreeGenerator::resolveWithExceptions(TokenIterator& token, IScope* base, bool onlyCurrentScope) const
{
	SymbolExpression* exp = resolve(token, base, onlyCurrentScope);
	if ( !exp ) {
		throw Common::Exceptions::InvalidSymbol("invalid symbol '" + token->content() + "' found", token->position());
	}

	return exp;
}

SymbolExpression* TreeGenerator::resolveWithThis(TokenIterator& token, IScope* base, bool onlyCurrentScope) const
{
	IScope* outer = mMethod->getEnclosingScope();

	auto blueprint = dynamic_cast<Designtime::BluePrintObject*>(outer);
	if ( blueprint ) {
		// resolve symbol (without exceptions so that we can try to resolve a second time) by using "this" identifier
		SymbolExpression* exp = resolve(token, blueprint, true);
		if ( exp ) {
			// insert "this" symbol as "parent" of our recently resolved symbol
			SymbolExpression* symbol = new RuntimeSymbolExpression(IDENTIFIER_THIS, blueprint->QualifiedTypename(), mMethod->isConst(), false);
			symbol->mSymbolExpression = exp;

			return symbol;
		}

/*		// resolve symbol (without exceptions so that we can try to resolve a second time) by using "base" identifier
		auto ancestors = blueprint->getAncestors();
		for ( auto it = ancestors.begin(); it != ancestors.end(); ++it ) {
			// resolve without exceptions so that we can try to resolve a second time
			SymbolExpression* exp = resolve(token, (*it)->, true);
			if ( exp ) {
				// insert "this" symbol as "parent" of our recently resolved symbol
				SymbolExpression* symbol = new RuntimeSymbolExpression(IDENTIFIER_BASE, blueprint->QualifiedTypename(), mMethod->isConst(), false);
				symbol->mSymbolExpression = exp;

				return symbol;
			}
		}
*/
	}

	return resolveWithExceptions(token, base, onlyCurrentScope);
}

MethodSymbol* TreeGenerator::resolveMethod(SymbolExpression* symbol, const ParameterList& params, Visibility::E visibility) const
{
	if ( !symbol ) {
		throw Runtime::Exceptions::InvalidSymbol("invalid symbol provided");
	}

	bool onlyCurrentScope = false;

	SymbolExpression* inner = symbol;
	while ( true ) {
		if ( inner->mSymbolExpression && inner->mSymbolExpression->mSurroundingScope ) {
			onlyCurrentScope = true;

			inner = inner->mSymbolExpression;
			continue;
		}

		break;
	}

	MethodScope* scope = getMethodScope(inner->mSurroundingScope);
	if ( !scope ) {
		throw Common::Exceptions::Exception("invalid scope");
	}

	return scope->resolveMethod(inner->mName, params, onlyCurrentScope, visibility);
}

std::string TreeGenerator::resolveType(Node* left, const Token& operation, Node* right) const
{
	Expression* l = dynamic_cast<Expression*>(left);
	if ( !l ) {
		throw Common::Exceptions::Exception("invalid left expression");
	}

	Expression* r = dynamic_cast<Expression*>(right);
	if ( !r ) {
		throw Common::Exceptions::Exception("invalid right expression");
	}

	return mTypeSystem->getType(l->getResultType(), operation, r->getResultType());
}


}
}
