
#ifndef ObjectiveScript_Core_AST_Expression_h
#define ObjectiveScript_Core_AST_Expression_h


// Library includes
#include <list>
#include <utility>

// Project includes
#include <Core/Consts.h>
#include <Core/Designtime/Parser/Token.h>
#include <Core/Runtime/AtomicValue.h>
#include <Core/Scope.h>
#include "Node.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace AST {

// Forward declarations
//class Statements;


class Expression : public Node
{
public:
	class ExpressionType {
	public:
		enum E {
			AssignmentExpression,
			BinaryExpression,
			CopyExpression,
			IsExpression,
			LiteralExpression,
			MethodExpression,
			NewExpression,
			ScopeExpression,
			SymbolExpression,
			TernaryExpression,
			TypecastExpression,
			TypeidExpression,
			UnaryExpression
		};

		static std::string ToString(E e) {
			switch ( e ) {
				case AssignmentExpression: return "AssignmentExpression";
				case BinaryExpression: return "BinaryExpression";
				case CopyExpression: return "CopyExpression";
				case IsExpression: return "IsExpression";
				case LiteralExpression: return "LiteralExpression";
				case MethodExpression: return "MethodExpression";
				case NewExpression: return "NewExpression";
				case ScopeExpression: return "ScopeExpression";
				case SymbolExpression: return "SymbolExpression";
				case TernaryExpression: return "TernaryExpression";
				case TypecastExpression: return "TypecastExpression";
				case TypeidExpression: return "TypeidExpression";
				case UnaryExpression: return "UnaryExpression";
			}

			assert( !"unknown expression type" );
			return "unknown expression type";
		}
	};

public:
	explicit Expression(ExpressionType::E expressionType)
	: Node(NodeType::Expression),
	  mExpressionType(expressionType),
	  mIsAtomicType(false),
	  mIsConst(false),
	  mIsMember(false)
	{ }

	ExpressionType::E getExpressionType() const {
		return mExpressionType;
	}

	virtual bool isAtomicType() const {
		return mIsAtomicType;
	}
	virtual bool isConst() const {
		return mIsConst;
	}
	virtual bool isInnerConst() const {
		return mIsConst;
	}
	virtual bool isMember() const {
		return mIsMember;
	}
	virtual std::string getResultType() const {
		return mResultType;
	}

protected:
	ExpressionType::E mExpressionType;
	bool mIsAtomicType;
	bool mIsConst;
	bool mIsMember;
	std::string mResultType;
};

typedef std::list<Node*> ExpressionList;


///////////////////////////////////////////////////////////////////////////////
// Binary expressions

class BinaryExpression : public Expression
{
public:
	class BinaryExpressionType {
	public:
		enum E {
			BooleanBinaryExpression,
			GenericBinaryExpression
		};
	};

public:
	explicit BinaryExpression(Node* lhs, Token  operation, Node* rhs, const std::string& resultType)
	: Expression(ExpressionType::BinaryExpression),
	  mLHS(lhs),
	  mOperation(std::move(operation)),
	  mRHS(rhs),
	  mBinaryExpressionType(BinaryExpressionType::GenericBinaryExpression)
	{
		mResultType = resultType;
	}
	~BinaryExpression() override {
		delete mLHS;
		delete mRHS;
	}

	BinaryExpressionType::E getBinaryExpressionType() const {
		return mBinaryExpressionType;
	}

public:
	Node* mLHS;
	Token mOperation;
	Node* mRHS;

protected:
	BinaryExpressionType::E mBinaryExpressionType;
};


class BooleanBinaryExpression : public BinaryExpression
{
public:
	explicit BooleanBinaryExpression(Node* left, const Token& operation, Node* right)
	: BinaryExpression(left, operation, right, _bool)
	{
		mBinaryExpressionType = BinaryExpressionType::BooleanBinaryExpression;
	}
};

// Binary expressions
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Literal expressions

