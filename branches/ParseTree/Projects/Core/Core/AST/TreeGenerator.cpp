
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
#include <Debugger/Debugger.h>
#include <Tools/Printer.h>
#include <Utils.h>

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

void TreeGenerator::expression(Runtime::Object* result, TokenIterator& start)
{
	parseCondition(result, start);

	for ( ; ; ) {
		Token::Type::E op = start->type();
		if ( op != Token::Type::AND &&
			 op != Token::Type::NAND &&
			 op != Token::Type::NOR &&
			 op != Token::Type::OR ) {
			return;
		}

		start++;	// consume operator token

		Runtime::Object v2;
		parseCondition(&v2, start);

		if ( op == Token::Type::AND && isTrue(*result) ) {
			*result = Runtime::BoolObject(isTrue(*result) && isTrue(v2));
		}
		else if ( op == Token::Type::NAND && !isTrue(*result) ) {
			*result = Runtime::BoolObject(!isTrue(*result) && !isTrue(v2));
		}
		else if ( op == Token::Type::NOR && !isTrue(*result) ) {
			*result = Runtime::BoolObject(!isTrue(*result) || !isTrue(v2));
		}
		else if ( op == Token::Type::OR && !isTrue(*result) ) {
			*result = Runtime::BoolObject(isTrue(*result) || isTrue(v2));
		}
	}
}

/*
 * executes the given tokens in a separate scope
 */
AST::Node* TreeGenerator::generate(const TokenList &tokens)
{
	pushScope();
		pushTokens(tokens);
			TokenIterator start = getTokens().begin();
			TokenIterator end = getTokens().end();

			Runtime::Object result;
			process(&result, start, end);
		popTokens();
	popScope();

	return 0;
}

