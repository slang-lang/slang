
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
#include <Core/Defines.h>
#include <Core/Designtime/BluePrintEnum.h>
#include <Core/Designtime/Parser/Parser.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Runtime/Namespace.h>
#include <Core/Runtime/OperatorOverloading.h>
#include <Core/Runtime/TypeCast.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include <Utils.h>
#include <Core/Designtime/Exceptions.h>

// AST includes
#include "ControlStatements.h"
#include "Keywords.h"

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


TreeGenerator::TreeGenerator()
: mOwner(0)
{
	mRepository = Controller::Instance().repository();
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

NamedScope* TreeGenerator::getEnclosingNamedScope(IScope *scope) const
{
	if ( !scope ) {
		scope = getScope();
	}

	while ( scope ) {
		IScope* parent = scope->getEnclosingScope();

		if ( parent && parent->getScopeType() == IScope::IType::NamedScope ) {
			return dynamic_cast<NamedScope*>(parent);
		}

		scope = parent;
	}

	return 0;
}

Runtime::Namespace* TreeGenerator::getEnclosingNamespace(IScope* scope) const
{
	if ( !scope ) {
		scope = getScope();
	}

	while ( scope ) {
		IScope* parent = scope->getEnclosingScope();

		if ( parent && parent->getScopeType() == IScope::IType::MethodScope ) {
			Runtime::Namespace* result = dynamic_cast<Runtime::Namespace*>(parent);
			if ( result ) {
				return result;
			}
		}

		scope = parent;
	}

	return 0;
}

Runtime::Object* TreeGenerator::getEnclosingObject(IScope* scope) const
{
	if ( !scope ) {
		scope = getScope();
	}

	while ( scope ) {
		IScope* parent = scope->getEnclosingScope();

		if ( parent && parent->getScopeType() == IScope::IType::MethodScope ) {
			Runtime::Object* result = dynamic_cast<Runtime::Object*>(parent);
			if ( result ) {
				return result;
			}
		}

		scope = parent;
	}

	return 0;
}

IScope* TreeGenerator::getScope() const
{
	StackLevel* stack = Controller::Instance().stack()->current();

	return stack->getScope();
}

const TokenList& TreeGenerator::getTokens() const
{
	StackLevel* stack = Controller::Instance().stack()->current();

	return stack->getTokens();
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

			if ( !result ) {
				Runtime::Namespace* space = getEnclosingNamespace();
				if ( space ) {
					result = getScope()->resolve(space->QualifiedTypename() + "." + identifier, onlyCurrentScope, Visibility::Private);
				}
			}
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
					result = dynamic_cast<Runtime::Namespace*>(result)->resolve(identifier, onlyCurrentScope, Visibility::Public);
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

			// look for an overloaded method
			if ( result && result->getSymbolType() == Symbol::IType::MethodSymbol ) {
				result = dynamic_cast<MethodScope*>(mOwner)->resolveMethod(identifier, params, onlyCurrentScope, Visibility::Private);
			}
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
					result = dynamic_cast<Runtime::Namespace*>(result)->resolveMethod(identifier, params, true, Visibility::Public);
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

		expression = new BinaryExpression((*start), expression, parseFactors(++start));
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

		factor = new BinaryExpression((*start), factor, parseInfixPostfix(++start));
	}
}

