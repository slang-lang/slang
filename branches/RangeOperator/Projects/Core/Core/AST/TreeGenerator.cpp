
// Header
#include "TreeGenerator.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Common/Method.h>
#include <Core/Common/Namespace.h>
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Designtime/Exceptions.h>
#include <Core/Designtime/Parser/Parser.h>
#include <Core/Runtime/BuildInTypes/BoolObject.h>
#include <Core/Runtime/BuildInTypes/DoubleObject.h>
#include <Core/Runtime/BuildInTypes/FloatObject.h>
#include <Core/Runtime/BuildInTypes/IntegerObject.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Runtime/BuildInTypes/VoidObject.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Runtime/OperatorOverloading.h>
#include <Core/Runtime/TypeCast.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include <Tools/Strings.h>
#include <Utils.h>

// AST includes
#include "Statement.h"

// Namespace declarations


namespace ObjectiveScript {
namespace AST {


TreeGenerator::TreeGenerator()
: mAllowConstModify(false),
  mControlFlow(Runtime::ControlFlow::Normal),
  mMethod(0),
  mThis(0),
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

	// find next balanced '{' & '}' pair
	TokenIterator bodyEnd = --findNextBalancedCurlyBracket(token, getTokens().end(), 0, Token::Type::BRACKET_CURLY_CLOSE);

	while ( token != bodyEnd ) {
		tokens.push_back((*++token));
	}

	++token;
	expect(Token::Type::BRACKET_CURLY_CLOSE, token);
}

void TreeGenerator::deinitialize()
{
	if ( !mThrownExceptions.empty() && !mMethod->throws() ) {
		// this method is not marked as 'throwing', but it throws uncaught exceptions
		std::string exceptions = "'";
		for ( std::set<std::string>::const_iterator it = mThrownExceptions.cbegin(); it != mThrownExceptions.cend(); ++it ) {
			if ( it != mThrownExceptions.cbegin() ) {
				exceptions += "', '";
			}
			exceptions += (*it);
 		}
 		exceptions += "'";

		throw Common::Exceptions::ControlFlowException("'" + mMethod->getFullScopeName() + "' throws " + exceptions + " exception(s) although it is not marked with 'throws'");
	}

	// pop tokens;
	mStackFrame->popTokens();
	// pop scope
	mStackFrame->popScope();
	// delete stack frame
	delete mStackFrame;
	mStackFrame = 0;

	// verify return statement existance
	if ( mMethod->QualifiedTypename() != Designtime::VoidObject::TYPENAME
		 && (mControlFlow != Runtime::ControlFlow::Return && mControlFlow != Runtime::ControlFlow::Throw) ) {
		Token last;
		if ( !mMethod->getTokens().empty() ) {
			last = mMethod->getTokens().back();
		}

		throw Designtime::Exceptions::DesigntimeException("return statement missing in '" + mMethod->getFullScopeName() + "'", last.position());
	}

	// reset reusable members
	mThis = 0;
	mMethod = 0;
	mControlFlow = Runtime::ControlFlow::Normal;
	mAllowConstModify = false;
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

		Token operation = (*start);
		Node* right = parseCondition(++start);
		/*std::string type =*/ resolveType(expression, operation, right);

		expression = new BooleanBinaryExpression(expression, operation, right);
	}
}

/*
 * executes the given tokens in a separate scope
 */
Statements* TreeGenerator::generate(const TokenList &tokens, bool allowBreakAndContinue, bool needsControlStatement)
{
	// reset control flow to be able to check for missing control flow statements during switch/case
	mControlFlow = Runtime::ControlFlow::Normal;

	Statements* statements = 0;

	pushScope(0, allowBreakAndContinue);
		pushTokens(tokens);
			TokenIterator start = getTokens().begin();
			TokenIterator end = getTokens().end();

			Common::Position position(start != end ? start->position() : Common::Position());

			statements = process(start, end);

			if ( needsControlStatement && mControlFlow == Runtime::ControlFlow::Normal ) {
				throw Common::Exceptions::ControlFlowException("block is missing control flow statement", position);
			}
		popTokens();
	popScope();

	return statements;
}

/*
 * generates the abstract syntax tree that is executed by the TreeInterpreter for the given method
 */
Statements* TreeGenerator::generateAST(Common::Method* method)
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

void TreeGenerator::initialize(Common::Method* method)
{
	// initialize reuseable members
	mAllowConstModify = method->getMethodType() == Common::Method::MethodType::Constructor || method->getMethodType() == Common::Method::MethodType::Destructor;
	mControlFlow = Runtime::ControlFlow::Normal;
	mMethod = method;
	mThis = dynamic_cast<Designtime::BluePrintObject*>(method->getEnclosingScope());
	mThrownExceptions.clear();

	// create new stack frame
	mStackFrame = new StackFrame(0, mMethod, mMethod->provideSignature());
	// push scope
	mStackFrame->pushScope(mMethod, false, false);
	// push tokens
	mStackFrame->pushTokens(mMethod->getTokens());

	IScope* scope = getScope();

	// add 'this' symbol to method
	if ( mThis && !mMethod->isStatic() ) {
		scope->define(IDENTIFIER_THIS, mThis);
	}

	const ParameterList& params = mMethod->provideSignature();
	// add parameters as locale variables
	for ( ParameterList::const_iterator it = params.begin(); it != params.end(); ++it ) {
		if ( it->name().empty() ) {
			// skip unnamed parameters
			continue;
		}

		Runtime::Object* object = mRepository->createInstance(it->type(), it->name());
		object->setIsReference(it->access() == AccessMode::ByReference);
		object->setMutability(it->mutability());

		scope->define(it->name(), object);
	}
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

		Token operation = (*start);
		Node* right = parseExpression(++start);


		if ( op == Token::Type::COMPARE_UNEQUAL ) {
			operation.resetContentTo("==");
			operation.resetTypeTo(Token::Type::COMPARE_EQUAL);
		}

		resolveType(condition, operation, right);

		condition = new BooleanBinaryExpression(condition, operation, right);

		// != operator is not defined but rather used as 'not =='
		if ( op == Token::Type::COMPARE_UNEQUAL ) {
			condition = new BooleanUnaryExpression(Token::Type::OPERATOR_NOT, condition, UnaryExpression::ValueType::RValue);
		}

/*
		if ( op == Token::Type::COMPARE_UNEQUAL ) {
			operation.resetContentTo("==");
			operation.resetTypeTo(Token::Type::COMPARE_EQUAL);
		}

		resolveType(condition, operation, right);

		SymbolExpression* exp = dynamic_cast<SymbolExpression*>(condition);

		if ( !exp || exp->isAtomicType() ) {
			condition = new BooleanBinaryExpression(condition, operation, right);
		}
		else {
			// check if we are using a valid type
			Designtime::BluePrintObject* blueprint = mRepository->findBluePrintObject(exp->getResultType());
			if ( !blueprint ) {
				throw Designtime::Exceptions::SyntaxError("'" + exp->getResultType() + "' is not a valid type", operation.position());
			}

			SymbolExpression* inner = exp;
			while ( inner->mSymbolExpression ) {
				inner = inner->mSymbolExpression;
			}

			inner->mSymbolExpression = new DesigntimeSymbolExpression("operator" + operation.content(), dynamic_cast<Expression*>(right)->getResultType(), PrototypeConstraints(), false);
			inner->mSymbolExpression->mSurroundingScope = blueprint;

			ExpressionList params;
			params.emplace_back(right);

			condition = process_method(exp, (*start), params);
		}

		// != operator is not defined but rather used as 'not =='
		if ( op == Token::Type::COMPARE_UNEQUAL ) {
			condition = new BooleanUnaryExpression(Token::Type::OPERATOR_NOT, condition, UnaryExpression::ValueType::RValue);
		}
*/
	}
}

