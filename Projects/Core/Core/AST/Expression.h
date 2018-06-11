
#ifndef ObjectiveScript_Core_AST_Expression_h
#define ObjectiveScript_Core_AST_Expression_h


// Library includes
#include <list>

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
			SymbolExpression,
			TernaryExpression,
			TypecastExpression,
			TypeidExpression,
			UnaryExpression
		};
	};

public:
	explicit Expression(ExpressionType::E expressionType)
	: Node(NodeType::Expression),
	  mExpressionType(expressionType),
	  mIsAtomicType(false),
	  mIsConst(false),
	  mIsMember(false)
	{ }
	virtual ~Expression() { }

	ExpressionType::E getExpressionType() const {
		return mExpressionType;
	}

	virtual bool isAtomicType() const {
		return mIsAtomicType;
	}
	virtual bool isConst() const {
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
	explicit BinaryExpression(Node* lhs, const Token& operation, Node* rhs, const std::string& resultType)
	: Expression(ExpressionType::BinaryExpression),
	  mLHS(lhs),
	  mOperation(operation),
	  mRHS(rhs),
	  mBinaryExpressionType(BinaryExpressionType::GenericBinaryExpression)
	{
		mResultType = resultType;
	}
	virtual ~BinaryExpression() {
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
	explicit LiteralExpression(Runtime::AtomicValue value)
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
	explicit BooleanLiteralExpression(Runtime::AtomicValue value)
	: LiteralExpression(value)
	{
		mResultType = _bool;
	}
};


class DoubleLiteralExpression : public LiteralExpression
{
public:
	explicit DoubleLiteralExpression(Runtime::AtomicValue value)
	: LiteralExpression(value)
	{
		mResultType = _double;
	}
};


class FloatLiteralExpression : public LiteralExpression
{
public:
	explicit FloatLiteralExpression(Runtime::AtomicValue value)
	: LiteralExpression(value)
	{
		mResultType = _float;
	}
};


class IntegerLiteralExpression : public LiteralExpression
{
public:
	explicit IntegerLiteralExpression(Runtime::AtomicValue value)
	: LiteralExpression(value)
	{
		mResultType = _int;
	}
};


class StringLiteralExpression : public LiteralExpression
{
public:
	explicit StringLiteralExpression(Runtime::AtomicValue value)
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
	explicit CopyExpression(Node* exp)
	: Expression(ExpressionType::CopyExpression),
	  mExpression(exp)
	{
		mResultType = static_cast<Expression*>(exp)->getResultType();
	}
	~CopyExpression() {
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
	~NewExpression() {
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
	explicit IsExpression(Node* expression, const std::string& matchType)
	: Expression(ExpressionType::IsExpression),
	  mExpression(expression),
	  mMatchType(matchType)
	{
		mResultType = _bool;
	}
	~IsExpression() {
		delete mExpression;
	}

public:
	Node* mExpression;
	std::string mMatchType;
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
	virtual ~SymbolExpression() {
		delete mSymbolExpression;
	}

	SymbolExpressionType::E getSymbolExpressionType() const {
		return mSymbolExpressionType;
	}

	bool isAtomicType() const {
		// it's only important to know if the target type is atomic not if any one of the types is
		return mSymbolExpression ? mSymbolExpression->isAtomicType() : mIsAtomicType;
	}

	bool isConst() const {
		// determines if at least one type in the chain is const
		return mIsConst || (mSymbolExpression ? mSymbolExpression->isConst() : false);
	}

	bool isMember() const {
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
	explicit SymbolExpression(const std::string& name, const std::string& resultType, bool isAtomicType)
	: Expression(ExpressionType::SymbolExpression),
	  mName(name),
	  mSurroundingScope(0),
	  mSymbolExpression(0),
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
	explicit DesigntimeSymbolExpression(const std::string& name, const std::string& resultType, const PrototypeConstraints& constraints, bool isAtomicType)
	: SymbolExpression(name, resultType, isAtomicType),
	  mConstraints(constraints)
	{
		mIsConst = false;
		mSymbolExpressionType = SymbolExpressionType::DesigntimeSymbolExpression;
	}

	bool isPrototype() const {
		return !mConstraints.empty();
	}

	std::string getResultType() const {
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

	std::string getResultType() const {
		return mSymbolExpression ? mSymbolExpression->getResultType() : mResultType;
	}
};


class LocalSymbolExpression : public SymbolExpression
{
public:
	explicit LocalSymbolExpression(const std::string& name, const std::string& resultType, bool isConst, bool isAtomicType)
	: SymbolExpression(name, resultType, isAtomicType)
	{
		mIsConst = isConst;
		mIsMember = false;
		mSymbolExpressionType = SymbolExpressionType::RuntimeSymbolExpression;
	}

	std::string getResultType() const {
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
		mResultType = static_cast<Expression*>(first)->getResultType();
		mSecondResultType = static_cast<Expression*>(second)->getResultType();
	}
	~TernaryExpression() {
		if ( mCondition == mFirst ) {
			// short ternary operator
			mCondition = 0;
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
	explicit TypecastExpression(const std::string& destinationType, Node* exp)
	: Expression(ExpressionType::TypecastExpression),
	  mDestinationType(destinationType),
	  mExpression(exp)
	{
		mResultType = mDestinationType;
	}
	~TypecastExpression() {
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
	~TypeidExpression() {
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
	explicit MethodExpression(SymbolExpression* symbol, const ExpressionList& params, const std::string& resultType, bool isConst, bool isMember)
	: Expression(ExpressionType::MethodExpression),
	  mParams(params),
	  mSymbolExpression(symbol)
	{
		mIsConst = isConst || symbol->isConst();
		mIsMember = isMember;
		// due to the possibility of method overloading we cannot use the result type of our symbol expression
		mResultType = resultType;
	}
	~MethodExpression() {
		for ( ExpressionList::iterator it = mParams.begin(); it != mParams.end(); ++it ) {
			delete (*it);
		}
		delete mSymbolExpression;
	}

public:
	ExpressionList mParams;
	SymbolExpression* mSymbolExpression;
};

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
	explicit UnaryExpression(const Token& operation, Node* exp, ValueType::E valueType)
	: Expression(ExpressionType::UnaryExpression),
	  mExpression(exp),
	  mOperation(operation),
	  mValueType(valueType)
	{
		mResultType = static_cast<Expression*>(exp)->getResultType();
	}
	virtual ~UnaryExpression() {
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
