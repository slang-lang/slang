
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
{
	// initialize virtual machine stuff
	mRepository = Controller::Instance().repository();
	mStack = Controller::Instance().stack();
}

TreeGenerator::~TreeGenerator()
{
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

		expression = new BooleanBinaryExpression((*start), expression, parseCondition(++start));
	}
}

/*
 * executes the given tokens in a separate scope
 */
Statements* TreeGenerator::generate(const TokenList &tokens)
{
	Statements* statements = 0;

	pushTokens(tokens);
		TokenIterator start = getTokens().begin();
		TokenIterator end = getTokens().end();

		statements = process(start, end);
	popTokens();

	return statements;
}

MethodScope* TreeGenerator::getEnclosingMethodScope(IScope* scope) const
{
	if ( !scope ) {
		scope = getScope();
	}

	while ( scope ) {
		IScope* parent = scope->getEnclosingScope();

		if ( parent && parent->getScopeType() == IScope::IType::MethodScope ) {
			return dynamic_cast<MethodScope*>(parent);
		}

		scope = parent;
	}

	return 0;
}

Common::Namespace* TreeGenerator::getEnclosingNamespace(IScope* scope) const
{
	if ( !scope ) {
		scope = getScope();
	}

	while ( scope ) {
		IScope* parent = scope->getEnclosingScope();

		if ( parent && parent->getScopeType() == IScope::IType::MethodScope ) {
			return dynamic_cast<Common::Namespace*>(parent);
		}

		scope = parent;
	}

	return 0;
}

IScope* TreeGenerator::getScope() const
{
	return mStack->current()->getScope();
}

const TokenList& TreeGenerator::getTokens() const
{
	return mStack->current()->getTokens();
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
				case Symbol::IType::UnknownSymbol:
					throw Common::Exceptions::SyntaxError("unexpected symbol found");
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
				case Symbol::IType::UnknownSymbol:
					throw Common::Exceptions::SyntaxError("unexpected symbol found");
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

		condition = new BooleanBinaryExpression((*start), condition, parseExpression(++start));
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

		expression = new BinaryExpression(token, expression, right, type);
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

		factor = new BinaryExpression(token, factor, right, type);
	}
}