Node* TreeGenerator::parseExpression(TokenIterator& start)
{
	Node* expression = parseFactor(start);

	for ( ; ; ) {
		Token::Type::E op = start->type();
		if ( op != Token::Type::BITAND &&
			 op != Token::Type::BITCOMPLEMENT &&
			 op != Token::Type::BITOR &&
			 op != Token::Type::MATH_ADDITION &&
			 op != Token::Type::MATH_SUBTRACT ) {
			return expression;
		}

		Token operation = (*start);
		Node* right = parseFactor(++start);
		std::string type = resolveType(expression, operation, right);

		SymbolExpression* exp = dynamic_cast<SymbolExpression*>(expression);

		if ( !exp || exp->isAtomicType() ) {
			expression = new BinaryExpression(expression, operation, right, type);
			continue;
		}

		// check if we are using a valid type
		Designtime::BluePrintObject* blueprint = mRepository->findBluePrintObject(exp->getResultType());
		if ( !blueprint ) {
			throw Designtime::Exceptions::SyntaxError("'" + exp->getResultType() + "' is not a valid type", operation.position());
		}

		SymbolExpression* inner = exp;
		while ( inner->mSymbolExpression ) {
			inner = inner->mSymbolExpression;
		}

		inner->mSymbolExpression = new DesigntimeSymbolExpression("operator" + operation.content(), type, PrototypeConstraints(), false);
		inner->mSymbolExpression->mSurroundingScope = blueprint;

		ExpressionList params;
		params.emplace_back(right);

		expression = process_method(exp, (*start), params);
	}
}

Node* TreeGenerator::parseFactor(TokenIterator &start)
{
	Node* factor = parseInfixPostfix(start);

	for ( ; ; ) {
		Token::Type::E op = start->type();
		if ( op != Token::Type::MATH_DIVIDE &&
			 op != Token::Type::MATH_MODULO &&
			 op != Token::Type::MATH_MULTIPLY ) {
			return factor;
		}

		Token operation = (*start);
		Node* right = parseInfixPostfix(++start);
		std::string type = resolveType(factor, operation, right);

		SymbolExpression* exp = dynamic_cast<SymbolExpression*>(factor);

		if ( !exp || exp->isAtomicType() ) {
			factor = new BinaryExpression(factor, operation, right, type);
			continue;
		}

		// check if we are using a valid type
		Designtime::BluePrintObject* blueprint = mRepository->findBluePrintObject(exp->getResultType());
		if ( !blueprint ) {
			throw Designtime::Exceptions::SyntaxError("'" + exp->getResultType() + "' is not a valid type", operation.position());
		}

		SymbolExpression* inner = exp;
		while ( inner->mSymbolExpression ) {
			inner = inner->mSymbolExpression;
		}

		inner->mSymbolExpression = new DesigntimeSymbolExpression("operator" + operation.content(), type, PrototypeConstraints(), false);
		inner->mSymbolExpression->mSurroundingScope = blueprint;

		ExpressionList params;
		params.emplace_back(right);

		factor = process_method(exp, (*start), params);
	}
}

Node* TreeGenerator::parseInfixPostfix(TokenIterator& start)
{
	Node* infixPostfix = 0;
	Token::Type::E op = start->type();

	// infix
	switch ( op ) {
		case Token::Type::MATH_ADDITION:
		case Token::Type::MATH_SUBTRACT: {		// infix +/- operators
			Token operation = (*start);

			infixPostfix = new UnaryExpression(operation, parseTerm(++start), UnaryExpression::ValueType::RValue);
		} break;
		case Token::Type::OPERATOR_NOT: {		// infix ! operator
			Token operation = (*start);

			infixPostfix = new BooleanUnaryExpression(operation, parseTerm(++start), UnaryExpression::ValueType::RValue);
		} break;
		default: {								// default term parsing
			infixPostfix = parseTerm(start);
		} break;
	}

	op = start->type();

	// postfix (single repeat)
	if ( op == Token::Type::OPERATOR_IS ) {		// postfix is operator
		++start;
		SymbolExpression* symbol = resolveWithExceptions(start, getScope());

		std::string type = symbol->getResultType();
		if ( dynamic_cast<DesigntimeSymbolExpression*>(symbol) ) {
			type = Designtime::Parser::buildRuntimeConstraintTypename(type, dynamic_cast<DesigntimeSymbolExpression*>(symbol)->mConstraints);
		}

		infixPostfix = new IsExpression(infixPostfix, type);
	}
	else if ( op == Token::Type::OPERATOR_RANGE ) {		// postfix .. operator
		++start;

		SymbolExpression* rangeExp = NULL;
		IntegerLiteralExpression* lhs = dynamic_cast<IntegerLiteralExpression*>(infixPostfix);
		IntegerLiteralExpression* rhs = NULL;

		// validate left expression (has to be integer literal expression)
		if ( !lhs ) {
			throw Designtime::Exceptions::SyntaxError("Range operator requires integer expression on left side", start->position());
		}

		// collect right expression
		rhs = dynamic_cast<IntegerLiteralExpression*>(expression(start));

		// validate right expression (has to be integer literal expression)
		if ( !rhs ) {
			throw Designtime::Exceptions::SyntaxError("Range operator requires integer expression on right side", start->position());
		}

		rangeExp = new DesigntimeSymbolExpression(CONSTRUCTOR, _void, PrototypeConstraints(), false);
		rangeExp->mSurroundingScope = mRepository->findBluePrintObject(std::string("Range"));

		if ( !rangeExp->mSurroundingScope ) {
			//throw Designtime::Exceptions::SyntaxError("could not resolve symbol 'Range', please import System.Collections.Range", start->position());
			throw Designtime::Exceptions::SyntaxError("to use range operator System.Collections.Range has to be imported", start->position());
		}

		ExpressionList params;
		params.push_back(lhs);
		params.push_back(rhs);

		infixPostfix = new NewExpression("Range", process_method(rangeExp, *start, params));
	}
	else if ( op == Token::Type::QUESTION_MARK ) {		// postfix ternary ? operator
		++start;

		Node* condition = infixPostfix;
		Node* first = NULL;
		Node* second = NULL;

		// determine the type of the ternary operator
		if ( start->type() == Token::Type::COLON ) {
			// use short ternary operator: <expression> ?: <expression>
			first = condition;
		}
		else {
			// use long ternary operator: <expression> ? <expression> : <expression>
			first = expression(start);
		}

		expect(Token::Type::COLON, start);
		++start;

		second = expression(start);

		TernaryExpression* ternaryExpression = new TernaryExpression(condition, first, second);
		if ( ternaryExpression->getResultType() != ternaryExpression->getSecondResultType() ) {
			throw Designtime::Exceptions::SyntaxError("expression results for first ('" + ternaryExpression->getResultType() + "') and second ('" + ternaryExpression->getSecondResultType() + "') expression don't match", start->position());
		}

		infixPostfix = ternaryExpression;
	}
	else if ( op == Token::Type::OPERATOR_NOT ) {		// postfix ! operator
		throw Common::Exceptions::NotSupported("postfix ! operator not supported", start->position());
	}
	else {
		// postfix (multiple repeat)
		for ( ; ; ) {
			Token::Type::E op = start->type();
			if ( op != Token::Type::BRACKET_OPEN &&
				 op != Token::Type::OPERATOR_DECREMENT &&
				 op != Token::Type::OPERATOR_INCREMENT &&
				 op != Token::Type::SCOPE ) {
				return infixPostfix;
			}

			switch ( op ) {
				case Token::Type::BRACKET_OPEN: {
					// postfix operator[]
					throw Common::Exceptions::NotSupported("postfix [] operator not supported", start->position());
				} break;
				case Token::Type::OPERATOR_DECREMENT:
				case Token::Type::OPERATOR_INCREMENT: {	// postfix --/++ operators for rvalue
					Token operation = (*start++);

					infixPostfix = new UnaryExpression(operation, infixPostfix, UnaryExpression::ValueType::RValue);

/*
					Expression* baseExp = dynamic_cast<Expression*>(infixPostfix);
					if ( !baseExp ) {
						throw Designtime::Exceptions::SyntaxError("invalid expression type detected!", start->position());
					}

					infixPostfix = process_incdecrement(start, baseExp);
*/
				} break;
				case Token::Type::SCOPE: {
					++start;

					//OSexperimental("Usage of extended scope operator is marked as unstable in " + start->position().toString());

					Expression* baseExp = dynamic_cast<Expression*>(infixPostfix);
					if ( !baseExp ) {
						throw Designtime::Exceptions::SyntaxError("invalid expression type detected!", start->position());
					}

					Designtime::BluePrintObject* scope = mRepository->findBluePrintObject(baseExp->getResultType());
					if ( !scope ) {
						throw Designtime::Exceptions::SyntaxError("invalid type '" + baseExp->getResultType() + "' detected!", start->position());
					}

					SymbolExpression* symbolExpression = resolve(start, scope, true, Visibility::Public);
					if ( !symbolExpression ) {
						throw Designtime::Exceptions::SyntaxError("invalid symbol '" + start->content() + "' for type '" + baseExp->getResultType() + "' detected!", start->position());
					}

					if ( start->type() == Token::Type::PARENTHESIS_OPEN ) {
						MethodExpression* method = process_method(symbolExpression, start);

						infixPostfix = new ScopeExpression(baseExp, method, method->getResultType());
					}
					else {
						infixPostfix = new ScopeExpression(baseExp, symbolExpression, symbolExpression->getResultType());
					}
				} break;
				default: {
				} break;
			}
		}
	}

	return infixPostfix;
}

