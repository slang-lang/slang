
#ifndef ObjectiveScript_Variable_h
#define ObjectiveScript_Variable_h


// Library includes
#include <cassert>
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Variable
{
public:
	Variable();
	Variable(const std::string& name, const std::string& type);
	Variable(const std::string& name, const std::string& type, const std::string& value);
	virtual ~Variable();

public:
	const std::string& name() const;
	const std::string& type() const;
	const std::string& value() const;

	void value(const std::string& value);

protected:
	std::string mVarName;
	std::string mVarType;
	std::string mVarValue;

private:

};


}


#endif