class LiteralExpression : public Expression
{
public:
	explicit LiteralExpression(const Runtime::AtomicValue& value)
	: Expression(ExpressionType::LiteralExpression),
	  mValue(value)
	{
		mIsAtomicType = true;
	}

public:
	Runtime::AtomicValue mValue;
};


class BooleanLiteralExpression : public LiteralExpression
{
public:
	explicit BooleanLiteralExpression(const Runtime::AtomicValue& value)
	: LiteralExpression(value)
	{
		mResultType = _bool;
	}
};


class DoubleLiteralExpression : public LiteralExpression
{
public:
	explicit DoubleLiteralExpression(const Runtime::AtomicValue& value)
	: LiteralExpression(value)
	{
		mResultType = _double;
	}
};


class FloatLiteralExpression : public LiteralExpression
{
public:
	explicit FloatLiteralExpression(const Runtime::AtomicValue& value)
	: LiteralExpression(value)
	{
		mResultType = _float;
	}
};


class IntegerLiteralExpression : public LiteralExpression
{
public:
	explicit IntegerLiteralExpression(const Runtime::AtomicValue& value)
	: LiteralExpression(value)
	{
		mResultType = _int;
	}
};


class StringLiteralExpression : public LiteralExpression
{
public:
	explicit StringLiteralExpression(const Runtime::AtomicValue& value)
	: LiteralExpression(value)
	{
		mResultType = _string;
	}
};

// Literal expressions
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Memory expressions

class CopyExpression : public Expression
{
public:
	explicit CopyExpression(const std::string& type, Node* exp)
	: Expression(ExpressionType::CopyExpression),
	  mExpression(exp)
	{
		mResultType = type;
	}
	~CopyExpression() override {
		delete mExpression;
	}

public:
	Node* mExpression;
};


class NewExpression : public Expression
{
public:
	explicit NewExpression(const std::string& type, Node* exp)
	: Expression(ExpressionType::NewExpression),
	  mExpression(exp)
	{
		mResultType = type;
	}
	~NewExpression() override {
		delete mExpression;
	}

public:
	Node* mExpression;
};

// Memory expressions
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Symbol expressions

class IsExpression : public Expression
{
public:
	explicit IsExpression(Node* expression, std::string matchType)
	: Expression(ExpressionType::IsExpression),
	  mExpression(expression),
	  mMatchType(std::move(matchType))
	{
		mResultType = _bool;
	}
	~IsExpression() override {
		delete mExpression;
	}

public:
	Node* mExpression;
	std::string mMatchType;
};


class ScopeExpression : public Expression
{
public:
	ScopeExpression(Expression* lhs, Expression* rhs, const std::string& resultType)
	: Expression(ExpressionType::ScopeExpression),
	  mLHS(lhs),
	  mRHS(rhs)
	{
		mResultType = resultType;
	}
	~ScopeExpression() override {
		delete mLHS;
		delete mRHS;
	}

public:
	Expression* mLHS;
	Expression* mRHS;
};


class SymbolExpression : public Expression
{
public:
	class SymbolExpressionType {
	public:
		enum E {
			DesigntimeSymbolExpression,
			RuntimeSymbolExpression
		};
	};

public:
	~SymbolExpression() override {
		delete mSymbolExpression;
	}

	SymbolExpressionType::E getSymbolExpressionType() const {
		return mSymbolExpressionType;
	}

	std::string innerName() const {
		// returns the name of the inner type in the chain
		return mSymbolExpression ? mSymbolExpression->innerName() : mName;
	}

	bool isAtomicType() const override {
		// it's only important to know if the target type is atomic not if any one of the types is
		return mSymbolExpression ? mSymbolExpression->isAtomicType() : mIsAtomicType;
	}

	bool isConst() const override {
		// determines if at least one type in the chain is const
		return mIsConst || (mSymbolExpression ? mSymbolExpression->isConst() : false);
	}

	bool isInnerConst() const override {
		// determines if the inner type in the chain is const
		return mSymbolExpression ? mSymbolExpression->isInnerConst() : mIsConst;
	}

