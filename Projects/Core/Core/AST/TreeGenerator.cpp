
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
: mMethod(0),
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
	// initialize reuseable members
	mHasReturnStatement = false;
	mMethod = method;

	// create new stack frame
	mStackFrame = new StackFrame(0, mMethod, mMethod->provideSignature());
	// push scope
	mStackFrame->pushScope(mMethod, false, false);
	// push tokens
	mStackFrame->pushTokens(mMethod->getTokens());

	// add parameters as locale variables
	for ( ParameterList::const_iterator it = mMethod->provideSignature().begin(); it != mMethod->provideSignature().end(); ++it ) {
		Runtime::Object *object = mRepository->createInstance(it->type(), it->name(), PrototypeConstraints());

		getScope()->define(it->name(), object);
	}

	// generate AST
	Statements* statements = generate(mMethod->getTokens());

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

	while ( token->type() == Token::Type::IDENTIFER || token->type() == Token::Type::TYPE ) {
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
		if ( tmp->type() != Token::Type::IDENTIFER && tmp->type() != Token::Type::TYPE ) {
			break;
		}

		token++;
	}

	return result;
}

Symbol* TreeGenerator::identifyMethod(TokenIterator& token, const ParameterList& params) const
{
	Symbol *result = 0;
	bool onlyCurrentScope = false;
	std::string prev_identifier;	// hack to allow special 'this'-handling

	while ( token->type() == Token::Type::IDENTIFER || token->type() == Token::Type::TYPE ) {
		std::string identifier = token->content();

		if ( !result ) {
			result = getScope()->resolve(identifier, onlyCurrentScope, Visibility::Private);

			prev_identifier = identifier;
		}
		else {
			switch ( result->getSymbolType() ) {
				case Symbol::IType::BluePrintEnumSymbol:
					result = dynamic_cast<Designtime::BluePrintEnum*>(result)->resolveMethod(identifier, params, true, Visibility::Public);
					break;
				case Symbol::IType::BluePrintObjectSymbol:
					result = dynamic_cast<Designtime::BluePrintObject*>(result)->resolveMethod(identifier, params, true, Visibility::Public);
					break;
				case Symbol::IType::NamespaceSymbol:
					result = dynamic_cast<Common::Namespace*>(result)->resolveMethod(identifier, params, true, Visibility::Public);
					break;
				case Symbol::IType::ObjectSymbol:
					result = dynamic_cast<Runtime::Object*>(result)->resolveMethod(identifier, params, true,
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
		if ( tmp->type() != Token::Type::IDENTIFER && tmp->type() != Token::Type::TYPE ) {
			break;
		}

		token++;
	}

	return result;
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
			SymbolExpression* symbol = resolve(start, getScope());

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
	SymbolExpression* exp = new RuntimeSymbolExpression(token->content(), "");
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
		case Token::Type::IDENTIFER:
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
Statements* TreeGenerator::process(TokenIterator& token, TokenIterator end, Token::Type::E terminator)
{
	Statements* statements = new Statements();

	while ( ( (token != getTokens().end()) && (token != end) ) &&
			( (token->type() != terminator) && (token->type() != Token::Type::ENDOFFILE) ) ) {
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
	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

	Common::Position position = token->position();

	Node* exp = expression(token);

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	++token;

	return new AssertStatement(exp, position);
}

/*
 * syntax:
 * break;
 */
Statement* TreeGenerator::process_break(TokenIterator& token)
{
	if ( !mStackFrame->allowBreakAndContinue() ) {
		throw Common::Exceptions::Exception("break not allowed here", token->position());
	}

	++token;

	return new BreakStatement();
}

/*
 * syntax:
 * continue;
 */
Statement* TreeGenerator::process_continue(TokenIterator& token)
{
	if ( !mStackFrame->allowBreakAndContinue() ) {
		throw Common::Exceptions::Exception("continue not allowed here", token->position());
	}

	++token;

	return new ContinueStatement();
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
	Node* exp = expression(token);

	expect(Token::Type::SEMICOLON, token);
	++token;

	return new DeleteStatement(exp);
}

/*
 * syntax:
 * exit;
 */
Statement* TreeGenerator::process_exit(TokenIterator& token)
{
	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

	Node* exp = expression(token);

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	++token;

	return new ExitStatement(exp);
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

	return new ForStatement(initialization, condition, iteration, loopBody);
}

/*
 * syntax:
 * for ( <type definition> <identifier> : <instance> ) { ... }
 */
Statement* TreeGenerator::process_foreach(TokenIterator& token)
{
	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

	TypeDeclaration* typeDeclaration = process_type(token, Initialization::NotAllowed);

	expect(Token::Type::COLON, token);
	++token;

	expect(Token::Type::IDENTIFER, token);

	SymbolExpression* symbol = parseSymbol(token);

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	++token;

	return new ForeachStatement(typeDeclaration, symbol, process_statement(token, true));
}

/*
 * executes a method, processes an assign statement and instantiates new types
 */
Node* TreeGenerator::process_identifier(TokenIterator& token, bool allowTypeCast)
{
	Node* node = 0;

	TokenIterator old = token;
	SymbolExpression* symbol = resolve(token, getScope());
	TokenIterator op = token;

	// type cast
	if ( allowTypeCast && op->type() == Token::Type::IDENTIFER ) {
		node = new TypecastExpression(old->content(), expression(++old));

		token = old;
	}
	// type declaration
	else if ( !allowTypeCast && op->type() == Token::Type::IDENTIFER ) {
		node = process_type(old, Initialization::Allowed);

		token = old;
	}
	// method call
	else if ( op->type() == Token::Type::PARENTHESIS_OPEN ) {
		node = process_method(symbol, token);
	}
	// assignment
	else if ( op->category() == Token::Category::Assignment ) {
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
		node = new UnaryExpression((*token), symbol, UnaryExpression::ValueType::LValue);
		++token;
	}
	// ++
	else if ( op->type() == Token::Type::OPERATOR_INCREMENT ) {
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

	return new IfStatement(exp, ifBlock, elseBlock);
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


	Common::Method* method = static_cast<Common::Method*>(resolveMethod(symbol, params, true, Visibility::Private));
	if ( !method ) {
		throw Common::Exceptions::UnknownIdentifer("method '" + symbol->toString() + "(" + toString(params) + ")' not found", token->position());
	}

	return new MethodExpression(symbol, parameterList, method->QualifiedTypename());
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
		throw Common::Exceptions::UnknownIdentifer("symbol '" + start->content() + "' not found");
	}
	if ( symbol->getSymbolType() != Symbol::IType::BluePrintEnumSymbol &&
		 symbol->getSymbolType() != Symbol::IType::BluePrintObjectSymbol ) {
		throw Designtime::Exceptions::DesigntimeException("invalid symbol type found");
	}

	SymbolExpression* exp = resolve(token, getScope());

	SymbolExpression* inner = exp;
	while ( true ) {
		if ( inner->mSymbolExpression ) {
			inner = inner->mSymbolExpression;
		}
		else {
			inner->mSymbolExpression = new DesigntimeSymbolExpression("Constructor", "");
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
	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

	Common::Position position = token->position();
	Node* exp = expression(token);

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	++token;

	expect(Token::Type::SEMICOLON, token);
	++token;

	return new PrintStatement(exp, position);
}

/*
 * syntax:
 * return [<expression>];
 */
Statement* TreeGenerator::process_return(TokenIterator& token)
{
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

	return new ReturnStatement(exp);
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
		case Token::Type::IDENTIFER:
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
			// skip case-label
			++token;

			Node* caseExpression = expression(token);

			expect(Token::Type::COLON, token);
			++token;

			TokenList caseTokens;
			collectScopeTokens(token, caseTokens);

			// process case-block tokens
			caseStatements.push_back(
				new CaseStatement(caseExpression, generate(caseTokens, true))
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

	return new SwitchStatement(switchExpression, caseStatements, defaultStatement);
}

/*
 * syntax:
 * throw [<expression>];
 */
Statement* TreeGenerator::process_throw(TokenIterator& token)
{
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

	return new ThrowStatement(exp);
}

/*
 * syntax:
 * try { ... }
 * [ catch { ... } ]
 * [ finally { ... } ]
 */
Statement* TreeGenerator::process_try(TokenIterator& token)
{
	expect(Token::Type::BRACKET_CURLY_OPEN, token);

	TokenList tryTokens;
	collectScopeTokens(token, tryTokens);

	// process try-block
	Statements* tryBlock = generate(tryTokens);

	TokenIterator tmp = ++token;

	std::list<TokenIterator> catchTokens;
	TokenIterator finallyToken = getTokens().end();

	// collect all catch- and finally-blocks
	for ( ; ; ) {
		if ( tmp != getTokens().end() && tmp->content() == KEYWORD_CATCH ) {
			catchTokens.push_back(tmp);

			tmp = findNextBalancedCurlyBracket(tmp, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

			if ( std::distance(token, tmp) ) {
				token = tmp;	// set exit token
			}
		}
		else if ( tmp != getTokens().end() && tmp->content() == KEYWORD_FINALLY ) {
			if ( finallyToken != getTokens().end() ) {
				throw Common::Exceptions::SyntaxError("multiple finally blocks are not allowed");
			}

			finallyToken = tmp;
			tmp = findNextBalancedCurlyBracket(tmp, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

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
		catchIt++;

		pushScope();	// push a new scope to allow reuse of the same exception instance name

		TypeDeclaration* typeDeclaration = 0;

		// parse exception type (if present)
		if ( catchIt->type() == Token::Type::PARENTHESIS_OPEN ) {
			catchIt++;

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
			new CatchStatement(typeDeclaration, generate(tokens))
		);

		popScope();		// pop exception instance scope
	}

	Statements* finallyBlock = 0;

	// process finally-block (if present)
	if ( finallyToken != getTokens().end() ) {
		++finallyToken;

		TokenList finallyTokens;
		collectScopeTokens(finallyToken, finallyTokens);

		finallyBlock = generate(finallyTokens);
	}

	++token;

	return new TryStatement(tryBlock, catchStatements, finallyBlock);
}

/*
 * syntax:
 * <type> <identifier> [const|modify] [ref|val] [= <initialization>]
 */
TypeDeclaration* TreeGenerator::process_type(TokenIterator& token, Initialization::E initialization)
{
	SymbolExpression* symbolExp = resolve(token, getScope());
	if ( !symbolExp ) {
		throw Common::Exceptions::InvalidSymbol("invalid symbol '" + token->content() + "'", token->position());
	}

	std::string type = symbolExp->getResultType();

	PrototypeConstraints constraints = Designtime::Parser::collectRuntimePrototypeConstraints(token);

	expect(Token::Type::IDENTIFER, token);

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
			throw Common::Exceptions::NotSupported("type initialization is not allowed here", token->position());
		}

		Token copy = (*token);
		++token;

		assignment = expression(token);

		Designtime::BluePrintGeneric* generic = mRepository->findBluePrint(static_cast<Expression*>(assignment)->getResultType());

		if ( accessMode == AccessMode::ByReference && generic->isAtomicType() ) {
			throw Runtime::Exceptions::InvalidAssignment("reference type expected", token->position());
		}
/* temporarily disabled because this prevents the usage of =operator with atomic types
		else if ( accessMode == AccessMode::ByValue && tmp.getReference().isValid() ) {
			throw Runtime::Exceptions::InvalidAssignment("value type expected", token->position());
		}
*/

		mTypeSystem->getType(type, copy, static_cast<Expression*>(assignment)->getResultType());
	}
	else if ( initialization == Initialization::Required ) {
		// initialization is required (probably because type inference is used) but no initialization sequence found
		throw Common::Exceptions::NotSupported("type inference required initialization", token->position());
	}
	else if ( initialization >= Initialization::Allowed &&
			  accessMode == AccessMode::ByReference &&
			  object->isAtomicType() ) {
		// atomic reference without initialization found
		throw Common::Exceptions::NotSupported("atomic references need to be initialized", token->position());
	}

	return new TypeDeclaration(type, constraints, name, mutability == Mutability::Const, accessMode == AccessMode::ByReference, assignment);
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
	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

	Node* exp = expression(token);

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	++token;

	return new WhileStatement(exp, process_statement(token, true));
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

SymbolExpression* TreeGenerator::resolve(TokenIterator& token, IScope* base) const
{
	if ( !base ) {
		throw Common::Exceptions::Exception("invalid base scope");
	}

	// retrieve symbol for token from base scope
	Symbol* result = base->resolve(token->content(), false, Visibility::Private);
	if ( !result ) {
		throw Common::Exceptions::InvalidSymbol("invalid symbol '" + token->content() + "' found", token->position());
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

			symbol = new DesigntimeSymbolExpression(name, type);
			break;
		case Symbol::IType::BluePrintObjectSymbol: {
			type = static_cast<Designtime::BluePrintObject*>(result)->QualifiedTypename();

			if ( !static_cast<Designtime::BluePrintObject*>(result)->isMember() ) {
				name = static_cast<Designtime::BluePrintObject*>(result)->UnqualifiedTypename();
			}

			scope = static_cast<Designtime::BluePrintObject*>(mRepository->findBluePrint(type));

			symbol = new DesigntimeSymbolExpression(name, type);
		} break;
		case Symbol::IType::NamespaceSymbol:
			scope = static_cast<Common::Namespace*>(result);
			type = static_cast<Common::Namespace*>(result)->QualifiedTypename();

			symbol = new DesigntimeSymbolExpression(name, type);
			break;
		case Symbol::IType::ObjectSymbol: {
			// set scope according to result type
			scope = static_cast<Runtime::Object*>(result)->isAtomicType() ? 0 : static_cast<Runtime::Object*>(result)->getBluePrint();
			type = static_cast<Runtime::Object*>(result)->QualifiedTypename();

			symbol = new RuntimeSymbolExpression(name, type);
		} break;
		case Symbol::IType::MethodSymbol:
			scope = 0;
			// don't set the result type yet because we first have to determine which method should get executed in case overloaded methods are present
			// this will be done in a later step (during method resolution)

			symbol = new RuntimeSymbolExpression(name, type);
			break;
	}

	if ( token->type() == Token::Type::SCOPE ) {
		symbol->mSymbolExpression = resolve(++token, scope);
	}
	symbol->mSurroundingScope = base;

	return symbol;
}

MethodSymbol* TreeGenerator::resolveMethod(SymbolExpression* symbol, const ParameterList& params, bool onlyCurrentScope, Visibility::E visibility) const
{
	if ( !symbol ) {
		throw Runtime::Exceptions::InvalidSymbol("invalid symbol provided");
	}

	SymbolExpression* inner = symbol;
	while ( true ) {
		if ( inner->mSymbolExpression && inner->mSymbolExpression->mSurroundingScope ) {
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