NamedScope* TreeGenerator::getEnclosingMethodScope(IScope* scope) const
{
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

Repository* TreeGenerator::getRepository() const
{
	return mRepository;
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
				Runtime::Namespace* space = getEnclosingNamespace(getScope());
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

void TreeGenerator::parseCondition(Runtime::Object *result, TokenIterator& start)
{
	parseExpression(result, start);

	for ( ; ; ) {
		Token::Type::E op = start->type();
		if ( op != Token::Type::COMPARE_EQUAL &&
			 op != Token::Type::COMPARE_GREATER &&
			 op != Token::Type::COMPARE_GREATER_EQUAL &&
			 op != Token::Type::COMPARE_LESS &&
			 op != Token::Type::COMPARE_LESS_EQUAL &&
			 op != Token::Type::COMPARE_UNEQUAL ) {
			 break;
		}

		start++;	// consume comparator token

		Runtime::Object v2;
		parseExpression(&v2, start);

		switch ( op ) {
			case Token::Type::COMPARE_EQUAL:
				*result = Runtime::BoolObject(Runtime::operator_binary_equal(result, &v2));
				break;
			case Token::Type::COMPARE_GREATER:
				*result = Runtime::BoolObject(Runtime::operator_binary_greater(result, &v2));
				break;
			case Token::Type::COMPARE_GREATER_EQUAL:
				*result = Runtime::BoolObject(Runtime::operator_binary_greater_equal(result, &v2));
				break;
			case Token::Type::COMPARE_LESS:
				*result = Runtime::BoolObject(Runtime::operator_binary_less(result, &v2));
				break;
			case Token::Type::COMPARE_LESS_EQUAL:
				*result = Runtime::BoolObject(Runtime::operator_binary_less_equal(result, &v2));
				break;
			case Token::Type::COMPARE_UNEQUAL:
				*result = Runtime::BoolObject(!Runtime::operator_binary_equal(result, &v2));
				break;
			default:
				break;
		}
	}
}

void TreeGenerator::parseExpression(Runtime::Object *result, TokenIterator& start)
{
	parseFactors(result, start);

	for ( ; ; ) {
		Token::Type::E op = start->type();
		if ( op != Token::Type::BITAND &&
			 op != Token::Type::BITCOMPLEMENT &&
			 op != Token::Type::BITOR &&
			 op != Token::Type::MATH_ADDITION &&
			 op != Token::Type::MATH_SUBTRACT ) {
			return;
		}

		start++;	// consume operator token

		Runtime::Object v2;
		parseFactors(&v2, start);

		switch ( op ) {
			case Token::Type::BITAND:
				Runtime::operator_binary_bitand(result, &v2);
				break;
			case Token::Type::BITCOMPLEMENT:
				Runtime::operator_binary_bitcomplement(result, &v2);
				break;
			case Token::Type::BITOR:
				Runtime::operator_binary_bitor(result, &v2);
				break;
			case Token::Type::MATH_ADDITION:
				Runtime::operator_binary_plus(result, &v2);
				break;
			case Token::Type::MATH_SUBTRACT:
				Runtime::operator_binary_subtract(result, &v2);
				break;
			default:
				break;
		}
	}
}

void TreeGenerator::parseFactors(Runtime::Object *result, TokenIterator& start)
{
	parseInfixPostfix(result, start);

	for ( ; ; ) {
		Token::Type::E op = start->type();
		if ( op != Token::Type::MATH_DIVIDE &&
			 op != Token::Type::MATH_MODULO &&
			 op != Token::Type::MATH_MULTIPLY ) {
			return;
		}

		start++;	// consume operator token

		Runtime::Object v2;
		parseInfixPostfix(&v2, start);

		switch ( op ) {
			case Token::Type::MATH_DIVIDE:
				Runtime::operator_binary_divide(result, &v2);
				break;
			case Token::Type::MATH_MODULO:
				Runtime::operator_binary_modulo(result, &v2);
				break;
			case Token::Type::MATH_MULTIPLY:
				Runtime::operator_binary_multiply(result, &v2);
				break;
			default:
				break;
		}
	}
}

void TreeGenerator::parseInfixPostfix(Runtime::Object *result, TokenIterator& start)
{
	Token::Type::E op = start->type();

	// infix
	switch ( op ) {
		case Token::Type::MATH_SUBTRACT: {
			start++;
			parseExpression(result, start);
			Runtime::operator_unary_minus(result);
		} break;
		case Token::Type::OPERATOR_DECREMENT: {
			start++;
			parseExpression(result, start);
			Runtime::operator_unary_decrement(result);
		} break;
		case Token::Type::OPERATOR_INCREMENT: {
			start++;
			parseExpression(result, start);
			Runtime::operator_unary_increment(result);
		} break;
		case Token::Type::OPERATOR_NOT: {
			start++;
			parseExpression(result, start);
			Runtime::operator_unary_not(result);
		} break;
		case Token::Type::PARENTHESIS_OPEN: {
			start++;	// consume operator token

			expression(result, start);

			expect(Token::Type::PARENTHESIS_CLOSE, start);

			start++;	// consume operator token
		} break;
		default: {
			parseTerm(result, start);
		} break;
	}

	op = start->type();

	// postfix
	switch ( op ) {
/*
		case Token::Type::BRACKET_OPEN: {
			start++;	// consume operator token

			Object tmp;
			expression(&tmp, start);

			expect(Token::Type::BRACKET_CLOSE, start);

			operator_trinary_array(result, &tmp, result);

			start++;	// consume operator token
		} break;
*/
		case Token::Type::OPERATOR_DECREMENT: {
			Runtime::operator_unary_decrement(result);
			start++;
		} break;
		case Token::Type::OPERATOR_INCREMENT: {
			Runtime::operator_unary_increment(result);
			start++;
		} break;
		case Token::Type::OPERATOR_IS: {
			start++;

			Symbol* symbol = identify(start);
			if ( !symbol ) {
				throw Common::Exceptions::UnknownIdentifer("unkown identifier '" + start->content() + "' found", start->position());
			}

			start++;

			std::string compareType;

			if ( symbol->getSymbolType() == Symbol::IType::ObjectSymbol ) {
				compareType = static_cast<Runtime::Object*>(symbol)->QualifiedTypename();
			}
			else if ( symbol->getSymbolType() == Symbol::IType::BluePrintEnumSymbol || symbol->getSymbolType() == Symbol::IType::BluePrintObjectSymbol ) {
				PrototypeConstraints constraints = Designtime::Parser::collectPrototypeConstraints(start);

				compareType = dynamic_cast<Designtime::BluePrintGeneric*>(symbol)->QualifiedTypename();
				compareType = Designtime::Parser::buildConstraintTypename(compareType, constraints);
			}
			else {
				throw Common::Exceptions::SyntaxError("invalid symbol type found", start->position());
			}

			*result = Runtime::BoolObject(operator_binary_is(result, compareType));
		} break;
		case Token::Type::OPERATOR_NOT: {
			operator_unary_validate(result);
			start++;
		} break;
		default: {
		} break;
	}
}

void TreeGenerator::parseTerm(Runtime::Object *result, TokenIterator& start)
{
	switch ( start->type() ) {
		case Token::Type::CONST_BOOLEAN: {
			Runtime::BoolObject tmp(Tools::stringToBool(start->content()));
			Runtime::operator_binary_assign(result, &tmp);
			start++;
		} break;
		case Token::Type::CONST_DOUBLE: {
			Runtime::DoubleObject tmp(Tools::stringToDouble(start->content()));
			Runtime::operator_binary_assign(result, &tmp);
			start++;
		} break;
		case Token::Type::CONST_FLOAT: {
			Runtime::FloatObject tmp(Tools::stringToFloat(start->content()));
			Runtime::operator_binary_assign(result, &tmp);
			start++;
		} break;
		case Token::Type::CONST_INTEGER: {
			Runtime::IntegerObject tmp(Tools::stringToInt(start->content()));
			Runtime::operator_binary_assign(result, &tmp);
			start++;
		} break;
		case Token::Type::CONST_LITERAL: {
			Runtime::StringObject tmp(start->content());
			Runtime::operator_binary_assign(result, &tmp);
			start++;
		} break;
		case Token::Type::IDENTIFER:
		case Token::Type::TYPE: {
			// find out if we have to execute a method or simply get a stored variable

			TokenIterator tmpToken = start;
			Symbol *symbol = identify(start);
			if ( !symbol ) {
				throw Common::Exceptions::UnknownIdentifer("unknown/unexpected identifier '" + start->content() + "' found", start->position());
			}

			switch ( symbol->getSymbolType() ) {
				case Symbol::IType::MethodSymbol:
					process_method(tmpToken, result);
					start = tmpToken;
					start++;
					break;
				case Symbol::IType::ObjectSymbol:
					Runtime::operator_binary_assign(result, static_cast<Runtime::Object*>(symbol));
					start++;
					break;
				case Symbol::IType::BluePrintEnumSymbol:
				case Symbol::IType::BluePrintObjectSymbol: {
					start++;

					PrototypeConstraints constraints = Designtime::Parser::collectPrototypeConstraints(start);

					std::string newType = dynamic_cast<Designtime::BluePrintGeneric*>(symbol)->QualifiedTypename();
								newType = Designtime::Parser::buildConstraintTypename(newType, constraints);

					Runtime::Object tmp;
					expression(&tmp, start);

					Runtime::typecast(&tmp, newType);

					operator_binary_assign(result, &tmp);
				} break;
				case Symbol::IType::NamespaceSymbol:
				case Symbol::IType::UnknownSymbol:
					throw Common::Exceptions::SyntaxError("unexpected symbol resolved", start->position());
			}
		} break;
		case Token::Type::KEYWORD: {
			process_keyword(start, result);
			start++;
		} break;
		case Token::Type::SEMICOLON: {
		} break;
		default: {
			throw Common::Exceptions::SyntaxError("identifier, literal or constant expected but " + start->content() + " found", start->position());
		} break;
	}
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
void TreeGenerator::process(Runtime::Object *result, TokenIterator& token, TokenIterator end, Token::Type::E terminator)
{
	while ( ( (token != getTokens().end()) && (token != end) ) &&
			( (token->type() != terminator) && (token->type() != Token::Type::ENDOFFILE) ) ) {
		switch ( token->type() ) {
			case Token::Type::IDENTIFER:
			case Token::Type::PROTOTYPE:
			case Token::Type::TYPE:
				process_identifier(token, result, terminator == Token::Type::NIL ? Token::Type::SEMICOLON : terminator);
				break;
			case Token::Type::KEYWORD:
				process_keyword(token, result);
				break;
			case Token::Type::BRACKET_CURLY_OPEN:
				process_scope(token, result);	// this opens a new scope
				break;
			case Token::Type::SEMICOLON:
				break;
			default:
				throw Common::Exceptions::SyntaxError("invalid token '" + token->content() + "' found", token->position());
		}

		token++;	// consume token
	}
}

/*
 * syntax:
 * assert( <expression> );
 */
void TreeGenerator::process_assert(TokenIterator& token)
{
	expect(Token::Type::PARENTHESIS_OPEN, token++);

	Runtime:: Object condition;
	expression(&condition, token);

	if ( !isTrue(condition) ) {
		throw Runtime::Exceptions::AssertionFailed(condition.ToString(), token->position());
	}

	expect(Token::Type::PARENTHESIS_CLOSE, token++);
}

/*
 * syntax:
 * break;
 */
void TreeGenerator::process_break(TokenIterator& /*token*/)
{
	//mControlFlow = ControlFlow::Break;
}

/*
 * syntax:
 * continue;
 */
void TreeGenerator::process_continue(TokenIterator& /*token*/)
{
	//mControlFlow = ControlFlow::Continue;
}

/*
 * syntax:
 * copy <identifier>;
 */
void TreeGenerator::process_copy(TokenIterator& token, Runtime::Object* result)
{
	Symbol* symbol = identify(token);
	if ( !symbol ) {
		throw Common::Exceptions::UnknownIdentifer("unknown identifier '" + token->content() + "'");
	}
	if ( symbol->getSymbolType() != Symbol::IType::ObjectSymbol ) {
		throw Common::Exceptions::Exception("object symbol expected!");
	}

	if ( symbol == result ) {
		throw Common::Exceptions::Exception("cannot assign copy to same object");
	}

	Runtime::Object* source = dynamic_cast<Runtime::Object*>(symbol);
	if ( !source ) {
		throw Common::Exceptions::Exception("nullptr access!");
	}
	if ( source->QualifiedTypename() != result->QualifiedTypename() ) {
		throw Common::Exceptions::Exception("object copies are only allowed to same types");
	}

	result->copy(*source);
}

/*
 * syntax:
 * delete <identifier>;
 */
void TreeGenerator::process_delete(TokenIterator& token)
{
	TokenIterator end = findNext(token, Token::Type::SEMICOLON);

	Symbol* symbol = identify(token);
	if ( !symbol ) {
		throw Common::Exceptions::UnknownIdentifer(token->content(), token->position());
	}

	switch ( symbol->getSymbolType() ) {
		case Symbol::IType::ObjectSymbol: {
			Runtime::Object *object = static_cast<Runtime::Object*>(symbol);

			object->assign(Runtime::Object());
		} break;
		case Symbol::IType::BluePrintEnumSymbol:
		case Symbol::IType::BluePrintObjectSymbol:
		case Symbol::IType::MethodSymbol:
		case Symbol::IType::NamespaceSymbol:
		case Symbol::IType::UnknownSymbol:
			throw Common::Exceptions::TypeMismatch("member or local variable expected but symbol '" + symbol->getName() + "' found", token->position());
	}

	token = end;
}

/*
 * syntax:
 * exit;
 */
void TreeGenerator::process_exit(TokenIterator& /*token*/)
{
	//throw ControlFlow::ExitProgram;
}

/*
 * syntax:
 * for ( <expression>; <condition>; <expression> ) { ... }
 */
void TreeGenerator::process_for(TokenIterator& token, Runtime::Object* /*result*/)
{
	expect(Token::Type::PARENTHESIS_OPEN, token++);

	TokenIterator initializationBegin = token;

	const TokenIterator conditionBegin = ++findNext(initializationBegin, Token::Type::SEMICOLON);

	const TokenIterator increaseBegin = ++findNext(conditionBegin, Token::Type::SEMICOLON);

	// find next open curly bracket '{'
	TokenIterator expressionEnd = findNext(increaseBegin, Token::Type::PARENTHESIS_CLOSE);

	expect(Token::Type::BRACKET_CURLY_OPEN, ++expressionEnd);

	// find next balanced '{' & '}' pair for loop-body
	TokenIterator bodyBegin = expressionEnd;
	TokenIterator bodyEnd = findNextBalancedCurlyBracket(bodyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

	// process our declaration part
	// {
	Runtime::Object declarationTmp;
	process(&declarationTmp, initializationBegin, conditionBegin, Token::Type::SEMICOLON);
	// }

	bodyBegin++;		// don't collect scope token
	token = bodyEnd;

	TokenList loopTokens;
	while ( bodyBegin != bodyEnd ) {
		loopTokens.push_back((*bodyBegin));
		bodyBegin++;
	}

	for ( ; ; ) {
		// Condition parsing
		// {
		TokenIterator condBegin = conditionBegin;

		if ( std::distance(condBegin, increaseBegin) > 1 ) {
			Runtime::Object condition;
			expression(&condition, condBegin);

			if ( !isTrue(condition) ) {
				break;
			}
		}
		// }

		// Body parsing
		// {
		generate(loopTokens);
		// }

		// Expression parsing
		// {
		TokenIterator exprBegin = increaseBegin;

		Runtime::Object expressionTmp;
		process(&expressionTmp, exprBegin, expressionEnd, Token::Type::PARENTHESIS_CLOSE);
		// }
	}
}

/*
 * syntax:
 * for ( <type definition> <identifier> : <instance> ) { ... }
 */
void TreeGenerator::process_foreach(TokenIterator& token, Runtime::Object* /*result*/)
{
	expect(Token::Type::PARENTHESIS_OPEN, token++);

	TokenIterator typedefIt = token;

	// identify the loop variable's type
	Symbol* symbol = identify(token);
	if ( !symbol ) {
		throw Common::Exceptions::UnknownIdentifer("identifier '" + typedefIt->content() + "' not found", token->position());
	}
	if ( symbol->getSymbolType() != Symbol::IType::BluePrintEnumSymbol && symbol->getSymbolType() != Symbol::IType::BluePrintObjectSymbol ) {
		throw Common::Exceptions::SyntaxError("invalid symbol type '" + symbol->getName() + "' found", token->position());
	}
	token++;

	PrototypeConstraints constraints = Designtime::Parser::collectPrototypeConstraints(token);
	(void)constraints;

	expect(Token::Type::IDENTIFER, token);
	token++;
	expect(Token::Type::COLON, token);
	token++;
	expect(Token::Type::IDENTIFER, token);

	// identify collection symbol
	Runtime::Object* collection = dynamic_cast<Runtime::Object*>(identify(token));
	if ( !collection ) {
		throw Common::Exceptions::SyntaxError("invalid symbol '" + token->content() + "' found", token->position());
	}
	if ( !collection->isInstanceOf("System.IIterateable") ) {
		throw Common::Exceptions::SyntaxError("symbol '" + collection->getName() + "' is not derived from IIteratable", token->position());
	}
	token++;

	// get collection's forward iterator
	Runtime::Object iterator;
	collection->execute(&iterator, "getIterator", ParameterList());

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	token++;

	// find next balanced '{' & '}' pair for loop-body
	TokenIterator bodyBegin = token;
	TokenIterator bodyEnd = findNextBalancedCurlyBracket(bodyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

	bodyBegin++;		// don't collect scope token
	token = bodyEnd;

	TokenList loopTokens;
	while ( bodyBegin != bodyEnd ) {
		loopTokens.push_back((*bodyBegin));
		bodyBegin++;
	}

	for ( ; ; ) {
		pushScope();	// needed for loop variable

		// Setup
		// {
		Runtime::Object tmp;
		iterator.execute(&tmp, "hasNext", ParameterList());

		if ( !isTrue(tmp) ) {	// do we have more items to iterate over?
			break;
		}

		// create and define loop variable
		TokenIterator typedefItCopy = typedefIt;
		Runtime::Object* loop = process_type(typedefItCopy, symbol);

		// get current item
		iterator.execute(loop, "next", ParameterList());
		// }

		// Body parsing
		// {
		generate(loopTokens);

		popScope();	// needed for loop variable
		// }
	}
}

/*
 * executes a method, processes an assign statement and instanciates new types
 */
void TreeGenerator::process_identifier(TokenIterator& token, Runtime::Object* /*result*/, Token::Type::E terminator)
{
	TokenIterator tmpToken = token;

	Symbol* symbol = identify(token);
	if ( !symbol ) {
		throw Common::Exceptions::UnknownIdentifer("identifier '" + token->content() + "' not found", token->position());
	}

	if ( symbol->getSymbolType() == Symbol::IType::BluePrintEnumSymbol || symbol->getSymbolType() == Symbol::IType::BluePrintObjectSymbol ) {
		process_type(token, symbol);
	}
	else if ( symbol->getSymbolType() == Symbol::IType::MethodSymbol ) {
		token = tmpToken;	// reset token after call to identify

		Runtime::Object tmpObject;
		process_method(token, &tmpObject);
	}
	else if ( symbol->getSymbolType() == Symbol::IType::ObjectSymbol ) {
		// try to find an assignment token
		TokenIterator assign = findNext(token, Token::Type::ASSIGN, terminator);
		// find next terminator token
		TokenIterator end = findNext(assign, terminator);

		Runtime::Object* object = dynamic_cast<Runtime::Object*>(symbol);
		if ( object->isConst() ) {	// we tried to modify a const symbol (i.e. member, parameter or constant local variable)
			throw Common::Exceptions::ConstCorrectnessViolated("tried to modify const symbol '" + object->getFullScopeName() + "'", token->position());
		}
/*
		if ( object->isMember() && dynamic_cast<Method*>(mOwner)->isConst() ) {	// we tried to modify a member in a const method
			throw Common::Exceptions::ConstCorrectnessViolated("tried to modify member '" + object->getFullScopeName() + "' in const method '" + getScope()->getScopeName() + "'", token->position());
		}
*/

		expression(object, ++assign);

		if ( !object->isConst() && object->isFinal() ) {
			// we have modified a final symbol for the first time, we now have to set it so const
			object->setConst(true);
			object->setFinal(false);

			object->setMutability(Mutability::Const);
		}

		// assign == end should now be true
		token = end;
	}
	else {
		throw Common::Exceptions::Exception("invalid symbol type found!");
	}
}

/*
 * syntax:
 * if ( <expression> ) { ... }
 * else { ... }
 */
void TreeGenerator::process_if(TokenIterator& token, Runtime::Object* /*result*/)
{
	expect(Token::Type::PARENTHESIS_OPEN, token++);

	TokenIterator condBegin = token;
	// find next balanced '(' & ')' pair
	TokenIterator condEnd = findNextBalancedParenthesis(condBegin);

	expect(Token::Type::BRACKET_CURLY_OPEN, ++condEnd);

	// find next open curly bracket '{'
	TokenIterator bodyBegin = condEnd;
	// find next balanced '{' & '}' pair
	TokenIterator bodyEnd = findNextBalancedCurlyBracket(bodyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

	bodyBegin++;		// don't collect scope token
	token = bodyEnd;	// no matter what, at least set our token to our if-block's end

	// collect all tokens for our if-block
	TokenList ifTokens;
	while ( bodyBegin != bodyEnd ) {
		ifTokens.push_back((*bodyBegin));
		bodyBegin++;
	}

	if ( bodyEnd != getTokens().end() ) {
		bodyEnd++;
	}

	bool targetReached = true;	// initially don't collect else-block tokens
	TokenIterator elseBegin = getTokens().end();
	TokenIterator elseEnd = getTokens().end();

	// look for an else-token
	if ( bodyEnd != getTokens().end() && (bodyEnd->type() == Token::Type::KEYWORD && bodyEnd->content() == "else") ) {
		elseBegin = findNext(bodyEnd, Token::Type::BRACKET_CURLY_OPEN);
		// find next balanced '{' & '}' pair
		elseEnd = findNextBalancedCurlyBracket(elseBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

		for ( ; ; ) {
			// check if there is another if after our else-block
			TokenIterator tmpIf = elseEnd;
			tmpIf++;
			if ( tmpIf != getTokens().end() && tmpIf->type() == Token::Type::KEYWORD && tmpIf->content() == "else" ) {
				// find next balanced '{' & '}' pair
				elseEnd = findNextBalancedCurlyBracket(tmpIf, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

				continue;
			}

			token = elseEnd;
			break;
		}

		// reset elseBegin to bodyEnd + 1
		elseBegin = ++bodyEnd;

		targetReached = false;
	}

	TokenList elseTokens;

	while ( !targetReached ) {
		if ( elseBegin == elseEnd ) {
			targetReached = true;
		}

		elseTokens.push_back((*elseBegin));
		elseBegin++;
	}


	Runtime::Object condition;
	expression(&condition, condBegin);

	if ( isTrue(condition) ) {
		//mControlFlow = interpret(ifTokens, result);
	}
	else if ( !elseTokens.empty() ) {
		//mControlFlow = interpret(elseTokens, result);
	}
}

void TreeGenerator::process_keyword(TokenIterator& token, Runtime::Object *result)
{
	std::string keyword = (*token++).content();

	if ( keyword == KEYWORD_ASSERT ) {
		process_assert(token);
	}
	else if ( keyword == KEYWORD_BREAK ) {
		process_break(token);
	}
	else if ( keyword == KEYWORD_CONTINUE ) {
		process_continue(token);
	}
	else if ( keyword == KEYWORD_COPY ) {
		process_copy(token, result);
	}
	else if ( keyword == KEYWORD_DELETE ) {
		process_delete(token);
	}
	else if ( keyword == KEYWORD_EXIT ) {
		process_exit(token);
	}
	else if ( keyword == KEYWORD_FOR ) {
		process_for(token, result);
	}
	else if ( keyword == KEYWORD_FOREACH ) {
		process_foreach(token, result);
	}
	else if ( keyword == KEYWORD_IF ) {
		process_if(token, result);
	}
	else if ( keyword == KEYWORD_NEW ) {
		process_new(token, result);
	}
	else if ( keyword == KEYWORD_PRINT ) {
		process_print(token);
	}
	else if ( keyword == KEYWORD_RETURN ) {
		process_return(token, result);
	}
	else if ( keyword == KEYWORD_SWITCH ) {
		process_switch(token, result);
	}
	else if ( keyword == KEYWORD_THROW ) {
		process_throw(token, result);
	}
	else if ( keyword == KEYWORD_TRY ) {
		process_try(token, result);
	}
	else if ( keyword == KEYWORD_TYPEID ) {
		process_typeid(token, result);
	}
	else if ( keyword == KEYWORD_WHILE ) {
		process_while(token, result);
	}
}

/*
 * syntax:
 * <type> <identifier>(<parameter list>);
 */
void TreeGenerator::process_method(TokenIterator& token, Runtime::Object *result)
{
	TokenIterator tmp = token;

	TokenIterator opened = findNext(tmp, Token::Type::PARENTHESIS_OPEN);
	TokenIterator closed = findNextBalancedParenthesis(++opened);

	std::list<Runtime::Object> objectList;	// this is a hack to prevent that the provided object parameters run out of scope
	ParameterList params;

	tmp = opened;
	// loop through all parameters separated by commas
	while ( tmp != closed ) {
		objectList.push_back(Runtime::Object());

		Runtime::Object *obj = &objectList.back();
		expression(obj, tmp);

		params.push_back(Parameter::CreateRuntime(obj->QualifiedOuterface(), obj->getValue(), obj->getReference()));

		if ( std::distance(tmp, closed) <= 0 ) {
			break;
		}
		tmp = findNext(tmp, Token::Type::COMMA);
		if ( std::distance(tmp, closed) < 0 ) {
			break;
		}
		tmp++;
	}

	Symbol* symbol = identifyMethod(token, params);

	Runtime::Method* method = dynamic_cast<Runtime::Method*>(symbol);
	if ( !method) {
		throw Common::Exceptions::UnknownIdentifer("could not resolve identifier '" + token->content() + "' with parameters '" + toString(params) + "'", token->position());
	}

	// compare callee's constness with its parent's constness
	Runtime::Object* calleeParent = dynamic_cast<Runtime::Object*>(method->getEnclosingScope());
	if ( calleeParent && calleeParent->isConst() && !method->isConst() ) {
		// we want to call a non-const method of a const object... neeeeey!
		throw Common::Exceptions::ConstCorrectnessViolated("only calls to const methods are allowed for const object '" + calleeParent->getFullScopeName() + "'", token->position());
	}

	// check caller's constness
	Runtime::Method* owner = dynamic_cast<Runtime::Method*>(getEnclosingMethodScope(getScope()));
	if ( owner && owner->isConst() ) {
		if ( owner->getEnclosingScope() == method->getEnclosingScope() && !method->isConst() ) {
			// check target method's constness
			// this is a const method and we want to call a non-const method... neeeeey!
			throw Common::Exceptions::ConstCorrectnessViolated("only calls to const methods are allowed in const method '" + getScope()->getFullScopeName() + "'", token->position());
		}
	}

	// static method check
	if ( owner && owner->isStatic() && !method->isStatic() ) {
		throw Runtime::Exceptions::StaticException("non-static method \"" + method->ToString() + "\" called from static method \"" + owner->ToString() + "\"", token->position());
	}

	if ( method->isExtensionMethod() ) {
		method->execute(params, result, (*token));
	}
	else {
		//execute(method, params, result);
	}

	token = closed;
}

/*
 * syntax:
 * new <Typename>([<parameter list>]);
 */
void TreeGenerator::process_new(TokenIterator& token, Runtime::Object *result)
{
	std::string name;
	std::string type = token->content();

	Symbol* symbol = identify(token);
	if ( !symbol ) {
		throw Common::Exceptions::UnknownIdentifer("unknown identifier '" + type + "'");
	}
	if ( symbol->getSymbolType() != Symbol::IType::BluePrintObjectSymbol ) {
		throw Common::Exceptions::Exception("blueprint symbol expected!");
	}

	token++;

	PrototypeConstraints constraints = Designtime::Parser::collectPrototypeConstraints(token);

	expect(Token::Type::PARENTHESIS_OPEN, token);

	TokenIterator opened = token;
	TokenIterator closed = findNextBalancedParenthesis(++opened);

	token = closed;

	std::list<Runtime::Object> objectList;	// this is a hack to prevent that the provided object parameters run out of scope
	ParameterList params;

	TokenIterator tmp = opened;
	// loop through all parameters separated by commas
	while ( tmp != closed ) {
		objectList.push_back(Runtime::Object());

		Runtime::Object *obj = &objectList.back();
		expression(obj, tmp);

		params.push_back(Parameter::CreateRuntime(obj->QualifiedOuterface(), obj->getValue(), obj->getReference()));

		if ( std::distance(tmp, closed) <= 0 ) {
			break;
		}
		tmp = findNext(tmp, Token::Type::COMMA);
		if ( std::distance(tmp, closed) < 0 ) {
			break;
		}
		tmp++;
	}

	// create initialized reference of new object
	*result = *getRepository()->createReference(static_cast<Designtime::BluePrintGeneric*>(symbol), name, constraints, Repository::InitilizationType::Final);

	// execute new object's constructor
	result->Constructor(params);
}

/*
 * syntax:
 * print(<expression>);
 */
void TreeGenerator::process_print(TokenIterator& token)
{
	expect(Token::Type::PARENTHESIS_OPEN, token++);

	Runtime::Object text;
	expression(&text, token);

	::Utils::PrinterDriver::Instance()->print(text.getValue().toStdString(), token->position().mFile, token->position().mLine);

	expect(Token::Type::PARENTHESIS_CLOSE, token++);
}

/*
 * syntax:
 * return [<expression>];
 */
void TreeGenerator::process_return(TokenIterator& token, Runtime::Object *result)
{
	expression(result, token);

	//mControlFlow = ControlFlow::Return;
}

// syntax:
// { <statement> }
void TreeGenerator::process_scope(TokenIterator& token, Runtime::Object* /*result*/)
{
	expect(Token::Type::BRACKET_CURLY_OPEN, token++);

	TokenIterator scopeBegin = token;
	TokenIterator scopeEnd = findNextBalancedCurlyBracket(scopeBegin, getTokens().end());

	token = scopeEnd;

	TokenList scopeTokens;
	while ( scopeBegin != scopeEnd ) {
		scopeTokens.push_back((*scopeBegin));
		scopeBegin++;
	}

	generate(scopeTokens);

	expect(Token::Type::BRACKET_CURLY_CLOSE, token);
}

/*
 * syntax:
 * switch ( <expression> ) {
 *		[ case <identifier>: { ... } ]
 *		[ default: { ... } ]
 * }
 */
void TreeGenerator::process_switch(TokenIterator& token, Runtime::Object* /*result*/)
{
	expect(Token::Type::PARENTHESIS_OPEN, token++);

	// find next open parenthesis '('
	TokenIterator condBegin = token;
	// find next balanced '(' & ')' pair
	TokenIterator condEnd = findNextBalancedParenthesis(condBegin);

	// evaluate switch-expression
	Runtime::Object expr;
	expression(&expr, token);

	expect(Token::Type::BRACKET_CURLY_OPEN, ++condEnd);

	// find next open curly bracket '{'
	TokenIterator bodyBegin = condEnd;
	// find next balanced '{' & '}' pair
	TokenIterator bodyEnd = findNextBalancedCurlyBracket(bodyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

	bodyBegin++;	// don't collect scope token
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
		bodyBegin++;
	}

	// loop through all case-labels and match their expressions against the switch-expression
	for ( CaseBlocks::iterator it = caseBlocks.begin(); it != caseBlocks.end(); ++it ) {
		it->mBegin++;

		// evaluate switch-expression
		Runtime::Object condition;
		expression(&condition, it->mBegin);

		// compare case block expression with switch-expression
		if ( operator_binary_equal(&expr, &condition) ) {
			expect(Token::Type::COLON, it->mBegin++);
			expect(Token::Type::BRACKET_CURLY_OPEN, it->mBegin++);	// don't collect scope token

			// collect case-block tokens
			TokenList caseTokens;
			while ( it->mBegin != it->mEnd ) {
				caseTokens.push_back((*it->mBegin));
				it->mBegin++;
			}

			// process/interpret case-block tokens
			generate(caseTokens);
		}
	}

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
		generate(defaultTokens);
	}
}

/*
 * syntax:
 * throw [<expression>];
 */
void TreeGenerator::process_throw(TokenIterator& token, Runtime::Object* /*result*/)
{
	// check if our parent scope is a method that is allowed to throw exceptions
	Runtime::Method* method = dynamic_cast<Runtime::Method*>(getEnclosingMethodScope(getScope()));
	if ( method && !method->throws() ) {
		// this method is not marked as 'throwing', so we can't throw exceptions here
		OSwarn(std::string(method->getFullScopeName() + " throws although it is not marked with 'throws' in " + token->position().toString()).c_str());
	}

	Runtime::Object* data = getRepository()->createInstance(OBJECT, ANONYMOUS_OBJECT, PrototypeConstraints());
	expression(data, token);

	//mControlFlow = ControlFlow::Throw;
	Controller::Instance().stack()->exception() = Runtime::ExceptionData(data, token->position());

	expect(Token::Type::SEMICOLON, token);
}

/*
 * syntax:
 * try { ... }
 * [ catch { ... } ]
 * [ finally { ... } ]
 */
void TreeGenerator::process_try(TokenIterator& token, Runtime::Object* /*result*/)
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
	generate(tryTokens);

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

	// process catch-blocks (if present)
	for ( std::list<TokenIterator>::const_iterator it = catchTokens.begin(); it != catchTokens.end(); ++it ) {
		TokenIterator catchIt = (*it);
		catchIt++;

		pushScope();	// push a new scope to allow reuse of the same exception instance name

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
			Runtime::Object* type = process_type(catchIt, symbol);

			expect(Token::Type::PARENTHESIS_CLOSE, catchIt++);

			if ( !type || !Controller::Instance().stack()->exception().getData() ) {
				throw Common::Exceptions::Exception("could not create exception type instance", catchIt->position());
			}

			// compare given exception type with thrown type inheritance
			if ( !Controller::Instance().stack()->exception().getData()->isInstanceOf(type->QualifiedTypename()) ) {
				popScope();		// pop exception instance scope
				continue;
			}

			// exception type match with thrown type, start with the real exception handling
			operator_binary_assign(type, Controller::Instance().stack()->exception().getData());
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

		// execute catch-block if an exception has been thrown
		generate(tokens);

		Runtime::Object* ex = Controller::Instance().stack()->exception().getData();
		if ( ex ) {
			getScope()->define(ex->getName(), ex);
		}

		popScope();		// pop exception instance scope
		break;
	}

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
		generate(finallyTokens);
	}
}

/*
 * syntax:
 * <type> <identifier> [= <initialization>]
 */
Runtime::Object* TreeGenerator::process_type(TokenIterator& token, Symbol* symbol)
{
	bool isConst = false;
	bool isFinal = false;

	token++;

	PrototypeConstraints constraints = Designtime::Parser::collectPrototypeConstraints(token);

	std::string name = token->content();

	expect(Token::Type::IDENTIFER, token);

	token++;

/*	Array handling
	bool isArray = false;
	int size = 0;

	if (  token->type() == Token::Type::BRACKET_OPEN ) {
		isArray = true;
		token++;

		Object tmp;
		try {
			expression(&tmp, token);
		}
		catch ( ControlFlow::E &e ) {
			mControlFlow = e;
			return 0;
		}

		size = tmp.getValue().toInt();

		expect(Token::Type::BRACKET_CLOSE, token++);
	}
*/

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


		Runtime::Object* object = getRepository()->createInstance(static_cast<Designtime::BluePrintGeneric*>(symbol), name, constraints);

	getScope()->define(name, object);

	//if ( isArray ) object->setArray(true, (size_t)size);
	if ( isConst ) object->setConst(true);
	if ( isFinal ) object->setFinal(true);

	if ( assign != getTokens().end() ) {
		// execute assignment statement
		Runtime::Object tmp;
		//tmp.setArray(true, (size_t)size);
		tmp.setConst(isConst);
		tmp.setFinal(isFinal);

		expression(&tmp, token);

		Runtime::operator_binary_assign(object, &tmp);
	}

	return object;
}

/*
 * typeid ( <expression> );
 */
void TreeGenerator::process_typeid(TokenIterator& token, Runtime::Object* result)
{
	expect(Token::Type::PARENTHESIS_OPEN, token++);

	Symbol* symbol = identify(token);
	if ( symbol ) {
		switch ( symbol->getSymbolType() ) {
			case Symbol::IType::BluePrintEnumSymbol:
			case Symbol::IType::BluePrintObjectSymbol:
				*result = Runtime::StringObject(static_cast<Designtime::BluePrintGeneric*>(symbol)->QualifiedTypename());
				break;
			case Symbol::IType::ObjectSymbol:
				*result = Runtime::StringObject(static_cast<Runtime::Object*>(symbol)->QualifiedTypename());
				break;
			default:
				*result = Runtime::StringObject("<not a valid symbol>");
				break;
		}
	}
	else {
		*result = Runtime::StringObject("<not a valid symbol>");
	}
	token++;

	expect(Token::Type::PARENTHESIS_CLOSE, token);
}

/*
 * syntax:
 * while ( <condition> ) { ... }
 */
void TreeGenerator::process_while(TokenIterator& token, Runtime::Object* /*result*/)
{
	expect(Token::Type::PARENTHESIS_OPEN, token++);

	// find next open parenthesis '('
	TokenIterator condBegin = token;
	// find next balanced '(' & ')' pair
	TokenIterator condEnd = findNextBalancedParenthesis(condBegin);

	expect(Token::Type::BRACKET_CURLY_OPEN, ++condEnd);

	// find next open curly bracket '{'
	TokenIterator bodyBegin = condEnd;
	// find next balanced '{' & '}' pair
	TokenIterator bodyEnd = findNextBalancedCurlyBracket(bodyBegin, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

	bodyBegin++;	// don't collect scope token;
	token = bodyEnd;

	TokenList statementTokens;
	while ( bodyBegin != bodyEnd ) {
		statementTokens.push_back((*bodyBegin));
		bodyBegin++;
	}

	for ( ; ; ) {
		TokenIterator tmp = condBegin;

		Runtime::Object condition;
		expression(&condition, tmp);

		if ( !isTrue(condition) ) {
			break;
		}

		generate(statementTokens);
	}
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