Node* TreeGenerator::parseTerm(TokenIterator& start)
{
	Node* term = 0;

	switch ( start->type() ) {
		case Token::Type::CONST_BOOLEAN: {
			term = new BooleanLiteralExpression(Utils::Tools::stringToBool(start->content()));
			++start;
		} break;
		case Token::Type::CONST_DOUBLE: {
			term = new DoubleLiteralExpression(Utils::Tools::stringToDouble(start->content()));
			++start;
		} break;
		case Token::Type::CONST_FLOAT: {
			term = new FloatLiteralExpression(Utils::Tools::stringToFloat(start->content()));
			++start;
		} break;
		case Token::Type::CONST_INTEGER: {
			term = new IntegerLiteralExpression(Utils::Tools::stringToInt(start->content()));
			++start;
		} break;
		case Token::Type::CONST_LITERAL: {
			term = new StringLiteralExpression(Runtime::AtomicValue(start->content()));
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
			throw Designtime::Exceptions::SyntaxError("identifier, literal or constant expected but '" + start->content() + "' found", start->position());
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

	Token firstToken = (*token);
	Statements* statements = 0;

	while ( (token != end) && (token->type() != Token::Type::ENDOFFILE) ) {
		Node* node = process_statement(token);

		if ( node ) {
			if ( !statements ) {
				statements = new Statements(firstToken);
			}

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

	Node* exp = expression(token);

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	++token;

	return new AssertStatement(start, exp);
}

/*
 * syntax:
 * <lvalue> = <rvalue>
 */
Expression* TreeGenerator::process_assignment(TokenIterator& token, SymbolExpression* lhs)
{
	TokenIterator op = token;

	if ( lhs->isConst() && !(mAllowConstModify && lhs->isMember()) ) {
		throw Common::Exceptions::ConstCorrectnessViolated("tried to modify const symbol '" + lhs->mName + "'", op->position());
	}

	Token assignment(Token::Category::Assignment, Token::Type::ASSIGN, "=", op->position());

	Expression* rhs = dynamic_cast<Expression*>(expression(++token));

	if ( op->type() != Token::Type::ASSIGN ) {
		Token operation;

		switch ( op->type() ) {
			case Token::Type::ASSIGN_ADDITION:      operation = Token(Token::Category::Operator, Token::Type::MATH_ADDITION, "+", op->position()); break;
			case Token::Type::ASSIGN_BITAND:        operation = Token(Token::Category::Operator, Token::Type::BITAND, "&", op->position()); break;
			case Token::Type::ASSIGN_BITCOMPLEMENT: operation = Token(Token::Category::Operator, Token::Type::BITCOMPLEMENT, "~", op->position()); break;
			case Token::Type::ASSIGN_BITOR:         operation = Token(Token::Category::Operator, Token::Type::BITOR, "|", op->position()); break;
			case Token::Type::ASSIGN_DIVIDE:        operation = Token(Token::Category::Operator, Token::Type::MATH_DIVIDE, "/", op->position()); break;
			case Token::Type::ASSIGN_MODULO:        operation = Token(Token::Category::Operator, Token::Type::MATH_MODULO, "%", op->position()); break;
			case Token::Type::ASSIGN_MULTIPLY:      operation = Token(Token::Category::Operator, Token::Type::MATH_MULTIPLY, "*", op->position()); break;
			case Token::Type::ASSIGN_SUBTRACT:      operation = Token(Token::Category::Operator, Token::Type::MATH_SUBTRACT, "-", op->position()); break;
			default: throw Designtime::Exceptions::SyntaxError("assignment type expected", token->position());
		}

		if ( lhs->isAtomicType() ) {
			rhs = new BinaryExpression(lhs, operation, rhs, resolveType(lhs, operation, rhs));
		}
		else {
			// check if we are using a valid type
			Designtime::BluePrintObject* blueprint = mRepository->findBluePrintObject(lhs->getResultType());
			if ( !blueprint ) {
				throw Designtime::Exceptions::SyntaxError("'" + lhs->getResultType() + "' is not a valid type", operation.position());
			}

			SymbolExpression* sym = new DesigntimeSymbolExpression(lhs->mName, lhs->getResultType(), PrototypeConstraints(), false);
			sym->mSurroundingScope = lhs->mSurroundingScope;
			sym->mSymbolExpression = new DesigntimeSymbolExpression("operator" + operation.content(), resolveType(lhs, operation, rhs), PrototypeConstraints(), false);
			sym->mSymbolExpression->mSurroundingScope = blueprint;

			ExpressionList params;
			params.emplace_back(rhs);

			rhs = process_method(sym, (*token), params);
		}
	}


	if ( lhs->isAtomicType() || lhs->getResultType() == rhs->getResultType() ) {
		return new AssignmentExpression(lhs, rhs, resolveType(lhs, assignment, rhs));
	}

	// check if we are using a valid type
	Designtime::BluePrintObject* blueprint = mRepository->findBluePrintObject(lhs->getResultType());
	if ( !blueprint ) {
		throw Designtime::Exceptions::SyntaxError("'" + lhs->getResultType() + "' is not a valid type", token->position());
	}

	SymbolExpression* inner = lhs;
	while ( inner->mSymbolExpression ) {
		inner = inner->mSymbolExpression;
	}

	inner->mSymbolExpression = new DesigntimeSymbolExpression("operator=", lhs->getResultType(), PrototypeConstraints(), false);
	inner->mSymbolExpression->mSurroundingScope = blueprint;

	ExpressionList params;
	params.emplace_back(rhs);

	return process_method(lhs, (*token), params);
}

/*
 * syntax:
 * break;
 */
Statement* TreeGenerator::process_break(TokenIterator& token)
{
	Token start = (*token);
	mControlFlow = Runtime::ControlFlow::Break;

	if ( !mStackFrame->allowBreakAndContinue() ) {
		throw Common::Exceptions::ControlFlowException("break not allowed here", token->position());
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
	mControlFlow = Runtime::ControlFlow::Continue;

	if ( !mStackFrame->allowBreakAndContinue() ) {
		throw Common::Exceptions::ControlFlowException("continue not allowed here", token->position());
	}

	expect(Token::Type::SEMICOLON, token);
	++token;

	return new ContinueStatement(start);
}

/*
 * syntax:
 * copy <expression>;
 */
Expression* TreeGenerator::process_copy(TokenIterator& token)
{
	return new CopyExpression(expression(token));
}

/*
 * syntax:
 * delete <expression>;
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
 * exit( <expression> );
 */
Statement* TreeGenerator::process_exit(TokenIterator& token)
{
	Token start = (*token);
	mControlFlow = Runtime::ControlFlow::ExitProgram;

	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

	Node* exp = expression(token);

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	++token;

	expect(Token::Type::SEMICOLON, token);
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
		throw Designtime::Exceptions::SyntaxError("invalid token '" + token->content() + "' found", token->position());
	}

	return expression;
}

/*
 * syntax:
 * for ( [<expression>]; [<condition>]; [<expression>] ) <statement>
 */
Statement* TreeGenerator::process_for(TokenIterator& token)
{
	Token start = (*token);

	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

	// Declaration parsing
	// {
	Node* initialization = 0;
	if ( token->type() != Token::Type::SEMICOLON ) {
		initialization = process_statement(token);
	}

	++token;
	// }

	// Condition parsing
	// {
	Node* condition = 0;
	if ( token->type() != Token::Type::SEMICOLON ) {
		condition = expression(token);

		if ( dynamic_cast<AssignmentExpression*>(condition) ) {
			OSwarn("Detected assignment expression that is used as conditional expression in " + token->position().toString());
		}
	}

	++token;
	// }

	// Iteration parsing
	// {
	Node* iteration = 0;
	if ( token->type() != Token::Type::PARENTHESIS_CLOSE ) {
		iteration = process_statement(token, true);
	}

	++token;
	// }

	// Body parsing
	// {
	Node* loopBody = process_statement(token, true);
	// }

	return new ForStatement(start, initialization, condition, iteration, loopBody);
}

/*
 * syntax:
 * foreach ( <type definition> <identifier> : <expression> ) <statement>
 */
Statement* TreeGenerator::process_foreach(TokenIterator& token)
{
	Token start = (*token);

	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

	TypeDeclaration* typeDeclaration = process_type(token, Initialization::NotAllowed);

	mRepository->prepareType(Common::TypeDeclaration(typeDeclaration->mType, typeDeclaration->mConstraints));

	expect(Token::Type::COLON, token);
	++token;

	MethodExpression* getIteratorExpression = NULL;
	MethodExpression* hasNextExpression = NULL;
	MethodExpression* nextExpression = NULL;

	Expression* collectionExpression = dynamic_cast<Expression*>(parseExpression(token));
	if ( collectionExpression ) {
		Designtime::BluePrintObject* collection = mRepository->findBluePrintObject(collectionExpression->getResultType());
		Designtime::BluePrintObject* iterator = NULL;

		if ( collection && collection->isOfType("Iterator") ) {
			// we received an iterator instead of a collection
			iterator = collection;
			collection = NULL;

			getIteratorExpression = dynamic_cast<MethodExpression*>(collectionExpression);
			collectionExpression = NULL;
		}
		else {
			// check if this expression offers an iterator
			if ( !collection || !collection->isIterable() ) {
				throw Designtime::Exceptions::SyntaxError(collectionExpression->getResultType() + " is not iterable", token->position());
			}

			Common::Method* getIteratorMethod = dynamic_cast<Common::Method*>(collection->resolveMethod("getIterator", ParameterList(), false, Visibility::Public));
			if ( !getIteratorMethod ) {
				throw Designtime::Exceptions::SyntaxError(collectionExpression->getResultType() + " has no 'getIterator' method", token->position());
			}

			// check if iterator is a valid type
			iterator = mRepository->findBluePrintObject(getIteratorMethod->ReturnType());

			{	// look up "getIterator" method in given collection
				SymbolExpression* expression = new DesigntimeSymbolExpression(getIteratorMethod->getName(), getIteratorMethod->QualifiedTypename(), PrototypeConstraints(), false);
				expression->mSurroundingScope = collection;

				getIteratorExpression = process_method(expression, *token, ExpressionList());
			}
		}

		if ( !iterator ) {
			throw Designtime::Exceptions::SyntaxError("no iterator found", token->position());
		}

		{	// look up "hasNext" method in given iterator
			SymbolExpression* expression = new DesigntimeSymbolExpression("hasNext", _bool, PrototypeConstraints(), true);
			expression->mSurroundingScope = iterator;

			hasNextExpression = process_method(expression, *token, ExpressionList());
		}

		{	// look up "next" method in given iterator
			SymbolExpression* expression = new DesigntimeSymbolExpression("next", typeDeclaration->mType, PrototypeConstraints(), false);
			expression->mSurroundingScope = iterator;

			nextExpression = process_method(expression, *token, ExpressionList());

			// validate result type
			//resolveType(typeDeclaration->mType, Token(Token::Category::Operator, Token::Type::ASSIGN, "=", token->position()), nextExpression->getResultType());
		}
	}

	expect(Token::Type::PARENTHESIS_CLOSE, token);
	++token;

	return new ForeachStatement(start, typeDeclaration, collectionExpression, getIteratorExpression, hasNextExpression, nextExpression, process_statement(token, true));
}

/*
 * executes a method, processes an assignment and instantiates new types
 */
Node* TreeGenerator::process_identifier(TokenIterator& token, bool allowTypeCast)
{
	Node* node = NULL;

	TokenIterator old = token;
	SymbolExpression* symbol = resolveWithThis(token, getScope());
	TokenIterator op = token;

	// type cast (followed by expression, identifier, literal, 'copy' or 'new' keyword)
	if ( allowTypeCast &&
		((op->category() == Token::Category::Constant || op->type() == Token::Type::IDENTIFIER || op->type() == Token::Type::KEYWORD) ||
		 (dynamic_cast<DesigntimeSymbolExpression*>(symbol) && dynamic_cast<DesigntimeSymbolExpression*>(symbol)->isPrototype()))
		) {

		mRepository->prepareType(Common::TypeDeclaration(symbol->getResultType(), dynamic_cast<DesigntimeSymbolExpression*>(symbol)->mConstraints));

		std::string type = symbol->getResultType();
		if ( dynamic_cast<DesigntimeSymbolExpression*>(symbol) ) {
			type = Designtime::Parser::buildRuntimeConstraintTypename(type, dynamic_cast<DesigntimeSymbolExpression*>(symbol)->mConstraints);
		}

		node = new TypecastExpression(type, expression(token));					// this processes all following expressions before casting
		//node = new TypecastExpression(type, parseInfixPostfix(token));		// this casts first and does not combine the subsequent expressions with this one

		// delete resolved symbol expression as it is not needed any more
		delete symbol;
	}
	// type declaration
	else if ( !allowTypeCast &&
		((op->type() == Token::Type::IDENTIFIER) ||
		 (dynamic_cast<DesigntimeSymbolExpression*>(symbol) && dynamic_cast<DesigntimeSymbolExpression*>(symbol)->isPrototype()))
		) {
		// delete resolved symbol expression as it is not needed any more
		delete symbol;

		node = process_type(old, Initialization::Allowed);

		token = old;
	}
	// assignment
	else if ( op->category() == Token::Category::Assignment ) {
		node = process_assignment(token, symbol);
	}
	// method call
	else if ( op->type() == Token::Type::PARENTHESIS_OPEN ) {
		node = process_method(symbol, token);
	}
	// subscript [] operator
	else if ( op->type() == Token::Type::BRACKET_OPEN ) {
		node = process_subscript(token, symbol);
	}
	// --/++ for lvalue
	else if ( op->type() == Token::Type::OPERATOR_DECREMENT || op->type() == Token::Type::OPERATOR_INCREMENT ) {
		node = process_incdecrement(token, symbol);
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

	if ( dynamic_cast<AssignmentExpression*>(exp) ) {
		OSwarn("Detected assignment expression that is used as conditional expression in " + token->position().toString());
	}

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

Expression* TreeGenerator::process_incdecrement(TokenIterator& token, Expression* lhs)
{
	if ( lhs->isConst() && !(mAllowConstModify && lhs->isMember()) ) {
		throw Common::Exceptions::ConstCorrectnessViolated("tried to modify const symbol '" + token->content() + "'", token->position());
	}

	if ( lhs->isAtomicType() ) {
		return new UnaryExpression((*token++), lhs, UnaryExpression::ValueType::LValue);
	}


	SymbolExpression* symbol = dynamic_cast<SymbolExpression*>(lhs);
	if ( !symbol ) {
		throw Designtime::Exceptions::SyntaxError("invalid expression type detected!", token->position());
	}

	// check if we are using a valid type
	Designtime::BluePrintObject* type = mRepository->findBluePrintObject(symbol->getResultType());
	if ( !type ) {
		throw Designtime::Exceptions::SyntaxError("'" + symbol->getResultType() + "' is not a valid type", token->position());
	}

	symbol->mSymbolExpression = new DesigntimeSymbolExpression("operator" + token->content(), _void, PrototypeConstraints(), false);
	symbol->mSymbolExpression->mSurroundingScope = type;

	++token;

	return process_method(symbol, (*token), ExpressionList());
}

Statement* TreeGenerator::process_keyword(TokenIterator& token)
{
	Statement* statement = 0;

	std::string keyword = (*token++).content();

	if ( keyword == KEYWORD_ASSERT ) {
		statement = process_assert(token);
	}
	else if ( keyword == KEYWORD_BREAK ) {
		statement = process_break(token);
	}
	else if ( keyword == KEYWORD_CONTINUE ) {
		statement = process_continue(token);
	}
	else if ( keyword == KEYWORD_DELETE ) {
		statement = process_delete(token);
	}
	else if ( keyword == KEYWORD_EXIT ) {
		statement = process_exit(token);
	}
	else if ( keyword == KEYWORD_FOR ) {
		statement = process_for(token);
	}
	else if ( keyword == KEYWORD_FOREACH ) {
		statement = process_foreach(token);
	}
	else if ( keyword == KEYWORD_IF ) {
		statement = process_if(token);
	}
	else if ( keyword == KEYWORD_PRINT ) {
		statement = process_print(token);
	}
	else if ( keyword == KEYWORD_RETURN ) {
		statement = process_return(token);
	}
	else if ( keyword == KEYWORD_SWITCH ) {
		statement = process_switch(token);
	}
	else if ( keyword == KEYWORD_THROW ) {
		statement = process_throw(token);
	}
	else if ( keyword == KEYWORD_TRY ) {
		statement = process_try(token);
	}
	else if ( keyword == KEYWORD_VAR ) {
		statement = process_var(token);
	}
	else if ( keyword == KEYWORD_WHILE ) {
		statement = process_while(token);
	}
	else {
		throw Designtime::Exceptions::DesigntimeException("invalid keyword '" + token->content() + "' found", token->position());
	}

	return statement;
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

	ExpressionList params;

	tmp = opened;
	// loop through all parameters separated by commas
	while ( tmp != closed ) {
		params.push_back(
			expression(tmp)
		);

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

	return process_method(symbol, start, params);
}

MethodExpression* TreeGenerator::process_method(SymbolExpression* symbol, const Token& token, const ExpressionList& expressions)
{
	ParameterList params;
	for ( ExpressionList::const_iterator it = expressions.begin(); it != expressions.end(); ++it ) {
		params.push_back(Parameter::CreateDesigntime(
			ANONYMOUS_OBJECT,
			Common::TypeDeclaration(dynamic_cast<Expression*>((*it))->getResultType(), PrototypeConstraints(), dynamic_cast<Expression*>((*it))->isConst() ? Mutability::Const : Mutability::Modify),
			Runtime::AtomicValue(),
			false,
			dynamic_cast<Expression*>((*it))->isConst() ? Mutability::Const : Mutability::Modify,
			dynamic_cast<Expression*>((*it))->isAtomicType() ? AccessMode::ByValue : AccessMode::ByReference
		));
	}

	Common::Method* method = dynamic_cast<Common::Method*>(resolveMethod(symbol, params, Visibility::Private));
	if ( !method ) {
		throw Common::Exceptions::UnknownIdentifer("method '" + symbol->toString() + "(" + toString(params) + ")' not found", token.position());
	}

	// validate parameters
	const ParameterList& expectedParams = method->provideSignature();
	ParameterList::const_iterator expectedIt = expectedParams.cbegin();
	ParameterList::const_iterator providedIt = params.cbegin();
	for ( ; expectedIt != expectedParams.cend(); ++expectedIt ) {
		if ( providedIt != params.end() ) {
			// validate constness
			if ( expectedIt->mAccessMode == AccessMode::ByReference &&
				 (expectedIt->mMutability == Mutability::Modify && providedIt->mMutability == Mutability::Const) ) {
				throw Common::Exceptions::ConstCorrectnessViolated("expected a modifiable by reference parameter", token.position());
			}

/* temporarily deactivated but this should be turned on again
			// validate access mode
			if ( expectedIt->mAccessMode == AccessMode::ByReference && providedIt->mAccessMode != AccessMode::ByReference ) {
				throw Common::Exceptions::AccessMode("expected a by reference parameter", token.position());
			}
*/

			++providedIt;
			continue;
		}

		// not enough parameters provided; this is okay because our called method can have default parameters
		break;
	}

	// prevent calls to modifiable methods from const methods
	if ( mMethod->isConstMethod() && mMethod->getEnclosingScope() == method->getEnclosingScope() && !method->isConstMethod() ) {
		throw Common::Exceptions::ConstCorrectnessViolated("only calls to const methods are allowed in const method '" + mMethod->getFullScopeName() + "'", token.position());
	}

	// prevent calls to modifiable method from const symbol (exception: constructors are allowed)
	if ( symbol->isConst() && !method->isConstMethod() /*&& method->getMethodType() != MethodAttributes::MethodType::Constructor*/ ) {
		throw Common::Exceptions::ConstCorrectnessViolated("only calls to const methods are allowed from within const symbol '" + symbol->toString() + "'", token.position());
	}

	// prevent calls to non-static methods from static methods
	if ( mMethod->isStatic() && !method->isStatic() ) {
		throw Common::Exceptions::StaticException("non-static method \"" + method->ToString() + "\" called from static method \"" + mMethod->ToString() + "\"", token.position());
	}

	// evaluate language feature state of the called method
	switch ( method->getLanguageFeatureState() ) {
		case LanguageFeatureState::Deprecated: OSinfo("executed method '" + method->getFullScopeName() + "' is marked as deprecated"); break;
		case LanguageFeatureState::NotImplemented: throw Common::Exceptions::NotImplemented("executed method '" + method->getFullScopeName() + "' is marked as not implemented", token.position()); break;
		case LanguageFeatureState::Stable: /* this is the normal language feature state, so there is no need to log anything here */ break;
		case LanguageFeatureState::Unspecified: throw Common::Exceptions::Exception("unknown language feature state set for executed method '" + method->getFullScopeName() + "'", token.position()); break;
		case LanguageFeatureState::Unstable: OSwarn("executed method '" + method->getFullScopeName() + "' is marked as unstable"); break;
	}

	return new MethodExpression(symbol, expressions, method->QualifiedTypename(), method->isConst(), method->getEnclosingScope() == mMethod->getEnclosingScope());
}

/*
 * syntax:
 * new <Typename>([<parameter list>]);
 */
Expression* TreeGenerator::process_new(TokenIterator& token)
{
	SymbolExpression* exp = resolveWithExceptions(token, getScope());

	std::string type;

	SymbolExpression* inner = exp;
	for ( ; ; ) {
		if ( inner->mSymbolExpression ) {
			inner = inner->mSymbolExpression;
		}
		else {
			PrototypeConstraints constraints = dynamic_cast<DesigntimeSymbolExpression*>(inner)->mConstraints;

			Common::TypeDeclaration typeDeclaration = Common::TypeDeclaration(inner->getResultType(), constraints);
			mRepository->prepareType(typeDeclaration);

			type = Designtime::Parser::buildRuntimeConstraintTypename(
				typeDeclaration.mName,
				typeDeclaration.mConstraints
			);

			inner->mSymbolExpression = new DesigntimeSymbolExpression(CONSTRUCTOR, _void, PrototypeConstraints(), false);
			inner->mSymbolExpression->mSurroundingScope = mRepository->findBluePrintObject(type);

			if ( !inner->mSymbolExpression->mSurroundingScope ) {
				throw Common::Exceptions::UnknownIdentifer(type, token->position());
			}
			break;
		}
	}

	if ( !mRepository->findBluePrintObject(exp->getResultType()) ) {
		throw Common::Exceptions::UnknownIdentifer(exp->getResultType(), token->position());
	}

	return new NewExpression(type, process_method(exp, token));
}

/*
 * syntax:
 * print( <expression> );
 */
Statement* TreeGenerator::process_print(TokenIterator& token)
{
	Token start = (*token);

	expect(Token::Type::PARENTHESIS_OPEN, token);
	++token;

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
	mControlFlow = Runtime::ControlFlow::Return;

	Node* exp = 0;
	std::string returnType = Designtime::VoidObject::TYPENAME;

	if ( token->type() != Token::Type::SEMICOLON ) {
		exp = expression(token);
		returnType = dynamic_cast<Expression*>(exp)->getResultType();
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
Statements* TreeGenerator::process_scope(TokenIterator& token, bool allowBreakAndContinue, bool needsControlStatement)
{
	TokenList scopeTokens;
	collectScopeTokens(token, scopeTokens);

	return generate(scopeTokens, allowBreakAndContinue, needsControlStatement);
}

Expression* TreeGenerator::process_subscript(TokenIterator& token, SymbolExpression* symbol)
{
	if ( !symbol ) {
		throw Common::Exceptions::InvalidSymbol("invalid symbol found: " + token->content(), token->position());
	}

	std::string type = symbol->getResultType();

	Designtime::BluePrintObject* obj = mRepository->findBluePrintObject(type);

	symbol->mSymbolExpression = new RuntimeSymbolExpression("operator[]", "", true, true, obj->isAtomicType());
	symbol->mSymbolExpression->mSurroundingScope = obj;

	Token opToken(Token::Category::Operator, Token::Type::BRACKET_OPEN, "[", token->position(), false);
	ExpressionList params;

	do {
		// skip [ or ,
		++token;

		params.push_back(
			expression(token)
		);
	} while ( token->type() == Token::Type::COMMA );

	// skip ]
	++token;

	return process_method(symbol, opToken, params);
}

Node* TreeGenerator::process_statement(TokenIterator& token, bool allowBreakAndContinue)
{
	Node* node = 0;

	switch ( token->type() ) {
		case Token::Type::BRACKET_CURLY_OPEN:
			node = process_scope(token, allowBreakAndContinue);	// this opens a new scope
			++token;
			break;
		case Token::Type::IDENTIFIER:
		case Token::Type::TYPE:
			node = process_identifier(token);
			break;
		case Token::Type::KEYWORD:
			node = process_keyword(token);
			break;
		case Token::Type::PARENTHESIS_OPEN:
			node = expression(token);
			break;
		case Token::Type::SEMICOLON:
			++token;
			break;
		default:
			throw Designtime::Exceptions::SyntaxError("invalid token '" + token->content() + "' found", token->position());
	}

	return node;
}

/*
 * syntax:
 * switch ( <expression> ) {
 *		[ case <expression>: { ... } ]
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

			// process case-block tokens
			caseStatements.push_back(
				new CaseStatement(start, caseExpression, process_scope(token, true, true))
			);
		}
		else if ( token->type() == Token::Type::KEYWORD && token->content() == KEYWORD_DEFAULT ) {
			if ( defaultStatement ) {
				throw Designtime::Exceptions::SyntaxError("duplicate default entry for switch statement", token->position());
			}

			// skip default-label
			++token;

			expect(Token::Type::COLON, token);
			++token;

			// process default-block tokens
			defaultStatement = process_scope(token, true, true);
		}
		else {
			throw Designtime::Exceptions::DesigntimeException("invalid token '" + token->content() + "' found", token->position());
		}

		expect(Token::Type::BRACKET_CURLY_CLOSE, token);
		++token;
	}

	// determine if we are using an enumeration expression
	Expression* enumExp = dynamic_cast<Expression*>(switchExpression);
	if ( enumExp ) {
		Designtime::BluePrintObject* blueprint = mRepository->findBluePrintObject(enumExp->getResultType());
		if ( !blueprint ) {
			// unknown result type of switch-expression
			throw Common::Exceptions::UnknownIdentifer(enumExp->getResultType(), start.position());
		}

		if ( blueprint->isEnumeration() && !defaultStatement ) {
			long available = std::distance(blueprint->beginSymbols(), blueprint->endSymbols());
			long used = caseStatements.size();

			if ( available > used ) {
				// no default statement is present, so all enumeration values should be used
				OSinfo("Consider using a default statement when not using all enumeration values in " + start.position().toString());
			}
			else  if ( available < used ) {
				// duplicate case statements have been used
				OSwarn("Duplicate case statements have been used in switch in " + start.position().toString());
			}
		}
	}

	expect(Token::Type::BRACKET_CURLY_CLOSE, token);
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
	mControlFlow = Runtime::ControlFlow::Throw;

	Node* exp = 0;

	if ( token->type() != Token::Type::SEMICOLON ) {
		exp = expression(token);

		if ( exp ) {
			mThrownExceptions.insert(dynamic_cast<Expression*>(exp)->getResultType());
		}
	}

	expect(Token::Type::SEMICOLON, token);
	++token;

	return new ThrowStatement(start, exp);
}

/*
 * syntax:
 * try { ... }
 * [ catch [ ( <expression> ) ] { ... } ]
 * [ finally { ... } ]
 */
Statement* TreeGenerator::process_try(TokenIterator& token)
{
	Token start = (*token);

	expect(Token::Type::BRACKET_CURLY_OPEN, token);

	std::set<std::string> thrownExceptions = mThrownExceptions;
	mThrownExceptions.clear();

	// process try-block
	Statements* tryBlock = process_scope(token);

	TokenIterator tmp = lookahead(token);
	TokenIterator localEnd = getTokens().end();

	CatchStatements catchStatements;
	Statements* finallyBlock = 0;

	// collect all catch- and finally-blocks
	for ( ; ; ) {
		if ( tmp != localEnd && tmp->content() == KEYWORD_CATCH ) {
			Token start = (*tmp);

			// skip catch-label
			++tmp;

			pushScope();	// push a new scope to allow reuse of the same exception instance name

			TypeDeclaration* typeDeclaration = 0;

			// parse exception type (if present)
			if ( tmp->type() == Token::Type::PARENTHESIS_OPEN ) {
				++tmp;

				// create new exception type instance
				typeDeclaration = process_type(tmp, Initialization::NotAllowed);

				mRepository->prepareType(Common::TypeDeclaration(typeDeclaration->mType, typeDeclaration->mConstraints));

				expect(Token::Type::PARENTHESIS_CLOSE, tmp);
				++tmp;

				// remove caught exception from list of not-caught exceptions
				mThrownExceptions.erase(typeDeclaration->mType);
			}
			else {
				// this is a catch block without an exception type (= a "catch all"-block), so we have to clear all exceptions
				mThrownExceptions.clear();
			}

			// TODO: prevent duplicate catch-blocks

			catchStatements.push_back(
				new CatchStatement(start, typeDeclaration, process_scope(tmp))
			);

			popScope();		// pop exception instance scope

			// set token to end of catch-block
			token = tmp;
		}
		else if ( tmp != localEnd && tmp->content() == KEYWORD_FINALLY ) {
			if ( finallyBlock ) {
				throw Designtime::Exceptions::SyntaxError("multiple finally blocks are not allowed");
			}

			++tmp;

			// parse finally-block
			finallyBlock = process_scope(tmp);

			// set token to end of finally-block
			token = tmp;
		}
		else {
			break;	// reached end of try-catch-finally-block
		}

		++tmp;
	}

	if ( catchStatements.empty() ) {
		// this is a try-block without catch statements (= a "no throw" try-block), so we have to clear all exceptions
		mThrownExceptions.clear();
	}

	// merge local thrown exceptions list with global list
	mThrownExceptions.insert(thrownExceptions.begin(), thrownExceptions.end());

	expect(Token::Type::BRACKET_CURLY_CLOSE, token);
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

	DesigntimeSymbolExpression* lhs = dynamic_cast<DesigntimeSymbolExpression*>(resolveWithExceptions(token, getScope()));
	if ( !lhs ) {
		throw Common::Exceptions::InvalidSymbol("invalid symbol '" + token->content() + "'", token->position());
	}

	std::string type = lhs->getResultType();
	PrototypeConstraints constraints = lhs->mConstraints;

	mRepository->prepareType(Common::TypeDeclaration(type, constraints));

	// delete resolved symbol expression as it is not needed any more
	delete lhs;
	lhs = 0;

	expect(Token::Type::IDENTIFIER, token);

	std::string name = token->content();
	++token;

	Mutability::E mutability = Designtime::Parser::parseMutability(token, Mutability::Modify);
	if ( mutability == Mutability::Unknown ) {
		throw Designtime::Exceptions::SyntaxError("invalid mutability set for '" + name + "'", token->position());
	}

	Runtime::Object* object = mRepository->createInstance(type, name, constraints, Repository::InitilizationType::AllowAbstract);
	object->setConst(object->isConst() || mutability == Mutability::Const);	// prevent constness of blueprint if set

	getScope()->define(name, object);

	// non-atomic types are references by default
	AccessMode::E accessMode = Designtime::Parser::parseAccessMode(token, object->isAtomicType() ? AccessMode::ByValue : AccessMode::ByReference);

	Expression* rhs = 0;

	if ( token->type() == Token::Type::ASSIGN ) {
		if ( initialization != Initialization::Allowed ) {
			// type declaration without initialization has been requested
			throw Common::Exceptions::NotSupported("initialization is not allowed here", token->position());
		}

		RuntimeSymbolExpression* lhs = new RuntimeSymbolExpression(name, object->QualifiedTypename(), false, object->isMember(), accessMode == AccessMode::ByValue);

		//Token copy = (*token);
		rhs = process_assignment(token, lhs);

		//mTypeSystem->getType(object->QualifiedTypename(), copy, rhs->getResultType());
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

	return new TypeDeclaration(start, type, constraints, name, mutability == Mutability::Const, accessMode == AccessMode::ByReference, rhs);
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
 * var <identifier> = <expression>;
 */
TypeDeclaration* TreeGenerator::process_var(TokenIterator& token)
{
	Token start = (*token);
	std::string name = token->content();

	expect(Token::Type::IDENTIFIER, token);
	++token;

	Mutability::E mutability = Designtime::Parser::parseMutability(token, Mutability::Modify);
	if ( mutability == Mutability::Unknown ) {
		throw Designtime::Exceptions::SyntaxError("invalid mutability set for '" + name + "'", token->position());
	}

	AccessMode::E accessMode = Designtime::Parser::parseAccessMode(token, AccessMode::ByValue);

	expect(Token::Type::ASSIGN, token);
	++token;

	Node* assignment = expression(token);
	std::string type = dynamic_cast<Expression*>(assignment)->getResultType();

	Runtime::Object* object = mRepository->createInstance(type, name, PrototypeConstraints(), Repository::InitilizationType::AllowAbstract);
	object->setMutability(mutability);
	object->setIsReference(accessMode == AccessMode::ByReference);

	getScope()->define(name, object);

	// this could easily be changed to return a TypeDeclaration statement, which would be a little faster but during debugging the wrong statement would be shown
	return new TypeInference(start, type, PrototypeConstraints(), name, mutability == Mutability::Const, accessMode == AccessMode::ByReference, assignment);
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

	if ( dynamic_cast<AssignmentExpression*>(exp) ) {
		OSwarn("Detected assignment expression that is used as conditional expression in " + token->position().toString());
	}

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

SymbolExpression* TreeGenerator::resolve(TokenIterator& token, IScope* base, bool onlyCurrentScope, Visibility::E visibility) const
{
	if ( !base ) {
		throw Designtime::Exceptions::DesigntimeException("invalid base scope");
	}

	std::string name = token->content();
	IScope* scope = 0;
	SymbolExpression* symbol = 0;
	std::string type;

	// retrieve symbol for token from base scope
	Symbol* result = base->resolve(name, onlyCurrentScope, !onlyCurrentScope ? Visibility::Private : visibility);
	if ( !result ) {
		return 0;
	}

	++token;

	// set scope & type according to symbol type
	switch ( result->getSymbolType() ) {
		case Symbol::IType::BluePrintObjectSymbol: {
			type = dynamic_cast<Designtime::BluePrintObject*>(result)->QualifiedTypename();

			Designtime::BluePrintObject* blueprint = mRepository->findBluePrintObject(type);
			if ( !blueprint ) {
				throw Common::Exceptions::UnknownIdentifer("'" + type + "' not found", token->position());
			}

			PrototypeConstraints constraints;
			if ( blueprint->isPrototype() ) {
				constraints = blueprint->getPrototypeConstraints().buildRawConstraints(
					Designtime::Parser::collectRuntimePrototypeConstraints(token)
				);
			}

			scope = blueprint;

			symbol = new DesigntimeSymbolExpression(name, type, constraints, blueprint->isAtomicType());
			//symbol = new DesigntimeSymbolExpression(name, Designtime::Parser::buildRuntimeConstraintTypename(type, constraints), PrototypeConstraints(), blueprint->isAtomicType());
		} break;
		case Symbol::IType::NamespaceSymbol: {
			Common::Namespace* space = dynamic_cast<Common::Namespace*>(result);

			scope = space;
			type = space->QualifiedTypename();

			symbol = new DesigntimeSymbolExpression(name, type, PrototypeConstraints(), true);
		} break;
		case Symbol::IType::ObjectSymbol: {
			Runtime::Object* object = dynamic_cast<Runtime::Object*>(result);

/*	this does not work because it also is true for valid static fields
			if ( dynamic_cast<Designtime::BluePrintObject*>(base) && !object->isMember() ) {
				throw Common::Exceptions::StaticException("cannot access static instance '" + object->getName() + "' from within runtime instance", token->position());
			}
*/

			// set scope according to result type
			scope = object->isAtomicType() ? NULL : object->getBluePrint();
			type = object->QualifiedTypename();

			symbol = new RuntimeSymbolExpression(name, type, object->isConst(), object->isMember(), object->isAtomicType());
		} break;
		case Symbol::IType::MethodSymbol: {
			// don't set the result type yet because we first have to determine which method should get executed in case overloaded methods
			// are present; this will be done in a later step (during method resolution)

			symbol = new RuntimeSymbolExpression(name, type, false, false, false);
		} break;
	}

	if ( token->type() == Token::Type::SCOPE ) {
		if ( name == IDENTIFIER_BASE ) {
			visibility = Visibility::Protected;		// this allows us to access protected and public members/methods of our base class
		}
		else if ( name == IDENTIFIER_THIS ) {
			visibility = Visibility::Private;		// this allows us full access to our owners class' members/methods
		}

		symbol->mSymbolExpression = resolve(++token, scope, true, visibility);

		if ( !symbol->mSymbolExpression ) {
			// exceptions are not allowed here so we have to return 0 (without leaving memleaks)
			delete symbol;

			return 0;
		}
	}
	symbol->mSurroundingScope = base;

	return symbol;
}

SymbolExpression* TreeGenerator::resolveWithExceptions(TokenIterator& token, IScope* base) const
{
	SymbolExpression* exp = resolve(token, base, false, Visibility::Public);
	if ( !exp ) {
		throw Common::Exceptions::InvalidSymbol("invalid symbol '" + token->content() + "' found", token->position());
	}

	return exp;
}

SymbolExpression* TreeGenerator::resolveWithThis(TokenIterator& token, IScope* base) const
{
	if ( mThis ) {
		// every class-method has a "this" local that points to the object's blueprint
		// resolve symbol by using the "this" identifier (without exceptions so that we can try to resolve another time)
		SymbolExpression* exp = resolve(token, mThis, true, Visibility::Private);
		if ( exp ) {
			// insert "this" symbol as "parent" of our recently resolved symbol
			SymbolExpression* symbol = new RuntimeSymbolExpression(IDENTIFIER_THIS, mThis->QualifiedTypename(), mMethod->isConstMethod(), true, false);
			symbol->mSymbolExpression = exp;

			return symbol;
		}
	}

	return resolveWithExceptions(token, base);
}

MethodSymbol* TreeGenerator::resolveMethod(SymbolExpression* symbol, const ParameterList& params, Visibility::E visibility) const
{
	if ( !symbol ) {
		throw Common::Exceptions::InvalidSymbol("invalid symbol provided");
	}

	bool onlyCurrentScope = false;

	SymbolExpression* inner = symbol;
	for ( ; ; ) {
		if ( inner->mSymbolExpression && inner->mSymbolExpression->mSurroundingScope ) {
			onlyCurrentScope = true;

			inner = inner->mSymbolExpression;
			continue;
		}

		break;
	}

	MethodScope* scope = getMethodScope(inner->mSurroundingScope);
	if ( !scope ) {
		throw Designtime::Exceptions::DesigntimeException("invalid scope");
	}

	return scope->resolveMethod(inner->mName, params, onlyCurrentScope, visibility);
}

std::string TreeGenerator::resolveType(Node* left, const Token& operation, Node* right) const
{
	Expression* l = dynamic_cast<Expression*>(left);
	if ( !l ) {
		throw Designtime::Exceptions::DesigntimeException("invalid left expression");
	}

	Expression* r = dynamic_cast<Expression*>(right);
	if ( !r ) {
		throw Designtime::Exceptions::DesigntimeException("invalid right expression");
	}

	return resolveType(l->getResultType(), operation, r->getResultType());
}

std::string TreeGenerator::resolveType(const std::string& left, const Token& operation, const std::string& right) const
{
	return mTypeSystem->getType(left, operation, right);
}


}
}