	bool isMember() const override {
		// determines if at least one type in the chain is a member
		return mIsMember || (mSymbolExpression ? mSymbolExpression->isMember() : false);
	}

	std::string toString() const {
		std::string result = mName;

		if ( mSymbolExpression ) {
			result += "." + mSymbolExpression->toString();
		}

		return result;
	}

public:
	std::string mName;
	IScope* mSurroundingScope;
	SymbolExpression* mSymbolExpression;

protected:
	explicit SymbolExpression(std::string name, const std::string& resultType, bool isAtomicType)
	: Expression(ExpressionType::SymbolExpression),
	  mName(std::move(name)),
	  mSurroundingScope(nullptr),
	  mSymbolExpression(nullptr),
	  mSymbolExpressionType(SymbolExpressionType::DesigntimeSymbolExpression)
	{
		mIsAtomicType = isAtomicType;
		mResultType = resultType;
	}

protected:
	SymbolExpressionType::E mSymbolExpressionType;
};


class DesigntimeSymbolExpression : public SymbolExpression
{
public:
	explicit DesigntimeSymbolExpression(const std::string& name, const std::string& resultType, PrototypeConstraints constraints, bool isAtomicType)
	: SymbolExpression(name, resultType, isAtomicType),
	  mConstraints(std::move(constraints))
	{
		mIsConst = false;
		mSymbolExpressionType = SymbolExpressionType::DesigntimeSymbolExpression;
	}

	explicit DesigntimeSymbolExpression(const std::string& name, const std::string& resultType, PrototypeConstraints constraints, bool isConst, bool isMember, bool isAtomicType)
	: SymbolExpression(name, resultType, isAtomicType),
	  mConstraints(std::move(constraints))
	{
		mIsConst = isConst;
		mIsMember = isMember;
		mSymbolExpressionType = SymbolExpressionType::DesigntimeSymbolExpression;
	}

	bool isPrototype() const {
		return !mConstraints.empty();
	}

	std::string getResultType() const override {
		return mSymbolExpression ? mSymbolExpression->getResultType() : mResultType;
	}

public:
	PrototypeConstraints mConstraints;
};


class RuntimeSymbolExpression : public SymbolExpression
{
public:
	explicit RuntimeSymbolExpression(const std::string& name, const std::string& resultType, bool isConst, bool isMember, bool isAtomicType)
	: SymbolExpression(name, resultType, isAtomicType)
	{
		mIsConst = isConst;
		mIsMember = isMember;
		mSymbolExpressionType = SymbolExpressionType::RuntimeSymbolExpression;
	}

	std::string getResultType() const override {
		return mSymbolExpression ? mSymbolExpression->getResultType() : mResultType;
	}
};


class LocalSymbolExpression : public SymbolExpression
{
public:
	explicit LocalSymbolExpression(const std::string& name, const std::string& resultType, bool isConst, bool isAtomicType)
	: SymbolExpression(name, resultType, isAtomicType),
	  mIndex( -1 )
	{
		mIsConst = isConst;
		mIsMember = false;
		mSymbolExpressionType = SymbolExpressionType::RuntimeSymbolExpression;
	}

	std::string getResultType() const override {
		return mSymbolExpression ? mSymbolExpression->getResultType() : mResultType;
	}

	unsigned int getIndex() const {
		return mIndex;
	}

private:
	unsigned int mIndex;
};

// Variable expressions
///////////////////////////////////////////////////////////////////////////////


class AssignmentExpression : public Expression
{
public:
	AssignmentExpression(SymbolExpression* lhs, Node* rhs, const std::string& resultType)
	: Expression(ExpressionType::AssignmentExpression),
	  mLHS(lhs),
	  mRHS(rhs)
	{
		mIsAtomicType = lhs->isAtomicType();
		mIsConst = lhs->isConst();
		mIsMember = lhs->isMember();
		mResultType = resultType;
	}
	~AssignmentExpression() override {
		delete mLHS;
		delete mRHS;
	}

public:
	SymbolExpression* mLHS;
	Node* mRHS;
};


