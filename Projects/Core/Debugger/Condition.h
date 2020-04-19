
#ifndef ObjectiveScript_Debugger_Condition_h
#define ObjectiveScript_Debugger_Condition_h


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace Slang {

// Forward declarations
class Symbol;

namespace Core {


class Condition
{
public:
	class Type
	{
	public:
		enum E {
			Invalid,
			Equals,
			Greater,
			GreaterEqual,
			Less,
			LessEqual,
			Unequal
		};
	};

public:
	Condition();
	Condition(const std::string& lhs, Type::E type, const std::string& rhs);
	Condition(const std::string& lhs, const std::string& type, const std::string& rhs);
	~Condition();

public:
	bool evaluate(Symbol* lhs, Symbol* rhs) const;

	bool isValid() const;
	const std::string& lhs() const;
	const std::string& rhs() const;
	std::string toString() const;
	Type::E type() const;

private:
	Type::E ConditionFromString(const std::string& type) const;

private:
	std::string mLeft;
	std::string mRight;
	Type::E mType;
};


}
}


#endif