Node* TreeGenerator::parseInfixPostfix(TokenIterator& start)
{
	Node* infixPostfix = 0;

	Token::Type::E op = start->type();

	// infix
	switch ( op ) {
		case Token::Type::MATH_ADDITION: {
			infixPostfix = new UnaryExpression((*start), expression(++start));
		} break;
		case Token::Type::MATH_SUBTRACT: {
			infixPostfix = new UnaryExpression((*start), expression(++start));
		} break;
		case Token::Type::OPERATOR_DECREMENT: {
			infixPostfix = new UnaryExpression((*start), expression(++start));
		} break;
		case Token::Type::OPERATOR_INCREMENT: {
			infixPostfix = new UnaryExpression((*start), expression(++start));
		} break;
		case Token::Type::OPERATOR_NOT: {
			infixPostfix = new UnaryExpression((*start), expression(++start));
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
			term = process_identifier(start);
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
		case Token::Type::SEMICOLON: {
			return 0;
		} break;
		default:
			throw Common::Exceptions::SyntaxError("identifier, literal or constant expected but " + start->content() + " found", start->position());
	}

	return term;
}

void TreeGenerator::popScope()
{
	StackLevel* stack = Controller::Instance().stack()->current();

	stack->popScope();
}

void TreeGenerator::popTokens()
{
	StackLevel* stack = Controller::Instance().stack()->current();

	stack->popTokens();
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

	Statement* statement = new AssertStatement(expression(token), position);

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	++token;

	return statement;
}

/*
 * syntax:
 * break;
 */
Statement* TreeGenerator::process_break(TokenIterator& /*token*/)
{
	return new BreakStatement();
}

/*
 * syntax:
 * continue;
 */
Statement* TreeGenerator::process_continue(TokenIterator& /*token*/)
{
	return new ContinueStatement();
}

/*
 * syntax:
 * copy <identifier>;
 */
Expression* TreeGenerator::process_copy(TokenIterator& token)
{
	Symbol* symbol = identify(token);
	if ( !symbol ) {
		throw Common::Exceptions::UnknownIdentifer("unknown identifier '" + token->content() + "'");
	}
	if ( symbol->getSymbolType() != Symbol::IType::ObjectSymbol ) {
		throw Common::Exceptions::Exception("object symbol expected!");
	}

	Runtime::Object* source = dynamic_cast<Runtime::Object*>(symbol);
	if ( !source ) {
		throw Common::Exceptions::Exception("nullptr access!");
	}

	return new CopyExpression(new VariableExpression((*token)));
}

/*
 * syntax:
 * delete <identifier>;
 */
Statement* TreeGenerator::process_delete(TokenIterator& token)
{
	DeleteStatement* statement = 0;

	TokenIterator end = findNext(token, Token::Type::SEMICOLON);

	Symbol* symbol = identify(token);
	if ( !symbol ) {
		throw Common::Exceptions::UnknownIdentifer(token->content(), token->position());
	}

	switch ( symbol->getSymbolType() ) {
		case Symbol::IType::ObjectSymbol: {
			statement = new DeleteStatement(new VariableExpression((*token)));
		} break;
		case Symbol::IType::BluePrintEnumSymbol:
		case Symbol::IType::BluePrintObjectSymbol:
		case Symbol::IType::MethodSymbol:
		case Symbol::IType::NamespaceSymbol:
		case Symbol::IType::UnknownSymbol:
			throw Common::Exceptions::TypeMismatch("member or local variable expected but symbol '" + symbol->getName() + "' found", token->position());
	}

	token = end;

	return statement;
}

/*
 * syntax:
 * exit;
 */
Statement* TreeGenerator::process_exit(TokenIterator& token)
{
	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

	Statement* statement = new ExitStatement(expression(token));

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	++token;

	return statement;
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
	else {
		throw Common::Exceptions::SyntaxError("invalid token '" + token->content() + "' found", token->position());
	}

	return expression;
}

/*
 * syntax:
 * for ( <expression>; <condition>; <expression> ) { ... }
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
	Node* loopBlock = process_statement(token);
	// }

	return new ForStatement(initialization, condition, iteration, loopBlock);
}

/*
 * syntax:
 * for ( <type definition> <identifier> : <instance> ) { ... }
 */
Statement* TreeGenerator::process_foreach(TokenIterator& token)
{
	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

	TypeDeclaration* typeDeclaration = process_type(token);	// maybe we should prevent type initialisation here with an additional parameter

	expect(Token::Type::COLON, token);
	++token;
	expect(Token::Type::IDENTIFER, token);

	TokenIterator identifier = token;

	++token;

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	++token;

	// Body parsing
	// {
	Node* loopBlock = process_statement(token);
	// }

	return new ForeachStatement(typeDeclaration, (*identifier), loopBlock);
}

/*
 * executes a method, processes an assign statement and instanciates new types
 */
Node* TreeGenerator::process_identifier(TokenIterator& token)
{
	Node* node = 0;

	TokenIterator op = lookahead(token);

	// type declaration
	if ( op->type() == Token::Type::IDENTIFER ) {
		node = process_type(token);
	}
	// method call
	else if ( op->type() == Token::Type::PARENTHESIS_OPEN ) {
		node = process_method(token);
	}
	// assignment
	else if ( op->category() == Token::Category::Assignment ) {
		TokenIterator identifier = token;
		TokenIterator assignment = ++token;
		Node* exp = 0;

		switch ( assignment->type() ) {
			case Token::Type::ASSIGN_ADDITION: exp = new BinaryExpression(Token(Token::Type::MATH_ADDITION), new VariableExpression((*identifier)), expression(++token)); break;
			case Token::Type::ASSIGN_BITAND: exp = new BinaryExpression(Token(Token::Type::BITAND), new VariableExpression((*identifier)), expression(++token)); break;
			case Token::Type::ASSIGN_BITCOMPLEMENT: exp = new BinaryExpression(Token(Token::Type::BITCOMPLEMENT), new VariableExpression((*identifier)), expression(++token)); break;
			case Token::Type::ASSIGN_BITOR: exp = new BinaryExpression(Token(Token::Type::BITOR), new VariableExpression((*identifier)), expression(++token)); break;
			case Token::Type::ASSIGN_DIVIDE: exp = new BinaryExpression(Token(Token::Type::MATH_DIVIDE), new VariableExpression((*identifier)), expression(++token)); break;
			case Token::Type::ASSIGN_MODULO: exp = new BinaryExpression(Token(Token::Type::MATH_MODULO), new VariableExpression((*identifier)), expression(++token)); break;
			case Token::Type::ASSIGN_MULTIPLY: exp = new BinaryExpression(Token(Token::Type::MATH_MULTIPLY), new VariableExpression((*identifier)), expression(++token)); break;
			case Token::Type::ASSIGN_SUBTRACT: exp = new BinaryExpression(Token(Token::Type::MATH_SUBTRACT), new VariableExpression((*identifier)), expression(++token)); break;
			default: exp = expression(++token); break;
		}

		node = new Assignment((*identifier), (*assignment), exp);
	}
/*
	// type cast
	else if ( op->type() == Token::Type::IDENTIFER ) {
		node = new TypecastExpression(token->content(), expression(++token));
	}
*/
	else if ( op->type() == Token::Type::OPERATOR_DECREMENT ) {
		Node* exp = new VariableExpression((*token));
		++token;

		node = new UnaryExpression((*token), exp);
		++token;
	}
	else if ( op->type() == Token::Type::OPERATOR_INCREMENT ) {
		Node* exp = new VariableExpression((*token));
		++token;

		node = new UnaryExpression((*token), exp);
		++token;
	}
	// variable usage
	else {
		node = new VariableExpression((*token));
		++token;

		//throw Common::Exceptions::Exception("invalid symbol type found!", token->position());
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

	TokenIterator condBegin = ++token;
	// find next balanced '(' & ')' pair
	TokenIterator condEnd = findNextBalancedParenthesis(condBegin);

	expect(Token::Type::PARENTHESIS_CLOSE, condEnd);

	token = ++condEnd;

	Node* ifBlock = process_statement(token);

	Node* elseBlock = 0;
	if ( token != getTokens().end() &&
		 token->type() == Token::Type::KEYWORD && token->content() == KEYWORD_ELSE ) {
		++token;

		elseBlock = process_statement(token);
	}

	return new IfStatement(expression(condBegin), ifBlock, elseBlock);
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
	else if ( keyword == KEYWORD_COPY ) {
		node = process_copy(token);
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
	else if ( keyword == KEYWORD_NEW ) {
		node = process_new(token);
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
	else if ( keyword == KEYWORD_TYPEID ) {
		node = process_typeid(token);
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
MethodExpression* TreeGenerator::process_method(TokenIterator& token)
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

	std::string name = token->content();

	token = ++closed;

	return new MethodExpression(name, parameterList);
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

	return new NewExpression(symbol, process_method(token));
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

	return statement;
}

/*
 * syntax:
 * return [<expression>];
 */
Statement* TreeGenerator::process_return(TokenIterator& token)
{
	return new ReturnStatement(expression(token));
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

	// find next open parenthesis '('
	TokenIterator condBegin = token;
	// find next balanced '(' & ')' pair
	TokenIterator condEnd = findNextBalancedParenthesis(condBegin);

	// evaluate switch-expression
	Node* switchExpression = expression(token);

	expect(Token::Type::PARENTHESIS_CLOSE, condEnd);
	++condEnd;

	expect(Token::Type::BRACKET_CURLY_OPEN, condEnd);
	++condEnd;

	// find next open curly bracket '{'
	TokenIterator bodyBegin = condEnd;
	// find next balanced '{' & '}' pair
	TokenIterator bodyEnd = findNextBalancedCurlyBracket(bodyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

	++bodyBegin;	// don't collect scope token
	token = bodyEnd;

	// CaseBlock is our data holder object for each case-block, hence the name
	class CaseBlock
	{
	public:
		CaseBlock(TokenIterator begin, TokenIterator end)
		: mBegin(begin),
		  mEnd(end)
		{ }

		TokenIterator mBegin;
		TokenIterator mEnd;
	};
	typedef std::list<CaseBlock> CaseBlocks;

	CaseBlocks caseBlocks;
	CaseBlock defaultBlock = CaseBlock(getTokens().end(), getTokens().end());

	// collect all case-blocks for further processing
	while ( bodyBegin != bodyEnd ) {
		if ( bodyBegin->type() == Token::Type::KEYWORD && bodyBegin->content() == KEYWORD_CASE ) {
			TokenIterator tmp = findNextBalancedCurlyBracket(bodyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

			caseBlocks.push_back(CaseBlock(bodyBegin, tmp));

			bodyBegin = tmp;
		}
		else if ( bodyBegin->type() == Token::Type::KEYWORD && bodyBegin->content() == KEYWORD_DEFAULT ) {
			if ( defaultBlock.mBegin != getTokens().end() ) {
				throw Common::Exceptions::SyntaxError("duplicate default entry for switch statement");
			}

			TokenIterator tmp = findNextBalancedCurlyBracket(bodyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

			defaultBlock = CaseBlock(bodyBegin, tmp);

			bodyBegin = tmp;
		}
		++bodyBegin;
	}

	CaseStatements caseStatements;

	// loop through all case-labels and match their expressions against the switch-expression
	for ( CaseBlocks::iterator it = caseBlocks.begin(); it != caseBlocks.end(); ++it ) {
		it->mBegin++;

		// evaluate switch-expression
		Node* caseExpression = expression(it->mBegin);

		expect(Token::Type::COLON, it->mBegin++);
		expect(Token::Type::BRACKET_CURLY_OPEN, it->mBegin++);	// don't collect scope token

		// collect case-block tokens
		TokenList caseTokens;
		while ( it->mBegin != it->mEnd ) {
			caseTokens.push_back((*it->mBegin));
			it->mBegin++;
		}

		Node* caseBlock = generate(caseTokens);

		// process/interpret case-block tokens
		caseStatements.push_back(
			new CaseStatement(caseExpression, caseBlock)
		);
	}

	Node* defaultStatement = 0;

	// execute the default block (if present)
	if ( defaultBlock.mBegin != getTokens().end() ) {
		defaultBlock.mBegin++;
		expect(Token::Type::COLON, defaultBlock.mBegin++);
		expect(Token::Type::BRACKET_CURLY_OPEN, defaultBlock.mBegin++);

		// collect default-block tokens
		TokenList defaultTokens;
		while ( defaultBlock.mBegin != defaultBlock.mEnd ) {
			defaultTokens.push_back((*defaultBlock.mBegin));
			defaultBlock.mBegin++;
		}

		// process/interpret case-block tokens
		defaultStatement = generate(defaultTokens);
	}

	return new SwitchStatement(switchExpression, caseStatements, defaultStatement);
}

/*
 * syntax:
 * throw [<expression>];
 */
Statement* TreeGenerator::process_throw(TokenIterator& token)
{
	// check if our parent scope is a method that is allowed to throw exceptions
	Runtime::Method* method = dynamic_cast<Runtime::Method*>(getEnclosingMethodScope());
	if ( method && !method->throws() ) {
		// this method is not marked as 'throwing', so we can't throw exceptions here
		OSwarn(std::string(method->getFullScopeName() + " throws although it is not marked with 'throws' in " + token->position().toString()).c_str());
	}

	ThrowStatement* statement = new ThrowStatement(expression(token));

	expect(Token::Type::SEMICOLON, token);
	++token;

	return statement;
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
			typeDeclaration = process_type(catchIt);

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
 * <type> <identifier> [= <initialization>]
 */
TypeDeclaration* TreeGenerator::process_type(TokenIterator& token)
{
	bool isConst = false;
	bool isFinal = false;

	Symbol* symbol = identify(token);
	if ( !symbol ) {
		throw Common::Exceptions::UnknownIdentifer("identifier '" + token->content() + "' not found", token->position());
	}

	token++;

	PrototypeConstraints constraints = Designtime::Parser::collectPrototypeConstraints(token);

	std::string name = token->content();

	expect(Token::Type::IDENTIFER, token);

	token++;

	std::string tmpStr = token->content();
	if ( tmpStr == MODIFIER_CONST || tmpStr == MODIFIER_FINAL ) {
		token++;

		if ( tmpStr == MODIFIER_CONST ) { isConst = true; }
		else if ( tmpStr == MODIFIER_FINAL ) { isFinal = true; }
	}

	TokenIterator assign = getTokens().end();
	if ( token->type() == Token::Type::ASSIGN ) {
		assign = ++token;
	}

	Node* assignment = 0;

	if ( assign != getTokens().end() ) {
		assignment = expression(token);
	}

	return new TypeDeclaration(symbol, constraints, name, assignment);
}

/*
 * typeid ( <expression> );
 */
Expression* TreeGenerator::process_typeid(TokenIterator& token)
{
	expect(Token::Type::PARENTHESIS_OPEN, token++);

	Symbol* symbol = identify(token);
	if ( symbol ) {
		switch ( symbol->getSymbolType() ) {
			case Symbol::IType::BluePrintEnumSymbol:
			case Symbol::IType::BluePrintObjectSymbol:
				//*result = Runtime::StringObject(static_cast<Designtime::BluePrintGeneric*>(symbol)->QualifiedTypename());
				break;
			case Symbol::IType::ObjectSymbol:
				//*result = Runtime::StringObject(static_cast<Runtime::Object*>(symbol)->QualifiedTypename());
				break;
			default:
				//*result = Runtime::StringObject("<not a valid symbol>");
				break;
		}
	}
	++token;

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	++token;

	return 0;
}

/*
 * syntax:
 * while ( <condition> ) { ... }
 */
Statement* TreeGenerator::process_while(TokenIterator& token)
{
	expect(Token::Type::PARENTHESIS_OPEN, token++);

	// find next open parenthesis '('
	TokenIterator condBegin = token;
	// find next balanced '(' & ')' pair
	TokenIterator condEnd = findNextBalancedParenthesis(condBegin);

	token = ++condEnd;

	Node* whileBlock = process_statement(token);

	return new WhileStatement(expression(condBegin), whileBlock);
}

void TreeGenerator::pushScope(IScope* scope)
{
	StackLevel* stack = Controller::Instance().stack()->current();

	bool allowDelete = !scope;

	if ( !scope ) {
		scope = new SymbolScope(stack->getScope());
	}

	stack->pushScope(scope, allowDelete);
}

void TreeGenerator::pushTokens(const TokenList& tokens)
{
	StackLevel* stack = Controller::Instance().stack()->current();

	stack->pushTokens(tokens);
}


}
}