class TernaryExpression : public Expression
{
public:
	explicit TernaryExpression(Node* condition, Node* first, Node* second)
	: Expression(ExpressionType::TernaryExpression),
	  mCondition(condition),
	  mFirst(first),
	  mSecond(second)
	{
		mResultType = dynamic_cast<Expression*>(first)->getResultType();
		mSecondResultType = dynamic_cast<Expression*>(second)->getResultType();
	}
	~TernaryExpression() override {
		if ( mCondition == mFirst ) {
			// short ternary operator
			mCondition = nullptr;
		}
		else {
			delete mCondition;
		}
		delete mFirst;
		delete mSecond;
	}

	std::string getSecondResultType() const {
		return mSecondResultType;
	}

public:
	Node* mCondition;
	Node* mFirst;
	Node* mSecond;

private:
	std::string mSecondResultType;
};


class TypecastExpression : public Expression
{
public:
	explicit TypecastExpression(std::string  destinationType, Node* exp)
	: Expression(ExpressionType::TypecastExpression),
	  mDestinationType(std::move(destinationType)),
	  mExpression(exp)
	{
		mResultType = mDestinationType;
	}
	~TypecastExpression() override {
		delete mExpression;
	}

public:
	std::string mDestinationType;
	Node* mExpression;
};


class TypeidExpression : public Expression
{
public:
	explicit TypeidExpression(Node* expression)
	: Expression(ExpressionType::TypeidExpression),
	  mExpression(expression)
	{
		mResultType = _string;
	}
	~TypeidExpression() override {
		delete mExpression;
	}

public:
	Node* mExpression;
};


///////////////////////////////////////////////////////////////////////////////
// Method expressions

class MethodExpression : public Expression
{
public:
	explicit MethodExpression(SymbolExpression* symbol, ExpressionList params, const std::string& resultType, bool isConst, bool isMember)
	: Expression(ExpressionType::MethodExpression),
	  mParams(std::move(params)),
	  mSymbolExpression(symbol)
	{
		mIsConst = isConst || symbol->isInnerConst();
		mIsMember = isMember;
		// due to the possibility of method overloading we cannot use the result type of our symbol expression
		mResultType = resultType;
	}
	~MethodExpression() override {
		for ( auto& mParam : mParams ) {
			delete mParam;
		}
		delete mSymbolExpression;
	}

public:
	ExpressionList mParams;
	SymbolExpression* mSymbolExpression;
};


/*
class LambdaExpression : public MethodExpression
{
public:
	explicit LambdaExpression(const ExpressionList& params, const std::string& resultType, bool isConst, Statements* statements)
	: MethodExpression(NULL, params, resultType, isConst, false),
	  mStatements(statements)
	{ }
	virtual ~LambdaExpression();

public:
	Statements* mStatements;
};
*/

// Method expressions
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Unary expressions

class UnaryExpression : public Expression
{
public:
	class ValueType {
	public:
		enum E {
			LValue,
			RValue
		};
	};

public:
	explicit UnaryExpression(Token  operation, Node* exp, ValueType::E valueType)
	: Expression(ExpressionType::UnaryExpression),
	  mExpression(exp),
	  mOperation(std::move(operation)),
	  mValueType(valueType)
	{
		mResultType = dynamic_cast<Expression*>(exp)->getResultType();
	}
	~UnaryExpression() override {
		delete mExpression;
	}

public:
	Node* mExpression;
	Token mOperation;
	ValueType::E mValueType;
};


class BooleanUnaryExpression : public UnaryExpression
{
public:
	explicit BooleanUnaryExpression(const Token& operation, Node* exp, ValueType::E valueType)
	: UnaryExpression(operation, exp, valueType)
	{
		mResultType = _bool;
	}
};

// Unary expressions
///////////////////////////////////////////////////////////////////////////////


}
}

#endif
