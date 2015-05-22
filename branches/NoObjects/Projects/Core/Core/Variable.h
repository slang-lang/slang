
#ifndef ObjectiveScript_Variable_h
#define ObjectiveScript_Variable_h


// Library includes
#include <cassert>
#include <list>
#include <string>

// Project includes
#include <Core/Attributes/Attributes.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Variable /*: public Attributes*/
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

public:
	bool operator==(const Variable& other);
	bool operator()();

protected:
	std::string mVarName;
	std::string mVarType;
	std::string mVarValue;

private:

};


}


#endif