Node* TreeGenerator::parseInfixPostfix(TokenIterator& start)
{
	Node* infixPostfix = 0;

	Token::Type::E op = start->type();

	// infix
	switch ( op ) {
		case Token::Type::MATH_ADDITION: {
			infixPostfix = new UnaryExpression((*start), parseExpression(++start));
		} break;
		case Token::Type::MATH_SUBTRACT: {
			infixPostfix = new UnaryExpression((*start), parseExpression(++start));
		} break;
		case Token::Type::OPERATOR_DECREMENT: {
			infixPostfix = new UnaryExpression((*start), parseExpression(++start));
		} break;
		case Token::Type::OPERATOR_INCREMENT: {
			infixPostfix = new UnaryExpression((*start), parseExpression(++start));
		} break;
		case Token::Type::OPERATOR_NOT: {
			infixPostfix = new UnaryExpression((*start), parseExpression(++start));
		} break;
		default: {
			infixPostfix = parseTerm(start);
		} break;
	}

	op = start->type();

	// postfix
	switch ( op ) {
		case Token::Type::BRACKET_OPEN: {
			assert(!"[] operator not supported");
		} break;
		case Token::Type::OPERATOR_DECREMENT: {
			Node* exp = expression(start);

			infixPostfix = new UnaryExpression((*start), exp);
		} break;
		case Token::Type::OPERATOR_INCREMENT: {
			Node* exp = expression(start);

			infixPostfix = new UnaryExpression((*start), exp);
		} break;
		case Token::Type::OPERATOR_IS: {
			assert(!"is operator not supported");
		} break;
		case Token::Type::OPERATOR_NOT: {
			Node* exp = expression(start);

			infixPostfix = new UnaryExpression((*start), exp);
		} break;
		default: {
		} break;
	}

	return infixPostfix;
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

void TreeGenerator::popTokens()
{
	mStack->current()->popTokens();
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
	++token;

	return new BreakStatement();
}

/*
 * syntax:
 * continue;
 */
Statement* TreeGenerator::process_continue(TokenIterator& token)
{
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
	Node* loopBody = process_statement(token);
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

	TypeDeclaration* typeDeclaration = process_type(token, false);

	expect(Token::Type::COLON, token);
	++token;

	expect(Token::Type::IDENTIFER, token);

	SymbolExpression* symbol = resolve(token);

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	++token;

	return new ForeachStatement(typeDeclaration, symbol, process_statement(token));
}

/*
 * executes a method, processes an assign statement and instantiates new types
 */
Node* TreeGenerator::process_identifier(TokenIterator& token, bool allowTypeCast)
{
	Node* node = 0;

	TokenIterator old = token;
	SymbolExpression* symbol = resolve(token);
	TokenIterator op = token;

	// type cast
	if ( allowTypeCast && op->type() == Token::Type::IDENTIFER ) {
		node = new TypecastExpression(*old, expression(++old));

		token = old;
	}
	// type declaration
	else if ( !allowTypeCast && op->type() == Token::Type::IDENTIFER ) {
		node = process_type(old);

		token = old;
	}
	// method call
	else if ( op->type() == Token::Type::PARENTHESIS_OPEN ) {
		node = process_method(symbol, token);
	}
	// assignment
	else if ( op->category() == Token::Category::Assignment ) {
		Node* right = expression(++token);

		if ( op->type() != Token::Type::ASSIGN ) {
			Token operation;

			switch ( op->type() ) {
				case Token::Type::ASSIGN_ADDITION: operation = Token(Token::Type::MATH_ADDITION); break;
				case Token::Type::ASSIGN_BITAND: operation = Token(Token::Type::BITAND); break;
				case Token::Type::ASSIGN_BITCOMPLEMENT: operation = Token(Token::Type::BITCOMPLEMENT); break;
				case Token::Type::ASSIGN_BITOR: operation = Token(Token::Type::BITOR); break;
				case Token::Type::ASSIGN_DIVIDE: operation = Token(Token::Type::MATH_DIVIDE); break;
				case Token::Type::ASSIGN_MODULO: operation = Token(Token::Type::MATH_MODULO); break;
				case Token::Type::ASSIGN_MULTIPLY: operation = Token(Token::Type::MATH_MULTIPLY); break;
				case Token::Type::ASSIGN_SUBTRACT: operation = Token(Token::Type::MATH_SUBTRACT); break;
				default: throw Common::Exceptions::SyntaxError("assignment type execpted", token->position());
			}

			right = new BinaryExpression(operation, symbol, right, resolveType(symbol, operation, right));
		}

		node = new Assignment(symbol, (*op), right);
	}
	// --
	else if ( op->type() == Token::Type::OPERATOR_DECREMENT ) {
		node = new UnaryExpression((*token), symbol);
		++token;
	}
	// ++
	else if ( op->type() == Token::Type::OPERATOR_INCREMENT ) {
		node = new UnaryExpression((*token), symbol);
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

	ExpressionList parameterList;

	tmp = opened;
	// loop through all parameters separated by commas
	while ( tmp != closed ) {
		parameterList.push_back(expression(tmp));

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

	return new MethodExpression(symbol, parameterList);
}

/*
 * syntax:
 * new <Typename>([<parameter list>]);
 */
Expression* TreeGenerator::process_new(TokenIterator& token)
{
	Symbol* symbol = identify(token);
	if ( !symbol ) {
		throw Common::Exceptions::UnknownIdentifer("symbol '" + token->content() + "' not found");
	}
	if ( symbol->getSymbolType() != Symbol::IType::BluePrintEnumSymbol &&
		 symbol->getSymbolType() != Symbol::IType::BluePrintObjectSymbol ) {
		throw Designtime::Exceptions::DesigntimeException("invalid symbol type found");
	}

	return new NewExpression(symbol, process_method(0, token));
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
	Statement* statement = new PrintStatement(expression(token), position);

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	++token;

	expect(Token::Type::SEMICOLON, token);
	++token;

	return statement;
}

/*
 * syntax:
 * return [<expression>];
 */
Statement* TreeGenerator::process_return(TokenIterator& token)
{
	Node* exp = 0;

	if ( token->type() != Token::Type::SEMICOLON ) {
		exp = expression(token);
	}

	expect(Token::Type::SEMICOLON, token);
	++token;

	return new ReturnStatement(exp);
}

// syntax:
// { <statement> }
Statements* TreeGenerator::process_scope(TokenIterator& token)
{
	expect(Token::Type::BRACKET_CURLY_OPEN, token);
	++token;

	TokenIterator scopeBegin = token;
	TokenIterator scopeEnd = findNextBalancedCurlyBracket(scopeBegin, getTokens().end());

	token = scopeEnd;

	TokenList scopeTokens;
	while ( scopeBegin != scopeEnd ) {
		scopeTokens.push_back((*scopeBegin));
		scopeBegin++;
	}

	Statements* statements = generate(scopeTokens);

	expect(Token::Type::BRACKET_CURLY_CLOSE, token);
	++token;

	return statements;
}

Node* TreeGenerator::process_statement(TokenIterator& token)
{
	Node* node = 0;

	switch ( token->type() ) {
		case Token::Type::IDENTIFER:
		case Token::Type::PROTOTYPE:
		case Token::Type::TYPE:
			node = process_identifier(token);
			break;
		case Token::Type::KEYWORD:
			node = process_keyword(token);
			break;
		case Token::Type::BRACKET_CURLY_OPEN:
			node = process_scope(token);	// this opens a new scope
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

	// find next balanced '{' & '}' pair
	TokenIterator bodyEnd = findNextBalancedCurlyBracket(token, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

	expect(Token::Type::BRACKET_CURLY_OPEN, token);
	++token;

	CaseStatements caseStatements;

	Statements* defaultStatement = 0;

	// collect all case-blocks
	while ( token != bodyEnd ) {
		if ( token->type() == Token::Type::KEYWORD && token->content() == KEYWORD_CASE ) {
			// skip case-label
			++token;

			Node* caseExpression = expression(token);

			expect(Token::Type::COLON, token);
			++token;

			expect(Token::Type::BRACKET_CURLY_OPEN, token);
			++token;

			TokenIterator caseEnd = findNextBalancedCurlyBracket(token, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

			// collect case-block tokens
			TokenList caseTokens;
			while ( token != caseEnd ) {
				caseTokens.push_back((*token));
				++token;
			}

			Statements* caseBlock = generate(caseTokens);

			// process/interpret case-block tokens
			caseStatements.push_back(
				new CaseStatement(caseExpression, caseBlock)
			);
		}
		else if ( token->type() == Token::Type::KEYWORD && token->content() == KEYWORD_DEFAULT ) {
			if ( defaultStatement ) {
				throw Common::Exceptions::SyntaxError("duplicate default entry for switch statement");
			}

			// skip default-label
			++token;

			expect(Token::Type::COLON, token);
			++token;

			expect(Token::Type::BRACKET_CURLY_OPEN, token);
			++token;

			TokenIterator defaultEnd = findNextBalancedCurlyBracket(token, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

			// collect default-block tokens
			TokenList defaultTokens;
			while ( token != defaultEnd ) {
				defaultTokens.push_back((*token));
				++token;
			}

			// process/interpret case-block tokens
			defaultStatement = generate(defaultTokens);
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
	// check if our parent scope is a method that is allowed to throw exceptions
	Common::Method* method = dynamic_cast<Common::Method*>(getEnclosingMethodScope());
	if ( method && !method->throws() ) {
		// this method is not marked as 'throwing', so we can't throw exceptions here
		OSwarn(std::string(method->getFullScopeName() + " throws although it is not marked with 'throws' in " + token->position().toString()).c_str());
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

	// find next open curly bracket '{'
	TokenIterator tryBegin = token;
	// find next balanced '{' & '}' pair
	TokenIterator tryEnd = findNextBalancedCurlyBracket(tryBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

	tryBegin++;	// don't collect scope tokens
	token = tryEnd;

	// collect try-block tokens
	TokenList tryTokens;
	while ( tryBegin != tryEnd ) {
		tryTokens.push_back((*tryBegin));
		tryBegin++;
	}

	// process try-block
	Statements* tryBlock = generate(tryTokens);

	TokenIterator tmp = lookahead(token, 1);

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
			typeDeclaration = process_type(catchIt, false);

			expect(Token::Type::PARENTHESIS_CLOSE, catchIt);
			++catchIt;
		}

		expect(Token::Type::BRACKET_CURLY_OPEN, catchIt);

		// find next open curly bracket '{'
		TokenIterator catchBegin = catchIt;
		// find next balanced '{' & '}' pair
		TokenIterator catchEnd = findNextBalancedCurlyBracket(catchBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

		catchBegin++;		// don't collect scope token

		// collect catch-block tokens
		TokenList tokens;
		while ( catchBegin != catchEnd ) {
			tokens.push_back((*catchBegin));
			catchBegin++;
		}

		catchStatements.push_back(
			new CatchStatement(typeDeclaration, generate(tokens))
		);
	}

	Statements* finallyBlock = 0;

	// process finally-block (if present)
	if ( finallyToken != getTokens().end() ) {
		finallyToken++;
		expect(Token::Type::BRACKET_CURLY_OPEN, finallyToken);

		// find next open curly bracket '{'
		TokenIterator finallyBegin = finallyToken;
		// find next balanced '{' & '}' pair
		TokenIterator finallyEnd = findNextBalancedCurlyBracket(finallyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

		finallyBegin++;		// don't collect scope token;

		// collect finally-block tokens
		TokenList finallyTokens;
		while ( finallyBegin != finallyEnd ) {
			finallyTokens.push_back((*finallyBegin));
			finallyBegin++;
		}

		// TODO: should we execute the finally-block in any case (i.e. even though a return has been issued by the user)?
		finallyBlock = generate(finallyTokens);
	}

	++token;

	return new TryStatement(tryBlock, catchStatements, finallyBlock);
}

/*
 * syntax:
 * <type> <identifier> [const|modify] [ref|val] [= <initialization>]
 */
TypeDeclaration* TreeGenerator::process_type(TokenIterator& token, bool allowInitialization)
{
	bool isConst = false;
	bool isReference = false;

	Symbol* symbol = identify(token);
	if ( !symbol ) {
		throw Common::Exceptions::UnknownIdentifer("identifier '" + token->content() + "' not found", token->position());
	}

	++token;

	PrototypeConstraints constraints = Designtime::Parser::collectRuntimePrototypeConstraints(token);

	std::string name = token->content();

	expect(Token::Type::IDENTIFER, token);

	++token;

	if ( token->type() == Token::Type::MODIFIER ) {
		if ( token->content() == MODIFIER_CONST ) { isConst = true; }
		else if ( token->content() == MODIFIER_MODIFY ) { isConst = false; }
		else {
			// invalid modifier
			throw Common::Exceptions::SyntaxError("invalid token '" + token->content() + "' found", token->position());
		}

		++token;
	}

	if ( token->type() == Token::Type::RESERVED_WORD ) {
		if ( token->content() == RESERVED_WORD_BY_REFERENCE ) { isReference = true; }
		else if ( token->content() == RESERVED_WORD_BY_VALUE ) { isReference = false; }
		else {
			// invalid type
			throw Common::Exceptions::SyntaxError("invalid token '" + token->content() + "' found", token->position());
		}

		++token;
	}

	TokenIterator assign = getTokens().end();
	if ( token->type() == Token::Type::ASSIGN ) {
		if ( !allowInitialization ) {
			// type declaration without initialization has been requested
			throw Common::Exceptions::NotSupported("type initialization is not allowed here", token->position());
		}

		assign = ++token;
	}

	Node* assignment = 0;

	if ( assign != getTokens().end() ) {
		assignment = expression(token);
	}

	return new TypeDeclaration(symbol, constraints, name, isConst, isReference, assignment);
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

	return new WhileStatement(exp, process_statement(token));
}

void TreeGenerator::pushTokens(const TokenList& tokens)
{
	mStack->current()->pushTokens(tokens);
}

SymbolExpression* TreeGenerator::resolve(TokenIterator& token) const
{
	SymbolExpression* symbol = new SymbolExpression(*token++);

	while ( token->type() == Token::Type::SCOPE ) {
		symbol->mScope = resolve(++token);
	}

	return symbol;
}

std::string TreeGenerator::resolveType(Node* left, const Token& operation, Node* right) const
{
	return Controller::Instance().typeSystem()->getType(
		static_cast<Expression*>(left)->getResultType(),
		operation.type(),
		static_cast<Expression*>(right)->getResultType()
	);
}


}
}
